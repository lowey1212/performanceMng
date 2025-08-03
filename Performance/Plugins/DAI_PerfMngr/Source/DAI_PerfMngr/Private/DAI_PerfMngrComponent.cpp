#include "DAI_PerfMngrComponent.h"
#include "SignificanceManager.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemComponent.h"
#include "Engine/Engine.h"
#include "Components/MeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Components/LightComponent.h"
#include "Components/WidgetComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Animation/AnimInstance.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GroomComponent.h"
#include "DAI_ProxyHISMManager.h"
#include "ProxyHISMRootActor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"


// Significance Helper (needs to be above UDAI_PerfMngrComponent::BeginPlay)
static float CalculateHybridSignificance(
    USignificanceManager::FManagedObjectInfo* Info,
    const FTransform& ViewTransform,
    float MaxDistance)
{
    AActor* TrackedActor = Cast<AActor>(Info->GetObject());
    if (!TrackedActor) return 0.0f;

    if (USkeletalMeshComponent* SkeletalMesh = TrackedActor->FindComponentByClass<USkeletalMeshComponent>())
    {
        if (UAnimInstance* AnimInstance = SkeletalMesh->GetAnimInstance())
        {
            int32 LODLevel = AnimInstance->GetLODLevel();
            int32 MaxLODs = 4;
            return 1.0f - static_cast<float>(LODLevel) / static_cast<float>(MaxLODs - 1);
        }
    }

    if (UStaticMeshComponent* StaticMesh = TrackedActor->FindComponentByClass<UStaticMeshComponent>())
    {
        const FVector ObjectLocation = TrackedActor->GetActorLocation();
        const FVector ViewLocation = ViewTransform.GetLocation();
        float Distance = FVector::Dist(ObjectLocation, ViewLocation);
        return 1.0f - FMath::Clamp(Distance / MaxDistance, 0.0f, 1.0f);
    }
    if (UNiagaraComponent* NiagaraComp = TrackedActor->FindComponentByClass<UNiagaraComponent>())
    {
        const FVector ObjectLocation = TrackedActor->GetActorLocation();
        const FVector ViewLocation = ViewTransform.GetLocation();
        float Distance = FVector::Dist(ObjectLocation, ViewLocation);
        return 1.0f - FMath::Clamp(Distance / MaxDistance, 0.0f, 1.0f);
    }
    return 0.0f;
}

// UDAI_PerfMngrComponent Implementation

// Constructor: set defaults for ticking and proxy options.
UDAI_PerfMngrComponent::UDAI_PerfMngrComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    bUseHISMProxyBatching = true;
    ProxyBatchAddSize = 50;
    bHasHISMInstance = false;
}

// Called when the game starts.
// Registers with the significance system, caches materials for color-by-significance,
// and starts a timer to periodically adjust ticking and proxies based on importance.
void UDAI_PerfMngrComponent::BeginPlay()
{
    Super::BeginPlay();

    AActor* Owner = GetOwner();
    if (!Owner) return;

    if (bAffectAbilitySystemTick)
    {
        CachedASC = Cast<UAbilitySystemComponent>(Owner->GetComponentByClass(UAbilitySystemComponent::StaticClass()));
    }

    if (bColorizeBySignificance)
    {
        TArray<UMeshComponent*> Meshes;
        Owner->GetComponents<UMeshComponent>(Meshes);

        for (UMeshComponent* Mesh : Meshes)
        {
            if (!Mesh || !Mesh->IsRegistered()) continue;

            TArray<UMaterialInstanceDynamic*> DynMats;
            int32 MatCount = Mesh->GetNumMaterials();

            for (int32 i = 0; i < MatCount; ++i)
            {
                if (UMaterialInstanceDynamic* DynMat = Mesh->CreateAndSetMaterialInstanceDynamic(i))
                {
                    DynMats.Add(DynMat);
                }
            }
            CachedDynamicMats.Add(Mesh, DynMats);
        }
    }

    if (USignificanceManager* Manager = USignificanceManager::Get(GetWorld()))
    {
        const float LocalMaxDistance = MaxDistance;

        Manager->RegisterObject(
            Owner,
            Category,
            [LocalMaxDistance](USignificanceManager::FManagedObjectInfo* Info, const FTransform& ViewTransform)
            {
                return CalculateHybridSignificance(Info, ViewTransform, LocalMaxDistance);
            },
            USignificanceManager::EPostSignificanceType::None,
            nullptr
        );

        GetWorld()->GetTimerManager().SetTimer(
            TickEvalTimerHandle,
            this,
            &UDAI_PerfMngrComponent::UpdateTickBasedOnSignificance,
            TickEvaluationRate,
            true
        );
    }
}

// Called when the component stops.
// Cleans up timers and removes any HISM proxy instance that was added.
void UDAI_PerfMngrComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(TickEvalTimerHandle);
    }
    if (bUseHISMProxyBatching && bHasHISMInstance && ProxyStaticMesh)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            if (UDAI_ProxyHISMManager* ProxyMgr = World->GetSubsystem<UDAI_ProxyHISMManager>())
            {
                ProxyMgr->RemoveInstanceAtTransform(ProxyHISMTag, ProxyHISMTransform);
            }
        }
        bHasHISMInstance = false;
    }
    Super::EndPlay(EndPlayReason);
}

// Final cleanup to remove any HISM instance if needed.
void UDAI_PerfMngrComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    if (bUseHISMProxyBatching && bHasHISMInstance && ProxyStaticMesh)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            if (UDAI_ProxyHISMManager* ProxyMgr = World->GetSubsystem<UDAI_ProxyHISMManager>())
            {
                ProxyMgr->RemoveInstanceAtTransform(ProxyHISMTag, ProxyHISMTransform);
            }
        }
        bHasHISMInstance = false;
    }
    Super::OnComponentDestroyed(bDestroyingHierarchy);
}

// Switch to a lightweight visual for this actor (proxy).
// Hide complex components (meshes, hair, widgets), and either spawn a simple mesh or batch into a HISM.
// Optionally spawn a simple hair proxy. Billboard/particles are handled separately.
void UDAI_PerfMngrComponent::SwapToProxy()
{
    AActor* Owner = GetOwner();
    if (!Owner)
    {
        UE_LOG(LogTemp, Error, TEXT("[PerfMngr] SwapToProxy: Owner is null!"));
        return;
    }

    if (!ProxyStaticMesh)
    {
        UE_LOG(LogTemp, Error, TEXT("[PerfMngr] SwapToProxy: ProxyStaticMesh is null!"));
        return;
    }

    // If we previously swapped to a billboard via HISM, remove that instance before using the regular proxy.
    if (bUseHISMProxyBatching && bHasHISMInstance && ProxyBillboardMesh)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            if (UDAI_ProxyHISMManager* ProxyMgr = World->GetSubsystem<UDAI_ProxyHISMManager>())
            {
                ProxyMgr->RemoveInstanceAtTransform(ProxyHISMTag, ProxyHISMTransform);
            }
        }
        bHasHISMInstance = false;
    }

    // Hide original mesh components while a proxy is shown.
    TArray<UMeshComponent*> Meshes;
    Owner->GetComponents<UMeshComponent>(Meshes);
    for (UMeshComponent* Mesh : Meshes)
    {
        Mesh->SetVisibility(false, true);
        Mesh->SetComponentTickEnabled(false);
    }

    // Hide hair components while a proxy is shown.
    TArray<UGroomComponent*> GroomComps;
    Owner->GetComponents<UGroomComponent>(GroomComps);
    for (UGroomComponent* Groom : GroomComps)
    {
        Groom->SetVisibility(false);
        Groom->Deactivate();
    }

    // If not using batching, create a one-off proxy mesh component on this actor.
    if (ProxyStaticMesh && !bUseHISMProxyBatching)
    {
        ProxyMeshComponent = NewObject<UStaticMeshComponent>(Owner);
        ProxyMeshComponent->RegisterComponent();
        ProxyMeshComponent->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
        ProxyMeshComponent->SetStaticMesh(ProxyStaticMesh);
        ProxyMeshComponent->SetVisibility(true);
    }

    // If using batching, add this actor’s transform into a pooled HISM for its proxy mesh.
    if (ProxyStaticMesh && Owner && bUseHISMProxyBatching)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            if (UDAI_ProxyHISMManager* ProxyMgr = World->GetSubsystem<UDAI_ProxyHISMManager>())
            {
                FName ProxyTag = ProxyStaticMesh->GetFName();
                UE_LOG(LogTemp, Warning, TEXT("SwapToProxy: Owner: %s Mesh: %s"), *Owner->GetName(), *ProxyStaticMesh->GetName());
                UHierarchicalInstancedStaticMeshComponent* HISM = ProxyMgr->GetOrCreateHISMForTag(ProxyTag, ProxyStaticMesh, Owner);
                if (!HISM)
                {
                    UE_LOG(LogTemp, Error, TEXT("SwapToProxy: Failed to create HISM for %s"), *ProxyStaticMesh->GetName());
                }
                else
                {
                    ProxyMgr->SetBatchSizeForTag(ProxyTag, ProxyBatchAddSize);
                    ProxyMgr->QueueInstanceForBatch(ProxyTag, Owner->GetActorTransform());

                    ProxyHISMTransform = Owner->GetActorTransform();
                    ProxyHISMTag = ProxyTag;
                    bHasHISMInstance = true;
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("SwapToProxy: ProxyMgr is null!"));
            }
        }
    }

    // Optional: spawn a simple hair proxy mesh (not batched).
    if (ProxyHairMesh)
    {
        ProxyHairMeshComponent = NewObject<UStaticMeshComponent>(Owner);
        ProxyHairMeshComponent->RegisterComponent();
        ProxyHairMeshComponent->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
        ProxyHairMeshComponent->SetStaticMesh(ProxyHairMesh);
        ProxyHairMeshComponent->SetVisibility(true);
        // Apply an optional tag so designers can identify hair proxy meshes via component tags
        if (!HairProxyTag.IsNone())
        {
            ProxyHairMeshComponent->ComponentTags.Add(HairProxyTag);
        }
    }

    // Billboard and particle proxies are handled elsewhere.

    // Hide UI widget components while using a proxy.
    TArray<UWidgetComponent*> WidgetComps;
    Owner->GetComponents<UWidgetComponent>(WidgetComps);
    for (UWidgetComponent* Widget : WidgetComps)
    {
        Widget->SetVisibility(false);
        Widget->SetComponentTickEnabled(false);
    }
}

// Return from proxy back to the full, original actor visuals.
// Remove any proxy components/HISM instance and show everything again.
void UDAI_PerfMngrComponent::SwapToFull()
{
    AActor* Owner = GetOwner();
    if (!Owner) return;

    // If we used a batched HISM proxy, remove its instance.
    if (bUseHISMProxyBatching && bHasHISMInstance && ProxyStaticMesh)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            if (UDAI_ProxyHISMManager* ProxyMgr = World->GetSubsystem<UDAI_ProxyHISMManager>())
            {
                ProxyMgr->RemoveInstanceAtTransform(ProxyHISMTag, ProxyHISMTransform);
            }
        }
        bHasHISMInstance = false;
    }

    // Clean up any spawned proxy components.
    if (ProxyMeshComponent)
    {
        ProxyMeshComponent->DestroyComponent();
        ProxyMeshComponent = nullptr;
    }
    if (ProxyHairMeshComponent)
    {
        ProxyHairMeshComponent->DestroyComponent();
        ProxyHairMeshComponent = nullptr;
    }
    if (BillboardMeshComponent)
    {
        BillboardMeshComponent->DestroyComponent();
        BillboardMeshComponent = nullptr;
    }
    // Reset billboard fade state and clear any temporary materials.
    bBillboardFadeActive = false;
    ProxyFadeMaterials.Empty();
    BillboardFadeMaterials.Empty();
    if (ProxyEffectComponent)
    {
        ProxyEffectComponent->DestroyComponent();
        ProxyEffectComponent = nullptr;
    }

    // Show original meshes again and resume their ticking.
    TArray<UMeshComponent*> Meshes;
    Owner->GetComponents<UMeshComponent>(Meshes);
    for (UMeshComponent* Mesh : Meshes)
    {
        Mesh->SetVisibility(true, true);
        Mesh->SetComponentTickEnabled(true);
    }

    // Show hair components again.
    TArray<UGroomComponent*> GroomComps;
    Owner->GetComponents<UGroomComponent>(GroomComps);
    for (UGroomComponent* Groom : GroomComps)
    {
        Groom->SetVisibility(true);
        Groom->Activate();
    }

    // Show UI widget components again.
    TArray<UWidgetComponent*> WidgetComps;
    Owner->GetComponents<UWidgetComponent>(WidgetComps);
    for (UWidgetComponent* Widget : WidgetComps)
    {
        Widget->SetVisibility(true);
        Widget->SetComponentTickEnabled(true);
    }
}

// State machine that decides when to enter/exit proxy mode based on "significance" (how important/near it is).
// Uses thresholds and delays to avoid rapid flickering between states.
void UDAI_PerfMngrComponent::HandleProxySwap(float DeltaTime, float Significance)
{
    ProxyTimeInCurrentState += DeltaTime;

    switch (ProxyState)
    {
    case EProxySwapState::Active:
        if (Significance < ProxyEnterThreshold)
        {
            ProxyState = EProxySwapState::PendingSwapToProxy;
            ProxyTimeInCurrentState = 0.0f;
        }
        break;

    case EProxySwapState::PendingSwapToProxy:
        if (Significance < ProxyEnterThreshold && ProxyTimeInCurrentState >= ProxySwapDelay)
        {
            SwapToProxy();
            ProxyState = EProxySwapState::ProxyActive;
            ProxyTimeInCurrentState = 0.0f;
            OnProxyEntered.Broadcast();
        }
        else if (Significance >= ProxyEnterThreshold)
        {
            ProxyState = EProxySwapState::Active;
        }
        break;

    case EProxySwapState::ProxyActive:
        if (Significance > ProxyExitThreshold)
        {
            ProxyState = EProxySwapState::PendingSwapToFull;
            ProxyTimeInCurrentState = 0.0f;
        }
        break;

    case EProxySwapState::PendingSwapToFull:
        if (Significance > ProxyExitThreshold && ProxyTimeInCurrentState >= ProxySwapDelay)
        {
            SwapToFull();
            ProxyState = EProxySwapState::Active;
            ProxyTimeInCurrentState = 0.0f;
            OnProxyExited.Broadcast();
        }
        else if (Significance <= ProxyExitThreshold)
        {
            ProxyState = EProxySwapState::ProxyActive;
        }
        break;
    }
}

// If enabled, tint dynamic materials from red (low importance) to green (high importance).
void UDAI_PerfMngrComponent::ApplyColorBySignificance(float Significance)
{
    for (auto& Entry : CachedDynamicMats)
    {
        for (UMaterialInstanceDynamic* Mat : Entry.Value)
        {
            if (Mat)
            {
                FLinearColor Color = FLinearColor::LerpUsingHSV(FLinearColor::Red, FLinearColor::Green, Significance);
                Mat->SetVectorParameterValue("Color", Color);
            }
        }
    }
}

// Run at a fixed interval.
// Computes how important the actor is (distance to camera),
// adjusts tick rates, manages AI pausing, and drives proxy/billboard/particle swaps.
void UDAI_PerfMngrComponent::UpdateTickBasedOnSignificance()
{
    AActor* Owner = GetOwner();
    if (!Owner) return;

    FVector ViewLocation = GEngine->GetFirstLocalPlayerController(GetWorld())->PlayerCameraManager->GetCameraLocation();
    float Significance = 1.0f - FMath::Clamp(FVector::Dist(Owner->GetActorLocation(), ViewLocation) / MaxDistance, 0.0f, 1.0f);

    if (bEnableDebugLog)
    {
        UE_LOG(LogTemp, Log, TEXT("[PerfMngr] Significance: %.2f"), Significance);
    }
    if (bPrintSignificanceToScreen)
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.1f, FColor::Yellow, FString::Printf(TEXT("Significance: %.2f"), Significance));
    }

    if (bColorizeBySignificance)
    {
        ApplyColorBySignificance(Significance);
    }

    HandleProxySwap(GetWorld()->GetDeltaSeconds(), Significance);

    // Re-check after full: force proxy if still under threshold
    if (ProxyState == EProxySwapState::Active && Significance < ProxyEnterThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("[PerfMngr] Forcing proxy re-entry after full, sig=%.2f"), Significance);
        ProxyState = EProxySwapState::PendingSwapToProxy;
        ProxyTimeInCurrentState = 0.0f;
    }
    HandleBillboardProxySwap(GetWorld()->GetDeltaSeconds(), Significance);
    HandleParticleProxySwap(GetWorld()->GetDeltaSeconds(), Significance);

    if (bAllowAIThrottling)
    {
        ACharacter* CharacterOwner = Cast<ACharacter>(Owner);
        if (CharacterOwner)
        {
            AAIController* AIController = Cast<AAIController>(CharacterOwner->GetController());
            if (AIController)
            {
                UBehaviorTreeComponent* BT = AIController->FindComponentByClass<UBehaviorTreeComponent>();
                if (BT)
                {
                    if (Significance < AIDeepFreezeSignificance && !BT->IsPaused())
                    {
                        // Pause AI logic when significance is below the deep freeze threshold.  Do not
                        // stop movement so that any in‑progress path following will continue updating
                        // the actor's location while the behavior tree remains paused.
                        BT->PauseLogic(FString("PerfMngr Deep Freeze"));
                    }
                    else if (Significance >= AIDeepFreezeSignificance && BT->IsPaused())
                    {
                        // Resume AI logic when the significance rises back above the threshold.
                        BT->ResumeLogic(FString("PerfMngr Resume"));
                    }
                }
            }
        }
    }

    if (bDrawDebugProxySphere && IsUsingProxy())
    {
        DrawDebugSphere(
            GetWorld(),
            GetOwner()->GetActorLocation(),
            100.f,
            16,
            FColor::Magenta,
            false,
            ProxyDebugSphereDuration
        );
    }
    float TickRate = FMath::Clamp(
        FMath::Lerp(TickIntervalHigh, TickIntervalLow, 1.0f - Significance),
        MinTickClamp,
        MaxTickClamp
    );

    Owner->SetActorTickInterval(TickRate);

    if (bAffectAbilitySystemTick && CachedASC)
    {
        CachedASC->SetComponentTickInterval(TickRate);
    }
    TArray<UActorComponent*> AllComponents;
    Owner->GetComponents(AllComponents);

    for (UActorComponent* Comp : AllComponents)
    {
        if (!Comp || !Comp->IsRegistered()) continue;

        bool bShouldSuppress = false;
        FComponentSuppressionRule MatchedRule;
        for (const FComponentSuppressionRule& Rule : ComponentSuppressionRules)
        {
            if (Significance >= Rule.SuppressBelowSignificance) continue;
            bool TagMatch = !Rule.ComponentTag.IsNone() && Comp->ComponentHasTag(Rule.ComponentTag);
            bool NameMatch = !Rule.NameContains.IsEmpty() && Comp->GetName().Contains(Rule.NameContains);

            switch (Rule.ComponentType)
            {
            case ESuppressionComponentType::Audio:
                bShouldSuppress = Comp->IsA<UAudioComponent>();
                break;
            case ESuppressionComponentType::Niagara:
                bShouldSuppress = Comp->IsA<UNiagaraComponent>();
                break;
            case ESuppressionComponentType::AbilitySystem:
                bShouldSuppress = Comp->IsA<UAbilitySystemComponent>();
                break;
            case ESuppressionComponentType::Light:
                bShouldSuppress = Comp->IsA<ULightComponent>();
                break;
            case ESuppressionComponentType::Widget:
                bShouldSuppress = Comp->IsA<UWidgetComponent>() && (TagMatch || NameMatch || Rule.ComponentTag.IsNone());
                break;
            case ESuppressionComponentType::MotionWarping:
                bShouldSuppress = NameMatch || TagMatch || Comp->GetName().Contains(TEXT("MotionWarp"));
                break;
            case ESuppressionComponentType::Hair:
                bShouldSuppress = Comp->IsA<UGroomComponent>() || NameMatch || TagMatch ||
                    Comp->GetName().Contains(TEXT("Groom")) || Comp->GetName().Contains(TEXT("Hair"));
                break;
            case ESuppressionComponentType::Physics:
                if (UMeshComponent* Mesh = Cast<UMeshComponent>(Comp))
                {
                    Mesh->SetSimulatePhysics(false);
                }
                bShouldSuppress = true;
                break;
            case ESuppressionComponentType::CustomTag:
                bShouldSuppress = TagMatch;
                break;
            default:
                break;
            }

            if (bShouldSuppress)
            {
                MatchedRule = Rule;
                break;
            }
        }

        if (bShouldSuppress && !SuppressedComponents.Contains(Comp))
        {
            Comp->SetComponentTickEnabled(false);

            if (UAudioComponent* Audio = Cast<UAudioComponent>(Comp))
            {
                Audio->Stop();
                Audio->SetActive(false);
            }
            else if (ULightComponent* Light = Cast<ULightComponent>(Comp))
            {
                Light->SetVisibility(false);
                Light->SetActive(false);
            }
            else if (UNiagaraComponent* Niagara = Cast<UNiagaraComponent>(Comp))
            {
                Niagara->DeactivateImmediate();
                Niagara->SetVisibility(false);
            }
            else if (UWidgetComponent* Widget = Cast<UWidgetComponent>(Comp))
            {
                Widget->SetVisibility(false);
                Widget->SetComponentTickEnabled(false);
            }
            else if (UGroomComponent* Hair = Cast<UGroomComponent>(Comp))
            {
                Hair->SetVisibility(false);
                Hair->Deactivate();
            }
            else if (UMeshComponent* Mesh = Cast<UMeshComponent>(Comp))
            {
                Mesh->SetSimulatePhysics(false);
            }
            else
            {
                Comp->Deactivate();
            }
            SuppressedComponents.Add(Comp, MatchedRule);
        }
        else if (!bShouldSuppress && SuppressedComponents.Contains(Comp))
        {
            if (ULightComponent* Light = Cast<ULightComponent>(Comp))
            {
                Light->SetVisibility(true);
                Light->SetComponentTickEnabled(true);
                Light->SetActive(true);
            }
            else if (UAudioComponent* Audio = Cast<UAudioComponent>(Comp))
            {
                Audio->SetComponentTickEnabled(true);
                Audio->SetActive(true);
                Audio->Play();
            }
            else if (UNiagaraComponent* Niagara = Cast<UNiagaraComponent>(Comp))
            {
                Niagara->SetComponentTickEnabled(true);
                Niagara->SetVisibility(true);
                Niagara->Activate();
            }
            else if (UWidgetComponent* Widget = Cast<UWidgetComponent>(Comp))
            {
                Widget->SetVisibility(true);
                Widget->SetComponentTickEnabled(true);
            }
            else if (UGroomComponent* Hair = Cast<UGroomComponent>(Comp))
            {
                Hair->SetVisibility(true);
                Hair->Activate();
            }
            else if (UMeshComponent* Mesh = Cast<UMeshComponent>(Comp))
            {
                Mesh->SetSimulatePhysics(true);
                Mesh->SetComponentTickEnabled(true);
            }
            else
            {
                Comp->SetComponentTickEnabled(true);
                Comp->Activate(true);
            }
            SuppressedComponents.Remove(Comp);
        }
    }



    if (bAffectAbilitySystemTick && CachedASC)
    {
        CachedASC->SetComponentTickInterval(TickRate);
    }
}

// Let designers change how often we re-evaluate significance and update tick/proxy decisions.
void UDAI_PerfMngrComponent::SetTickEvaluationRate(float NewRate)
{
    TickEvaluationRate = FMath::Clamp(NewRate, MinTickClamp, MaxTickClamp);

    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(TickEvalTimerHandle);
        World->GetTimerManager().SetTimer(
            TickEvalTimerHandle,
            this,
            &UDAI_PerfMngrComponent::UpdateTickBasedOnSignificance,
            TickEvaluationRate,
            true
        );
    }
}

// Setter: change the replication/significance threshold value.
void UDAI_PerfMngrComponent::SetSignificanceThreshold(float NewThreshold)
{
    ReplicationSignificanceThreshold = NewThreshold;
}

// Setter: change the overall performance mode.
void UDAI_PerfMngrComponent::SetPerformanceMode(EPerformanceMode NewMode)
{
    PerformanceMode = NewMode;
}

// Networking boilerplate (currently default behavior).
void UDAI_PerfMngrComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

// Quick check: are we currently in proxy mode?
bool UDAI_PerfMngrComponent::IsUsingProxy() const
{
    return ProxyState == EProxySwapState::ProxyActive;
}

// Expose the current proxy swap state.
EProxySwapState UDAI_PerfMngrComponent::GetCurrentProxyState() const
{
    return ProxyState;
}

// Force immediate switch into proxy mode (skips the usual checks).
void UDAI_PerfMngrComponent::ForceSwapToProxy()
{
    SwapToProxy();
    ProxyState = EProxySwapState::ProxyActive;
    ProxyTimeInCurrentState = 0.0f;
}

// Force immediate switch back to full visuals.
void UDAI_PerfMngrComponent::ForceSwapToFull()
{
    SwapToFull();
    ProxyState = EProxySwapState::Active;
    ProxyTimeInCurrentState = 0.0f;
}

// Per-frame updates for this component.
// Keeps billboards facing the camera and prints optional debug info.
void UDAI_PerfMngrComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (BillboardMeshComponent && BillboardMeshComponent->IsVisible())
    {
        if (APlayerCameraManager* CamMgr = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0))
        {
            FVector CameraLoc = CamMgr->GetCameraLocation();
            FVector MyLoc = BillboardMeshComponent->GetComponentLocation();
            FRotator LookAtRot = (CameraLoc - MyLoc).Rotation();
            BillboardMeshComponent->SetWorldRotation(LookAtRot);
        }
    }

    static float PrintTimer = 0.0f;
    PrintTimer += DeltaTime;
    if (bEnableDebugLog && PrintTimer > 2.0f)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            if (UDAI_ProxyHISMManager* ProxyMgr = World->GetSubsystem<UDAI_ProxyHISMManager>())
            {
                ProxyMgr->PrintAllHISMDebugInfo();
            }
        }
        PrintTimer = 0.0f;
    }
}


// Billboard proxy swap logic (simplified explanation below).

// Handles swapping between a 3D proxy mesh and a simpler billboard version when the actor is very far away.
// Supports instant swap or a smooth cross-fade if a fade material and duration are set.
void UDAI_PerfMngrComponent::HandleBillboardProxySwap(float DeltaTime, float Significance)
{
    BillboardTimeInCurrentState += DeltaTime;

    switch (BillboardState)
    {
    case EProxySwapState::Active:
    {
        // If significance falls below the billboard threshold and the actor is already in proxy mode,
        // begin the pending swap to billboard.  Only transition when we are currently using a proxy
        // representation (either HISM or unique mesh).
        if (Significance < BillboardEnterThreshold)
        {
            const bool bProxyVisible = (ProxyMeshComponent != nullptr) || bHasHISMInstance;
            if (bProxyVisible && ProxyState == EProxySwapState::ProxyActive)
            {
                BillboardState = EProxySwapState::PendingSwapToProxy;
                BillboardTimeInCurrentState = 0.0f;
                // Reset fade state
                bBillboardFadeActive = false;
            }
        }
        break;
    }
    case EProxySwapState::PendingSwapToProxy:
    {
        // Abort billboard swap if significance increases above the enter threshold
        if (Significance >= BillboardEnterThreshold)
        {
            BillboardState = EProxySwapState::Active;
            break;
        }

        // HISM batching: swap instantly after the configured delay
        if (bUseHISMProxyBatching)
        {
            if (BillboardTimeInCurrentState >= ProxySwapDelay)
            {
                // Remove the existing proxy HISM instance
                if (bHasHISMInstance && ProxyStaticMesh)
                {
                    if (UDAI_ProxyHISMManager* ProxyMgr = GetWorld()->GetSubsystem<UDAI_ProxyHISMManager>())
                    {
                        ProxyMgr->RemoveInstanceAtTransform(ProxyHISMTag, ProxyHISMTransform);
                    }
                    bHasHISMInstance = false;
                }

                // Add a billboard instance via the HISM manager
                if (ProxyBillboardMesh)
                {
                    if (UDAI_ProxyHISMManager* ProxyMgr = GetWorld()->GetSubsystem<UDAI_ProxyHISMManager>())
                    {
                        FName BillboardTag = ProxyBillboardMesh->GetFName();
                        UHierarchicalInstancedStaticMeshComponent* HISM = ProxyMgr->GetOrCreateHISMForTag(BillboardTag, ProxyBillboardMesh, GetOwner());
                        if (HISM)
                        {
                            ProxyMgr->SetBatchSizeForTag(BillboardTag, ProxyBatchAddSize);
                            ProxyMgr->QueueInstanceForBatch(BillboardTag, GetOwner()->GetActorTransform());
                            ProxyHISMTag = BillboardTag;
                            ProxyHISMTransform = GetOwner()->GetActorTransform();
                            bHasHISMInstance = true;
                        }
                    }
                }
                BillboardState = EProxySwapState::ProxyActive;
                BillboardTimeInCurrentState = 0.0f;
            }
        }
        else // not batching
        {
            // Determine the duration to use for the fade.  If a fade material is not specified
            // or the duration is zero, fall back to an instant swap based on ProxySwapDelay.
            const bool bShouldFade = BillboardFadeMaterial && BillboardFadeDuration > 0.0f;

            if (!bShouldFade)
            {
                // Wait for the standard proxy swap delay before performing an instant swap
                if (BillboardTimeInCurrentState >= ProxySwapDelay)
                {
                    // Destroy the current proxy mesh component (if any)
                    if (ProxyMeshComponent)
                    {
                        ProxyMeshComponent->DestroyComponent();
                        ProxyMeshComponent = nullptr;
                        ProxyFadeMaterials.Empty();
                    }
                    // Spawn the billboard mesh component
                    if (ProxyBillboardMesh)
                    {
                        BillboardMeshComponent = NewObject<UStaticMeshComponent>(GetOwner());
                        BillboardMeshComponent->RegisterComponent();
                        BillboardMeshComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
                        BillboardMeshComponent->SetStaticMesh(ProxyBillboardMesh);
                        BillboardMeshComponent->SetVisibility(true);
                        BillboardMeshComponent->ComponentTags.Add(BillboardProxyTag);
                    }
                    BillboardState = EProxySwapState::ProxyActive;
                    BillboardTimeInCurrentState = 0.0f;
                }
            }
            else
            {
                // Initialize fade on first tick
                if (!bBillboardFadeActive)
                {
                    // Spawn billboard component if it does not exist
                    if (ProxyBillboardMesh && BillboardMeshComponent == nullptr)
                    {
                        BillboardMeshComponent = NewObject<UStaticMeshComponent>(GetOwner());
                        BillboardMeshComponent->RegisterComponent();
                        BillboardMeshComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
                        BillboardMeshComponent->SetStaticMesh(ProxyBillboardMesh);
                        BillboardMeshComponent->SetVisibility(true);
                        BillboardMeshComponent->ComponentTags.Add(BillboardProxyTag);
                    }
                    // Create dynamic material instances for the proxy mesh component
                    ProxyFadeMaterials.Empty();
                    if (ProxyMeshComponent)
                    {
                        const int32 NumMats = ProxyMeshComponent->GetNumMaterials();
                        for (int32 Index = 0; Index < NumMats; ++Index)
                        {
                            UMaterialInstanceDynamic* Dyn = UMaterialInstanceDynamic::Create(BillboardFadeMaterial, this);
                            ProxyFadeMaterials.Add(Dyn);
                            ProxyMeshComponent->SetMaterial(Index, Dyn);
                        }
                    }
                    // Create dynamic material instances for the billboard mesh component
                    BillboardFadeMaterials.Empty();
                    if (BillboardMeshComponent)
                    {
                        const int32 NumMats = BillboardMeshComponent->GetNumMaterials();
                        for (int32 Index = 0; Index < NumMats; ++Index)
                        {
                            UMaterialInstanceDynamic* Dyn = UMaterialInstanceDynamic::Create(BillboardFadeMaterial, this);
                            BillboardFadeMaterials.Add(Dyn);
                            BillboardMeshComponent->SetMaterial(Index, Dyn);
                        }
                    }
                    bBillboardFadeActive = true;
                }
                // Compute fade progress
                float Progress = FMath::Clamp(BillboardTimeInCurrentState / BillboardFadeDuration, 0.0f, 1.0f);
                // Update dynamic materials
                for (UMaterialInstanceDynamic* Dyn : ProxyFadeMaterials)
                {
                    if (Dyn)
                    {
                        Dyn->SetScalarParameterValue(FName("FadeAlpha"), 1.0f - Progress);
                    }
                }
                for (UMaterialInstanceDynamic* Dyn : BillboardFadeMaterials)
                {
                    if (Dyn)
                    {
                        Dyn->SetScalarParameterValue(FName("FadeAlpha"), Progress);
                    }
                }
                // When progress reaches 1, complete the fade
                if (Progress >= 1.0f)
                {
                    // Destroy the proxy mesh component and clear fade materials
                    if (ProxyMeshComponent)
                    {
                        ProxyMeshComponent->DestroyComponent();
                        ProxyMeshComponent = nullptr;
                    }
                    ProxyFadeMaterials.Empty();
                    // Reset fade state
                    bBillboardFadeActive = false;
                    BillboardState = EProxySwapState::ProxyActive;
                    BillboardTimeInCurrentState = 0.0f;
                }
            }
        }
        break;
    }
    case EProxySwapState::ProxyActive:
    {
        // When significance rises above the billboard exit threshold, begin pending swap back to proxy
        if (Significance > BillboardExitThreshold)
        {
            BillboardState = EProxySwapState::PendingSwapToFull;
            BillboardTimeInCurrentState = 0.0f;
            // Reset fade state for reverse fade
            bBillboardFadeActive = false;
        }
        break;
    }
    case EProxySwapState::PendingSwapToFull:
    {
        // Cancel exit if significance drops again below the exit threshold
        if (Significance <= BillboardExitThreshold)
        {
            BillboardState = EProxySwapState::ProxyActive;
            break;
        }

        // HISM batching: swap instantly after the configured delay
        if (bUseHISMProxyBatching)
        {
            if (BillboardTimeInCurrentState >= ProxySwapDelay)
            {
                // Remove the billboard instance
                if (bHasHISMInstance && ProxyBillboardMesh)
                {
                    if (UDAI_ProxyHISMManager* ProxyMgr = GetWorld()->GetSubsystem<UDAI_ProxyHISMManager>())
                    {
                        ProxyMgr->RemoveInstanceAtTransform(ProxyHISMTag, ProxyHISMTransform);
                    }
                    bHasHISMInstance = false;
                }
                // Restore the proxy instance via HISM
                if (ProxyStaticMesh)
                {
                    if (UDAI_ProxyHISMManager* ProxyMgr = GetWorld()->GetSubsystem<UDAI_ProxyHISMManager>())
                    {
                        FName ProxyTag = ProxyStaticMesh->GetFName();
                        UHierarchicalInstancedStaticMeshComponent* HISM = ProxyMgr->GetOrCreateHISMForTag(ProxyTag, ProxyStaticMesh, GetOwner());
                        if (HISM)
                        {
                            ProxyMgr->SetBatchSizeForTag(ProxyTag, ProxyBatchAddSize);
                            ProxyMgr->QueueInstanceForBatch(ProxyTag, GetOwner()->GetActorTransform());
                            ProxyHISMTag = ProxyTag;
                            ProxyHISMTransform = GetOwner()->GetActorTransform();
                            bHasHISMInstance = true;
                        }
                    }
                }
                BillboardState = EProxySwapState::Active;
                BillboardTimeInCurrentState = 0.0f;
            }
        }
        else // not batching
        {
            const bool bShouldFade = BillboardFadeMaterial && BillboardFadeDuration > 0.0f;
            if (!bShouldFade)
            {
                // Instant swap back to proxy after delay
                if (BillboardTimeInCurrentState >= ProxySwapDelay)
                {
                    // Destroy billboard mesh component
                    if (BillboardMeshComponent)
                    {
                        BillboardMeshComponent->DestroyComponent();
                        BillboardMeshComponent = nullptr;
                        BillboardFadeMaterials.Empty();
                    }
                    // Spawn new proxy mesh component
                    if (ProxyStaticMesh)
                    {
                        ProxyMeshComponent = NewObject<UStaticMeshComponent>(GetOwner());
                        ProxyMeshComponent->RegisterComponent();
                        ProxyMeshComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
                        ProxyMeshComponent->SetStaticMesh(ProxyStaticMesh);
                        ProxyMeshComponent->SetVisibility(true);
                    }
                    BillboardState = EProxySwapState::Active;
                    BillboardTimeInCurrentState = 0.0f;
                }
            }
            else
            {
                // Initialize fade on first tick of exiting billboard
                if (!bBillboardFadeActive)
                {
                    // Spawn a new proxy mesh component if it does not exist
                    if (ProxyStaticMesh && ProxyMeshComponent == nullptr)
                    {
                        ProxyMeshComponent = NewObject<UStaticMeshComponent>(GetOwner());
                        ProxyMeshComponent->RegisterComponent();
                        ProxyMeshComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
                        ProxyMeshComponent->SetStaticMesh(ProxyStaticMesh);
                        ProxyMeshComponent->SetVisibility(true);
                    }
                    // Create dynamic material instances for the proxy mesh component
                    ProxyFadeMaterials.Empty();
                    if (ProxyMeshComponent)
                    {
                        const int32 NumMats = ProxyMeshComponent->GetNumMaterials();
                        for (int32 Index = 0; Index < NumMats; ++Index)
                        {
                            UMaterialInstanceDynamic* Dyn = UMaterialInstanceDynamic::Create(BillboardFadeMaterial, this);
                            ProxyFadeMaterials.Add(Dyn);
                            ProxyMeshComponent->SetMaterial(Index, Dyn);
                        }
                    }
                    // Create dynamic material instances for the billboard mesh component
                    BillboardFadeMaterials.Empty();
                    if (BillboardMeshComponent)
                    {
                        const int32 NumMats = BillboardMeshComponent->GetNumMaterials();
                        for (int32 Index = 0; Index < NumMats; ++Index)
                        {
                            UMaterialInstanceDynamic* Dyn = UMaterialInstanceDynamic::Create(BillboardFadeMaterial, this);
                            BillboardFadeMaterials.Add(Dyn);
                            BillboardMeshComponent->SetMaterial(Index, Dyn);
                        }
                    }
                    bBillboardFadeActive = true;
                }
                // Compute progress for reverse fade (proxy fading in, billboard fading out)
                float Progress = FMath::Clamp(BillboardTimeInCurrentState / BillboardFadeDuration, 0.0f, 1.0f);
                for (UMaterialInstanceDynamic* Dyn : ProxyFadeMaterials)
                {
                    if (Dyn)
                    {
                        Dyn->SetScalarParameterValue(FName("FadeAlpha"), Progress);
                    }
                }
                for (UMaterialInstanceDynamic* Dyn : BillboardFadeMaterials)
                {
                    if (Dyn)
                    {
                        Dyn->SetScalarParameterValue(FName("FadeAlpha"), 1.0f - Progress);
                    }
                }
                if (Progress >= 1.0f)
                {
                    // Destroy billboard component and clear materials
                    if (BillboardMeshComponent)
                    {
                        BillboardMeshComponent->DestroyComponent();
                        BillboardMeshComponent = nullptr;
                    }
                    BillboardFadeMaterials.Empty();
                    // Reset fade state
                    bBillboardFadeActive = false;
                    BillboardState = EProxySwapState::Active;
                    BillboardTimeInCurrentState = 0.0f;
                }
            }
        }
        break;
    }
    }
}



// Particle proxy swap logic (simplified explanation below).
// Handles swapping to/from a lightweight particle effect when the actor is extremely far away.
void UDAI_PerfMngrComponent::HandleParticleProxySwap(float DeltaTime, float Significance)
{
    ParticleTimeInCurrentState += DeltaTime;

    switch (ParticleState)
    {
    case EProxySwapState::Active:
        if (Significance < ParticleEnterThreshold)
        {
            ParticleState = EProxySwapState::PendingSwapToProxy;
            ParticleTimeInCurrentState = 0.0f;
        }
        break;

    case EProxySwapState::PendingSwapToProxy:
        if (Significance < ParticleEnterThreshold && ParticleTimeInCurrentState >= ProxySwapDelay)
        {
            if (ProxyEffectComponent == nullptr && ProxyParticleEffect)
            {
                // Spawn the Niagara particle effect when entering particle proxy mode
                ProxyEffectComponent = NewObject<UNiagaraComponent>(GetOwner());
                ProxyEffectComponent->SetAsset(ProxyParticleEffect);
                ProxyEffectComponent->RegisterComponent();
                ProxyEffectComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
                ProxyEffectComponent->Activate();
                // Tag the particle proxy for identification
                if (!ParticleProxyTag.IsNone())
                {
                    ProxyEffectComponent->ComponentTags.Add(ParticleProxyTag);
                }
            }
            // Immediately enter the active state; particle proxies do not use HISM batching
            ParticleState = EProxySwapState::ProxyActive;
        }
        else if (Significance >= ParticleEnterThreshold)
        {
            ParticleState = EProxySwapState::Active;
        }
        break;

    case EProxySwapState::ProxyActive:
        if (Significance > ParticleExitThreshold)
        {
            ParticleState = EProxySwapState::PendingSwapToFull;
            ParticleTimeInCurrentState = 0.0f;
        }
        break;

    case EProxySwapState::PendingSwapToFull:
        if (Significance > ParticleExitThreshold && ParticleTimeInCurrentState >= ProxySwapDelay)
        {
            // Destroy the Niagara particle effect when leaving particle proxy mode
            if (ProxyEffectComponent)
            {
                ProxyEffectComponent->DestroyComponent();
                ProxyEffectComponent = nullptr;
            }
            ParticleState = EProxySwapState::Active;
        }
        else if (Significance <= ParticleExitThreshold)
        {
            // If significance drops again before the delay completes, remain in proxy active state
            ParticleState = EProxySwapState::ProxyActive;
        }
        break;
    }
}