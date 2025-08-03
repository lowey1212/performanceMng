#include "PerformanceComponentManager.h"

#include "Net/UnrealNetwork.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/DecalComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/RectLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SynthComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/ArrowComponent.h"

#if UE_WITH_IRIS
#include "Iris/ReplicationSystem/ReplicationSystem.h"
#endif

UPerformanceComponentManager::UPerformanceComponentManager()
{
    bReplicates = true;
    SetIsReplicatedByDefault(true);
}

void UPerformanceComponentManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void UPerformanceComponentManager::SetComponentActive(AActor* Target, EManagedComponentType Type, bool bActive)
{
    if (GetOwnerRole() == ROLE_Authority)
    {
        InternalSetComponentActive(Target, Type, bActive);
        MulticastSetComponentActive(Target, Type, bActive);
    }
    else
    {
        ServerSetComponentActive(Target, Type, bActive);
    }
}

void UPerformanceComponentManager::ServerSetComponentActive_Implementation(AActor* Target, EManagedComponentType Type, bool bActive)
{
    InternalSetComponentActive(Target, Type, bActive);
    MulticastSetComponentActive(Target, Type, bActive);
}

void UPerformanceComponentManager::MulticastSetComponentActive_Implementation(AActor* Target, EManagedComponentType Type, bool bActive)
{
    InternalSetComponentActive(Target, Type, bActive);
}

void UPerformanceComponentManager::InternalSetComponentActive(AActor* Target, EManagedComponentType Type, bool bActive)
{
    if (!Target)
    {
        return;
    }

    UActorComponent* Comp = nullptr;
    switch (Type)
    {
    case EManagedComponentType::Scene:
        Comp = Target->FindComponentByClass<USceneComponent>();
        break;
    case EManagedComponentType::ChildActor:
        Comp = Target->FindComponentByClass<UChildActorComponent>();
        break;
    case EManagedComponentType::StaticMesh:
        Comp = Target->FindComponentByClass<UStaticMeshComponent>();
        break;
    case EManagedComponentType::SkeletalMesh:
        Comp = Target->FindComponentByClass<USkeletalMeshComponent>();
        break;
    case EManagedComponentType::Decal:
        Comp = Target->FindComponentByClass<UDecalComponent>();
        break;
    case EManagedComponentType::TextRender:
        Comp = Target->FindComponentByClass<UTextRenderComponent>();
        break;
    case EManagedComponentType::PointLight:
        Comp = Target->FindComponentByClass<UPointLightComponent>();
        break;
    case EManagedComponentType::SpotLight:
        Comp = Target->FindComponentByClass<USpotLightComponent>();
        break;
    case EManagedComponentType::DirectionalLight:
        Comp = Target->FindComponentByClass<UDirectionalLightComponent>();
        break;
    case EManagedComponentType::RectLight:
        Comp = Target->FindComponentByClass<URectLightComponent>();
        break;
    case EManagedComponentType::SkyLight:
        Comp = Target->FindComponentByClass<USkyLightComponent>();
        break;
    case EManagedComponentType::Camera:
        Comp = Target->FindComponentByClass<UCameraComponent>();
        break;
    case EManagedComponentType::SpringArm:
        Comp = Target->FindComponentByClass<USpringArmComponent>();
        break;
    case EManagedComponentType::Input:
        Comp = Target->InputComponent;
        break;
    case EManagedComponentType::PawnSensing:
        Comp = Target->FindComponentByClass<UPawnSensingComponent>();
        break;
    case EManagedComponentType::BoxCollision:
        Comp = Target->FindComponentByClass<UBoxComponent>();
        break;
    case EManagedComponentType::SphereCollision:
        Comp = Target->FindComponentByClass<USphereComponent>();
        break;
    case EManagedComponentType::CapsuleCollision:
        Comp = Target->FindComponentByClass<UCapsuleComponent>();
        break;
    case EManagedComponentType::PhysicsConstraint:
        Comp = Target->FindComponentByClass<UPhysicsConstraintComponent>();
        break;
    case EManagedComponentType::RadialForce:
        Comp = Target->FindComponentByClass<URadialForceComponent>();
        break;
    case EManagedComponentType::Audio:
        Comp = Target->FindComponentByClass<UAudioComponent>();
        break;
    case EManagedComponentType::Synth:
        Comp = Target->FindComponentByClass<USynthComponent>();
        break;
    case EManagedComponentType::Widget:
        Comp = Target->FindComponentByClass<UWidgetComponent>();
        break;
    case EManagedComponentType::Billboard:
        Comp = Target->FindComponentByClass<UBillboardComponent>();
        break;
    case EManagedComponentType::Arrow:
        Comp = Target->FindComponentByClass<UArrowComponent>();
        break;
    default:
        break;
    }

    if (Comp)
    {
        if (bActive)
        {
            Comp->Activate(true);
            Comp->SetComponentTickEnabled(true);
        }
        else
        {
            Comp->Deactivate();
            Comp->SetComponentTickEnabled(false);
        }

#if WITH_EDITOR
        UE_LOG(LogTemp, Verbose, TEXT("Set component %s active %s"), *GetNameSafe(Comp), bActive ? TEXT("true") : TEXT("false"));
#endif
    }
}

