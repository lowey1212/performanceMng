#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "DAI_PerfMngrComponent.generated.h"

// Forward declarations...
class UAbilitySystemComponent;
class UMaterialInstanceDynamic;
class UMaterialInterface;
class UStaticMesh;
class UStaticMeshComponent;
class UWidgetComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UGroomComponent;
class UDAI_ProxyHISMManager;
class UBehaviorTreeComponent;
class AAIController;

// Optional Mutable plugin support
#if __has_include("CustomizableSkeletalComponent.h")
#include "CustomizableObjectInstance.h"
#include "CustomizableObjectSystem.h"
#include "CustomizableSkeletalComponent.h"
#define WITH_CUSTOMIZABLE_OBJECT 1
#else
#define WITH_CUSTOMIZABLE_OBJECT 0
class UCustomizableObjectInstance;
class UCustomizableSkeletalComponent;
class UCustomizableObjectSystem;
#endif

/**
 * @brief Component that automatically swaps an actor between "full" and "proxy"
 * representations based on how important (significant) the actor is to the
 * player (usually how close it is).
 */
UENUM(BlueprintType)
enum class EProxySwapState : uint8 {
    Active,
    PendingSwapToProxy,
    ProxyActive,
    PendingSwapToFull
};
UENUM(BlueprintType)
enum class EPerformanceMode : uint8 { Auto, Full, Proxy };
UENUM(BlueprintType)
enum class ESuppressionComponentType : uint8 {
    Audio,
    Niagara,
    AbilitySystem,
    Light,
    Widget,
    MotionWarping,
    Hair,
    Physics,
    Camera,
    CustomTag
};
UENUM(BlueprintType)
enum class EPerformanceQuality : uint8 { High, Medium, Low };
/**
 * @brief Rule describing which component(s) can be suppressed as significance
 * drops.
 */
USTRUCT(BlueprintType)
struct FComponentSuppressionRule {
    GENERATED_BODY()

#if WITH_CUSTOMIZABLE_OBJECT
    UPROPERTY(Transient)
    UCustomizableSkeletalComponent* MutableComponent;
#else
    void* MutableComponent = nullptr;

#if WITH_EDITORONLY_DATA
    /** Print information about Mutable combinations to the screen for debugging.
     * Editor only. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Mutable",
        meta = (ToolTip = "If true, shows on-screen debug info about which meshes and materials were combined."))
    bool bDebugMutableCombination = false;
#endif

    /** Gather available mesh and material tags for editor drop-downs. */
    UFUNCTION(BlueprintCallable, Category = "PerfMngr|Mutable")
    TArray<FName> GetMutableTagOptions() const;

    /** Update a specific mesh slot and reapply the combined mesh. */
    UFUNCTION(BlueprintCallable, Category = "PerfMngr|Mutable")
    void UpdateMutableMeshSlot(FName SlotName, USkeletalMesh* NewMesh);

    /** Update a material slot and reapply the combined mesh. */
    UFUNCTION(BlueprintCallable, Category = "PerfMngr|Mutable")
    void UpdateMutableMaterialSlot(int32 MaterialIndex,
        UMaterialInterface* NewMaterial);

    /** Recombine current slots and apply to the character's mesh component. */
    UFUNCTION(BlueprintCallable, Category = "PerfMngr|Mutable")
    void ApplyMutableCombination();

protected:
    /** Cached previous significance from last evaluation. */
    float PreviousSignificance = 1.0f;

    // Billboard and Particle proxy state tracking
    EProxySwapState BillboardState = EProxySwapState::Active;
    EProxySwapState ParticleState = EProxySwapState::Active;
    float BillboardTimeInCurrentState = 0.0f;
    float ParticleTimeInCurrentState = 0.0f;

    FTimerHandle TickEvalTimerHandle;
    EProxySwapState ProxyState = EProxySwapState::Active;
    float ProxyTimeInCurrentState = 0.0f;
    float LastSignificance = 1.0f;

    /** Components currently suppressed and their rules (for restoring later). */
    TMap<UActorComponent*, FComponentSuppressionRule> SuppressedComponents;

    /** Dynamic materials we created while fading proxies/billboards, per mesh
     * component. */
    TMap<UMeshComponent*, TArray<UMaterialInstanceDynamic*>> CachedDynamicMats;

    /** Cached pointer to the owner's Ability System (if any). */
    UAbilitySystemComponent* CachedASC = nullptr;

    /** Only replicate state changes when significance crosses this threshold. */
    float ReplicationSignificanceThreshold = 0.25f;

    /** Current performance mode (Auto/Full/Proxy). */
    EPerformanceMode PerformanceMode = EPerformanceMode::Auto;

    // Billboard fade support: dynamic material instances for proxy and billboard
    // meshes

    /** Dynamic MIs used when fading out the proxy mesh during a billboard swap.
     */
    TArray<UMaterialInstanceDynamic*> ProxyFadeMaterials;

    /** Dynamic MIs used when fading in the billboard mesh during a billboard
     * swap. */
    TArray<UMaterialInstanceDynamic*> BillboardFadeMaterials;

    /** True while a billboard fade is in progress (prevents re-initialisation).
     */
    bool bBillboardFadeActive = false;

    // Helpers (internal use)
    /** Handles switching between full, proxy and billboard modes over time. */
    void HandleProxySwap(float DeltaTime, float Significance);
    /** Optional color tint for debug based on significance value. */
    void ApplyColorBySignificance(float Significance);
    /** Adjusts component and optional ASC tick intervals based on significance.
     */
    void UpdateTickBasedOnSignificance();
    /** Sets how often to evaluate significance. */
    void SetTickEvaluationRate(float NewRate);
    /** Sets a global significance threshold for this actor (advanced). */
    void SetSignificanceThreshold(float NewThreshold);
    /** Set performance mode (Auto/Full/Proxy). */
    void SetPerformanceMode(EPerformanceMode NewMode);
    /** Handles billboard enter/exit (and fade) based on significance. */
    void HandleBillboardProxySwap(float DeltaTime, float Significance);
    /** Handles particle proxy enter/exit based on significance. */
    void HandleParticleProxySwap(float DeltaTime, float Significance);
    /** Optionally merge all static mesh components into a single mesh. */
    void MergeStaticMeshes();
    /** Ensures only one visual representation is active at any time. */
    void EnsureSingleRepresentation();

#if WITH_CUSTOMIZABLE_OBJECT
    /** Attach and update the Mutable skeletal mesh when high detail is needed. */
    void ActivateMutable();
    /** Release Mutable resources and detach the component when not needed. */
    void DeactivateMutable();
#endif
};

#endif  // Auto-added to fix mismatch
