# Beginner-Friendly Code Comments Template

> **Purpose:** Standardized commenting style for DAI plugin codebase to make code accessible to Unreal Engine beginners while maintaining professional quality.

---

## Philosophy

**Target Audience:** Developers with 0-6 months Unreal C++ experience

**Goals:**
1. Explain Unreal-specific concepts without being condescending
2. Clarify architecture patterns (Components, Subsystems, DataAssets)
3. Surface "why" decisions, not just "what" the code does
4. Keep comments concise - don't over-explain basic C++

---

## Template Sections

### 1. File Header Comments

#### `.h` Header Files
```cpp
#pragma once

// This file is part of the DAI_[PluginName] plugin.
// Beginner-friendly note: [Brief architecture explanation for this file type]

#include "CoreMinimal.h"
// ... other includes
```

**Examples by File Type:**

**Components:**
```cpp
// This file is part of the DAI_MagGrab plugin.
// Beginner-friendly note: Components = add-on pieces for Actors. Subsystems = global helpers. Presets = reusable settings.
```

**Subsystems:**
```cpp
// This file is part of the DAI_Faction plugin.
// Beginner-friendly note: World Subsystems = per-level singletons. Game Instance Subsystems = persist across level loads.
```

**DataAssets:**
```cpp
// This file is part of the DAI_LoadDirector plugin.
// Beginner-friendly note: Data Assets = reusable configuration stored as .uasset files in Content Browser.
```

**Blueprint Function Libraries:**
```cpp
// This file is part of the DAI_Navigation plugin.
// Beginner-friendly note: Blueprint Function Libraries = static utility functions callable from Blueprints.
```

**Actor Components:**
```cpp
// This file is part of the DAI_AI plugin.
// Beginner-friendly note: Actor Components = modular behaviors attached to Actors. Tick = per-frame update.
```

#### `.cpp` Implementation Files
```cpp
// New to Unreal C++?
// - .h files declare types (what exists).
// - .cpp files define behavior (what they do).
// - UCLASS/UPROPERTY make things visible to the Editor/Blueprints.

#include "YourHeaderFile.h"
// ... other includes
```

**Alternative for advanced features:**
```cpp
// Advanced Unreal patterns used in this file:
// - Weak pointers (TWeakObjectPtr) prevent dangling references when objects are destroyed.
// - Delegates (DECLARE_DYNAMIC_MULTICAST) = event system for loose coupling.
// - Replication (UPROPERTY Replicated) = network synchronization for multiplayer.

#include "YourHeaderFile.h"
```

---

### 2. Class/Struct Comments

#### UCLASS Comments
```cpp
/**
 * [One-sentence summary of what this class does]
 * 
 * [Architecture context - where does this fit in the system?]
 * [Key responsibilities - what are the 2-3 main jobs?]
 * [Usage notes - how should developers interact with this?]
 */
UCLASS([specifiers])
class PLUGINNAME_API UYourClass : public UParentClass
{
    GENERATED_BODY()
    
    // ... implementation
};
```

**Example - Component:**
```cpp
/**
 * Magnetic attractor that pulls nearby compatible objects.
 * 
 * Add this component to actors that should attract pickups (e.g., player characters).
 * Configure Radius and Strength to control attraction behavior.
 * Use Presets for consistent settings across multiple attractors.
 * 
 * Works with: UDAI_MagneticAttractedComponent (on pickups) and UDAI_MagneticPickupSubsystem (global coordinator).
 */
UCLASS(ClassGroup = (MagGrab), meta = (BlueprintSpawnableComponent))
class DAI_MAGGRAB_API UDAI_MagneticAttractorComponent : public UActorComponent
{
    GENERATED_BODY()
    // ...
};
```

**Example - Subsystem:**
```cpp
/**
 * World subsystem coordinating all magnetic attraction interactions.
 * 
 * Automatically created once per level. Manages performance budgets, spatial optimization,
 * and pairing between attractors and attracted objects.
 * 
 * Access via: GetWorld()->GetSubsystem<UDAI_MagneticPickupSubsystem>()
 */
UCLASS(Config = Game, meta = (DisplayName = "MagGrab Pickup Subsystem"))
class DAI_MAGGRAB_API UDAI_MagneticPickupSubsystem : public UTickableWorldSubsystem
{
    GENERATED_BODY()
    // ...
};
```

#### USTRUCT Comments
```cpp
/**
 * [What data does this struct hold?]
 * [When/where is it used?]
 */
USTRUCT(BlueprintType)
struct PLUGINNAME_API FYourStruct
{
    GENERATED_BODY()
    // ...
};
```

**Example:**
```cpp
/**
 * Configuration for a single loading stage in a sequence.
 * Used by ULoadDirectorSequence to define ordered/parallel load operations.
 */
USTRUCT(BlueprintType)
struct FLoadDirectorSequenceRegion
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag Region;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAutoLoad = false;
};
```

#### UENUM Comments
```cpp
/**
 * [What choices does this enum represent?]
 */
UENUM(BlueprintType)
enum class EYourEnum : uint8
{
    Value1 UMETA(DisplayName = "Human Readable Name", ToolTip = "When to use this option"),
    Value2 UMETA(DisplayName = "...", ToolTip = "..."),
};
```

**Example:**
```cpp
/**
 * Movement style for magnetic attraction.
 */
UENUM(BlueprintType)
enum class EDAI_MagneticAttractorStyle : uint8
{
    Straight UMETA(DisplayName = "Straight", ToolTip = "Direct linear movement to attractor"),
    Spiral UMETA(DisplayName = "Spiral", ToolTip = "Helical motion around attraction vector"),
    Arc UMETA(DisplayName = "Arc", ToolTip = "Parabolic trajectory"),
    Ease UMETA(DisplayName = "Ease", ToolTip = "Smooth acceleration/deceleration"),
    Wobble UMETA(DisplayName = "Wobble", ToolTip = "Side-to-side oscillation during movement")
};
```

---

### 3. Property (UPROPERTY) Comments

#### Format
```cpp
// [What does this control?] [Typical values or constraints]
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CategoryName", 
    meta = (ToolTip = "Detailed explanation for Editor tooltip", 
            Keywords = "searchable editor terms"))
Type PropertyName;
```

#### Examples by Property Type

**Floats (Distances/Ranges):**
```cpp
// Maximum attraction distance in world units (cm). Objects beyond this range are ignored.
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnetic Attractor", 
    meta = (ClampMin = "0.0", ToolTip = "Maximum attraction distance in world units (cm)."))
float Radius = 500.f;
```

**Floats (Rates/Frequencies):**
```cpp
// How many times per second to evaluate attraction pairs. Higher = smoother but more CPU.
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance", 
    meta = (ClampMin = "1.0", ClampMax = "60.0", ToolTip = "Update frequency in Hz."))
float UpdateRateHz = 15.f;
```

**Integers (Counts/Limits):**
```cpp
// Maximum number of targets each attractor may pull simultaneously. Acts as performance budget.
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance", 
    meta = (ClampMin = "1", ClampMax = "32", ToolTip = "Max concurrent targets per attractor."))
int32 MaxTargetsPerAttractor = 4;
```

**Booleans (Toggles):**
```cpp
// Enable debug visualization in editor/PIE (shows attraction radius, vectors, stats).
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug", 
    meta = (ToolTip = "Show debug visuals and on-screen stats."))
bool bEnableDebug = false;
```

**Enums (Choices):**
```cpp
// Movement pattern for attracted objects (Straight = fastest, Spiral = most visually interesting).
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnetic Attractor", 
    meta = (ToolTip = "Visual style of attraction movement."))
EDAI_MagneticAttractorStyle Style = EDAI_MagneticAttractorStyle::Ease;
```

**Object References (Components/Actors):**
```cpp
// Primitive component to move when attracted; if unset, uses owner's root component.
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnetic Attracted", 
    meta = (ToolTip = "Target primitive for attraction force. Defaults to root if null."))
UPrimitiveComponent* TargetPrimitive;
```

**GameplayTags:**
```cpp
// Region identifier for load sequencing (e.g., Region.Map.Area1).
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadDirector", 
    meta = (Categories = "Region", ToolTip = "Gameplay tag identifying this region."))
FGameplayTag Region;
```

**DataAsset References:**
```cpp
// Preset containing reusable attractor settings. Apply with ApplyPreset().
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnetic Attractor", 
    meta = (ToolTip = "Preset data asset. Use ApplyPreset() to load values."))
UDAI_MagneticAttractorPreset* Preset;
```

---

### 4. Function Comments

#### Public API Functions
```cpp
/**
 * [One-line summary of what this function does]
 * 
 * @param ParamName [What this parameter controls and valid values]
 * @param ParamName2 [...]
 * @return [What the return value represents, or conditions for true/false]
 * 
 * [Usage notes, side effects, or important warnings]
 */
UFUNCTION(BlueprintCallable, Category = "CategoryName")
ReturnType FunctionName(Type ParamName, Type ParamName2);
```

**Example - Simple Query:**
```cpp
/**
 * Check if a region has been marked ready.
 * 
 * @param Region Gameplay tag identifying the region
 * @return True if LoadRegion() has been called for this tag
 */
UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LoadDirector")
bool IsRegionReady(const FGameplayTag& Region) const;
```

**Example - Action with Side Effects:**
```cpp
/**
 * Begin executing a load sequence, canceling any active sequence.
 * 
 * @param Sequence Data asset defining regions to load and their order
 * 
 * Fires OnSequenceProgress as regions complete. Use GetSequenceProgress() to poll.
 * Broadcasts OnSequenceCompleted when all regions are ready.
 */
UFUNCTION(BlueprintCallable, Category = "LoadDirector|Sequence")
void BeginSequence(ULoadDirectorSequence* Sequence);
```

**Example - Async/Callback Pattern:**
```cpp
/**
 * Execute callback when a region becomes ready (or immediately if already ready).
 * 
 * @param Region Tag to wait for
 * @param Callback Lambda or function to invoke on ready
 * 
 * If region is already loaded, callback fires synchronously.
 * Otherwise, callback is queued until LoadRegion() is called.
 */
void WhenReady(const FGameplayTag& Region, TFunction<void()> Callback);
```

#### Protected/Private Implementation Functions
```cpp
// [Brief explanation of internal logic]
// [Why this function exists - architectural reasoning]
void InternalHelperFunction();
```

**Example:**
```cpp
// Recomputes sequence progress (0-1) based on ready regions.
// Called after each LoadRegion() to update OnSequenceProgress delegate.
void RecomputeSequenceProgress();

// Applies current performance budgets (UpdateRateHz, MaxPairs) to timer.
// Invoked when settings change or FPS throttling kicks in.
void RestartStepTimer();
```

#### Override Functions (Virtual)
```cpp
// [What Unreal lifecycle event this responds to]
virtual void FunctionName() override;
```

**Example:**
```cpp
// Called when component registers with world (before BeginPlay).
// Registers this attractor with the global MagneticPickupSubsystem.
virtual void OnRegister() override;

// Called once per frame. Checks for nearby attracted objects within radius.
virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, 
                          FActorComponentTickFunction* ThisTickFunction) override;
```

---

### 5. Inline Code Comments

#### When to Use Inline Comments

**DO comment:**
- Non-obvious algorithms or math
- Unreal-specific patterns (weak pointers, delegates, replication)
- Performance optimizations
- Workarounds for engine quirks
- Critical safety checks

**DON'T comment:**
- Self-explanatory code (`i++; // increment i`)
- Obvious logic (`if (IsValid(Actor)) // check if actor is valid`)

#### Inline Comment Patterns

**Algorithm Explanation:**
```cpp
// Build candidate list using spatial grid for O(1) neighbor lookup.
// Falls back to full scan if grid disabled or actor count < threshold.
if (bUseGrid && ActiveAttracted.Num() > GridActivationThreshold)
{
    const FIntVector Center = GetCellForLocation(AttractorLocation);
    const int32 Range = FMath::CeilToInt(EffectiveRadius / GridCellSize);
    // Query 3x3x3 (or 3x3x1 for 2D) grid neighborhood
    for (int32 dx = -Range; dx <= Range; ++dx)
    {
        // ...
    }
}
```

**Unreal Pattern Explanation:**
```cpp
// TWeakObjectPtr prevents crashes if actor destroyed mid-frame.
// IsValid() checks both pointer validity and IsPendingKill flag.
for (TWeakObjectPtr<UDAI_MagneticAttractedComponent> AttractedPtr : ActiveAttracted)
{
    UDAI_MagneticAttractedComponent* Attracted = AttractedPtr.Get();
    if (!IsValid(Attracted)) continue;
    // ...
}
```

**Performance Note:**
```cpp
// Only recompute grid cells when actor count exceeds threshold (300+).
// Grid overhead outweighs benefits for small object counts.
if (ActiveAttracted.Num() > GridActivationThreshold)
{
    RebuildSpatialGrid();
}
```

**Network/Replication Note:**
```cpp
// Server authority: reset transient state each tick so clients receive fresh data.
// Prevents stale attraction states from previous frames persisting on clients.
if (HasAuthority())
{
    for (auto& Component : ActiveAttracted)
    {
        Component->State = EDAI_MagneticAttractedState::Inactive;
    }
}
```

**Safety/Edge Case:**
```cpp
// Prevent duplicate attractors on same actor (Blueprint double-add protection).
// Only register if no other attractor component exists on owner.
TArray<UActorComponent*> Comps;
Owner->GetComponents(Comps);
for (UActorComponent* C : Comps)
{
    if (C && C != this && C->IsA<UDAI_MagneticAttractorComponent>())
    {
        return; // Another attractor exists; skip registration
    }
}
```

---

### 6. Section Dividers

Use for logical grouping within large files:

```cpp
// ============================================================================
// Initialization & Lifecycle
// ============================================================================

void Initialize() { }
void Deinitialize() { }

// ============================================================================
// Registration & Tracking
// ============================================================================

void RegisterAttractor() { }
void UnregisterAttractor() { }

// ============================================================================
// Spatial Grid Operations
// ============================================================================

FIntVector GetCellForLocation() { }
void RebuildGrid() { }

// ============================================================================
// Debug & Visualization
// ============================================================================

void ShowDebugOverlay() { }
```

**Alternative style (more compact):**
```cpp
// ---------------- Initialization -----------------
void Initialize() { }

// ---------------- Update Loop -----------------
void Tick(float DeltaTime) { }

// ---------------- Public API -----------------
bool IsRegionReady() { }
```

---

### 7. TODO / FIXME / NOTE Comments

```cpp
// TODO: Add console command for runtime debugging (DAI.MagGrab.SetRadius <value>)
// FIXME: Spiral style needs phase reset on attractor switch to prevent visual pop
// NOTE: This optimization assumes flat terrain (2D grid); 3D grid available via bUse3DGrid
// OPTIMIZE: Cache AttractorLocation outside loop to avoid repeated GetActorLocation() calls
// HACK: Manual null check needed here - engine bug with component garbage collection (UE-12345)
```

---

## Complete File Examples

### Example 1: Simple Component Header

```cpp
#pragma once

// This file is part of the DAI_Faction plugin.
// Beginner-friendly note: Components = add-on pieces for Actors. Subsystems = global helpers. Presets = reusable settings.

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "FactionComponentMultiTag.generated.h"

class UFactionServiceSubsystem;

/**
 * Component enabling multi-faction membership for actors.
 * 
 * Add this to characters/NPCs to track faction relationships and reputation.
 * Supports multiple simultaneous faction memberships via GameplayTags.
 * 
 * Works with: UFactionServiceSubsystem (queries reputation, hostility checks).
 */
UCLASS(ClassGroup = (Faction), meta = (BlueprintSpawnableComponent))
class DAI_FACTION_API UFactionComponentMultiTag : public UActorComponent
{
    GENERATED_BODY()

public:
    UFactionComponentMultiTag();

    // Faction tags this actor belongs to (e.g., DAI.Faction.Type.Bandit, DAI.Faction.Type.Guild).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction", 
        meta = (Categories = "DAI.Faction.Type", ToolTip = "Faction memberships for this actor."))
    FGameplayTagContainer FactionTags;

    /**
     * Set faction tags, replacing all current memberships.
     * 
     * @param NewTags Container of faction tags to assign
     * 
     * Broadcasts OnFactionMembershipChanged event through subsystem.
     */
    UFUNCTION(BlueprintCallable, Category = "Faction")
    void SetFactionTags(const FGameplayTagContainer& NewTags);

protected:
    virtual void OnRegister() override;
    virtual void OnUnregister() override;
};
```

### Example 2: Simple Component Implementation

```cpp
// New to Unreal C++?
// - .h files declare types (what exists).
// - .cpp files define behavior (what they do).
// - UCLASS/UPROPERTY make things visible to the Editor/Blueprints.

#include "FactionComponentMultiTag.h"
#include "FactionServiceSubsystem.h"
#include "Engine/World.h"

UFactionComponentMultiTag::UFactionComponentMultiTag()
{
    PrimaryComponentTick.bCanEverTick = false; // No per-frame update needed
}

void UFactionComponentMultiTag::OnRegister()
{
    Super::OnRegister();

    // Register with global faction subsystem for relationship tracking
    if (UWorld* World = GetWorld())
    {
        if (UFactionServiceSubsystem* FactionSys = World->GetSubsystem<UFactionServiceSubsystem>())
        {
            FactionSys->RegisterFactionMember(this);
        }
    }
}

void UFactionComponentMultiTag::OnUnregister()
{
    // Clean up subsystem registration to prevent dangling references
    if (UWorld* World = GetWorld())
    {
        if (UFactionServiceSubsystem* FactionSys = World->GetSubsystem<UFactionServiceSubsystem>())
        {
            FactionSys->UnregisterFactionMember(this);
        }
    }

    Super::OnUnregister();
}

void UFactionComponentMultiTag::SetFactionTags(const FGameplayTagContainer& NewTags)
{
    FactionTags = NewTags;

    // Notify subsystem to update reputation caches and fire events
    if (UWorld* World = GetWorld())
    {
        if (UFactionServiceSubsystem* FactionSys = World->GetSubsystem<UFactionServiceSubsystem>())
        {
            FactionSys->OnFactionMembershipChanged.Broadcast(GetOwner(), NewTags);
        }
    }
}
```

---

## Style Guidelines

### Tone
- **Friendly but professional** - Explain without patronizing
- **Concise** - One sentence where possible, two max
- **Actionable** - Focus on "how to use" not "what it is"

### Terminology
- **Prefer Unreal terms:** "Actor" not "game object", "Component" not "script"
- **Define jargon once:** First use of "TWeakObjectPtr" gets explanation, later uses don't
- **Use examples:** "e.g., DAI.Faction.Type.Bandit" helps more than abstract descriptions

### Consistency
- **Always explain UCLASS specifiers** in header class comment
- **Always explain side effects** in function comments
- **Always note performance implications** for optimization code
- **Match existing plugin style** - DAI_MagGrab is the gold standard

---

## Applying to Existing Code

### Step 1: Audit Current Comments
- [ ] Does file header explain Unreal architecture concept?
- [ ] Does class comment explain "what, where, how"?
- [ ] Do properties have tooltips for Editor discoverability?
- [ ] Do functions explain side effects and usage patterns?

### Step 2: Prioritize High-Traffic Files
1. **Public headers** (.h files) - seen by users
2. **Blueprint function libraries** - directly called by designers
3. **Subsystems** - central to plugin architecture
4. **Complex algorithms** - non-obvious math/logic

### Step 3: Add Comments Incrementally
- Don't rewrite everything at once
- Add comments when:
  - Fixing bugs (explain the fix)
  - Adding features (document new code)
  - Onboarding new developers (capture questions they ask)

---

## Quick Reference Card

```cpp
// ============ FILE HEADERS ============
// .h: "This file is part of DAI_X. Beginner note: [architecture concept]"
// .cpp: "New to Unreal? .h = declare, .cpp = implement, UPROPERTY = visible"

// ============ CLASSES ============
/** [One-line summary] + [Context] + [Usage] + [Related types] */

// ============ PROPERTIES ============
// [What it does] [Typical range/values]
UPROPERTY(meta = (ToolTip = "Detailed editor explanation"))

// ============ FUNCTIONS ============
/** [Summary] + @param/@return + [Side effects/warnings] */

// ============ INLINE ============
// Comment when: algorithms, Unreal patterns, performance, safety, quirks
// Don't comment: obvious code, redundant info

// ============ SECTIONS ============
// ============================================================================
// Section Name
// ============================================================================
```

---

## Template Checklist

When adding comments to a new file, ensure:

- [ ] **File header** explains Unreal architecture concept for this file type
- [ ] **Class comment** covers: what, where (in architecture), how (to use), and related types
- [ ] **All UPROPERTY** have inline comments and ToolTip meta tags
- [ ] **Public UFUNCTION** have doc comments with @param/@return and usage notes
- [ ] **Complex algorithms** have inline explanation comments
- [ ] **Unreal-specific patterns** (weak ptrs, delegates, replication) are explained once
- [ ] **Performance code** notes optimization reasoning
- [ ] **Section dividers** used for files >200 lines
- [ ] **Tone is friendly** but professional (not condescending)
- [ ] **Terminology is consistent** with Unreal conventions

---

## Examples from DAI Codebase

**Best Examples to Study:**
1. `DAI_MagGrab` - Gold standard for beginner-friendly comments
2. `DAI_Faction` - Clean architecture documentation
3. `DAI_AI` - Complex system with clear inline explanations

**Before/After Comparison:**

**Before:**
```cpp
float Radius;
int32 MaxTargets;
void Step();
```

**After:**
```cpp
// Maximum attraction distance in world units (cm). Objects beyond this range are ignored.
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnetic Attractor", 
    meta = (ClampMin = "0.0", ToolTip = "Maximum attraction distance in world units (cm)."))
float Radius = 500.f;

// Maximum number of targets each attractor may pull simultaneously. Acts as performance budget.
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance", 
    meta = (ClampMin = "1", ClampMax = "32", ToolTip = "Max concurrent targets per attractor."))
int32 MaxTargets = 4;

// Evaluates attractor-attracted pairs up to performance budget (MaxPairsPerStep).
// Called via timer at UpdateRateHz frequency. Updates attraction states and applies forces.
void Step();
```

---

**Last Updated:** November 2, 2025  
**Based On:** DAI_MagGrab plugin commenting style (reference implementation)  
**Maintained By:** DAI Team
