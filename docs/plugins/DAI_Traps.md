# DAI_Traps Plugin Documentation

## Overview

**DAI_Traps** is a comprehensive trap system for Unreal Engine 5.5 that provides trap actors and placement utilities integrated with DAI_Spawner, featuring full replication support and Iris compatibility. The system offers intelligent trap mechanics, visual effects integration, and seamless multiplayer synchronization for dynamic gameplay experiences.

### Key Features
- 🪤 **Comprehensive Trap System**: Various trap types with customizable behaviors
- 🎭 **Dynamic Placement**: Runtime trap placement and removal utilities
- 🌐 **Multiplayer Ready**: Full replication support with Iris compatibility
- 🎯 **Smart Triggering**: Intelligent trigger detection and filtering systems
- ✨ **Niagara Integration**: Visual effects for trap activation and destruction
- 🔄 **Spawner Integration**: Seamless integration with DAI_Spawner for dynamic content
- 📊 **Performance Optimized**: Efficient trap management and culling systems
- 🎮 **Blueprint Friendly**: Extensive Blueprint integration for designers

### Hub integration (optional, soft)
- The traps plugin remains fully independent. If the optional DAI_Hub plugin is present, `ADAI_TrapActor` can auto-register itself with the hub at runtime using a soft-reference pattern—no compile-time dependency is introduced.
- Toggle via `bRegisterWithHub` (default: true). When enabled and running on the authority (server), traps will register with the hub on BeginPlay and unregister on EndPlay. When the hub isn’t loaded, this is a no-op.
- This enables hub-mediated wiring with other systems (for example, SmartObject providers/consumers) without forcing DAI_Hub as a hard dependency.

## Architecture

The DAI_Traps system consists of:
- **Trap Actors**: Various trap types with specialized behaviors
- **Trigger System**: Detection and activation mechanisms
- **Placement Utilities**: Tools for dynamic trap placement
- **Effect Integration**: Niagara-based visual and audio effects
- **Replication Layer**: Network synchronization for multiplayer

## Core Components

### DAITrapActor
*Base class for all trap implementations*

**Type**: `Actor`  
**Interfaces**: `IDAITrapInterface`  
**File**: `DAITrapActor.h`

Base actor providing core trap functionality with replication and effect support.

### DAIExplosiveTrap
*Explosive trap with area damage*

**Type**: `Actor`  
**Parent**: `DAITrapActor`  
**File**: `DAIExplosiveTrap.h`

Specialized trap that deals area damage when triggered.

### DAISpikeTrap
*Spike trap with direct damage*

**Type**: `Actor`  
**Parent**: `DAITrapActor`  
**File**: `DAISpikeTrap.h`

Ground-based spike trap that damages actors walking over it.

### DAISlowTrap
*Trap that applies movement debuffs*

**Type**: `Actor`  
**Parent**: `DAITrapActor`  
**File**: `DAISlowTrap.h`

Trap that slows down or immobilizes affected actors.

### DAIPoisonTrap
*Trap that applies damage over time*

**Type**: `Actor`  
**Parent**: `DAITrapActor`  
**File`: `DAIPoisonTrap.h`

Trap that applies poison effects and damage over time.

### DAITrapPlacementComponent
*Component for dynamic trap placement*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `Traps|Placement`  
**File**: `DAITrapPlacementComponent.h`

Handles intelligent trap placement with validation and conflict resolution.

## Blueprint Functions

### Core Trap Operations

#### PlaceTrap
**Type**: `BlueprintCallable`  
**Category**: `Traps`  
**Returns**: `bool`  
**Purpose**: Place a trap at a specific location

**Parameters**:
- `TrapClass` (TSubclassOf<ADAITrapActor>): Class of trap to place
- `Location` (FVector): World location for trap placement
- `Rotation` (FRotator): Rotation for the trap
- `Placer` (AActor): Actor placing the trap
- `bValidateLocation` (bool): Whether to validate placement location

```cpp
bool PlaceTrap(UObject* WorldContextObject, TSubclassOf<ADAITrapActor> TrapClass, const FVector& Location, const FRotator& Rotation, AActor* Placer, bool bValidateLocation = true);
```

**Usage**: Primary function for placing traps during gameplay.

#### RemoveTrap
**Type**: `BlueprintCallable`  
**Category**: `Traps`  
**Returns**: `bool`  
**Purpose**: Remove an existing trap from the world

**Parameters**:
- `Trap` (ADAITrapActor): Trap to remove
- `bPlayDestructionEffects` (bool): Whether to play destruction effects

```cpp
bool RemoveTrap(UObject* WorldContextObject, ADAITrapActor* Trap, bool bPlayDestructionEffects = true);
```

**Usage**: Clean removal of traps with optional visual effects.

#### TriggerTrap
**Type**: `BlueprintCallable`  
**Category**: `Traps`  
**Returns**: `bool`  
**Purpose**: Manually trigger a trap

**Parameters**:
- `Trap` (ADAITrapActor): Trap to trigger
- `Triggerer` (AActor): Actor causing the trigger
- `bForceActivation` (bool): Whether to bypass trigger conditions

```cpp
bool TriggerTrap(UObject* WorldContextObject, ADAITrapActor* Trap, AActor* Triggerer, bool bForceActivation = false);
```

**Usage**: Manually activate traps for scripted events or abilities.

#### GetTrapsInArea
**Type**: `BlueprintCallable`  
**Category**: `Traps`  
**Returns**: `TArray<ADAITrapActor*>`  
**Purpose**: Find all traps within a specified area

**Parameters**:
- `Center` (FVector): Center point of search area
- `Radius` (float): Search radius
- `TrapTypes` (FGameplayTagContainer): Types of traps to find
- `bOnlyActive` (bool): Whether to only return active traps

```cpp
TArray<ADAITrapActor*> GetTrapsInArea(UObject* WorldContextObject, const FVector& Center, float Radius, const FGameplayTagContainer& TrapTypes, bool bOnlyActive = true);
```

**Usage**: Locate traps for disarming, avoiding, or area effects.

### Trap State Management

#### SetTrapActive
**Type**: `BlueprintCallable`  
**Category**: `Traps`  
**Purpose**: Activate or deactivate a trap

**Parameters**:
- `Trap` (ADAITrapActor): Trap to modify
- `bActive` (bool): Whether to activate the trap

```cpp
void SetTrapActive(ADAITrapActor* Trap, bool bActive);
```

**Usage**: Toggle trap activation state for dynamic scenarios.

#### DisarmTrap
**Type**: `BlueprintCallable`  
**Category**: `Traps`  
**Returns**: `bool`  
**Purpose**: Attempt to disarm a trap

**Parameters**:
- `Trap` (ADAITrapActor): Trap to disarm
- `Disarmer` (AActor): Actor attempting to disarm
- `DisarmSkill` (float): Skill level for disarming (0-1)

```cpp
bool DisarmTrap(UObject* WorldContextObject, ADAITrapActor* Trap, AActor* Disarmer, float DisarmSkill);
```

**Usage**: Allow players or AI to disarm traps with skill checks.

#### GetTrapState
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `Traps`  
**Returns**: `EDAITrapState`  
**Purpose**: Get current state of a trap

**Parameters**:
- `Trap` (ADAITrapActor): Trap to check

```cpp
EDAITrapState GetTrapState(ADAITrapActor* Trap);
```

**Usage**: Query trap status for UI display or logic decisions.

### Trap Detection and Interaction

#### CanDetectTrap
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `Traps`  
**Returns**: `bool`  
**Purpose**: Check if an actor can detect a specific trap

**Parameters**:
- `Actor` (AActor): Actor attempting detection
- `Trap` (ADAITrapActor): Trap to detect
- `DetectionRange` (float): Maximum detection range

```cpp
bool CanDetectTrap(AActor* Actor, ADAITrapActor* Trap, float DetectionRange);
```

**Usage**: Determine if characters can spot hidden traps.

#### GetDetectableTrapsNear
**Type**: `BlueprintCallable`  
**Category**: `Traps`  
**Returns**: `TArray<ADAITrapActor*>`  
**Purpose**: Get all traps detectable by an actor in range

**Parameters**:
- `Actor` (AActor): Actor doing the detection
- `DetectionRange` (float): Range for detection
- `DetectionSkill` (float): Actor's detection skill level

```cpp
TArray<ADAITrapActor*> GetDetectableTrapsNear(AActor* Actor, float DetectionRange, float DetectionSkill);
```

**Usage**: Implement detection mechanics for gameplay or AI.

### Placement Utilities

#### ValidateTrapPlacement
**Type**: `BlueprintCallable`  
**Category**: `Traps|Placement`  
**Returns**: `bool`  
**Purpose**: Check if a location is valid for trap placement

**Parameters**:
- `TrapClass` (TSubclassOf<ADAITrapActor>): Class of trap to validate
- `Location` (FVector): Proposed placement location
- `PlacementConstraints` (FDAITrapPlacementConstraints): Placement validation rules

```cpp
bool ValidateTrapPlacement(UObject* WorldContextObject, TSubclassOf<ADAITrapActor> TrapClass, const FVector& Location, const FDAITrapPlacementConstraints& PlacementConstraints);
```

**Usage**: Ensure trap placement follows game rules and physics.

#### FindOptimalTrapLocation
**Type**: `BlueprintCallable`  
**Category**: `Traps|Placement`  
**Returns**: `bool`  
**Purpose**: Find best location for trap placement near a target point

**Parameters**:
- `TargetLocation` (FVector): Desired placement area
- `SearchRadius` (float): Radius to search for valid locations
- `TrapClass` (TSubclassOf<ADAITrapActor>): Class of trap to place
- `OutLocation` (FVector): Found optimal location

```cpp
bool FindOptimalTrapLocation(UObject* WorldContextObject, const FVector& TargetLocation, float SearchRadius, TSubclassOf<ADAITrapActor> TrapClass, FVector& OutLocation);
```

**Usage**: Intelligently place traps in tactically advantageous positions.

## Blueprint Data Types

### EDAITrapState (Trap State)
**Type**: `BlueprintType Enum`  
**Purpose**: Current operational state of a trap

**Values**:
- `Inactive`: Trap is placed but not active
- `Armed`: Trap is active and ready to trigger
- `Triggered`: Trap has been activated
- `Disarmed`: Trap has been safely disarmed
- `Destroyed`: Trap has been destroyed
- `Reloading`: Trap is reloading after activation

### EDAITrapType (Trap Type)
**Type**: `BlueprintType Enum`  
**Purpose**: Classification of trap functionality

**Values**:
- `Explosive`: Deals area damage when triggered
- `Spike`: Direct piercing damage trap
- `Poison`: Applies damage over time effects
- `Slow`: Movement impairment trap
- `Stun`: Temporary incapacitation trap
- `Alarm`: Detection and alert trap
- `Custom`: User-defined trap behavior

### EDAITrapTrigger (Trap Trigger)
**Type**: `BlueprintType Enum`  
**Purpose**: Method by which traps are activated

**Values**:
- `Proximity`: Triggered by nearby actors
- `Contact`: Triggered by direct contact
- `Timer`: Triggered after a time delay
- `Remote`: Triggered by external signal
- `Damage`: Triggered when taking damage
- `Manual`: Triggered by direct activation

### FDAITrapInfo (Trap Information)
**Type**: `BlueprintType Struct`  
**Purpose**: Complete information about a trap instance

**Properties**:
- `TrapId` (FGuid): Unique identifier for this trap
- `TrapType` (EDAITrapType): Type classification of the trap
- `TrapState` (EDAITrapState): Current operational state
- `PlacedBy` (AActor): Actor who placed this trap
- `PlacementTime` (float): Game time when trap was placed
- `TriggerConditions` (FDAITrapTriggerConditions): Conditions for activation
- `EffectSettings` (FDAITrapEffectSettings): Visual and audio effect configuration

### FDAITrapTriggerConditions (Trap Trigger Conditions)
**Type**: `BlueprintType Struct`  
**Purpose**: Configuration for trap activation conditions

**Properties**:
- `TriggerType` (EDAITrapTrigger): Method of activation
- `TriggerRadius` (float): Activation range for proximity triggers
- `RequiredTags` (FGameplayTagContainer): Tags required on triggering actor
- `ForbiddenTags` (FGameplayTagContainer): Tags that prevent activation
- `MinTriggerWeight` (float): Minimum weight/mass to trigger
- `bRequireLineOfSight` (bool): Whether trigger requires line of sight
- `CooldownTime` (float): Time before trap can trigger again

### FDAITrapEffectSettings (Trap Effect Settings)
**Type**: `BlueprintType Struct`  
**Purpose**: Configuration for trap visual and audio effects

**Properties**:
- `ArmingEffect` (UNiagaraSystem): Effect played when trap becomes armed
- `TriggerEffect` (UNiagaraSystem): Effect played when trap activates
- `DisarmEffect` (UNiagaraSystem): Effect played when trap is disarmed
- `DestructionEffect` (UNiagaraSystem): Effect played when trap is destroyed
- `ArmingSound` (USoundBase): Audio played when arming
- `TriggerSound` (USoundBase): Audio played on activation
- `bLoopIdleEffects` (bool): Whether to loop ambient effects while armed

### FDAITrapPlacementConstraints (Trap Placement Constraints)
**Type**: `BlueprintType Struct`  
**Purpose**: Rules and constraints for trap placement validation

**Properties**:
- `MinDistanceFromActors` (float): Minimum distance from other actors
- `MinDistanceFromTraps` (float): Minimum distance from existing traps
- `RequiredSurfaceAngle` (float): Required surface angle for placement
- `RequiredSpace` (FVector): Required clear space dimensions
- `ForbiddenSurfaces` (FGameplayTagContainer): Surface types that forbid placement
- `bRequireGroundContact` (bool): Whether trap must be on solid ground
- `bAllowWaterPlacement` (bool): Whether placement in water is allowed

### FDAITrapDamageInfo (Trap Damage Information)
**Type**: `BlueprintType Struct`  
**Purpose**: Damage configuration for offensive traps

**Properties**:
- `BaseDamage` (float): Base damage amount
- `DamageType` (TSubclassOf<UDamageType>): Type of damage dealt
- `DamageRadius` (float): Radius for area damage effects
- `bScaleWithDistance` (bool): Whether damage decreases with distance
- `DamageOverTime` (FDAIDamageOverTime): Damage over time configuration
- `KnockbackForce` (float): Force applied to damaged actors
- `StatusEffects` (TArray<TSubclassOf<UGameplayEffect>>): Effects to apply on damage

## Component Properties

### DAITrapActor Properties

#### Basic Configuration
**Property**: `TrapType`  
**Type**: `EDAITrapType`  
**Category**: `Trap`  
**Blueprint Access**: `Read/Write`  
**Replication**: `Yes`  
**Purpose**: Classification of this trap's functionality

**Property**: `TrapState`  
**Type**: `EDAITrapState`  
**Category**: `Trap`  
**Blueprint Access**: `Read Only`  
**Replication**: `Yes`  
**Purpose**: Current operational state of the trap

**Property**: `bIsHidden`  
**Type**: `bool`  
**Category**: `Trap`  
**Blueprint Access**: `Read/Write`  
**Default**: `false`  
**Purpose**: Whether this trap is hidden from normal detection

#### Trigger Settings
**Property**: `TriggerConditions`  
**Type**: `FDAITrapTriggerConditions`  
**Category**: `Trap|Triggering`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Configuration for trap activation

**Property**: `bCanRetrigger`  
**Type**: `bool`  
**Category**: `Trap|Triggering`  
**Blueprint Access**: `Read/Write`  
**Default**: `false`  
**Purpose**: Whether trap can be triggered multiple times

**Property**: `MaxTriggers`  
**Type**: `int32`  
**Category**: `Trap|Triggering`  
**Blueprint Access**: `Read/Write`  
**Default**: `1`  
**Purpose**: Maximum number of times trap can trigger

#### Effect Configuration
**Property**: `EffectSettings`  
**Type**: `FDAITrapEffectSettings`  
**Category**: `Trap|Effects`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Visual and audio effect configuration

**Property**: `bUseCustomEffects`  
**Type**: `bool`  
**Category**: `Trap|Effects`  
**Blueprint Access**: `Read/Write`  
**Default**: `false`  
**Purpose**: Whether to use custom effects instead of defaults

### DAITrapPlacementComponent Properties

#### Placement Rules
**Property**: `DefaultConstraints`  
**Type**: `FDAITrapPlacementConstraints`  
**Category**: `Placement`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Default constraints for trap placement validation

**Property**: `bValidateOnPlacement`  
**Type**: `bool`  
**Category**: `Placement`  
**Blueprint Access**: `Read/Write`  
**Default**: `true`  
**Purpose**: Whether to validate placement locations automatically

#### Management Settings
**Property**: `MaxTrapsPerPlayer`  
**Type**: `int32`  
**Category**: `Placement`  
**Blueprint Access**: `Read/Write`  
**Default**: `10`  
**Purpose**: Maximum number of traps each player can place

**Property**: `TrapLifetime`  
**Type**: `float`  
**Category**: `Placement`  
**Blueprint Access**: `Read/Write`  
**Default**: `300.0`  
**Purpose**: Automatic lifetime for placed traps (0 = permanent)

## Events and Delegates

### OnTrapTriggered
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Traps`  
**Purpose**: Fired when a trap is triggered

**Parameters**:
- `Trap` (ADAITrapActor): Trap that was triggered
- `Triggerer` (AActor): Actor who triggered the trap
- `TriggerLocation` (FVector): Location where trigger occurred

**Usage**: Handle trap effects, update scores, or trigger related events.

### OnTrapPlaced
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Traps`  
**Purpose**: Fired when a trap is placed

**Parameters**:
- `Trap` (ADAITrapActor): Trap that was placed
- `Placer` (AActor): Actor who placed the trap
- `PlacementLocation` (FVector): Location where trap was placed

**Usage**: Update UI, play effects, or adjust tactical AI behavior.

### OnTrapDisarmed
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Traps`  
**Purpose**: Fired when a trap is successfully disarmed

**Parameters**:
- `Trap` (ADAITrapActor): Trap that was disarmed
- `Disarmer` (AActor): Actor who disarmed the trap
- `bWasDestroyed` (bool): Whether trap was destroyed during disarming

**Usage**: Award experience, play effects, or update trap counters.

### OnTrapDestroyed
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Traps`  
**Purpose**: Fired when a trap is destroyed

**Parameters**:
- `Trap` (ADAITrapActor): Trap that was destroyed
- `Destroyer` (AActor): Actor responsible for destruction
- `DestructionCause` (EDAITrapDestructionCause): Reason for destruction

**Usage**: Clean up references, play destruction effects, or update statistics.

## Developer Settings

Access via **Project Settings → Game → DAI Traps**

### General Settings

#### Trap System
**Property**: `bEnableTrapSystem`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to enable the trap system globally

**Property**: `MaxGlobalTraps`  
**Type**: `int32`  
**Default**: `200`  
**Range**: `10-1000`  
**Purpose**: Maximum total number of traps in the world

**Property**: `TrapUpdateFrequency`  
**Type**: `float`  
**Default**: `0.1`  
**Range**: `0.01-1.0`  
**Purpose**: Seconds between trap system updates

#### Performance Settings
**Property**: `TrapCullDistance`  
**Type**: `float`  
**Default**: `3000.0`  
**Range**: `500.0-10000.0`  
**Purpose**: Distance at which to cull trap processing

**Property**: `bUseLODForTraps`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to use LOD for distant traps

### Placement Settings

#### Validation Rules
**Property**: `bEnforceGlobalConstraints`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to enforce global placement constraints

**Property**: `GlobalMinTrapDistance`  
**Type**: `float`  
**Default**: `200.0`  
**Range**: `50.0-1000.0`  
**Purpose**: Global minimum distance between any traps

**Property**: `bAllowTrapStacking`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether multiple traps can occupy same area

#### Default Constraints
**Property**: `DefaultPlacementConstraints`  
**Type**: `FDAITrapPlacementConstraints`  
**Purpose**: Global default constraints for all trap placement

### Effect Settings

#### Visual Effects
**Property**: `bEnableTrapEffects`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to enable trap visual effects

**Property**: `EffectQualityLevel`  
**Type**: `EDAIEffectQuality`  
**Default**: `High`  
**Purpose**: Quality level for trap effects

**Property**: `MaxConcurrentEffects`  
**Type**: `int32`  
**Default**: `20`  
**Range**: `5-100`  
**Purpose**: Maximum simultaneous trap effects

#### Audio Settings
**Property**: `bEnableTrapAudio`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to enable trap audio effects

**Property**: `TrapAudioRange`  
**Type**: `float`  
**Default**: `1000.0`  
**Range**: `100.0-5000.0`  
**Purpose**: Maximum range for trap audio effects

### Detection Settings

#### Detection Mechanics
**Property**: `bEnableTrapDetection`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether traps can be detected by players/AI

**Property**: `BaseDetectionRange`  
**Type**: `float`  
**Default**: `300.0`  
**Range**: `50.0-1000.0`  
**Purpose**: Base range for trap detection

**Property**: `DetectionSkillInfluence`  
**Type**: `float`  
**Default**: `0.5`  
**Range**: `0.0-2.0`  
**Purpose**: How much detection skill affects range

### Multiplayer Settings

#### Replication
**Property**: `bReplicateTraps`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to replicate trap state in multiplayer

**Property**: `TrapReplicationRate`  
**Type**: `float`  
**Default**: `10.0`  
**Range**: `1.0-60.0`  
**Purpose**: Replication frequency for trap updates

#### Authority
**Property**: `bServerAuthoritative`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether server has authority over trap activation

### Debug Settings

#### Visualization
**Property**: `bDrawTrapDebug`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to draw trap debug information

**Property**: `bShowTriggerRadius`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to visualize trap trigger ranges

**Property**: `bShowPlacementConstraints`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to visualize placement constraint areas

#### Logging
**Property**: `bLogTrapEvents`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to log trap activation and placement events

## Usage Examples

### Basic Trap Placement and Management
```blueprint
// Set up trap placement for player
void SetupTrapPlacement(APlayerController* Player)
{
    // Add trap placement component to player
    UDAITrapPlacementComponent* PlacementComp = Player->GetPawn()->CreateDefaultSubobject<UDAITrapPlacementComponent>("TrapPlacement");
    
    // Configure placement constraints
    FDAITrapPlacementConstraints Constraints;
    Constraints.MinDistanceFromActors = 150.0f;
    Constraints.MinDistanceFromTraps = 300.0f;
    Constraints.bRequireGroundContact = true;
    Constraints.RequiredSurfaceAngle = 30.0f;
    
    PlacementComp->DefaultConstraints = Constraints;
    PlacementComp->MaxTrapsPerPlayer = 5;
    PlacementComp->TrapLifetime = 180.0f; // 3 minutes
}

// Handle player trap placement input
void OnPlayerPlaceTrap(APlayerController* Player, TSubclassOf<ADAITrapActor> TrapClass)
{
    APawn* PlayerPawn = Player->GetPawn();
    FVector PlacementLocation = PlayerPawn->GetActorLocation() + PlayerPawn->GetActorForwardVector() * 200.0f;
    
    // Validate placement location
    bool bValidLocation = UDAITrapsBlueprintLibrary::ValidateTrapPlacement(
        this,
        TrapClass,
        PlacementLocation,
        GetDefaultPlacementConstraints()
    );
    
    if (bValidLocation)
    {
        // Place the trap
        bool bPlaced = UDAITrapsBlueprintLibrary::PlaceTrap(
            this,
            TrapClass,
            PlacementLocation,
            PlayerPawn->GetActorRotation(),
            PlayerPawn,
            true // Validate location
        );
        
        if (bPlaced)
        {
            ShowMessage(Player, "Trap placed successfully");
            PlayTrapPlacementEffect(PlacementLocation);
        }
        else
        {
            ShowMessage(Player, "Failed to place trap");
        }
    }
    else
    {
        ShowMessage(Player, "Invalid placement location");
    }
}
```

### Advanced Trap Detection System
```blueprint
// Implement trap detection for AI or skilled players
void UpdateTrapDetection(AActor* DetectingActor)
{
    float DetectionSkill = GetDetectionSkill(DetectingActor);
    float DetectionRange = BaseDetectionRange * (1.0f + DetectionSkill);
    
    // Find detectable traps near actor
    TArray<ADAITrapActor*> DetectedTraps = UDAITrapsBlueprintLibrary::GetDetectableTrapsNear(
        DetectingActor,
        DetectionRange,
        DetectionSkill
    );
    
    // Process newly detected traps
    for (ADAITrapActor* Trap : DetectedTraps)
    {
        if (!IsTrapsAlreadyKnown(DetectingActor, Trap))
        {
            // Mark trap as detected
            MarkTrapAsDetected(DetectingActor, Trap);
            
            // Show visual indicator for players
            if (IsPlayer(DetectingActor))
            {
                ShowTrapIndicator(Trap);
            }
            
            // Update AI behavior for AI actors
            if (IsAI(DetectingActor))
            {
                UpdateAIPathfindingToAvoidTrap(DetectingActor, Trap);
            }
        }
    }
}

// Handle trap disarming attempts
void AttemptTrapDisarm(AActor* Disarmer, ADAITrapActor* Trap)
{
    float DisarmSkill = GetDisarmSkill(Disarmer);
    
    // Check if trap can be disarmed
    if (Trap->CanBeDisarmed() && CanActorReachTrap(Disarmer, Trap))
    {
        // Play disarming animation
        PlayDisarmAnimation(Disarmer);
        
        // Attempt disarm with skill check
        bool bDisarmSuccessful = UDAITrapsBlueprintLibrary::DisarmTrap(
            this,
            Trap,
            Disarmer,
            DisarmSkill
        );
        
        if (bDisarmSuccessful)
        {
            // Award experience and show success message
            GiveDisarmExperience(Disarmer, Trap->GetDifficultyRating());
            ShowMessage(Disarmer, "Trap disarmed successfully");
            
            // Give trap components as loot
            GiveTrapComponents(Disarmer, Trap);
        }
        else
        {
            // Failed disarm - might trigger trap
            float TriggerChance = (1.0f - DisarmSkill) * 0.5f;
            if (FMath::RandRange(0.0f, 1.0f) < TriggerChance)
            {
                ShowMessage(Disarmer, "Disarm failed - trap triggered!");
                UDAITrapsBlueprintLibrary::TriggerTrap(this, Trap, Disarmer, true);
            }
            else
            {
                ShowMessage(Disarmer, "Disarm failed but trap remained stable");
            }
        }
    }
}
```

### Specialized Trap Implementations
```blueprint
// Create explosive trap with area damage
UCLASS()
class MYGAME_API AMyExplosiveTrap : public ADAIExplosiveTrap
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explosive")
    float ExplosionRadius = 400.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explosive")
    float ExplosionDamage = 100.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explosive")
    UNiagaraSystem* ExplosionEffect;

protected:
    virtual void OnTrapTriggered_Implementation(AActor* Triggerer) override
    {
        Super::OnTrapTriggered_Implementation(Triggerer);
        
        // Apply explosion damage
        TArray<AActor*> ActorsInRange;
        UKismetSystemLibrary::SphereOverlapActors(
            this,
            GetActorLocation(),
            ExplosionRadius,
            {UEngineTypes::ConvertToObjectType(ECC_Pawn)},
            APawn::StaticClass(),
            {this},
            ActorsInRange
        );
        
        for (AActor* Actor : ActorsInRange)
        {
            float Distance = FVector::Dist(GetActorLocation(), Actor->GetActorLocation());
            float DamageFalloff = 1.0f - (Distance / ExplosionRadius);
            float ActualDamage = ExplosionDamage * DamageFalloff;
            
            // Apply damage
            UGameplayStatics::ApplyPointDamage(
                Actor,
                ActualDamage,
                GetActorLocation(),
                FHitResult(),
                nullptr,
                this,
                UDamageType::StaticClass()
            );
            
            // Apply knockback
            FVector KnockbackDirection = (Actor->GetActorLocation() - GetActorLocation()).GetSafeNormal();
            ApplyKnockback(Actor, KnockbackDirection, ActualDamage * 10.0f);
        }
        
        // Play explosion effects
        if (ExplosionEffect)
        {
            UNiagaraFunctionLibrary::SpawnSystemAtLocation(
                this,
                ExplosionEffect,
                GetActorLocation(),
                GetActorRotation()
            );
        }
        
        // Destroy trap after explosion
        SetLifeSpan(2.0f);
    }
};

// Create poison gas trap
UCLASS()
class MYGAME_API APoisonGasTrap : public ADAIPoisonTrap
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Poison")
    float GasRadius = 300.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Poison")
    float GasDuration = 10.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Poison")
    TSubclassOf<UGameplayEffect> PoisonEffect;

protected:
    virtual void OnTrapTriggered_Implementation(AActor* Triggerer) override
    {
        Super::OnTrapTriggered_Implementation(Triggerer);
        
        // Create poison gas area
        CreatePoisonGasArea();
        
        // Start gas effect timer
        GetWorld()->GetTimerManager().SetTimer(
            GasEffectTimer,
            FTimerDelegate::CreateUObject(this, &APoisonGasTrap::ApplyPoisonEffect),
            1.0f, // Apply effect every second
            true, // Loop
            0.0f  // Start immediately
        );
        
        // End gas after duration
        GetWorld()->GetTimerManager().SetTimer(
            GasEndTimer,
            FTimerDelegate::CreateUObject(this, &APoisonGasTrap::EndGasEffect),
            GasDuration,
            false
        );
    }
    
private:
    FTimerHandle GasEffectTimer;
    FTimerHandle GasEndTimer;
    
    void ApplyPoisonEffect()
    {
        // Find actors in gas area
        TArray<AActor*> ActorsInGas = GetActorsInGasArea();
        
        for (AActor* Actor : ActorsInGas)
        {
            // Apply poison effect if actor has ability system
            if (UAbilitySystemComponent* ASC = Actor->FindComponentByClass<UAbilitySystemComponent>())
            {
                FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
                EffectContext.AddSourceObject(this);
                
                FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(
                    PoisonEffect,
                    1.0f,
                    EffectContext
                );
                
                ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
            }
        }
    }
};
```

### Multiplayer Trap Coordination
```blueprint
// Server-authoritative trap system
void PlaceTrapOnServer(APlayerController* Player, TSubclassOf<ADAITrapActor> TrapClass, FVector Location)
{
    // Validate on server
    if (GetNetMode() == NM_DedicatedServer || GetNetMode() == NM_ListenServer)
    {
        // Check player trap quota
        int32 PlayerTrapCount = GetPlayerTrapCount(Player);
        if (PlayerTrapCount >= MaxTrapsPerPlayer)
        {
            NotifyClient_TrapPlacementFailed(Player, "Too many traps placed");
            return;
        }
        
        // Validate placement
        if (ValidateTrapPlacement(TrapClass, Location))
        {
            // Spawn trap on server
            ADAITrapActor* NewTrap = GetWorld()->SpawnActor<ADAITrapActor>(
                TrapClass,
                Location,
                FRotator::ZeroRotator
            );
            
            if (NewTrap)
            {
                // Set ownership and replicate
                NewTrap->SetOwner(Player->GetPawn());
                NewTrap->SetReplicates(true);
                
                // Register trap
                RegisterPlayerTrap(Player, NewTrap);
                
                // Notify all clients
                NotifyClients_TrapPlaced(NewTrap, Player);
            }
        }
        else
        {
            NotifyClient_TrapPlacementFailed(Player, "Invalid placement location");
        }
    }
}

// Handle trap synchronization
UFUNCTION(NetMulticast, Reliable)
void NotifyClients_TrapPlaced(ADAITrapActor* Trap, APlayerController* Placer)
{
    if (Trap)
    {
        // Play placement effects on all clients
        PlayTrapPlacementEffect(Trap->GetActorLocation());
        
        // Update UI for trap count
        UpdateTrapCountUI(Placer);
        
        // Update AI pathfinding if this is an AI client
        UpdateAIPathfindingForNewTrap(Trap);
    }
}

// Iris-compatible trap replication
void SetupTrapReplication(ADAITrapActor* Trap)
{
    // Configure for Iris replication system
    Trap->SetReplicates(true);
    Trap->bAlwaysRelevant = false; // Use distance-based relevance
    
    // Set replication conditions
    Trap->SetReplicationCondition(COND_OwnerOnly, false);
    Trap->SetReplicationCondition(COND_SkipOwner, false);
    Trap->SetReplicationCondition(COND_SimulatedOnly, false);
    
    // Configure spatial relevance for Iris
    if (UNetObjectPrioritizer* Prioritizer = Trap->GetNetObjectPrioritizer())
    {
        Prioritizer->SetSpatialRequirement(ESpatialRequirement::RequiresSpatialConnection);
    }
}
```

## Integration with Other Plugins

### DAI_Spawner Integration
- **Dynamic Placement**: Traps can be spawned through DAI_Spawner system
- **Pool Integration**: Frequently used traps can utilize object pooling
- **Coordinated Spawning**: Trap placement respects spawner performance budgets

### DAI_Hub Integration
- **Service Registration**: Trap system registers with hub for discovery
- **Event Publishing**: Trap events published through hub system
- **Performance Coordination**: Trap operations respect hub performance budgets

### Niagara Integration
- **Visual Effects**: Comprehensive Niagara effects for all trap states
- **Dynamic Parameters**: Effect parameters driven by trap properties
- **Performance Scaling**: Effect quality scales with performance settings

### DAI_AI Integration
- **AI Awareness**: AI characters can detect and avoid traps
- **Tactical Placement**: AI can use traps strategically
- **Behavior Modification**: Trap presence affects AI pathfinding and decision making

## Best Practices

### Trap Design
1. **Design clear visual feedback** for trap states and detection
2. **Balance trap power** with placement limitations and costs
3. **Provide counterplay options** through detection and disarming
4. **Test multiplayer synchronization** thoroughly
5. **Consider accessibility** for players with different skill levels

### Performance Optimization
1. **Use culling systems** for distant traps
2. **Limit concurrent trap effects** to maintain frame rate
3. **Implement trap LOD** for performance scaling
4. **Monitor memory usage** with large numbers of traps
5. **Optimize replication** for multiplayer scenarios

### Gameplay Integration
1. **Integrate with level design** for natural trap placement opportunities
2. **Provide clear feedback** for trap interactions
3. **Balance risk vs reward** for trap usage
4. **Consider trap interactions** with other game systems
5. **Test edge cases** like overlapping traps or simultaneous triggers

### Multiplayer Considerations
1. **Implement server authority** for trap state management
2. **Handle network prediction** for responsive trap placement
3. **Synchronize visual effects** across all clients
4. **Consider bandwidth usage** for trap replication
5. **Test with various network conditions** and latency

## Technical Notes

- **Thread Safety**: Trap operations designed for game thread usage
- **Memory Management**: Efficient cleanup of destroyed traps and effects
- **Networking**: Full replication support with Iris compatibility
- **Performance**: Optimized trigger detection and effect management
- **Platform Support**: Cross-platform trap functionality with platform-specific optimizations

---

*For more information about spawner integration, see [DAI_Spawner documentation](DAI_Spawner.md).*  
*For hub integration details, see [DAI_Hub documentation](DAI_Hub.md).*  
*For AI integration, see [DAI_AI documentation](DAI_AI.md).*

---

Last updated: October 6, 2025