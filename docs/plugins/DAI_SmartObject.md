# DAI_SmartObject Plugin Documentation

## Overview

**DAI_SmartObject** is a comprehensive Smart Object integration system for Unreal Engine 5.5 that provides reusable component wrappers for contextual interactions like benches, mounts, assassination sync points, and environmental interactions. The system is aligned with Unreal's built-in Smart Objects framework (USmartObjectComponent + USmartObjectSubsystem) and extends it with DAI-specific functionality. A lightweight mode remains available for projects that prefer not to author full Smart Object Definitions.

### Key Features
- 🧠 **Engine-aligned base**: Reuses the Engine Smart Objects system when present
- 🔌 **Automatic bridge**: Can auto-attach an Engine SmartObject component at runtime (non-destructive)
- 🧠 **Smart Object Wrapper**: Enhanced Smart Object functionality with DAI integration
- 🪑 **Contextual Interactions**: Benches, chairs, mounts, and interaction points
- 🎯 **Assassination Sync Points**: Coordinated takedown and stealth mechanics
- 🔄 **Reusable Components**: Modular components for different interaction types
- 🎮 **Animation Integration**: Seamless animation and movement coordination
- 📊 **Performance Optimized**: Efficient interaction detection and management
- 🌐 **Hub Integration**: Full integration with DAI_Hub event system
- 🎭 **Multi-User Support**: Support for multiple simultaneous users

## Architecture

The DAI_SmartObject system consists of:
- **Smart Object Service**: Central management and coordination
- **Interaction Components**: Specialized components for different interaction types
- **Animation Coordination**: Movement and animation synchronization
- **State Management**: Tracking of object states and user assignments
- **Performance Integration**: Optimization through DAI_PerfMngr integration

## Core Components

### Engine Subsystem Usage
This plugin now leverages the Engine `USmartObjectSubsystem` when bridging is enabled. No custom world subsystem is required. For places where a service class is useful, see `UDAI_SmartObjectServiceImpl`, a lightweight shim that demonstrates how to interact with the engine subsystem without introducing hard dependencies into gameplay code.

### DAISmartObjectComponent
*Base component for smart object functionality*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `SmartObject`  
**File**: `DAISmartObjectComponent.h`

Core component providing basic smart object functionality with DAI enhancements.

#### New utilities (Blueprint)
- SmartObject|Slots
    - GetAllSlotNames(out SlotNames)
    - GetAvailableSlotNames(User, out SlotNames)
    - GetSlotTags(SlotName, out Tags)
- SmartObject|Cooldowns
    - ResetSlotCooldown(SlotName)
    - ResetAllCooldowns()
- SmartObject|Alignment
    - GetSlotAlignmentTransform(SlotName, out Transform, bYawOnly)
    - AlignActorToSlot(User, SlotName, bTeleport, bYawOnly)

Notes:
- Component spatial hash updates automatically on movement to keep QueryNearby accurate.
- In-editor, duplicate or empty SlotNames are auto-resolved to unique names.

### DAISittableComponent
*Component for sittable objects like benches and chairs*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `SmartObject|Sittable`  
**File**: `DAISittableComponent.h`

Specialized component for seating interactions with animation and positioning support.

### DAIMountableComponent
*Component for mountable objects and vehicles*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `SmartObject|Mountable`  
**File**: `DAIMountableComponent.h`

Component for mount interactions including horses, vehicles, and rideable creatures.

### DAIAssassinationSyncComponent
*Component for coordinated assassination points*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `SmartObject|Assassination`  
**File**: `DAIAssassinationSyncComponent.h`

Specialized component for stealth takedown coordination and synchronization.

## Blueprint Functions

### Core Smart Object Operations

#### FindSmartObjectsNear
**Type**: `BlueprintCallable`  
**Category**: `SmartObject`  
**Returns**: `TArray<AActor*>`  
**Purpose**: Find smart objects within range of a location

**Parameters**:
- `Location` (FVector): Center point for search
- `SearchRadius` (float): Radius to search within
- `ObjectTypes` (FGameplayTagContainer): Types of smart objects to find
- `bRequireAvailable` (bool): Whether to only return available objects

```cpp
TArray<AActor*> FindSmartObjectsNear(UObject* WorldContextObject, const FVector& Location, float SearchRadius, const FGameplayTagContainer& ObjectTypes, bool bRequireAvailable = true);
```

**Usage**: Locate nearby smart objects for AI decision making or player interaction prompts.

#### ClaimSmartObject
**Type**: `BlueprintCallable`  
**Category**: `SmartObject`  
**Returns**: `bool`  
**Purpose**: Claim a smart object for exclusive use

**Parameters**:
- `SmartObject` (AActor): Smart object to claim
- `User` (AActor): Actor claiming the object
- `InteractionType` (FGameplayTag): Type of interaction being performed

```cpp
bool ClaimSmartObject(UObject* WorldContextObject, AActor* SmartObject, AActor* User, FGameplayTag InteractionType);
```

**Usage**: Reserve smart objects to prevent conflicts and enable exclusive interactions.

#### ReleaseSmartObject
**Type**: `BlueprintCallable`  
**Category**: `SmartObject`  
**Purpose**: Release a previously claimed smart object

**Parameters**:
- `SmartObject` (AActor): Smart object to release
- `User` (AActor): Actor releasing the object

```cpp
void ReleaseSmartObject(UObject* WorldContextObject, AActor* SmartObject, AActor* User);
```

**Usage**: Free smart objects when interactions are complete.

#### GetSmartObjectState
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `SmartObject`  
**Returns**: `ESmartObjectState`  
**Purpose**: Get current state of a smart object

**Parameters**:
- `SmartObject` (AActor): Smart object to check

```cpp
ESmartObjectState GetSmartObjectState(UObject* WorldContextObject, AActor* SmartObject);
```

**Usage**: Check availability and current usage state of smart objects.

### Sittable Object Functions

#### SitOnObject
**Type**: `BlueprintCallable`  
**Category**: `SmartObject|Sittable`  
**Returns**: `bool`  
**Purpose**: Make an actor sit on a sittable object

**Parameters**:
- `SittableObject` (AActor): Object to sit on
- `Actor` (AActor): Actor who will sit
- `SeatIndex` (int32): Specific seat to use (if multi-seat object)

```cpp
bool SitOnObject(UObject* WorldContextObject, AActor* SittableObject, AActor* Actor, int32 SeatIndex = 0);
```

**Usage**: Execute sitting animations and position actors on benches, chairs, etc.

#### StandUpFromObject
**Type**: `BlueprintCallable`  
**Category**: `SmartObject|Sittable`  
**Purpose**: Make an actor stand up from a sittable object

**Parameters**:
- `SittableObject` (AActor): Object to stand up from
- `Actor` (AActor): Actor who will stand up

```cpp
void StandUpFromObject(UObject* WorldContextObject, AActor* SittableObject, AActor* Actor);
```

**Usage**: Exit sitting interactions and return to normal movement.

#### GetAvailableSeats
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `SmartObject|Sittable`  
**Returns**: `TArray<int32>`  
**Purpose**: Get list of available seat indices on a multi-seat object

**Parameters**:
- `SittableObject` (AActor): Object to check for available seats

```cpp
TArray<int32> GetAvailableSeats(UObject* WorldContextObject, AActor* SittableObject);
```

**Usage**: Find open seats on benches or multi-person furniture.

### Mountable Object Functions

#### MountObject
**Type**: `BlueprintCallable`  
**Category**: `SmartObject|Mountable`  
**Returns**: `bool`  
**Purpose**: Mount an actor onto a mountable object

**Parameters**:
- `MountableObject` (AActor): Object to mount
- `Rider` (AActor): Actor who will mount
- `MountPoint` (FName): Specific mount point to use

```cpp
bool MountObject(UObject* WorldContextObject, AActor* MountableObject, AActor* Rider, FName MountPoint = NAME_None);
```

**Usage**: Handle mounting animations and attachment for horses, vehicles, etc.

#### DismountObject
**Type**: `BlueprintCallable`  
**Category**: `SmartObject|Mountable`  
**Purpose**: Dismount an actor from a mountable object

**Parameters**:
- `MountableObject` (AActor): Object to dismount from
- `Rider` (AActor): Actor who will dismount

```cpp
void DismountObject(UObject* WorldContextObject, AActor* MountableObject, AActor* Rider);
```

**Usage**: Handle dismounting animations and return to normal movement.

#### GetMountCapacity
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `SmartObject|Mountable`  
**Returns**: `int32`  
**Purpose**: Get maximum number of riders for a mountable object

**Parameters**:
- `MountableObject` (AActor): Object to check capacity for

```cpp
int32 GetMountCapacity(UObject* WorldContextObject, AActor* MountableObject);
```

**Usage**: Determine how many actors can simultaneously use a mount.

### Assassination Sync Functions

#### RegisterAssassinationTarget
**Type**: `BlueprintCallable`  
**Category**: `SmartObject|Assassination`  
**Returns**: `bool`  
**Purpose**: Register a target for assassination sync points

**Parameters**:
- `Target` (AActor): Actor that can be assassination target
- `SyncPoints` (TArray<AActor*>): Smart objects that can sync with this target

```cpp
bool RegisterAssassinationTarget(UObject* WorldContextObject, AActor* Target, const TArray<AActor*>& SyncPoints);
```

**Usage**: Set up coordinated assassination opportunities for stealth gameplay.

#### ExecuteAssassination
**Type**: `BlueprintCallable`  
**Category**: `SmartObject|Assassination`  
**Returns**: `bool`  
**Purpose**: Execute a coordinated assassination using sync points

**Parameters**:
- `Assassin` (AActor): Actor performing the assassination
- `Target` (AActor): Target to be assassinated
- `SyncPoint` (AActor): Smart object coordinating the assassination

```cpp
bool ExecuteAssassination(UObject* WorldContextObject, AActor* Assassin, AActor* Target, AActor* SyncPoint);
```

**Usage**: Trigger synchronized takedown animations and effects.

#### GetNearbyAssassinationOpportunities
**Type**: `BlueprintCallable`  
**Category**: `SmartObject|Assassination`  
**Returns**: `TArray<FAssassinationOpportunity>`  
**Purpose**: Find assassination opportunities near a location

**Parameters**:
- `Location` (FVector): Location to search from
- `SearchRadius` (float): Range to search within
- `Assassin` (AActor): Actor looking for opportunities

```cpp
TArray<FAssassinationOpportunity> GetNearbyAssassinationOpportunities(UObject* WorldContextObject, const FVector& Location, float SearchRadius, AActor* Assassin);
```

**Usage**: Present stealth gameplay options to players or AI.

## Notes on Engine Alignment

- Registration: when bridging is enabled on `DAISmartObjectComponent` (default true), a transient `USmartObjectComponent` is attached or an existing one is reused and registered with `USmartObjectSubsystem` on BeginPlay. This keeps assets unmodified while enabling full engine participation.
- Definitions: set `DefinitionAsset` to point at a Smart Object Definition asset. If omitted, `SlotSyncPoints` still drive alignment and the DAI lightweight registry and queries continue to work.
- Queries: DAI provides Blueprint-friendly queries (`FindNearestUsableSmartObjectSlot`, `QueryUsableSmartObjectSlots`) that work in both lightweight and engine-bridged modes.
- Independence: No hard dependency on DAI_Hub or other plugins is introduced by the bridge.

Migration tips:
- Existing actors that already have an Engine `USmartObjectComponent` are detected and reused automatically.
- You can enable/disable bridging per-instance with `bBridgeToEngineSmartObjects` to opt in or out at runtime.

Service fallback:
- The provided `UDAI_SmartObjectServiceImpl` will attempt to use the Engine `USmartObjectSubsystem` when an engine
    `USmartObjectComponent` is present; otherwise it falls back to the lightweight `UDAISmartObjectComponent` APIs
    (e.g., `ReserveSlotForUser`). This keeps gameplay code decoupled while supporting both modes.

## Blueprint Data Types

### ESmartObjectState (Smart Object State)
**Type**: `BlueprintType Enum`  
**Purpose**: Current state of a smart object

**Values**:
- `Available`: Object is free and can be used
- `Claimed`: Object is reserved but not yet in use
- `InUse`: Object is currently being used
- `Disabled`: Object is temporarily disabled
- `Broken`: Object is broken and cannot be used

### EInteractionType (Interaction Type)
**Type**: `BlueprintType Enum`  
**Purpose**: Type of interaction with smart object

**Values**:
- `Sit`: Sitting interaction
- `Mount`: Mounting interaction
- `Assassinate`: Assassination sync interaction
- `Hide`: Hiding/cover interaction
- `Craft`: Crafting station interaction
- `Trade`: Trading/merchant interaction
- `Custom`: User-defined interaction type

### FSmartObjectSlot (Smart Object Slot)
**Type**: `BlueprintType Struct`  
**Purpose**: Individual interaction slot within a smart object

**Properties**:
- `SlotIndex` (int32): Unique index for this slot
- `SlotType` (EInteractionType): Type of interaction this slot supports
- `Transform` (FTransform): World transform for this slot
- `bIsOccupied` (bool): Whether this slot is currently in use
- `CurrentUser` (AActor): Actor currently using this slot
- `Tags` (FGameplayTagContainer): Additional tags for this slot

### FSittableSettings (Sittable Settings)
**Type**: `BlueprintType Struct`  
**Purpose**: Configuration for sittable objects

**Properties**:
- `SeatCount` (int32): Number of available seats
- `SeatSpacing` (float): Distance between seats
- `SitAnimation` (UAnimMontage): Animation to play when sitting
- `StandAnimation` (UAnimMontage): Animation to play when standing
- `bAutoFaceForward` (bool): Whether to automatically orient sitters
- `ComfortRadius` (float): Radius around seat for comfort calculation

### FMountableSettings (Mountable Settings)
**Type**: `BlueprintType Struct`  
**Purpose**: Configuration for mountable objects

**Properties**:
- `MountPoints` (TArray<FName>): Available mount point names
- `MaxRiders` (int32): Maximum number of simultaneous riders
- `MountAnimation` (UAnimMontage): Animation for mounting
- `DismountAnimation` (UAnimMontage): Animation for dismounting
- `bRequireApproachAngle` (bool): Whether mounting requires specific approach angle
- `ApproachAngle` (float): Required approach angle in degrees

### FAssassinationOpportunity (Assassination Opportunity)
**Type**: `BlueprintType Struct`  
**Purpose**: Information about an assassination opportunity

**Properties**:
- `Target` (AActor): Target that can be assassinated
- `SyncPoint` (AActor): Smart object for coordinated assassination
- `AssassinPosition` (FVector): Position where assassin should be
- `TargetPosition` (FVector): Position where target should be
- `RequiredTags` (FGameplayTagContainer): Tags required for this opportunity
- `Difficulty` (float): Difficulty rating of this assassination

### FSmartObjectInteraction (Smart Object Interaction)
**Type**: `BlueprintType Struct`  
**Purpose**: Complete interaction configuration

**Properties**:
- `InteractionType` (EInteractionType): Type of interaction
- `User` (AActor): Actor performing the interaction
- `SmartObject` (AActor): Object being interacted with
- `SlotIndex` (int32): Slot being used
- `StartTime` (float): When interaction began
- `Duration` (float): How long interaction should last
- `bIsCompleted` (bool): Whether interaction has finished

## Component Properties

### DAISmartObjectComponent Properties

#### Basic Configuration
**Property**: `ObjectType`  
**Type**: `FGameplayTag`  
**Category**: `Smart Object`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Type classification for this smart object

**Property**: `InteractionTypes`  
**Type**: `FGameplayTagContainer`  
**Category**: `Smart Object`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Types of interactions this object supports

**Property**: `MaxSimultaneousUsers`  
**Type**: `int32`  
**Category**: `Smart Object`  
**Blueprint Access**: `Read/Write`  
**Default**: `1`  
**Purpose**: Maximum number of actors that can use this object simultaneously

#### Availability Settings
**Property**: `bIsEnabled`  
**Type**: `bool`  
**Category**: `Smart Object`  
**Blueprint Access**: `Read/Write`  
**Default**: `true`  
**Purpose**: Whether this object is currently available for interaction

**Property**: `RequiredTags`  
**Type**: `FGameplayTagContainer`  
**Category**: `Smart Object`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Tags required for actors to interact with this object

### DAISittableComponent Properties

#### Seating Configuration
**Property**: `SeatCount`  
**Type**: `int32`  
**Category**: `Sittable`  
**Blueprint Access**: `Read/Write`  
**Default**: `1`  
**Purpose**: Number of seats available on this object

**Property**: `SeatSpacing`  
**Type**: `float`  
**Category**: `Sittable`  
**Blueprint Access**: `Read/Write`  
**Default**: `100.0`  
**Purpose**: Distance between seats for multi-seat objects

#### Animation Settings
**Property**: `SitAnimation`  
**Type**: `UAnimMontage*`  
**Category**: `Sittable`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Animation montage to play when sitting down

**Property**: `IdleAnimation`  
**Type**: `UAnimMontage*`  
**Category**: `Sittable`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Animation to loop while sitting

**Property**: `StandAnimation`  
**Type**: `UAnimMontage*`  
**Category**: `Sittable`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Animation montage to play when standing up

### DAIMountableComponent Properties

#### Mount Configuration
**Property**: `MountType`  
**Type**: `EMountType`  
**Category**: `Mountable`  
**Blueprint Access**: `Read/Write`  
**Default**: `Horse`  
**Purpose**: Type of mount this object represents

**Property**: `MaxRiders`  
**Type**: `int32`  
**Category**: `Mountable`  
**Blueprint Access**: `Read/Write`  
**Default**: `1`  
**Purpose**: Maximum number of riders this mount can support

#### Movement Settings
**Property**: `MovementSpeed`  
**Type**: `float`  
**Category**: `Mountable`  
**Blueprint Access**: `Read/Write`  
**Default**: `600.0`  
**Purpose**: Movement speed when mounted

**Property**: `bCanFly`  
**Type**: `bool`  
**Category**: `Mountable`  
**Blueprint Access**: `Read/Write`  
**Default**: `false`  
**Purpose**: Whether this mount can fly

### DAIAssassinationSyncComponent Properties

#### Assassination Settings
**Property**: `AssassinationType`  
**Type**: `EAssassinationType`  
**Category**: `Assassination`  
**Blueprint Access**: `Read/Write`  
**Default**: `Stealth`  
**Purpose**: Type of assassination this point supports

**Property**: `RequiredApproachAngle`  
**Type**: `float`  
**Category**: `Assassination`  
**Blueprint Access**: `Read/Write`  
**Default**: `45.0`  
**Purpose**: Angle from which assassination must be approached

#### Timing Configuration
**Property**: `SyncWindowDuration`  
**Type**: `float`  
**Category**: `Assassination`  
**Blueprint Access**: `Read/Write`  
**Default**: `2.0`  
**Purpose**: Time window for coordinated assassination execution

**Property**: `PrepareTime`  
**Type**: `float`  
**Category**: `Assassination`  
**Blueprint Access**: `Read/Write`  
**Default**: `1.0`  
**Purpose**: Time needed to prepare for assassination

## Events and Delegates

### OnSmartObjectClaimed
**Type**: `Dynamic Multicast Delegate`  
**Category**: `SmartObject`  
**Purpose**: Fired when a smart object is claimed

**Parameters**:
- `SmartObject` (AActor): Object that was claimed
- `User` (AActor): Actor who claimed it
- `InteractionType` (FGameplayTag): Type of interaction

**Usage**: Update UI, trigger effects, or notify other systems of object reservation.

### OnInteractionStarted
**Type**: `Dynamic Multicast Delegate`  
**Category**: `SmartObject`  
**Purpose**: Fired when an interaction begins

**Parameters**:
- `SmartObject` (AActor): Object being interacted with
- `User` (AActor): Actor starting the interaction
- `SlotIndex` (int32): Slot being used

**Usage**: Play animations, effects, or update interaction UI.

### OnInteractionCompleted
**Type**: `Dynamic Multicast Delegate`  
**Category**: `SmartObject`  
**Purpose**: Fired when an interaction completes

**Parameters**:
- `SmartObject` (AActor): Object that was interacted with
- `User` (AActor): Actor who completed the interaction
- `bWasSuccessful` (bool): Whether interaction completed successfully

**Usage**: Clean up interaction state, trigger rewards, or update progression.

### OnAssassinationExecuted
**Type**: `Dynamic Multicast Delegate`  
**Category**: `SmartObject|Assassination`  
**Purpose**: Fired when a coordinated assassination is executed

**Parameters**:
- `Assassin` (AActor): Actor performing the assassination
- `Target` (AActor): Target being assassinated
- `SyncPoint` (AActor): Smart object coordinating the assassination

**Usage**: Play dramatic effects, update stealth status, or trigger story events.

## Developer Settings

Access via **Project Settings → Game → DAI Smart Object**

### General Settings

#### Smart Object Management
**Property**: `bEnableSmartObjects`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to enable smart object system

**Property**: `MaxActiveInteractions`  
**Type**: `int32`  
**Default**: `100`  
**Range**: `10-1000`  
**Purpose**: Maximum number of simultaneous smart object interactions

**Property**: `InteractionUpdateFrequency`  
**Type**: `float`  
**Default**: `0.1`  
**Range**: `0.01-1.0`  
**Purpose**: Seconds between smart object interaction updates

#### Performance Settings
**Property**: `SmartObjectCullDistance`  
**Type**: `float`  
**Default**: `2000.0`  
**Range**: `500.0-10000.0`  
**Purpose**: Distance at which to cull smart object processing

**Property**: `bUseDistanceCulling`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to cull distant smart objects for performance

### Interaction Settings

#### Animation Configuration
**Property**: `DefaultSitAnimation`  
**Type**: `UAnimMontage*`  
**Purpose**: Default animation for sitting interactions

**Property**: `DefaultMountAnimation`  
**Type**: `UAnimMontage*`  
**Purpose**: Default animation for mounting interactions

**Property**: `DefaultAssassinationAnimation`  
**Type**: `UAnimMontage*`  
**Purpose**: Default animation for assassination interactions

#### Timing Settings
**Property**: `DefaultInteractionDuration`  
**Type**: `float`  
**Default**: `2.0`  
**Range**: `0.1-10.0`  
**Purpose**: Default duration for timed interactions

**Property**: `InteractionTimeoutDuration`  
**Type**: `float`  
**Default**: `30.0`  
**Range**: `5.0-300.0`  
**Purpose**: Time before uncompleted interactions timeout

### Assassination Settings

#### Stealth Configuration
**Property**: `bRequireStealthForAssassination`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether assassinations require stealth state

**Property**: `AssassinationDetectionRadius`  
**Type**: `float`  
**Default**: `500.0`  
**Range**: `100.0-2000.0`  
**Purpose**: Radius within which assassinations can be detected

**Property**: `AssassinationNoiseLevel`  
**Type**: `float`  
**Default**: `0.3`  
**Range**: `0.0-1.0`  
**Purpose**: Noise level generated by assassinations

### Debug Settings

#### Visualization
**Property**: `bDrawSmartObjectDebug`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to draw smart object debug information

**Property**: `bDrawInteractionRanges`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to visualize interaction ranges

**Property**: `bDrawAssassinationOpportunities`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to visualize assassination opportunities

#### Logging
**Property**: `bLogSmartObjectEvents`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to log smart object interaction events

## Usage Examples

### Basic Smart Object Setup
```blueprint
// Create a basic sittable bench
void SetupBench()
{
    // Add smart object component
    UDAISittableComponent* SittableComp = CreateDefaultSubobject<UDAISittableComponent>("SittableComponent");
    
    // Configure seating
    SittableComp->SeatCount = 3;
    SittableComp->SeatSpacing = 80.0f;
    SittableComp->SitAnimation = BenchSitAnimation;
    SittableComp->IdleAnimation = BenchIdleAnimation;
    SittableComp->StandAnimation = BenchStandAnimation;
    
    // Set interaction types
    SittableComp->InteractionTypes.AddTag(FGameplayTag::RequestGameplayTag("Interaction.Sit"));
    SittableComp->ObjectType = FGameplayTag::RequestGameplayTag("SmartObject.Furniture.Bench");
}

// Handle player interaction with bench
void OnPlayerInteractWithBench(APlayerController* Player, AActor* Bench)
{
    // Find available seat
    TArray<int32> AvailableSeats = UDAISmartObjectBlueprintLibrary::GetAvailableSeats(this, Bench);
    
    if (AvailableSeats.Num() > 0)
    {
        // Claim and sit on the bench
        bool bClaimed = UDAISmartObjectBlueprintLibrary::ClaimSmartObject(
            this,
            Bench,
            Player->GetPawn(),
            FGameplayTag::RequestGameplayTag("Interaction.Sit")
        );
        
        if (bClaimed)
        {
            bool bSat = UDAISmartObjectBlueprintLibrary::SitOnObject(
                this,
                Bench,
                Player->GetPawn(),
                AvailableSeats[0]
            );
            
            if (bSat)
            {
                // Show sitting UI or disable movement
                SetPlayerSittingState(Player, true);
            }
        }
    }
    else
    {
        ShowMessage(Player, "Bench is full");
    }
}
```

### Mount System Implementation
```blueprint
// Create a horse mount
void SetupHorseMount()
{
    UDAIMountableComponent* MountComp = CreateDefaultSubobject<UDAIMountableComponent>("MountableComponent");
    
    // Configure mount settings
    MountComp->MountType = EMountType::Horse;
    MountComp->MaxRiders = 1;
    MountComp->MovementSpeed = 800.0f;
    MountComp->bCanFly = false;
    
    // Set animations
    MountComp->MountAnimation = HorseMountAnimation;
    MountComp->DismountAnimation = HorseDismountAnimation;
    
    // Configure interaction
    MountComp->InteractionTypes.AddTag(FGameplayTag::RequestGameplayTag("Interaction.Mount"));
    MountComp->ObjectType = FGameplayTag::RequestGameplayTag("SmartObject.Mount.Horse");
}

// Handle mounting
void OnPlayerMountHorse(APlayerController* Player, AActor* Horse)
{
    bool bMounted = UDAISmartObjectBlueprintLibrary::MountObject(
        this,
        Horse,
        Player->GetPawn(),
        NAME_None // Use default mount point
    );
    
    if (bMounted)
    {
        // Switch to mounted movement mode
        SetPlayerMountedState(Player, Horse);
        
        // Update camera for mounted view
        UpdateCameraForMount(Player, Horse);
        
        // Enable mount controls
        EnableMountControls(Player);
    }
}

// Handle dismounting
void OnPlayerDismount(APlayerController* Player)
{
    AActor* CurrentMount = GetPlayerCurrentMount(Player);
    if (CurrentMount)
    {
        UDAISmartObjectBlueprintLibrary::DismountObject(this, CurrentMount, Player->GetPawn());
        
        // Return to normal movement
        SetPlayerMountedState(Player, nullptr);
        
        // Reset camera
        ResetCameraAfterMount(Player);
        
        // Disable mount controls
        DisableMountControls(Player);
    }
}
```

### Assassination Sync Points
```blueprint
// Set up assassination sync point
void SetupAssassinationPoint()
{
    UDAIAssassinationSyncComponent* AssassinComp = CreateDefaultSubobject<UDAIAssassinationSyncComponent>("AssassinationSync");
    
    // Configure assassination settings
    AssassinComp->AssassinationType = EAssassinationType::Stealth;
    AssassinComp->RequiredApproachAngle = 30.0f;
    AssassinComp->SyncWindowDuration = 3.0f;
    AssassinComp->PrepareTime = 1.5f;
    
    // Set interaction type
    AssassinComp->InteractionTypes.AddTag(FGameplayTag::RequestGameplayTag("Interaction.Assassinate"));
    AssassinComp->ObjectType = FGameplayTag::RequestGameplayTag("SmartObject.Assassination.Cover");
}

// Find and execute assassination opportunities
void CheckForAssassinationOpportunities(AActor* Assassin)
{
    TArray<FAssassinationOpportunity> Opportunities = 
        UDAISmartObjectBlueprintLibrary::GetNearbyAssassinationOpportunities(
            this,
            Assassin->GetActorLocation(),
            1000.0f,
            Assassin
        );
    
    for (const FAssassinationOpportunity& Opportunity : Opportunities)
    {
        // Check if player meets requirements
        if (CanExecuteAssassination(Assassin, Opportunity))
        {
            // Show assassination prompt
            ShowAssassinationPrompt(Assassin, Opportunity);
            break; // Show only the best opportunity
        }
    }
}

// Execute assassination
void ExecutePlayerAssassination(AActor* Assassin, const FAssassinationOpportunity& Opportunity)
{
    bool bExecuted = UDAISmartObjectBlueprintLibrary::ExecuteAssassination(
        this,
        Assassin,
        Opportunity.Target,
        Opportunity.SyncPoint
    );
    
    if (bExecuted)
    {
        // Play dramatic effects
        PlayAssassinationEffects(Opportunity.SyncPoint);
        
        // Update stealth meter
        ModifyStealthMeter(Assassin, -0.2f); // Slight stealth penalty
        
        // Award experience
        GiveAssassinationExperience(Assassin, Opportunity.Difficulty);
    }
}
```

### AI Integration with Smart Objects
```blueprint
// AI behavior for using smart objects
void AIFindAndUseSmartObject(AActor* AICharacter, FGameplayTag ObjectType)
{
    // Find nearby objects of desired type
    TArray<AActor*> NearbyObjects = UDAISmartObjectBlueprintLibrary::FindSmartObjectsNear(
        this,
        AICharacter->GetActorLocation(),
        500.0f,
        FGameplayTagContainer(ObjectType),
        true // Require available
    );
    
    if (NearbyObjects.Num() > 0)
    {
        // Choose closest available object
        AActor* ChosenObject = NearbyObjects[0];
        
        // Move to object and use it
        NavigateToSmartObject(AICharacter, ChosenObject);
    }
}

// Navigate to and use smart object
void NavigateToSmartObject(AActor* AICharacter, AActor* SmartObject)
{
    // Get AI controller
    AAIController* AIController = Cast<AAIController>(AICharacter->GetInstigatorController());
    if (AIController)
    {
        // Move to smart object
        AIController->MoveToActor(SmartObject, 100.0f);
        
        // Set up completion callback
        FAIMoveCompletedSignature::CreateUObject(this, &AMyGameMode::OnAIMoveToSmartObjectComplete);
    }
}

// Handle AI reaching smart object
void OnAIMoveToSmartObjectComplete(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    if (Result.IsSuccess())
    {
        // Use the smart object based on its type
        AActor* SmartObject = GetAITargetSmartObject(RequestID);
        AActor* AICharacter = GetAICharacterFromRequest(RequestID);
        
        UseSmartObjectForAI(AICharacter, SmartObject);
    }
}
```

## Integration with Other Plugins

### DAI_Hub Integration
- **Service Registration**: Smart object subsystem registers with hub for discovery
- **Event Publishing**: Interaction events published through hub system
- **Performance Coordination**: Respects hub performance budgets

### DAI_Navigation Integration (formerly DAI__Navigation)
- **Path Integration**: Smart objects can define custom navigation paths
- **Approach Points**: Navigation system can path to smart object interaction points
- **Movement Coordination**: Smooth transitions between navigation and interaction

### DAI_AI Integration
- **Behavior Integration**: AI characters can autonomously use smart objects
- **Decision Making**: Smart objects factor into AI behavior planning
- **Animation Coordination**: AI animations sync with smart object interactions

### DAI_QuestManager Integration
- **Quest Objectives**: Smart object interactions can complete quest objectives
- **Progress Tracking**: Interaction events automatically update quest progress
- **Conditional Availability**: Smart objects can be gated by quest progress

## Best Practices

### Smart Object Design
1. **Design clear interaction affordances** so players understand what objects do
2. **Use consistent interaction types** across similar objects
3. **Provide visual feedback** for interaction availability and progress
4. **Test accessibility** from multiple approach angles and heights
5. **Consider multiplayer scenarios** with multiple simultaneous users

### Performance Optimization
1. **Use distance culling** to disable distant smart objects
2. **Limit concurrent interactions** to maintain performance
3. **Cache frequent lookups** rather than searching repeatedly
4. **Monitor interaction complexity** and optimize expensive operations
5. **Profile AI pathfinding** to smart objects for bottlenecks

### Animation Integration
1. **Design smooth transitions** between normal movement and interactions
2. **Align animation timing** with interaction durations
3. **Provide interrupt handling** for cancelled interactions
4. **Test with various character sizes** and proportions
5. **Create fallback animations** for edge cases

### User Experience
1. **Provide clear interaction prompts** when objects are available
2. **Handle edge cases gracefully** (interrupted interactions, conflicts, etc.)
3. **Give meaningful feedback** for why interactions might fail
4. **Support different input methods** (keyboard, controller, touch)
5. **Test usability** with different player skill levels

## Technical Notes

- **Thread Safety**: Smart object operations designed for game thread usage
- **Memory Management**: Efficient storage and cleanup of interaction data
- **Platform Support**: Cross-platform interaction handling
- **Performance**: Optimized search and state management systems
- **Integration**: Clean interfaces for extending smart object functionality

---

*For more information about navigation integration, see [DAI_Navigation documentation](DAI_Navigation.md).*  
*For hub integration details, see [DAI_Hub documentation](DAI_Hub.md).*  
*For AI integration, see [DAI_AI documentation](DAI_AI.md).*

---

Last updated: October 6, 2025