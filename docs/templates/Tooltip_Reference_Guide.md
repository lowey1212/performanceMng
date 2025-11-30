# Unreal Engine Tooltip Reference Guide

**Purpose:** Comprehensive guide for writing clear, consistent, and beginner-friendly tooltips across all DAI plugins.

**Last Updated:** November 2, 2025

---

## Table of Contents

1. [Overview](#overview)
2. [Tooltip Principles](#tooltip-principles)
3. [Class Tooltips](#class-tooltips)
4. [Property Tooltips](#property-tooltips)
5. [Function Tooltips](#function-tooltips)
6. [Enum Tooltips](#enum-tooltips)
7. [Struct Tooltips](#struct-tooltips)
8. [Meta Keywords](#meta-keywords)
9. [Common Patterns](#common-patterns)
10. [Examples by Plugin Type](#examples-by-plugin-type)
11. [Quality Checklist](#quality-checklist)

---

## Overview

Tooltips appear when users hover over properties, functions, and classes in the Unreal Editor and Blueprint editor. They are the **primary documentation** users see while working, making them critical for usability.

### Why Tooltips Matter

- **First Point of Contact:** Users see tooltips before reading any external documentation
- **Context-Sensitive Help:** Appears exactly when and where users need it
- **Workflow Integration:** Reduces context-switching between editor and documentation
- **Blueprint Discoverability:** Makes your systems more accessible to Blueprint users

### Tooltip vs. Comment

| **Tooltip** | **Code Comment** |
|------------|------------------|
| User-facing (editor/Blueprint) | Developer-facing (source code) |
| Concise (1-3 sentences) | Can be detailed/technical |
| Explains **what** and **how to use** | Explains **why** and **how it works** |
| Always required for exposed members | Optional for internal implementation |

---

## Tooltip Principles

### 1. **Be Concise Yet Complete**

**Good:** "Radius around this actor where attraction applies (world units)."

**Too Verbose:** "This property defines the maximum distance in world space units (typically centimeters in UE5) within which the magnetic attraction force will be applied to eligible actors that have the attracted component attached."

**Too Brief:** "Attraction radius." (Missing units and context)

### 2. **Start with What It Does**

Begin with the action or purpose, not implementation details.

**Good:** "Spawns enemies in waves based on difficulty curve."

**Bad:** "Calls SpawnWaveInternal() on a timer with randomized delays."

### 3. **Include Units and Ranges**

Always specify units for numeric values.

**Good:** 
- "Maximum health (hit points, 1-1000)."
- "Delay before activation (seconds)."
- "Movement speed multiplier (0.0 = stopped, 1.0 = normal, 2.0 = double)."

### 4. **Explain When to Use It**

For bool flags and complex options, explain the use case.

**Good:** "Enable physics simulation for attracted objects. Disable for kinematic-only attraction."

**Bad:** "Physics enabled flag."

### 5. **Use Consistent Terminology**

Match UE5 terminology and your plugin's vocabulary:
- "Actor" not "object" (when referring to AActor)
- "Component" not "module" or "part"
- "World units" for distance (typically cm in UE5)
- "Hit points" for health values
- "Seconds" not "time" for duration

### 6. **Avoid Redundancy**

Don't just restate the property name.

**Bad:** "The radius value." (for property named `Radius`)

**Good:** "Maximum distance for attraction effect (world units)."

---

## Class Tooltips

Class tooltips should answer: **What is this?** and **When would I use it?**

### Component Classes

```cpp
UCLASS(ClassGroup = (Navigation), 
       meta = (BlueprintSpawnableComponent,
               DisplayName = "DAI Navigation Component",
               ToolTip = "Enables AI pathfinding with support for dynamic obstacles, jump links, and NavMesh queries. Add to pawns that need intelligent navigation.",
               Keywords = "navigation pathfinding AI movement navmesh obstacle avoidance"))
class UDAI_NavigationComponent : public UActorComponent
```

**Template:**
```
"[Primary capability]. [Key features]. [Where to attach/use]."
```

### Subsystem Classes

```cpp
UCLASS(meta = (DisplayName = "Quest Manager Subsystem",
               ToolTip = "World subsystem managing quest progression, objectives, and rewards. Automatically tracks quest state and broadcasts events.",
               Keywords = "quest objective mission task progression manager"))
class UDAI_QuestManagerSubsystem : public UWorldSubsystem
```

**Template:**
```
"[Subsystem type] managing [domain]. [Key responsibilities]."
```

### Data Asset Classes

```cpp
UCLASS(BlueprintType, 
       meta = (DisplayName = "Weather Biome Data",
               ToolTip = "Defines weather patterns, transitions, and parameters for a biome region. Create one asset per biome type (desert, forest, tundra, etc).",
               Keywords = "weather biome climate environment data asset"))
class UDAI_BiomeData : public UDataAsset
```

**Template:**
```
"Defines [what configuration]. [Usage instructions]. [Examples]."
```

### Actor Classes

```cpp
UCLASS(meta = (DisplayName = "Smart Object Actor",
               ToolTip = "Interactive object that AI and players can use with context-specific actions (sit, open, activate). Place in level and configure available interactions.",
               Keywords = "interaction smart object usable interactable AI"))
class ADAI_SmartObjectActor : public AActor
```

**Template:**
```
"[Actor purpose] that [capabilities]. [Placement/usage instructions]."
```

### Settings Classes

```cpp
UCLASS(Config = Game, DefaultConfig,
       meta = (DisplayName = "DAI Navigation Settings",
               ToolTip = "Project-level defaults for navigation system behavior, performance budgets, and debug visualization.",
               Keywords = "settings navigation config project defaults"))
class UDAI_NavigationSettings : public UDeveloperSettings
```

**Template:**
```
"Project-level defaults for [system]. [What can be configured]."
```

---

## Property Tooltips

Property tooltips should answer: **What does this control?** and **What values make sense?**

### Numeric Properties

Always include units and ranges when applicable.

```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attraction",
          meta = (ClampMin = "0.0", ClampMax = "10000.0",
                  ToolTip = "Maximum distance for magnetic attraction (world units, 0-10000).",
                  Keywords = "radius range distance"))
float Radius = 500.0f;

UPROPERTY(EditAnywhere, Category = "Performance",
          meta = (ClampMin = "0.1", ClampMax = "60.0",
                  ToolTip = "Updates per second (0.1 = every 10s, 60 = every frame).",
                  Keywords = "update rate frequency hz tick"))
float UpdateRateHz = 10.0f;

UPROPERTY(EditAnywhere, Category = "Health",
          meta = (ClampMin = "1", ClampMax = "1000",
                  ToolTip = "Maximum hit points. Characters die when health reaches zero.",
                  Keywords = "health hp hitpoints max maximum"))
int32 MaxHealth = 100;
```

**Templates:**

- **Distance:** "[Purpose] (world units, [range])."
- **Time:** "[Purpose] (seconds, [range])."
- **Rate:** "[Purpose] (updates per second, [range])."
- **Multiplier:** "[Purpose] (0.0 = [min meaning], 1.0 = [normal], 2.0 = [max meaning])."
- **Count:** "[Purpose]. Maximum of [N] [things]."

### Boolean Properties

Explain what happens when true/false, not just what the flag means.

```cpp
UPROPERTY(EditAnywhere, Category = "Physics",
          meta = (ToolTip = "Allow attraction while simulating physics. Disable for kinematic-only movement.",
                  Keywords = "physics simulation dynamic kinematic"))
bool bAllowPhysics = true;

UPROPERTY(EditAnywhere, Category = "Debug",
          meta = (ToolTip = "Draw debug spheres in editor/PIE. Use to visualize attraction radius.",
                  Keywords = "debug visualization sphere editor"))
bool bShowDebugSpheres = false;

UPROPERTY(EditAnywhere, Category = "Filtering",
          meta = (ToolTip = "Require matching GameplayTags before applying effect. Disable to affect all targets.",
                  Keywords = "filter tags gameplaytags required gating"))
bool bUseTagFiltering = false;
```

**Templates:**

- **Enable/Disable:** "[What it enables]. [When to enable/disable]."
- **Debug Flags:** "[What it visualizes]. Use to [debug purpose]."
- **Filtering:** "[What it requires]. Disable to [alternative behavior]."

### Enum Properties

Explain what the different options mean or link to enum.

```cpp
UPROPERTY(EditAnywhere, Category = "Movement",
          meta = (ToolTip = "Movement style toward attractor (affects path shape and feel).",
                  Keywords = "style movement curve path"))
EDAI_MagneticAttractorStyle Style = EDAI_MagneticAttractorStyle::Straight;

UPROPERTY(EditAnywhere, Category = "AI",
          meta = (ToolTip = "Behavior when target is lost (Continue, Stop, Return Home).",
                  Keywords = "lost target behavior fallback"))
EAILostTargetBehavior LostTargetBehavior;
```

**Template:**
```
"[What it controls] ([list key options if short])."
```

### Object Reference Properties

Explain what should be assigned and what happens if null.

```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup",
          meta = (ToolTip = "Primitive to move when attracted. If unset, uses owner's root component.",
                  Keywords = "target primitive mesh component"))
UPrimitiveComponent* TargetPrimitive = nullptr;

UPROPERTY(EditAnywhere, Category = "Weather",
          meta = (ToolTip = "Biome data asset defining weather patterns. Required for weather system to function.",
                  AllowedClasses = "/Script/DAI_UltraSky.DAI_BiomeData",
                  Keywords = "biome weather data asset"))
UDAI_BiomeData* BiomeData = nullptr;

UPROPERTY(EditAnywhere, Category = "Animation",
          meta = (ToolTip = "Optional curve adjusting strength over distance. Leave empty for linear falloff.",
                  Keywords = "curve falloff distance optional"))
UCurveFloat* StrengthCurve = nullptr;
```

**Templates:**

- **Required:** "[What to assign]. Required for [system] to function."
- **Optional:** "Optional [purpose]. Leave empty for [default behavior]."
- **Auto-assigned:** "[What to assign]. If unset, uses [fallback]."

### Array Properties

Explain what elements represent and typical count.

```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning",
          meta = (ToolTip = "Enemy types to spawn in this wave. Empty array skips spawning.",
                  Keywords = "spawn enemies wave types"))
TArray<TSubclassOf<AActor>> EnemyClasses;

UPROPERTY(EditAnywhere, Category = "Navigation",
          meta = (ToolTip = "Valid navigation points for AI. Auto-populated at runtime if empty.",
                  Keywords = "waypoints navigation points AI"))
TArray<FVector> WaypointLocations;
```

**Template:**
```
"[What elements are]. [What happens if empty]."
```

### Replicated Properties

Mention replication for multiplayer-relevant properties.

```cpp
UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "State",
          meta = (ToolTip = "Current attraction state (replicated for multiplayer).",
                  Keywords = "state replicated network multiplayer"))
EDAI_MagneticAttractedState State;

UPROPERTY(ReplicatedUsing = OnRep_Health, Category = "Health",
          meta = (ToolTip = "Current hit points (replicated, triggers OnRep_Health on clients).",
                  Keywords = "health hp replicated network"))
int32 CurrentHealth;
```

**Template:**
```
"[What it represents] (replicated [additional details])."
```

---

## Function Tooltips

Function tooltips should answer: **What does this do?** and **When would I call it?**

### Blueprint Callable Functions

```cpp
UFUNCTION(BlueprintCallable, Category = "Magnetic Attractor",
          meta = (ToolTip = "Apply preset values to this component. Call after spawning to configure from data asset.",
                  Keywords = "preset apply configure setup"))
void ApplyPreset(UDAI_MagneticAttractorPreset* Preset);

UFUNCTION(BlueprintCallable, Category = "Quest",
          meta = (ToolTip = "Start a new quest by name. Returns false if quest already active or not found.",
                  Keywords = "quest start begin activate"))
bool StartQuest(FName QuestID);

UFUNCTION(BlueprintPure, Category = "Navigation",
          meta = (ToolTip = "Check if path exists from start to goal. Does not modify state (pure function).",
                  Keywords = "pathfinding valid path exists reachable"))
bool CanReachLocation(FVector Start, FVector Goal) const;
```

**Templates:**

- **Actions:** "[What it does]. Call [when/where]."
- **Queries:** "[What it checks/returns]. Does not modify state (pure function)."
- **Setters:** "Set [property/state] to [value]. [Side effects if any]."

### Event Functions

```cpp
UFUNCTION(BlueprintImplementableEvent, Category = "Events",
          meta = (ToolTip = "Called when actor is grabbed by magnet. Implement in Blueprint to add custom behavior.",
                  Keywords = "event grabbed magnet blueprint"))
void OnGrabbed(AActor* Attractor);

UFUNCTION(BlueprintNativeEvent, Category = "Quest",
          meta = (ToolTip = "Called when quest objective completes. Override in Blueprint or C++ to add rewards/feedback.",
                  Keywords = "event objective complete quest"))
void OnObjectiveCompleted(FName ObjectiveID);
```

**Template:**
```
"Called when [event trigger]. [Override/Implement] in Blueprint to [purpose]."
```

---

## Enum Tooltips

### Enum Type Tooltip

```cpp
UENUM(BlueprintType, meta = (ToolTip = "Movement style for magnetic attraction path."))
enum class EDAI_MagneticAttractorStyle : uint8
{
    Straight UMETA(DisplayName = "Straight Line"),
    Spiral UMETA(DisplayName = "Spiral Path"),
    Arc UMETA(DisplayName = "Arcing Path"),
    Ease UMETA(DisplayName = "Smooth Ease"),
    Wobble UMETA(DisplayName = "Wobbling Path")
};
```

### Enum Value DisplayNames

Always provide DisplayName for better editor presentation:

```cpp
UENUM(BlueprintType)
enum class EDAI_QuestState : uint8
{
    NotStarted UMETA(DisplayName = "Not Started"),
    InProgress UMETA(DisplayName = "In Progress"),
    Completed UMETA(DisplayName = "Completed"),
    Failed UMETA(DisplayName = "Failed")
};
```

**Guidelines:**

- Use proper capitalization and spacing
- Make it readable in dropdowns
- Keep it concise (2-3 words max)
- Match terminology users expect

---

## Struct Tooltips

### Struct Type

```cpp
USTRUCT(BlueprintType, 
        meta = (ToolTip = "Defines a quest objective with completion criteria and rewards.",
                Keywords = "quest objective task mission"))
struct FDAIQuestObjective
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite,
              meta = (ToolTip = "Unique identifier for this objective.",
                      Keywords = "id name identifier"))
    FName ObjectiveID;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite,
              meta = (ToolTip = "Description shown to player in quest log.",
                      Keywords = "description text player"))
    FText Description;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite,
              meta = (ClampMin = "1",
                      ToolTip = "Number of times task must be completed (1 = once, 3 = collect 3 items).",
                      Keywords = "count required amount target"))
    int32 RequiredCount = 1;
};
```

---

## Meta Keywords

Keywords improve searchability in the editor's search/filter boxes.

### When to Add Keywords

- **Always:** On classes, structs, enums
- **Often:** On complex properties, key functions
- **Rarely:** On simple/obvious properties (booleans, common names)

### Keyword Guidelines

```cpp
meta = (ToolTip = "...",
        Keywords = "word1 word2 phrase word3")
```

**Good Keywords:**
- Synonyms: "hp health hitpoints"
- Related concepts: "spawn create instantiate summon"
- System names: "GAS gameplay ability system attributes"
- Common misspellings: "navmesh nav-mesh navigation"
- Use cases: "debug visualization editor PIE"

**Bad Keywords:**
- Don't repeat words from the tooltip
- Don't use generic terms like "property" or "value"
- Don't include special characters unnecessarily

### Keyword Examples by System

**Navigation:**
```cpp
Keywords = "navigation pathfinding AI movement navmesh obstacle avoidance waypoint"
```

**GAS (Gameplay Ability System):**
```cpp
Keywords = "GAS gameplay ability system attribute effect modifier tags"
```

**Spawning:**
```cpp
Keywords = "spawn create instantiate summon pool actor enemy"
```

**Weather:**
```cpp
Keywords = "weather climate biome environment rain snow temperature"
```

**Quests:**
```cpp
Keywords = "quest objective mission task progression achievement"
```

---

## Common Patterns

### Performance Properties

```cpp
UPROPERTY(EditAnywhere, Category = "Performance",
          meta = (ClampMin = "1", ClampMax = "100",
                  ToolTip = "Maximum evaluations per frame (budget). Lower values improve performance but reduce responsiveness.",
                  Keywords = "performance budget throttle limit optimization"))
int32 MaxOperationsPerFrame = 50;
```

### Debug Visualization

```cpp
UPROPERTY(EditAnywhere, Category = "Debug",
          meta = (ToolTip = "Draw debug spheres in editor/PIE. Green = active, Red = inactive, Blue = transitioning.",
                  Keywords = "debug visualization sphere color editor PIE"))
bool bShowDebugSpheres = false;
```

### GameplayTag Properties

```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags",
          meta = (ToolTip = "Required tags for activation. Must have at least one matching tag to proceed.",
                  Categories = "GameplayTag.Activation",
                  Keywords = "tags gameplaytags filter required GAS activation"))
FGameplayTagContainer RequiredTags;
```

### Optional Overrides

```cpp
UPROPERTY(EditAnywhere, Category = "Advanced",
          meta = (EditCondition = "bOverrideDefaults",
                  ToolTip = "Custom spawn height. Only used when Override Defaults is enabled.",
                  Keywords = "override custom height spawn"))
float CustomSpawnHeight = 100.0f;

UPROPERTY(EditAnywhere, Category = "Advanced",
          meta = (InlineEditConditionToggle,
                  ToolTip = "Enable to use custom spawn settings instead of defaults."))
bool bOverrideDefaults = false;
```

### Curve Properties

```cpp
UPROPERTY(EditAnywhere, Category = "Curves",
          meta = (ToolTip = "Strength multiplier over distance (X=0 at center, X=1 at radius edge). Leave empty for linear falloff.",
                  XAxisName = "Distance Normalized",
                  YAxisName = "Strength Multiplier",
                  Keywords = "curve falloff distance strength optional"))
UCurveFloat* StrengthDistanceCurve = nullptr;
```

---

## Examples by Plugin Type

### AI/Navigation Plugin

```cpp
UCLASS(ClassGroup = (AI), 
       meta = (BlueprintSpawnableComponent,
               DisplayName = "DAI Navigation Component",
               ToolTip = "Handles AI pathfinding with dynamic obstacles, jump links, and NavMesh queries. Add to pawns requiring intelligent movement.",
               Keywords = "navigation pathfinding AI movement navmesh obstacle"))
class UDAI_NavigationComponent : public UActorComponent
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, Category = "Navigation",
              meta = (ClampMin = "10.0", ClampMax = "1000.0",
                      ToolTip = "Acceptable distance from goal to consider path complete (world units, 10-1000).",
                      Keywords = "threshold distance goal complete tolerance"))
    float AcceptanceRadius = 50.0f;
    
    UPROPERTY(EditAnywhere, Category = "Performance",
              meta = (ToolTip = "Update path every N frames. Higher values improve performance but reduce accuracy.",
                      Keywords = "performance optimization update interval"))
    int32 PathUpdateInterval = 10;
};
```

### Gameplay Ability System Plugin

```cpp
UCLASS(meta = (DisplayName = "DAI Attribute Set",
               ToolTip = "Base attributes for GAS including health, stamina, and damage modifiers."))
class UDAI_AttributeSet : public UAttributeSet
{
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadOnly, Category = "Attributes", 
              ReplicatedUsing = OnRep_Health,
              meta = (ToolTip = "Current hit points (0-MaxHealth). Character dies when reaching zero.",
                      Keywords = "health hp hitpoints current"))
    FGameplayAttributeData Health;
    
    UPROPERTY(BlueprintReadOnly, Category = "Attributes",
              meta = (ToolTip = "Maximum possible hit points. Regeneration cannot exceed this value.",
                      Keywords = "health max maximum limit cap"))
    FGameplayAttributeData MaxHealth;
};
```

### Weather/Environment Plugin

```cpp
UCLASS(BlueprintType,
       meta = (DisplayName = "Weather Biome Data",
               ToolTip = "Defines weather patterns, intensity curves, and transition rules for a biome. Create one per biome type.",
               Keywords = "weather biome climate environment data"))
class UDAI_BiomeData : public UDataAsset
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, Category = "Weather",
              meta = (ToolTip = "Precipitation intensity (0.0 = none, 0.5 = moderate, 1.0 = heavy storm).",
                      ClampMin = "0.0", ClampMax = "1.0",
                      Keywords = "rain snow precipitation intensity"))
    float PrecipitationIntensity = 0.0f;
    
    UPROPERTY(EditAnywhere, Category = "Transitions",
              meta = (ToolTip = "Time to blend from previous weather (seconds, 0-600).",
                      ClampMin = "0.0", ClampMax = "600.0",
                      Keywords = "transition blend fade duration time"))
    float TransitionDuration = 30.0f;
};
```

### Spawning/Pool Plugin

```cpp
UCLASS(meta = (DisplayName = "DAI Spawner Component",
               ToolTip = "Spawns actors with pooling, wave support, and performance budgets. Attach to spawn point actors.",
               Keywords = "spawn pool wave enemy performance"))
class UDAI_SpawnerComponent : public UActorComponent
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, Category = "Spawning",
              meta = (ToolTip = "Actor classes to spawn. Randomly selected if multiple entries provided.",
                      AllowedClasses = "Actor",
                      Keywords = "spawn actors classes types random"))
    TArray<TSubclassOf<AActor>> SpawnClasses;
    
    UPROPERTY(EditAnywhere, Category = "Waves",
              meta = (ClampMin = "1",
                      ToolTip = "Enemies per wave. Each wave spawns this many actors (1-100).",
                      Keywords = "wave count amount enemies"))
    int32 EnemiesPerWave = 5;
};
```

---

## Quality Checklist

Use this checklist when reviewing tooltips:

### ✅ All Classes

- [ ] Class has `ToolTip` in meta specifier
- [ ] Tooltip explains what the class does
- [ ] Tooltip explains when/where to use it
- [ ] `DisplayName` is user-friendly (if applicable)
- [ ] `Keywords` include synonyms and related terms

### ✅ All UPROPERTY

- [ ] Property has `ToolTip` in meta specifier
- [ ] Tooltip explains what it controls (not just restates name)
- [ ] Numeric properties include units and ranges
- [ ] Boolean properties explain true/false behavior
- [ ] Object references explain what to assign
- [ ] Replicated properties mention replication
- [ ] Keywords added for complex/searchable properties

### ✅ All UFUNCTION

- [ ] BlueprintCallable functions have `ToolTip`
- [ ] Tooltip explains what function does
- [ ] Tooltip explains when to call it
- [ ] Pure functions mention they don't modify state
- [ ] Event functions explain when they fire

### ✅ All UENUM

- [ ] Enum type has `ToolTip` explaining purpose
- [ ] Each value has `DisplayName` with proper capitalization
- [ ] DisplayNames are readable in dropdowns

### ✅ All USTRUCT

- [ ] Struct has `ToolTip` explaining what it represents
- [ ] Struct properties follow same rules as UPROPERTY

### ✅ Consistency

- [ ] Terminology matches UE5 conventions
- [ ] Units are consistent (world units, seconds, hit points)
- [ ] Style matches other tooltips in the plugin
- [ ] Keywords don't duplicate tooltip text unnecessarily

---

## Quick Reference: Meta Specifier Keywords

### Common Meta Specifiers with Tooltips

```cpp
// Basic tooltip
meta = (ToolTip = "Description here.")

// With keywords for search
meta = (ToolTip = "...", Keywords = "word1 word2 word3")

// Numeric clamping
meta = (ClampMin = "0.0", ClampMax = "100.0", ToolTip = "...")

// Edit conditions
meta = (EditCondition = "bSomeFlag", ToolTip = "...")

// Inline edit condition toggle
meta = (InlineEditConditionToggle, ToolTip = "...")

// Allowed classes for object properties
meta = (AllowedClasses = "Actor", ToolTip = "...")

// GameplayTag categories
meta = (Categories = "GameplayTag.Root", ToolTip = "...")

// Curve axis names
meta = (XAxisName = "Time", YAxisName = "Value", ToolTip = "...")

// Class display name
meta = (DisplayName = "Friendly Name", ToolTip = "...")

// Blueprint spawnable component
meta = (BlueprintSpawnableComponent, ToolTip = "...")
```

---

## Template Summary

### Quick Copy-Paste Templates

**Component:**
```cpp
UCLASS(ClassGroup = (PluginName), 
       meta = (BlueprintSpawnableComponent,
               DisplayName = "User-Friendly Name",
               ToolTip = "[Primary capability]. [Key features]. [Where to attach].",
               Keywords = "relevant search terms"))
```

**Subsystem:**
```cpp
UCLASS(meta = (DisplayName = "System Name",
               ToolTip = "[Subsystem type] managing [domain]. [Key responsibilities].",
               Keywords = "relevant search terms"))
```

**Data Asset:**
```cpp
UCLASS(BlueprintType,
       meta = (DisplayName = "Asset Name",
               ToolTip = "Defines [configuration]. Create one per [instance type].",
               Keywords = "relevant search terms"))
```

**Float Property:**
```cpp
UPROPERTY(EditAnywhere, Category = "CategoryName",
          meta = (ClampMin = "0.0", ClampMax = "100.0",
                  ToolTip = "[Purpose] ([units], [range]).",
                  Keywords = "optional keywords"))
float PropertyName = 50.0f;
```

**Bool Property:**
```cpp
UPROPERTY(EditAnywhere, Category = "CategoryName",
          meta = (ToolTip = "[What it enables]. [When to enable/disable].",
                  Keywords = "optional keywords"))
bool bPropertyName = true;
```

**Function:**
```cpp
UFUNCTION(BlueprintCallable, Category = "CategoryName",
          meta = (ToolTip = "[What it does]. Call [when/where].",
                  Keywords = "optional keywords"))
void FunctionName();
```

**Enum:**
```cpp
UENUM(BlueprintType, meta = (ToolTip = "[What this represents]."))
enum class EEnumName : uint8
{
    Value1 UMETA(DisplayName = "Display Name 1"),
    Value2 UMETA(DisplayName = "Display Name 2")
};
```

---

## Maintenance Notes

**When to Update This Guide:**

- New UE5 features affecting tooltips
- Plugin-wide terminology changes
- User feedback about unclear tooltips
- New common patterns emerge

**Related Documents:**

- `Beginner_Friendly_Code_Comments_Template.md` - Code comment standards
- Plugin-specific guides in `docs/` folder
- Epic's official UE5 documentation style guide

---

**End of Tooltip Reference Guide**
