#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PerformanceComponentManager.generated.h"

class AActor;
class USceneComponent;
class UChildActorComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;
class UDecalComponent;
class UTextRenderComponent;
class UPointLightComponent;
class USpotLightComponent;
class UDirectionalLightComponent;
class URectLightComponent;
class USkyLightComponent;
class UCameraComponent;
class USpringArmComponent;
class UInputComponent;
class UAIPerceptionComponent;   
class UBoxComponent;
class USphereComponent;
class UCapsuleComponent;
class UPhysicsConstraintComponent;
class URadialForceComponent;
class UAudioComponent;
class USynthComponent;
class UWidgetComponent;
class UBillboardComponent;
class UArrowComponent;

UENUM(BlueprintType)
enum class EManagedComponentType : uint8
{
    Scene,
    ChildActor,
    StaticMesh,
    SkeletalMesh,
    Decal,
    TextRender,
    PointLight,
    SpotLight,
    DirectionalLight,
    RectLight,
    SkyLight,
    Camera,
    SpringArm,
    Input,
    AIPerception,  
    BoxCollision,
    SphereCollision,
    CapsuleCollision,
    PhysicsConstraint,
    RadialForce,
    Audio,
    Synth,
    Widget,
    Billboard,
    Arrow
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAI_PERFMNGR_API UPerformanceComponentManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UPerformanceComponentManager(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, Category = "Performance")
    void SetComponentActive(AActor* Target, EManagedComponentType Type, bool bActive);

protected:
    UFUNCTION(Server, Reliable)
    void ServerSetComponentActive(AActor* Target, EManagedComponentType Type, bool bActive);

    UFUNCTION(NetMulticast, Reliable)
    void MulticastSetComponentActive(AActor* Target, EManagedComponentType Type, bool bActive);

    void InternalSetComponentActive(AActor* Target, EManagedComponentType Type, bool bActive);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
