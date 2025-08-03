#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DAI_PerfMngrComponent.generated.h"

// Forward declarations...
class UAbilitySystemComponent;
class UMaterialInstanceDynamic;
class UMaterialInterface;
class UStaticMesh;
class UStaticMeshComponent;
class UWidgetComponent;
class UNiagaraComponent;
class UGroomComponent;
class UDAI_ProxyHISMManager;
class UBehaviorTreeComponent;
class AAIController;

/**
 * @brief Component that automatically swaps an actor between "full" and "proxy" representations
 * based on how important (significant) the actor is to the player (usually how close it is).
 *
 * In plain English: this speeds things up by showing cheap stand‑ins (proxies) for far‑away actors
 * and the full, expensive version when the actor is close enough to matter.
 */
UENUM(BlueprintType)
enum class EProxySwapState : uint8
{
    /** Full, high‑quality representation is active. */
    Active,
    /** A proxy is about to be used, swap is pending. */
    PendingSwapToProxy,
    /** Proxy (cheap stand‑in) is currently active. */
    ProxyActive,
    /** Returning from proxy to full representation, swap is pending. */
    PendingSwapToFull
};

/**
 * @brief How the component should decide what to show.
 * Auto = pick for me. Full = always full quality. Proxy = always proxy.
 */
UENUM(BlueprintType)
enum class EPerformanceMode : uint8
{
    Auto,
    Full,
    Proxy
};

/**
 * @brief Types of components this system can temporarily turn off (suppress) when the actor
 * is unimportant (low significance).
 *
 * In plain English: what parts can we temporarily mute to save performance.
 */
UENUM(BlueprintType)
enum class ESuppressionComponentType : uint8
{
    Audio,
    Niagara,
    AbilitySystem,
    Light,
    Widget,
    MotionWarping,
    Hair,
    Physics,
    CustomTag
};

/**
 * @brief Rule describing which component(s) can be suppressed as significance drops.
 *
 * Layman’s terms: When the actor is far away (not important), these rules tell the system
 * which bits to switch off and when.
 */
USTRUCT(BlueprintType)
struct FComponentSuppressionRule
{
    GENERATED_BODY()

    /** What kind of component to affect (sound, VFX, hair, etc). */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suppression", meta = (ToolTip = "What type of component this rule affects (e.g., Audio, Niagara, Hair)."))
    ESuppressionComponentType ComponentType = ESuppressionComponentType::Audio;

    /** Only affect components with this tag. Leave blank to affect all of the chosen type. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suppression", meta = (ToolTip = "Optional filter: only components with this tag are affected. Leave empty to match all of the chosen type."))
    FName ComponentTag;

    /** Only affect components whose name contains this text (case‑insensitive). */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suppression", meta = (ToolTip = "Optional filter by name: only components with names containing this text are affected."))
    FString NameContains;

    /** If the actor’s significance drops below this value, suppress this component. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suppression", meta = (ClampMin = "0.0", ClampMax = "1.0", ToolTip = "When the actor’s significance is below this value (0..1), this component gets turned off to save performance."))
    float SuppressBelowSignificance = 0.4f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnProxyEnteredSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnProxyExitedSignature);

/**
 * @brief Main Performance Manager component. Add this to actors you want to auto‑optimize.
 *
 * It monitors the actor’s distance/importance and swaps meshes/effects to cheaper versions or
 * reduces tick rates to save frame time.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAI_PERFMNGR_API UDAI_PerfMngrComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDAI_PerfMngrComponent();

    // Component overrides...
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // Proxy management

    /** Swap to the proxy (cheap) representation when safe to do so. */
    UFUNCTION(BlueprintCallable, Category = "PerfMngr|Proxy", meta = (ToolTip = "Swap to the proxy (cheap) version of this actor when safe to do so."))
    void SwapToProxy();

    /** Swap back to the full (high‑quality) representation when safe to do so. */
    UFUNCTION(BlueprintCallable, Category = "PerfMngr|Proxy", meta = (ToolTip = "Swap back to the full (high‑quality) version of this actor when safe to do so."))
    void SwapToFull();

    /** Is the actor currently using a proxy? */
    UFUNCTION(BlueprintCallable, Category = "PerfMngr|Proxy", meta = (ToolTip = "Returns true if the actor is currently using a proxy representation."))
    bool IsUsingProxy() const;

    /** What is the current proxy swap state? */
    UFUNCTION(BlueprintCallable, Category = "PerfMngr|Proxy", meta = (ToolTip = "Gets the current proxy swap state (Active, ProxyActive, or pending states)."))
    EProxySwapState GetCurrentProxyState() const;

    /** Force an immediate swap to proxy (skips delays/safety checks). */
    UFUNCTION(BlueprintCallable, Category = "PerfMngr|Proxy", meta = (ToolTip = "Forces an immediate switch to the proxy version (ignores normal delays/safety checks)."))
    void ForceSwapToProxy();

    /** Force an immediate swap to full (skips delays/safety checks). */
    UFUNCTION(BlueprintCallable, Category = "PerfMngr|Proxy", meta = (ToolTip = "Forces an immediate switch back to the full version (ignores normal delays/safety checks)."))
    void ForceSwapToFull();

    // Configurables

    /** Max distance at which this actor is considered for full quality. Beyond this we prefer proxy/billboard. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr", meta = (ClampMin = "0.0", ToolTip = "How far from the player this actor can be before we prefer cheaper representations (proxies/billboards)."))
    float MaxDistance = 5000.0f;

    /** How often (seconds) to evaluate significance & state. Higher values = fewer checks. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr", meta = (ClampMin = "0.01", ToolTip = "How often (in seconds) to re-evaluate significance and choose proxy/full state. Higher = less CPU overhead."))
    float TickEvaluationRate = 1.0f;

    /** Fast tick when close/important (seconds between ticks). */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr", meta = (ClampMin = "0.0", ToolTip = "Tick interval to use when the actor is close or important (smaller = more updates, smoother behavior)."))
    float TickIntervalHigh = 0.02f;

    /** Slow tick when far/unimportant (seconds between ticks). */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr", meta = (ClampMin = "0.0", ToolTip = "Tick interval to use when the actor is far or unimportant (larger = fewer updates, better performance)."))
    float TickIntervalLow = 0.2f;

    /** Lower bound on tick interval clamping applied by this component. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr", meta = (ClampMin = "0.0", ToolTip = "Minimum allowed tick interval after clamping."))
    float MinTickClamp = 0.01f;

    /** Upper bound on tick interval clamping applied by this component. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr", meta = (ClampMin = "0.0", ToolTip = "Maximum allowed tick interval after clamping."))
    float MaxTickClamp = 1.0f;

    /** If true, also slow down the owner’s Ability System tick when insignificant. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr", meta = (ToolTip = "Also throttle the owner’s Ability System Component tick when significance is low."))
    bool bAffectAbilitySystemTick = false;

    /** Enable detailed logging to the Output Log. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Debug", meta = (ToolTip = "Print detailed debug information to the Output Log."))
    bool bEnableDebugLog = false;

    /** Print the current significance to screen each evaluation. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Debug", meta = (ToolTip = "Draw the actor’s current significance value on screen each time it’s evaluated."))
    bool bPrintSignificanceToScreen = false;

    /** Draw a debug sphere showing the proxy swap radius. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Debug", meta = (ToolTip = "Draw a sphere in the world to visualize the proxy/billboard swap radius."))
    bool bDrawDebugProxySphere = false;

    /** How long to keep the debug sphere visible. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Debug", meta = (ClampMin = "0.0", ToolTip = "How long (seconds) the debug sphere should remain on screen."))
    float ProxyDebugSphereDuration = 2.0f;

    /** Static mesh to use for the general proxy (cheap stand‑in) when enabled. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Proxy", meta = (ToolTip = "Mesh used as the actor’s cheap proxy representation when in proxy mode."))
    UStaticMesh* ProxyStaticMesh = nullptr;

    /**
     * Mesh used when swapping the owner's hair for a proxy representation.
     * Only spawned in proxy mode; hidden when leaving proxy.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Proxy|Hair", meta = (ToolTip = "Optional mesh to display as a cheap hair stand‑in while in proxy mode."))
    UStaticMesh* ProxyHairMesh = nullptr;

    /**
     * Mesh used for billboard proxies when significance is very low.
     * Added through HISM batching if enabled, otherwise spawned as a unique component.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Proxy|Billboard", meta = (ToolTip = "Billboard mesh used when significance is very low. Can be batched via HISM for large crowds."))
    UStaticMesh* ProxyBillboardMesh = nullptr;

    /** Niagara system used as a particle‑only proxy at very low significance. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Proxy|Particle", meta = (ToolTip = "Niagara effect to show when using a particle-only proxy representation."))
    class UNiagaraSystem* ProxyParticleEffect = nullptr;

    /**
     * Material used to fade between proxy and billboard during swaps.
     * Must contain a scalar parameter named "FadeAlpha".
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Proxy|Billboard", meta = (ToolTip = "Material with a 'FadeAlpha' parameter used to cross-fade between proxy and billboard."))
    class UMaterialInterface* BillboardFadeMaterial = nullptr;

    /** Duration (seconds) for billboard fade. 0 = instant swap. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Proxy|Billboard", meta = (ClampMin = 0.0f, ToolTip = "How long to cross-fade (in seconds) between proxy mesh and billboard. 0 = instant."))
    float BillboardFadeDuration = 0.2f;

    /** Tag applied to billboard proxies for filtering or selection. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Proxy|Billboard", meta = (ToolTip = "Component tag added to billboard proxy meshes (useful for filtering in gameplay logic)."))
    FName BillboardProxyTag = "Proxy_Billboard";

    /** Enter billboard mode below this significance. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Proxy|Billboard", meta = (ClampMin = "0.0", ClampMax = "1.0", ToolTip = "When significance is below this, show the billboard proxy."))
    float BillboardEnterThreshold = 0.15f;

    /** Leave billboard mode above this significance. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Proxy|Billboard", meta = (ClampMin = "0.0", ClampMax = "1.0", ToolTip = "When significance rises above this, hide the billboard proxy."))
    float BillboardExitThreshold = 0.25f;

    /** Tag applied to particle proxies for filtering or selection. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Proxy|Particle", meta = (ToolTip = "Component tag added to particle proxy components (useful for filtering in gameplay logic)."))
    FName ParticleProxyTag = "Proxy_Particle";

    /** Enter particle proxy mode below this significance. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Proxy|Particle", meta = (ClampMin = "0.0", ClampMax = "1.0", ToolTip = "When significance is below this, show the particle proxy."))
    float ParticleEnterThreshold = 0.1f;

    /** Leave particle proxy mode above this significance. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Proxy|Particle", meta = (ClampMin = "0.0", ClampMax = "1.0", ToolTip = "When significance rises above this, hide the particle proxy."))
    float ParticleExitThreshold = 0.2f;

    /** Optional tag added to any spawned hair proxy mesh for easy identification. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Proxy|Hair", meta = (ToolTip = "Optional tag assigned to hair proxy meshes so you can find/manipulate them later."))
    FName HairProxyTag = "Proxy_Hair";

    /** Optional category label for grouping in significance logic. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Proxy", meta = (ToolTip = "Optional category name used by significance systems to group similar actors."))
    FName Category;

    /** If true, tint meshes by significance value for easy visual debugging. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Proxy", meta = (ToolTip = "Colorize meshes by their significance value (debug/visualization)."))
    bool bColorizeBySignificance = false;

    /** Rules that decide which components to temporarily turn off at low significance. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Suppression", meta = (ToolTip = "List of suppression rules. Each rule can turn off a type of component when significance is low."))
    TArray<FComponentSuppressionRule> ComponentSuppressionRules;

    /** Enter proxy mode below this significance. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Proxy", meta = (ClampMin = "0.0", ClampMax = "1.0", ToolTip = "When significance is below this, swap to the proxy representation."))
    float ProxyEnterThreshold = 0.2f;

    /** Return to full mode above this significance. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Proxy", meta = (ClampMin = "0.0", ClampMax = "1.0", ToolTip = "When significance rises above this, swap back to full representation."))
    float ProxyExitThreshold = 0.3f;

    /** Delay between detecting a threshold and performing the visual swap (seconds). */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Proxy", meta = (ClampMin = "0.0", ToolTip = "Grace period before a swap actually happens. Helps avoid flicker when value bounces around."))
    float ProxySwapDelay = 0.2f;

    // HISM batching variables

    /** Add proxies to HISM batches to reduce draw calls for large crowds. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Proxy", meta = (ToolTip = "Enable Hierarchical Instanced Static Mesh (HISM) batching for proxies to reduce draw calls."))
    bool bUseHISMProxyBatching = true;

    /** How many instances to add to each HISM per tick. Lower to reduce hitching; raise to fill faster. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|Proxy", meta = (EditCondition = "bUseHISMProxyBatching", ClampMin = 1, ClampMax = 1000, UIMin = 1, UIMax = 200, ToolTip = "Number of proxy instances to add to each HISM per tick (throttles mass adds)."))
    int32 ProxyBatchAddSize = 50;

    // AI suppression

    /** If true, allows AI to be slowed or paused when actor is not significant. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|AI", meta = (ToolTip = "Allow AI logic (BT/Perception/etc.) to be throttled when this actor is far away and not important."))
    bool bAllowAIThrottling = true;

    /** Below this significance, put AI into a deep sleep to save CPU. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerfMngr|AI", meta = (EditCondition = "bAllowAIThrottling", ClampMin = 0.0, ClampMax = 1.0, ToolTip = "When significance is below this, heavily throttle or pause AI."))
    float AIDeepFreezeSignificance = 0.05f;

    // — Runtime/Transient state (not exposed) —
    bool bHasHISMInstance = false;
    FName ProxyHISMTag;
    FTransform ProxyHISMTransform;
    int32 ProxyHISMInstanceIndex = INDEX_NONE;

    // Proxy components created at runtime
    UPROPERTY(Transient) UStaticMeshComponent* ProxyMeshComponent = nullptr;
    UPROPERTY(Transient) UStaticMeshComponent* ProxyHairMeshComponent = nullptr;
    UPROPERTY(Transient) UStaticMeshComponent* BillboardMeshComponent = nullptr;
    UPROPERTY(Transient) UNiagaraComponent* ProxyEffectComponent = nullptr;

    // Events (Blueprint assignable)
    UPROPERTY(BlueprintAssignable, meta = (ToolTip = "Event fired when the actor enters proxy mode."))
    FOnProxyEnteredSignature OnProxyEntered;
    UPROPERTY(BlueprintAssignable, meta = (ToolTip = "Event fired when the actor exits proxy mode (back to full)."))
    FOnProxyExitedSignature  OnProxyExited;

protected:
    /** Cached previous significance from last evaluation. */
    float PreviousSignificance = 1.0f;

    // Billboard and Particle proxy state tracking
    EProxySwapState BillboardState = EProxySwapState::Active;
    EProxySwapState ParticleState = EProxySwapState::Active;
    float BillboardTimeInCurrentState = 0.0f;
    float ParticleTimeInCurrentState = 0.0f;

    FTimerHandle   TickEvalTimerHandle;
    EProxySwapState ProxyState = EProxySwapState::Active;
    float          ProxyTimeInCurrentState = 0.0f;
    float          LastSignificance = 1.0f;

    /** Components currently suppressed and their rules (for restoring later). */
    TMap<UActorComponent*, FComponentSuppressionRule>                     SuppressedComponents;

    /** Dynamic materials we created while fading proxies/billboards, per mesh component. */
    TMap<UMeshComponent*, TArray<UMaterialInstanceDynamic*>>               CachedDynamicMats;

    /** Cached pointer to the owner's Ability System (if any). */
    UAbilitySystemComponent* CachedASC = nullptr;

    /** Only replicate state changes when significance crosses this threshold. */
    float ReplicationSignificanceThreshold = 0.25f;

    /** Current performance mode (Auto/Full/Proxy). */
    EPerformanceMode PerformanceMode = EPerformanceMode::Auto;

    // Billboard fade support: dynamic material instances for proxy and billboard meshes

    /** Dynamic MIs used when fading out the proxy mesh during a billboard swap. */
    TArray<UMaterialInstanceDynamic*> ProxyFadeMaterials;

    /** Dynamic MIs used when fading in the billboard mesh during a billboard swap. */
    TArray<UMaterialInstanceDynamic*> BillboardFadeMaterials;

    /** True while a billboard fade is in progress (prevents re-initialisation). */
    bool bBillboardFadeActive = false;

    // Helpers (internal use)
    /** Handles switching between full, proxy and billboard modes over time. */
    void HandleProxySwap(float DeltaTime, float Significance);
    /** Optional color tint for debug based on significance value. */
    void ApplyColorBySignificance(float Significance);
    /** Adjusts component and optional ASC tick intervals based on significance. */
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
    /** Ensures only one visual representation is active at any time. */
    void EnsureSingleRepresentation();
};
