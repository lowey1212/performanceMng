#include "DAI_PerfMngrComponent.h"
#include "AIController.h"
#include "AbilitySystemComponent.h"
#include "Animation/AnimInstance.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Components/AudioComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Components/LightComponent.h"
#include "Components/MeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "DAI_ProxyHISMManager.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GroomComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Net/UnrealNetwork.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "ProxyHISMRootActor.h"
#include "SignificanceManager.h"
#include "TimerManager.h"

// Significance Helper (needs to be above UDAI_PerfMngrComponent::BeginPlay)
static float
CalculateHybridSignificance(USignificanceManager::FManagedObjectInfo *Info,
                            const FTransform &ViewTransform,
                            float MaxDistance) {
  AActor *TrackedActor = Cast<AActor>(Info->GetObject());
  if (!TrackedActor)
    return 0.0f;

  if (USkeletalMeshComponent *SkeletalMesh =
          TrackedActor->FindComponentByClass<USkeletalMeshComponent>()) {
    if (UAnimInstance *AnimInstance = SkeletalMesh->GetAnimInstance()) {
      int32 LODLevel = AnimInstance->GetLODLevel();
      int32 MaxLODs = 4;
      return 1.0f -
             static_cast<float>(LODLevel) / static_cast<float>(MaxLODs - 1);
    }
  }

  if (UStaticMeshComponent *StaticMesh =
          TrackedActor->FindComponentByClass<UStaticMeshComponent>()) {
    const FVector ObjectLocation = TrackedActor->GetActorLocation();
    const FVector ViewLocation = ViewTransform.GetLocation();
    float Distance = FVector::Dist(ObjectLocation, ViewLocation);
    return 1.0f - FMath::Clamp(Distance / MaxDistance, 0.0f, 1.0f);
  }
  if (UNiagaraComponent *NiagaraComp =
          TrackedActor->FindComponentByClass<UNiagaraComponent>()) {
    const FVector ObjectLocation = TrackedActor->GetActorLocation();
    const FVector ViewLocation = ViewTransform.GetLocation();
    float Distance = FVector::Dist(ObjectLocation, ViewLocation);
    return 1.0f - FMath::Clamp(Distance / MaxDistance, 0.0f, 1.0f);
  }
  return 0.0f;
}

// UDAI_PerfMngrComponent Implementation

// Constructor: set defaults for ticking and proxy options.
UDAI_PerfMngrComponent::UDAI_PerfMngrComponent() {
  PrimaryComponentTick.bCanEverTick = true;
  ProxyBatchAddSize = 50;
  bHasHISMInstance = false;
}

// Called when the game starts.
// Registers with the significance system, caches materials for
// color-by-significance, and starts a timer to periodically adjust ticking and
// proxies based on importance.
void UDAI_PerfMngrComponent::BeginPlay() {
  Super::BeginPlay();

  AActor *Owner = GetOwner();
  if (!Owner)
    return;

  if (bAffectAbilitySystemTick) {
    CachedASC = Cast<UAbilitySystemComponent>(
        Owner->GetComponentByClass(UAbilitySystemComponent::StaticClass()));
  }

  if (bColorizeBySignificance) {
    TArray<UMeshComponent *> Meshes;
    Owner->GetComponents<UMeshComponent>(Meshes);

    for (UMeshComponent *Mesh : Meshes) {
      if (!Mesh || !Mesh->IsRegistered())
        continue;

      TArray<UMaterialInstanceDynamic *> DynMats;
      int32 MatCount = Mesh->GetNumMaterials();

      for (int32 i = 0; i < MatCount; ++i) {
        if (UMaterialInstanceDynamic *DynMat =
                Mesh->CreateAndSetMaterialInstanceDynamic(i)) {
          DynMats.Add(DynMat);
        }
      }
      CachedDynamicMats.Add(Mesh, DynMats);
    }
  }

  if (USignificanceManager *Manager = USignificanceManager::Get(GetWorld())) {
    const float LocalMaxDistance = MaxDistance;

    Manager->RegisterObject(
        Owner, Category,
        [LocalMaxDistance](USignificanceManager::FManagedObjectInfo *Info,
                           const FTransform &ViewTransform) {
          return CalculateHybridSignificance(Info, ViewTransform,
                                             LocalMaxDistance);
        },
        USignificanceManager::EPostSignificanceType::None, nullptr);

    GetWorld()->GetTimerManager().SetTimer(
        TickEvalTimerHandle, this,
        &UDAI_PerfMngrComponent::UpdateTickBasedOnSignificance,
        TickEvaluationRate, true);
  }
}

// Called when the component stops.
// Cleans up timers and removes any HISM proxy instance that was added.
void UDAI_PerfMngrComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) {
  if (UWorld *World = GetWorld()) {
    World->GetTimerManager().ClearTimer(TickEvalTimerHandle);
  }
  if (bHasHISMInstance && ProxyStaticMesh) {
    UWorld *World = GetWorld();
    if (World) {
      if (UDAI_ProxyHISMManager *ProxyMgr =
              World->GetSubsystem<UDAI_ProxyHISMManager>()) {
        ProxyMgr->RemoveInstanceAtTransform(ProxyHISMTag, ProxyHISMTransform);
      }
    }
    bHasHISMInstance = false;
  }
  Super::EndPlay(EndPlayReason);
}

// Final cleanup to remove any HISM instance if needed.
void UDAI_PerfMngrComponent::OnComponentDestroyed(bool bDestroyingHierarchy) {
  if (bHasHISMInstance && ProxyStaticMesh) {
    UWorld *World = GetWorld();
    if (World) {
      if (UDAI_ProxyHISMManager *ProxyMgr =
              World->GetSubsystem<UDAI_ProxyHISMManager>()) {
        ProxyMgr->RemoveInstanceAtTransform(ProxyHISMTag, ProxyHISMTransform);
      }
    }
    bHasHISMInstance = false;
  }
  Super::OnComponentDestroyed(bDestroyingHierarchy);
}

// Switch to a lightweight visual for this actor (proxy).
// Hide complex components (meshes, hair, widgets), and either spawn a simple
// mesh or batch into a HISM. Optionally spawn a simple hair proxy.
// Billboard/particles are handled separately.
void UDAI_PerfMngrComponent::SwapToProxy() {
  AActor *Owner = GetOwner();
  if (!Owner) {
    UE_LOG(LogTemp, Error, TEXT("[PerfMngr] SwapToProxy: Owner is null!"));
    return;
  }

  if (!ProxyStaticMesh) {
    UE_LOG(LogTemp, Error,
           TEXT("[PerfMngr] SwapToProxy: ProxyStaticMesh is null!"));
    return;
  }

  // If we previously swapped to a billboard via HISM, remove that instance
  // before using the regular proxy.
  if (bHasHISMInstance && ProxyBillboardMesh) {
    UWorld *World = GetWorld();
    if (World) {
      if (UDAI_ProxyHISMManager *ProxyMgr =
              World->GetSubsystem<UDAI_ProxyHISMManager>()) {
        ProxyMgr->RemoveInstanceAtTransform(ProxyHISMTag, ProxyHISMTransform);
      }
    }
    bHasHISMInstance = false;
  }

  // Hide original mesh components while a proxy is shown.
  TArray<UMeshComponent *> Meshes;
  Owner->GetComponents<UMeshComponent>(Meshes);
  for (UMeshComponent *Mesh : Meshes) {
    Mesh->SetVisibility(false, true);
    Mesh->SetComponentTickEnabled(false);
  }

  // Hide hair components while a proxy is shown.
  TArray<UGroomComponent *> GroomComps;
  Owner->GetComponents<UGroomComponent>(GroomComps);
  for (UGroomComponent *Groom : GroomComps) {
    Groom->SetVisibility(false);
    Groom->Deactivate();
  }

  // Add this actor’s transform into a pooled HISM for its proxy mesh.
  if (ProxyStaticMesh && Owner) {
    UWorld *World = GetWorld();
    if (World) {
      if (UDAI_ProxyHISMManager *ProxyMgr =
              World->GetSubsystem<UDAI_ProxyHISMManager>()) {
        // Use only the mesh name for the tag so actors sharing the same
        // proxy mesh batch into a single HISM component.
        FName ProxyTag = FName(
            *FString::Printf(TEXT("Proxy_%s"), *ProxyStaticMesh->GetName()));
        UE_LOG(LogTemp, Warning, TEXT("SwapToProxy: Owner: %s Mesh: %s"),
               *Owner->GetName(), *ProxyStaticMesh->GetName());
        UHierarchicalInstancedStaticMeshComponent *HISM =
            ProxyMgr->GetOrCreateHISMForTag(ProxyTag, ProxyStaticMesh, Owner);
        if (!HISM) {
          UE_LOG(LogTemp, Error,
                 TEXT("SwapToProxy: Failed to create HISM for %s"),
                 *ProxyStaticMesh->GetName());
        } else {

          ProxyMgr->SetBatchSizeForTag(ProxyTag, ProxyBatchAddSize);
          ProxyMgr->QueueInstanceForBatch(ProxyTag, Owner->GetActorTransform());
          ProxyHISMTransform = Owner->GetActorTransform();
          ProxyHISMTag = ProxyTag;
          bHasHISMInstance = true;
        }
      } else {
        UE_LOG(LogTemp, Error, TEXT("SwapToProxy: ProxyMgr is null!"));
      }
    }
  }

  // Optional: spawn a simple hair proxy mesh (not batched).
  if (ProxyHairMesh) {
    ProxyHairMeshComponent = NewObject<UStaticMeshComponent>(Owner);
    ProxyHairMeshComponent->RegisterComponent();
    ProxyHairMeshComponent->AttachToComponent(
        Owner->GetRootComponent(),
        FAttachmentTransformRules::KeepRelativeTransform);
    ProxyHairMeshComponent->SetStaticMesh(ProxyHairMesh);
    ProxyHairMeshComponent->SetVisibility(true);
    // Apply an optional tag so designers can identify hair proxy meshes via
    // component tags
    if (!HairProxyTag.IsNone()) {
      ProxyHairMeshComponent->ComponentTags.Add(HairProxyTag);
    }
  }

  // Billboard and particle proxies are handled elsewhere.

  // Hide UI widget components while using a proxy.
  TArray<UWidgetComponent *> WidgetComps;
  Owner->GetComponents<UWidgetComponent>(WidgetComps);
  for (UWidgetComponent *Widget : WidgetComps) {
    Widget->SetVisibility(false);
    Widget->SetComponentTickEnabled(false);
  }
  EnsureSingleRepresentation();
}

// Return from proxy back to the full, original actor visuals.
// Remove any proxy components/HISM instance and show everything again.
void UDAI_PerfMngrComponent::SwapToFull() {
  AActor *Owner = GetOwner();
  if (!Owner)
    return;

  // If we used a batched HISM proxy, remove its instance.
  if (bHasHISMInstance && ProxyStaticMesh) {
    UWorld *World = GetWorld();
    if (World) {
      if (UDAI_ProxyHISMManager *ProxyMgr =
              World->GetSubsystem<UDAI_ProxyHISMManager>()) {
        ProxyMgr->RemoveInstanceAtTransform(ProxyHISMTag, ProxyHISMTransform);
      }
    }
    bHasHISMInstance = false;
  }

  // Clean up any spawned proxy components.
  if (ProxyMeshComponent) {
    ProxyMeshComponent->DestroyComponent();
    ProxyMeshComponent = nullptr;
  }
  if (ProxyHairMeshComponent) {
    ProxyHairMeshComponent->DestroyComponent();
    ProxyHairMeshComponent = nullptr;
  }
  if (BillboardMeshComponent) {
    BillboardMeshComponent->DestroyComponent();
    BillboardMeshComponent = nullptr;
  }
  // Reset billboard fade state and clear any temporary materials.
  bBillboardFadeActive = false;
  ProxyFadeMaterials.Empty();
  BillboardFadeMaterials.Empty();
  if (ProxyEffectComponent) {
    ProxyEffectComponent->DestroyComponent();
    ProxyEffectComponent = nullptr;
  }

  // Show original meshes again and resume their ticking.
  TArray<UMeshComponent *> Meshes;
  Owner->GetComponents<UMeshComponent>(Meshes);
  for (UMeshComponent *Mesh : Meshes) {
    Mesh->SetVisibility(true, true);
    Mesh->SetComponentTickEnabled(true);
  }

  // Show hair components again.
  TArray<UGroomComponent *> GroomComps;
  Owner->GetComponents<UGroomComponent>(GroomComps);
  for (UGroomComponent *Groom : GroomComps) {
    Groom->SetVisibility(true);
    Groom->Activate();
  }

  // Show UI widget components again.
  TArray<UWidgetComponent *> WidgetComps;
  Owner->GetComponents<UWidgetComponent>(WidgetComps);
  for (UWidgetComponent *Widget : WidgetComps) {
    Widget->SetVisibility(true);
    Widget->SetComponentTickEnabled(true);
  }
  EnsureSingleRepresentation();
}

// State machine that decides when to enter/exit proxy mode based on
// "significance" (how important/near it is). Uses thresholds and delays to
// avoid rapid flickering between states.
void UDAI_PerfMngrComponent::HandleProxySwap(float DeltaTime,
                                             float Significance) {
  if (!ProxyStaticMesh) {
    ProxyState = EProxySwapState::Active;
    return;
  }

  ProxyTimeInCurrentState += DeltaTime;

  switch (ProxyState) {
  case EProxySwapState::Active:
    if (Significance < ProxyEnterThreshold) {
      ProxyState = EProxySwapState::PendingSwapToProxy;
      ProxyTimeInCurrentState = 0.0f;
    }
    break;

  case EProxySwapState::PendingSwapToProxy:
    if (Significance < ProxyEnterThreshold &&
        ProxyTimeInCurrentState >= ProxySwapDelay) {
      SwapToProxy();
      ProxyState = EProxySwapState::ProxyActive;
      ProxyTimeInCurrentState = 0.0f;
      OnProxyEntered.Broadcast();
    } else if (Significance >= ProxyEnterThreshold) {
      ProxyState = EProxySwapState::Active;
    }
    break;

  case EProxySwapState::ProxyActive:
    if (Significance > ProxyExitThreshold) {
      ProxyState = EProxySwapState::PendingSwapToFull;
      ProxyTimeInCurrentState = 0.0f;
    }
    break;

  case EProxySwapState::PendingSwapToFull:
    if (Significance > ProxyExitThreshold &&
        ProxyTimeInCurrentState >= ProxySwapDelay) {
      SwapToFull();
      ProxyState = EProxySwapState::Active;
      ProxyTimeInCurrentState = 0.0f;
      OnProxyExited.Broadcast();
    } else if (Significance <= ProxyExitThreshold) {
      ProxyState = EProxySwapState::ProxyActive;
    }
    break;
  }
  EnsureSingleRepresentation();
}

// If enabled, tint dynamic materials from red (low importance) to green (high
// importance).
void UDAI_PerfMngrComponent::ApplyColorBySignificance(float Significance) {
  for (auto &Entry : CachedDynamicMats) {
    for (UMaterialInstanceDynamic *Mat : Entry.Value) {
      if (Mat) {
        FLinearColor Color = FLinearColor::LerpUsingHSV(
            FLinearColor::Red, FLinearColor::Green, Significance);
        Mat->SetVectorParameterValue("Color", Color);
      }
    }
  }
}

// Run at a fixed interval.
// Computes how important the actor is (distance to camera),
// adjusts tick rates, manages AI pausing, and drives proxy/billboard/particle
// swaps.
void UDAI_PerfMngrComponent::UpdateTickBasedOnSignificance() {
  AActor *Owner = GetOwner();
  if (!Owner)
    return;

  FVector ViewLocation = GEngine->GetFirstLocalPlayerController(GetWorld())
                             ->PlayerCameraManager->GetCameraLocation();
  float Significance =
      1.0f -
      FMath::Clamp(FVector::Dist(Owner->GetActorLocation(), ViewLocation) /
                       MaxDistance,
                   0.0f, 1.0f);

  if (bEnableDebugLog) {
    UE_LOG(LogTemp, Log, TEXT("[PerfMngr] Significance: %.2f"), Significance);
  }
  if (bPrintSignificanceToScreen) {
    GEngine->AddOnScreenDebugMessage(
        -1, 1.1f, FColor::Yellow,
        FString::Printf(TEXT("Significance: %.2f"), Significance));
  }

  if (bColorizeBySignificance) {
    ApplyColorBySignificance(Significance);
  }

  if (ProxyStaticMesh) {
    HandleProxySwap(GetWorld()->GetDeltaSeconds(), Significance);

    // Re-check after full: force proxy if still under threshold
    if (ProxyState == EProxySwapState::Active &&
        Significance < ProxyEnterThreshold) {
      UE_LOG(LogTemp, Warning,
             TEXT("[PerfMngr] Forcing proxy re-entry after full, sig=%.2f"),
             Significance);
      ProxyState = EProxySwapState::PendingSwapToProxy;
      ProxyTimeInCurrentState = 0.0f;
    }

    if (ProxyBillboardMesh) {
      HandleBillboardProxySwap(GetWorld()->GetDeltaSeconds(), Significance);
    }
  }

  if (ProxyParticleEffect) {
    HandleParticleProxySwap(GetWorld()->GetDeltaSeconds(), Significance);
  }

  if (bAllowAIThrottling) {
    ACharacter *CharacterOwner = Cast<ACharacter>(Owner);
    if (CharacterOwner) {
      AAIController *AIController =
          Cast<AAIController>(CharacterOwner->GetController());
      if (AIController) {
        UBehaviorTreeComponent *BT =
            AIController->FindComponentByClass<UBehaviorTreeComponent>();
        if (BT) {
          if (Significance < AIDeepFreezeSignificance && !BT->IsPaused()) {
            // Pause AI logic when significance is below the deep freeze
            // threshold.  Do not stop movement so that any in‑progress path
            // following will continue updating the actor's location while the
            // behavior tree remains paused.
            BT->PauseLogic(FString("PerfMngr Deep Freeze"));
          } else if (Significance >= AIDeepFreezeSignificance &&
                     BT->IsPaused()) {
            // Resume AI logic when the significance rises back above the
            // threshold.
            BT->ResumeLogic(FString("PerfMngr Resume"));
          }
        }
      }
    }
  }

  if (bDrawDebugProxySphere && IsUsingProxy()) {
    DrawDebugSphere(GetWorld(), GetOwner()->GetActorLocation(), 100.f, 16,
                    FColor::Magenta, false, ProxyDebugSphereDuration);
  }
  float QualityMultiplier = 1.0f;
  if (PerformanceQuality == EPerformanceQuality::Medium) {
    QualityMultiplier = 1.25f;
  } else if (PerformanceQuality == EPerformanceQuality::Low) {
    QualityMultiplier = 1.5f;
  }

  float TickRate = FMath::Clamp(
      FMath::Lerp(TickIntervalHigh, TickIntervalLow, 1.0f - Significance) *
          QualityMultiplier,
      MinTickClamp, MaxTickClamp);

  Owner->SetActorTickInterval(TickRate);

  if (bAffectAbilitySystemTick && CachedASC) {
    CachedASC->SetComponentTickInterval(TickRate);
  }

  if (ComponentSuppressionRules.Num() > 0) {
    TArray<UActorComponent *> AllComponents;
    Owner->GetComponents(AllComponents);

    for (UActorComponent *Comp : AllComponents) {
      if (!Comp || !Comp->IsRegistered())
        continue;

      FComponentSuppressionRule *MatchedRule = nullptr;
      for (FComponentSuppressionRule &Rule : ComponentSuppressionRules) {
        bool TagMatch = !Rule.ComponentTagFilter.IsNone() &&
                        Comp->ComponentHasTag(Rule.ComponentTagFilter);
        bool NameMatch = !Rule.NameContains.IsEmpty() &&
                         Comp->GetName().Contains(Rule.NameContains);

        bool bMatches = false;
        switch (Rule.ComponentType) {
        case ESuppressionComponentType::Audio:
          bMatches = Comp->IsA<UAudioComponent>();
          break;
        case ESuppressionComponentType::Niagara:
          bMatches = Comp->IsA<UNiagaraComponent>();
          break;
        case ESuppressionComponentType::AbilitySystem:
          bMatches = Comp->IsA<UAbilitySystemComponent>();
          break;
        case ESuppressionComponentType::Light:
          bMatches = Comp->IsA<ULightComponent>();
          break;
        case ESuppressionComponentType::Widget:
          bMatches =
              Comp->IsA<UWidgetComponent>() &&
              (TagMatch || NameMatch || Rule.ComponentTagFilter.IsNone());
          break;
        case ESuppressionComponentType::MotionWarping:
          bMatches = NameMatch || TagMatch ||
                     Comp->GetName().Contains(TEXT("MotionWarp"));
          break;
        case ESuppressionComponentType::Hair:
          bMatches = Comp->IsA<UGroomComponent>() || NameMatch || TagMatch ||
                     Comp->GetName().Contains(TEXT("Groom")) ||
                     Comp->GetName().Contains(TEXT("Hair"));
          break;
        case ESuppressionComponentType::Physics:
          if (UMeshComponent *Mesh = Cast<UMeshComponent>(Comp)) {
            (void)Mesh->SetSimulatePhysics(false);
          }
          bMatches = true;
          break;
        case ESuppressionComponentType::CustomTag:
          bMatches = TagMatch;
          break;
        default:
          break;
        }

        if (bMatches) {
          MatchedRule = &Rule;
          break;
        }
      }

      if (!MatchedRule)
        continue;

      bool bShouldSuppress = Significance < MatchedRule->SuppressionThreshold;

      if (bShouldSuppress) {
        if (MatchedRule->ComponentTickInterval > 0.0f) {
          // When suppressed but still ticking, dynamically blend between the
          // suppressed tick interval and the "low" interval as significance
          // approaches the suppression threshold.
          const float Range = MatchedRule->SuppressionThreshold;
          const float Normalized = Range > KINDA_SMALL_NUMBER
                                       ? FMath::Clamp(Significance / Range, 0.0f,
                                                      1.0f)
                                       : 1.0f;
          float SuppTick = FMath::Lerp(MatchedRule->ComponentTickInterval,
                                       MatchedRule->ComponentTickIntervalLow,
                                       Normalized);
          SuppTick =
              FMath::Clamp(SuppTick * QualityMultiplier, MinTickClamp, MaxTickClamp);
          Comp->SetComponentTickInterval(SuppTick);
          Comp->SetComponentTickEnabled(true);
          SuppressedComponents.Add(Comp, *MatchedRule);
        } else if (!SuppressedComponents.Contains(Comp)) {
          Comp->SetComponentTickEnabled(false);

          if (UAudioComponent *Audio = Cast<UAudioComponent>(Comp)) {
            Audio->Stop();
            Audio->SetActive(false);
          } else if (ULightComponent *Light = Cast<ULightComponent>(Comp)) {
            Light->SetVisibility(false);
            Light->SetActive(false);
          } else if (UNiagaraComponent *Niagara =
                         Cast<UNiagaraComponent>(Comp)) {
            Niagara->DeactivateImmediate();
            Niagara->SetVisibility(false);
          } else if (UWidgetComponent *Widget =
                         Cast<UWidgetComponent>(Comp)) {
            Widget->SetVisibility(false);
            Widget->SetComponentTickEnabled(false);
          } else if (UGroomComponent *Hair = Cast<UGroomComponent>(Comp)) {
            Hair->SetVisibility(false);
            Hair->Deactivate();
          } else if (UMeshComponent *Mesh = Cast<UMeshComponent>(Comp)) {
            Mesh->SetSimulatePhysics(false);
          } else {
            Comp->Deactivate();
          }
          SuppressedComponents.Add(Comp, *MatchedRule);
        } else {
          // Already suppressed and disabled; nothing else to do.
        }
      } else {
        if (SuppressedComponents.Contains(Comp)) {
          const FComponentSuppressionRule &PrevRule =
              SuppressedComponents[Comp];
          if (PrevRule.ComponentTickInterval <= 0.0f) {
            if (ULightComponent *Light = Cast<ULightComponent>(Comp)) {
              Light->SetVisibility(true);
              Light->SetComponentTickEnabled(true);
              Light->SetActive(true);
            } else if (UAudioComponent *Audio = Cast<UAudioComponent>(Comp)) {
              Audio->SetComponentTickEnabled(true);
              Audio->SetActive(true);
              Audio->Play();
            } else if (UNiagaraComponent *Niagara =
                           Cast<UNiagaraComponent>(Comp)) {
              Niagara->SetComponentTickEnabled(true);
              Niagara->SetVisibility(true);
              Niagara->Activate();
            } else if (UWidgetComponent *Widget =
                           Cast<UWidgetComponent>(Comp)) {
              Widget->SetVisibility(true);
              Widget->SetComponentTickEnabled(true);
            } else if (UGroomComponent *Hair = Cast<UGroomComponent>(Comp)) {
              Hair->SetVisibility(true);
              Hair->Activate();
            } else if (UMeshComponent *Mesh = Cast<UMeshComponent>(Comp)) {
              Mesh->SetSimulatePhysics(true);
              Mesh->SetComponentTickEnabled(true);
            } else {
              Comp->SetComponentTickEnabled(true);
              Comp->Activate(true);
            }
          }
          SuppressedComponents.Remove(Comp);
        }

        if (MatchedRule->ComponentTickIntervalHigh > 0.0f ||
            MatchedRule->ComponentTickIntervalLow > 0.0f) {
          // Map the current significance into the 0-1 range relative to the
          // suppression threshold so that components just above the threshold
          // tick slowly and ramp up as they become more significant.
          const float Range = 1.0f - MatchedRule->SuppressionThreshold;
          const float Normalized = Range > KINDA_SMALL_NUMBER
                                       ? FMath::Clamp(
                                             (Significance -
                                              MatchedRule->SuppressionThreshold) /
                                                 Range,
                                             0.0f, 1.0f)
                                       : 1.0f;

          float ActiveTick = FMath::Lerp(MatchedRule->ComponentTickIntervalLow,
                                         MatchedRule->ComponentTickIntervalHigh,
                                         Normalized);
          ActiveTick = FMath::Clamp(ActiveTick * QualityMultiplier,
                                    MinTickClamp, MaxTickClamp);
          Comp->SetComponentTickInterval(ActiveTick);
          Comp->SetComponentTickEnabled(true);
        }
      }
    }
  }

  if (bAffectAbilitySystemTick && CachedASC) {
    CachedASC->SetComponentTickInterval(TickRate);
  }
}

// Let designers change how often we re-evaluate significance and update
// tick/proxy decisions.
void UDAI_PerfMngrComponent::SetTickEvaluationRate(float NewRate) {
  TickEvaluationRate = FMath::Clamp(NewRate, MinTickClamp, MaxTickClamp);

  if (UWorld *World = GetWorld()) {
    World->GetTimerManager().ClearTimer(TickEvalTimerHandle);
    World->GetTimerManager().SetTimer(
        TickEvalTimerHandle, this,
        &UDAI_PerfMngrComponent::UpdateTickBasedOnSignificance,
        TickEvaluationRate, true);
  }
}

// Setter: change the replication/significance threshold value.
void UDAI_PerfMngrComponent::SetSignificanceThreshold(float NewThreshold) {
  ReplicationSignificanceThreshold = NewThreshold;
}

// Setter: change the overall performance mode.
void UDAI_PerfMngrComponent::SetPerformanceMode(EPerformanceMode NewMode) {
  PerformanceMode = NewMode;
}

void UDAI_PerfMngrComponent::SetPerformanceQuality(
    EPerformanceQuality NewQuality) {
  PerformanceQuality = NewQuality;
}

// Networking boilerplate (currently default behavior).
void UDAI_PerfMngrComponent::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty> &OutLifetimeProps) const {
  Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

// Quick check: are we currently in proxy mode?
bool UDAI_PerfMngrComponent::IsUsingProxy() const {
  return ProxyState == EProxySwapState::ProxyActive;
}

// Expose the current proxy swap state.
EProxySwapState UDAI_PerfMngrComponent::GetCurrentProxyState() const {
  return ProxyState;
}

// Force immediate switch into proxy mode (skips the usual checks).
void UDAI_PerfMngrComponent::ForceSwapToProxy() {
  SwapToProxy();
  ProxyState = EProxySwapState::ProxyActive;
  ProxyTimeInCurrentState = 0.0f;
}

// Force immediate switch back to full visuals.
void UDAI_PerfMngrComponent::ForceSwapToFull() {
  SwapToFull();
  ProxyState = EProxySwapState::Active;
  ProxyTimeInCurrentState = 0.0f;
}

// Ensure only one representation (full, proxy, or billboard) is active at a
// time.
void UDAI_PerfMngrComponent::EnsureSingleRepresentation() {
  AActor *Owner = GetOwner();
  if (!Owner) {
    return;
  }

  const bool bBillboardVisible =
      BillboardMeshComponent && BillboardMeshComponent->IsVisible();
  const bool bProxyVisible =
      ProxyMeshComponent && ProxyMeshComponent->IsVisible();

  bool bFullVisible = false;
  TArray<UMeshComponent *> Meshes;
  Owner->GetComponents<UMeshComponent>(Meshes);
  for (UMeshComponent *Mesh : Meshes) {
    if (Mesh && Mesh->IsVisible() && Mesh != ProxyMeshComponent &&
        Mesh != BillboardMeshComponent) {
      bFullVisible = true;
      break;
    }
  }

  const int32 VisibleCount = (bBillboardVisible ? 1 : 0) +
                             (bProxyVisible ? 1 : 0) + (bFullVisible ? 1 : 0);
  if (VisibleCount <= 1) {
    return;
  }

  if (bBillboardVisible) {
    if (ProxyMeshComponent) {
      ProxyMeshComponent->DestroyComponent();
      ProxyMeshComponent = nullptr;
    }
    for (UMeshComponent *Mesh : Meshes) {
      if (Mesh && Mesh != BillboardMeshComponent) {
        Mesh->SetVisibility(false, true);
        Mesh->SetComponentTickEnabled(false);
      }
    }
  } else if (bProxyVisible) {
    if (BillboardMeshComponent) {
      BillboardMeshComponent->DestroyComponent();
      BillboardMeshComponent = nullptr;
    }
    for (UMeshComponent *Mesh : Meshes) {
      if (Mesh && Mesh != ProxyMeshComponent) {
        Mesh->SetVisibility(false, true);
        Mesh->SetComponentTickEnabled(false);
      }
    }
  } else {
    SwapToFull();
    ProxyState = EProxySwapState::Active;
    BillboardState = EProxySwapState::Active;
  }

  bool bBillboardCheck =
      BillboardMeshComponent && BillboardMeshComponent->IsVisible();
  bool bProxyCheck = ProxyMeshComponent && ProxyMeshComponent->IsVisible();
  bool bFullCheck = false;
  for (UMeshComponent *Mesh : Meshes) {
    if (Mesh && Mesh->IsVisible() && Mesh != ProxyMeshComponent &&
        Mesh != BillboardMeshComponent) {
      bFullCheck = true;
      break;
    }
  }
  const int32 Remaining =
      (bBillboardCheck ? 1 : 0) + (bProxyCheck ? 1 : 0) + (bFullCheck ? 1 : 0);
  if (Remaining > 1) {
    SwapToFull();
    ProxyState = EProxySwapState::Active;
    BillboardState = EProxySwapState::Active;
  }
}

// Per-frame updates for this component.
// Keeps billboards facing the camera and prints optional debug info.
void UDAI_PerfMngrComponent::TickComponent(
    float DeltaTime, enum ELevelTick TickType,
    FActorComponentTickFunction *ThisTickFunction) {
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  EnsureSingleRepresentation();

  if (BillboardMeshComponent && BillboardMeshComponent->IsVisible()) {
    if (APlayerCameraManager *CamMgr =
            UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)) {
      FVector CameraLoc = CamMgr->GetCameraLocation();
      FVector MyLoc = BillboardMeshComponent->GetComponentLocation();
      FRotator LookAtRot = (CameraLoc - MyLoc).Rotation();
      BillboardMeshComponent->SetWorldRotation(LookAtRot);
    }
  }

  static float PrintTimer = 0.0f;
  PrintTimer += DeltaTime;
  if (bEnableDebugLog && PrintTimer > 2.0f) {
    UWorld *World = GetWorld();
    if (World) {
      if (UDAI_ProxyHISMManager *ProxyMgr =
              World->GetSubsystem<UDAI_ProxyHISMManager>()) {
        ProxyMgr->PrintAllHISMDebugInfo();
      }
    }
    PrintTimer = 0.0f;
  }
}

// Billboard proxy swap logic (simplified explanation below).

// Handles swapping between a 3D proxy mesh and a simpler billboard version when
// the actor is very far away. Supports instant swap or a smooth cross-fade if a
// fade material and duration are set.
void UDAI_PerfMngrComponent::HandleBillboardProxySwap(float DeltaTime,
                                                      float Significance) {
  if (!ProxyBillboardMesh) {
    BillboardState = EProxySwapState::Active;
    return;
  }

  BillboardTimeInCurrentState += DeltaTime;

  switch (BillboardState) {
  case EProxySwapState::Active: {
    // If significance falls below the billboard threshold and the actor is
    // already in proxy mode, begin the pending swap to billboard.  Only
    // transition when we are currently using a proxy representation (either
    // HISM or unique mesh).
    if (Significance < BillboardEnterThreshold) {
      const bool bProxyVisible =
          (ProxyMeshComponent != nullptr) || bHasHISMInstance;
      if (bProxyVisible && ProxyState == EProxySwapState::ProxyActive) {
        BillboardState = EProxySwapState::PendingSwapToProxy;
        BillboardTimeInCurrentState = 0.0f;
        // Reset fade state
        bBillboardFadeActive = false;
      }
    }
    break;
  }
  case EProxySwapState::PendingSwapToProxy: {
    // Abort billboard swap if significance increases above the enter threshold
    if (Significance >= BillboardEnterThreshold) {
      BillboardState = EProxySwapState::Active;
      break;
    }

    // Swap instantly after the configured delay
    if (BillboardTimeInCurrentState >= ProxySwapDelay) {
      // Remove the existing proxy HISM instance
      if (bHasHISMInstance && ProxyStaticMesh) {
        if (UDAI_ProxyHISMManager *ProxyMgr =
                GetWorld()->GetSubsystem<UDAI_ProxyHISMManager>()) {
          ProxyMgr->RemoveInstanceAtTransform(ProxyHISMTag, ProxyHISMTransform);
        }
        bHasHISMInstance = false;
      }

      // Add a billboard instance via the HISM manager
      if (ProxyBillboardMesh) {
        if (UDAI_ProxyHISMManager *ProxyMgr =
                GetWorld()->GetSubsystem<UDAI_ProxyHISMManager>()) {
          // Batch billboard proxies by mesh so many actors share one HISM.
          FName BillboardTag = FName(*FString::Printf(
              TEXT("Billboard_%s"), *ProxyBillboardMesh->GetName()));
          UHierarchicalInstancedStaticMeshComponent *HISM =
              ProxyMgr->GetOrCreateHISMForTag(BillboardTag, ProxyBillboardMesh,
                                              GetOwner());
          if (HISM) {
            ProxyMgr->SetBatchSizeForTag(BillboardTag, ProxyBatchAddSize);
            ProxyMgr->QueueInstanceForBatch(BillboardTag,
                                            GetOwner()->GetActorTransform());
            ProxyHISMTag = BillboardTag;
            ProxyHISMTransform = GetOwner()->GetActorTransform();
            bHasHISMInstance = true;
          }
        }
      }
      BillboardState = EProxySwapState::ProxyActive;
      BillboardTimeInCurrentState = 0.0f;
    }
    break;
  }
  case EProxySwapState::ProxyActive: {
    // When significance rises above the billboard exit threshold, begin pending
    // swap back to proxy
    if (Significance > BillboardExitThreshold) {
      BillboardState = EProxySwapState::PendingSwapToFull;
      BillboardTimeInCurrentState = 0.0f;
      // Reset fade state for reverse fade
      bBillboardFadeActive = false;
    }
    break;
  }
  case EProxySwapState::PendingSwapToFull: {
    // Cancel exit if significance drops again below the exit threshold
    if (Significance <= BillboardExitThreshold) {
      BillboardState = EProxySwapState::ProxyActive;
      break;
    }

    // Swap instantly after the configured delay
    if (BillboardTimeInCurrentState >= ProxySwapDelay) {
      // Remove the billboard instance
      if (bHasHISMInstance && ProxyBillboardMesh) {
        if (UDAI_ProxyHISMManager *ProxyMgr =
                GetWorld()->GetSubsystem<UDAI_ProxyHISMManager>()) {
          ProxyMgr->RemoveInstanceAtTransform(ProxyHISMTag, ProxyHISMTransform);
        }
        bHasHISMInstance = false;
      }
      // Restore the proxy instance via HISM
      if (ProxyStaticMesh) {
        if (UDAI_ProxyHISMManager *ProxyMgr =
                GetWorld()->GetSubsystem<UDAI_ProxyHISMManager>()) {
          // Tag proxies solely by mesh name so actors reuse the same HISM.
          FName ProxyTag = FName(
              *FString::Printf(TEXT("Proxy_%s"), *ProxyStaticMesh->GetName()));
          UHierarchicalInstancedStaticMeshComponent *HISM =
              ProxyMgr->GetOrCreateHISMForTag(ProxyTag, ProxyStaticMesh,
                                              GetOwner());
          if (HISM) {
            ProxyMgr->SetBatchSizeForTag(ProxyTag, ProxyBatchAddSize);
            ProxyMgr->QueueInstanceForBatch(ProxyTag,
                                            GetOwner()->GetActorTransform());
            ProxyHISMTag = ProxyTag;
            ProxyHISMTransform = GetOwner()->GetActorTransform();
            bHasHISMInstance = true;
          }
        }
      }
      BillboardState = EProxySwapState::Active;
      BillboardTimeInCurrentState = 0.0f;
    }
    break;
  }
  }
  EnsureSingleRepresentation();
}

// Particle proxy swap logic (simplified explanation below).
// Handles swapping to/from a lightweight particle effect when the actor is
// extremely far away.
void UDAI_PerfMngrComponent::HandleParticleProxySwap(float DeltaTime,
                                                     float Significance) {
  if (!ProxyParticleEffect) {
    ParticleState = EProxySwapState::Active;
    return;
  }

  ParticleTimeInCurrentState += DeltaTime;

  switch (ParticleState) {
  case EProxySwapState::Active:
    if (Significance < ParticleEnterThreshold) {
      ParticleState = EProxySwapState::PendingSwapToProxy;
      ParticleTimeInCurrentState = 0.0f;
    }
    break;

  case EProxySwapState::PendingSwapToProxy:
    if (Significance < ParticleEnterThreshold &&
        ParticleTimeInCurrentState >= ProxySwapDelay) {
      if (ProxyEffectComponent == nullptr && ProxyParticleEffect) {
        // Spawn the Niagara particle effect when entering particle proxy mode
        ProxyEffectComponent = NewObject<UNiagaraComponent>(GetOwner());
        ProxyEffectComponent->SetAsset(ProxyParticleEffect);
        ProxyEffectComponent->RegisterComponent();
        ProxyEffectComponent->AttachToComponent(
            GetOwner()->GetRootComponent(),
            FAttachmentTransformRules::KeepRelativeTransform);
        ProxyEffectComponent->Activate();
        // Tag the particle proxy for identification
        if (!ParticleProxyTag.IsNone()) {
          ProxyEffectComponent->ComponentTags.Add(ParticleProxyTag);
        }
      }
      // Immediately enter the active state; particle proxies do not use HISM
      // batching
      ParticleState = EProxySwapState::ProxyActive;
    } else if (Significance >= ParticleEnterThreshold) {
      ParticleState = EProxySwapState::Active;
    }
    break;

  case EProxySwapState::ProxyActive:
    if (Significance > ParticleExitThreshold) {
      ParticleState = EProxySwapState::PendingSwapToFull;
      ParticleTimeInCurrentState = 0.0f;
    }
    break;

  case EProxySwapState::PendingSwapToFull:
    if (Significance > ParticleExitThreshold &&
        ParticleTimeInCurrentState >= ProxySwapDelay) {
      // Destroy the Niagara particle effect when leaving particle proxy mode
      if (ProxyEffectComponent) {
        ProxyEffectComponent->DestroyComponent();
        ProxyEffectComponent = nullptr;
      }
      ParticleState = EProxySwapState::Active;
    } else if (Significance <= ParticleExitThreshold) {
      // If significance drops again before the delay completes, remain in proxy
      // active state
      ParticleState = EProxySwapState::ProxyActive;
    }
    break;
  }
}