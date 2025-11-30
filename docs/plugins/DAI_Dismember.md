# DAI_Dismember Plugin Documentation

## Overview

**DAI_Dismember** is a comprehensive dismemberment system for Unreal Engine 5.5 that provides selective mesh part removal with visual effects and gameplay consequences. The system integrates with Unreal's Mutable framework and Gameplay Ability System (GAS) to deliver realistic limb severing, dynamic mesh modifications, and performance-optimized representation modes.

### Key Features
- 🔪 **Selective Dismemberment**: Remove specific body parts with precision
- 🎨 **Mutable Integration**: Dynamic mesh generation and modification
- 🎯 **Gameplay Integration**: GAS-based ability system integration
- 📊 **Performance Management**: Multiple representation modes for optimization
- 🩺 **Limb Health System**: Health tracking for individual body parts
- 🎮 **Blueprint Friendly**: Extensive Blueprint integration for designers
- 💾 **Save System**: Persistent dismemberment state through DAI_Save
- 🔧 **Configurable**: Extensive settings for customization

## Architecture

The DAI_Dismember system consists of:
- **Dismember Subsystem**: Central coordination and performance management
- **Limb Health Components**: Individual body part health tracking
- **Mutable Integration**: Dynamic mesh generation and modification
- **Performance Bridge**: Integration with DAI_PerfMngr for optimization
- **Save Integration**: Persistent state management

## Core Components

### DAI_DismemberSubsystem
*World subsystem managing all dismemberment operations*

**Type**: `World Subsystem`  
**Interfaces**: `IDAIDismemberService`, `IDAISaveFragmentProvider`  
**File**: `DAI_DismemberSubsystem.h`

Central service for dismemberment operations, performance management, and save state handling.

### DAI_LimbHealth
*Component for individual limb health tracking*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `DAI|Dismember`  
**File**: `DAI_LimbHealth.h`

Manages health and state for individual body parts with dismemberment triggers.

### DAI_PerfBridgeComponent
*Performance management integration component*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `DAI|Performance`  
**File**: `DAI_PerfBridgeComponent.h`

Bridges dismemberment system with performance management for optimization.

## Blueprint Functions

### Dismemberment Operations

#### SeverLimb
**Type**: `BlueprintCallable`  
**Category**: `DAI|Dismember`  
**Returns**: `bool`  
**Purpose**: Sever a specific limb with optional effects

**Parameters**:
- `Owner` (AActor): Actor to dismember
- `LimbID` (FName): Identifier of the limb to sever
- `SeverMode` (EDAI_SeverMode): How to handle the severing (cut, tear, etc.)
- `SpawnSeveredPart` (bool): Whether to spawn the severed part as a separate actor

```cpp
bool SeverLimb(AActor* Owner, FName LimbID, EDAI_SeverMode SeverMode, bool SpawnSeveredPart = true);
```

**Usage**: Primary function for removing limbs from characters during combat or events.

#### RestoreLimb
**Type**: `BlueprintCallable`  
**Category**: `DAI|Dismember`  
**Returns**: `bool`  
**Purpose**: Restore a previously severed limb

**Parameters**:
- `Owner` (AActor): Actor to restore limb on
- `LimbID` (FName): Identifier of the limb to restore

```cpp
bool RestoreLimb(AActor* Owner, FName LimbID);
```

**Usage**: Useful for healing abilities, save/load restoration, or special gameplay mechanics.

### Health Management

#### GetLimbHealth
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `DAI|Dismember`  
**Returns**: `float`  
**Purpose**: Get current health of a specific limb

**Parameters**:
- `LimbID` (FName): Identifier of the limb to check

```cpp
float GetLimbHealth(FName LimbID) const;
```

**Usage**: Query limb health for UI display or gameplay decisions.

#### SetLimbHealth
**Type**: `BlueprintCallable`  
**Category**: `DAI|Dismember`  
**Purpose**: Set health of a specific limb

**Parameters**:
- `LimbID` (FName): Identifier of the limb
- `NewHealth` (float): New health value
- `bTriggerEvents` (bool): Whether to trigger health change events

```cpp
void SetLimbHealth(FName LimbID, float NewHealth, bool bTriggerEvents = true);
```

**Usage**: Direct health modification for damage application or restoration.

#### DamageLimb
**Type**: `BlueprintCallable`  
**Category**: `DAI|Dismember`  
**Purpose**: Apply damage to a specific limb

**Parameters**:
- `LimbID` (FName): Identifier of the limb to damage
- `DamageAmount` (float): Amount of damage to apply
- `DamageType` (TSubclassOf<UDamageType>): Type of damage being applied

```cpp
void DamageLimb(FName LimbID, float DamageAmount, TSubclassOf<UDamageType> DamageType);
```

**Usage**: Apply targeted damage that may trigger dismemberment when health reaches zero.

### Representation Management

#### SetRepresentationMode
**Type**: `BlueprintCallable`  
**Category**: `DAI|Dismember`  
**Purpose**: Change how dismembered parts are represented

**Parameters**:
- `Owner` (AActor): Actor to modify
- `LimbID` (FName): Identifier of the limb
- `Mode` (EDAI_LimbRepresentation): New representation mode

```cpp
void SetRepresentationMode(AActor* Owner, FName LimbID, EDAI_LimbRepresentation Mode);
```

**Usage**: Performance optimization by switching between full mesh and simplified representations.

## Console Commands

The plugin provides convenient console commands (available in editor and PIE) for quick testing and debugging:

- `DAI.Dismember.ListSevered` — List all severed limbs in the current world.
- `DAI.Dismember.RestoreAll [ActorName]` — Restore all severed limbs for all actors, or for a specific actor if a name is provided.
- `DAI.Dismember.Sever <ActorName> <LimbID>` — Sever a specific limb on an actor by name.
- `DAI.Dismember.CombineToSingleMaterial <ActorName> [MaterialPath] [Priority]` — Request a Mutable-driven combine for the actor.
- `DAI.Dismember.MarkEquipmentChanged <ActorName> [Priority]` — Debounced request to re-combine after equipment/appearance changes.
- `DAI.Dismember.CombineStatus <ActorName>` — Print combine in-progress flag and last start time.

These are implemented via `UDAI_DismemberConsole` and require no additional setup.

## Blueprint Helpers

For designer workflows, a small Blueprint library is included:

- `GetSeveredLimbs(Owner, OutLimbIDs)` — Returns the severed limbs on an actor.
- `RestoreAllLimbs(Owner)` — Restores all severed limbs on an actor.
- `SeverLimbBP(Owner, LimbID)` — Sever a limb from Blueprints.

See `UDAI_DismemberBlueprintLibrary` in the C++ sources.

### Mutable Combine (Single Mesh/Material)

To assist with batching and performance, you can request a Mutable-driven “combine to single mesh/material” on any actor using the Performance Bridge component:

- Add component: `DAI Performance Bridge` to your actor.
- Call `CombineAllMeshesToSingleMaterialUsingMutable(SingleMaterialOverride, Priority)`.
- If Mutable is enabled in settings, your project’s Mutable API should perform the merge at runtime. This plugin ships a soft-integration placeholder and a graceful fallback that unifies materials on the primary mesh when Mutable isn’t present.

You can also trigger this via:

- Console: `DAI.Dismember.CombineToSingleMaterial <ActorName> [MaterialPath] [Priority]`
- Blueprints: `CombineActorMeshesToSingleMaterial(Owner, SingleMaterialOverride, Priority)`

For frequent appearance changes (e.g., gear swaps), prefer:

- Perf Bridge: `Schedule Mutable Combine(SingleMaterialOverride, Priority, DelaySeconds, bCoalesce)`
- Perf Bridge: `Mark Equipment Changed(Priority)` — a shorthand that debounces with coalescing.

Tip: Use `DAI.Dismember.Help` in the console to list all available commands.

Note: For full combine (true mesh merge and one material), wire this method to your Mutable runtime implementation in your project. The plugin does not hard-depend on Mutable.

#### Best-practice wiring (soft service interface)

To keep DAI_Dismember decoupled while enabling a real merge:

1. Implement `IDAI_MutableCombinerService` (C++ or Blueprint) and provide your Mutable pipeline in `CombineActorToSingleMesh(Actor, Material, Priority)`.
2. In Project Settings → DAI Dismember → Mutable → set `Mutable Combiner Service Class` to your service class.
3. Call `CombineAllMeshesToSingleMaterialUsingMutable(...)` from the Performance Bridge.

If the service is present, it will be invoked first. If it returns false or is not set, the component falls back to safe material unification.

The plugin ships a simple default service (`UDAI_DefaultMutableCombinerService`) which only unifies materials; for real geometry merging and atlasing, provide your own service that calls your Mutable graph.

#### Using Mutable State nodes
#### Async completion and status

- The Perf Bridge component broadcasts `OnMutableCombineCompleted(Owner, bSuccess)` when a combine finishes (service-initiated or fallback).
- Query status with `IsMutableCombineInProgress()` and `GetLastMutableCombineTime()`.
- Runtime tunables (CVars): `dai.Dismember.MutableCombineCooldown`, `dai.Dismember.MutableCombineWatchdog`.

## Runtime usage

Follow these steps to use DAI_Dismember at runtime (PIE, Standalone, or packaged builds):

1) Add the `DAI Performance Bridge` component to your character/actor Blueprints.
2) Configure Project Settings → DAI Dismember:
    - Enable Mutable Updates if you plan to use single-material combine.
    - Optionally set `Mutable Combine State Name` and `Mutable Combiner Service Class` (BP/C++) for your pipeline.
3) Drive behavior via Blueprint or C++:
    - Sever/restore using your own logic or the BP library (`SeverLimbBP`, `RestoreAllLimbs`).
    - For appearance changes (gear), call `MarkEquipmentChanged` on the Perf Bridge; it debounces and coalesces combines.
    - Optionally bind to `OnMutableCombineCompleted` to react after merges.
4) Tune performance at runtime using CVars (set in INI for packaged builds):
    - `dai.Dismember.MutableCombineCooldown` (seconds)
    - `dai.Dismember.MutableCombineWatchdog` (seconds)

Note: If `MutableCombinerServiceClass` is not provided or returns false, the system falls back to safe material unification on the primary mesh.

## Shipping notes

- The Dismember runtime module has no Editor-only dependencies; it builds for game targets.
- An optional Editor module adds Tools menu entries (Combine/MarkChanged/Status) in the editor only; it is excluded from packaged builds.
- Set CVar defaults in `DefaultEngine.ini` or `DefaultGame.ini` for packaged games if you need non-default cooldown/watchdog values.
- If your combiner service is a Blueprint, ensure it lives in a runtime plugin/module or game content (not Editor-only), and is referenced by `MutableCombinerServiceClass` in settings.

If your pipeline uses Mutable (Customizable Object) States, set up a dedicated State (e.g., `SingleMaterial`) that outputs one material slot and consolidated geometry. In your service implementation, switch the CO Instance to this State, set parameters (e.g., atlas size or quality), and trigger an update. You can store the State name in Project Settings → DAI Dismember → Mutable → `Mutable Combine State Name` and read it at runtime for consistency.

## Save Integration

DAI_Dismember integrates with DAI_Save using a soft-coupled fragment provider.

1. Open Project Settings → DAI Save → Fragment Providers.
2. Add class: `DAI_DismemberSaveProvider`.
3. The provider contributes a fragment named `Dismember` containing limb state (severed flags and health).
4. On load, the provider applies the saved state automatically.

No hard dependency on the save module is required; the provider will be invoked by name if present.

## Blueprint Data Types

### EDAI_SeverMode (Sever Mode)
**Type**: `BlueprintType Enum`  
**Purpose**: Defines how limbs are severed

**Values**:
- `Cut`: Clean severing with precise edges
- `Tear`: Rough tearing with jagged edges  
- `Burn`: Cauterized severing with burn effects
- `Freeze`: Frozen and shattered severing
- `Dissolve`: Gradual dissolution effect

### EDAI_LimbRepresentation (Limb Representation)
**Type**: `BlueprintType Enum`  
**Purpose**: Performance modes for representing dismembered parts

**Values**:
- `FullMesh`: Complete mesh with all details
- `SimplifiedMesh`: Reduced polygon mesh for distance viewing
- `Billboard`: 2D sprite representation for far distances
- `Hidden`: Completely hidden (no rendering)
- `Proxy`: Simple geometric proxy shape

### FDAI_SeverRequest (Sever Request)
**Type**: `BlueprintType Struct`  
**Purpose**: Complete request for limb severing

**Properties**:
- `LimbID` (FName): Identifier of the limb to sever
- `SeverMode` (EDAI_SeverMode): How to perform the severing
- `SpawnSeveredPart` (bool): Whether to create a separate actor for the severed part
- `EffectOverride` (UNiagaraSystem): Optional custom visual effect
- `SoundOverride` (USoundBase): Optional custom audio effect
- `DelaySeconds` (float): Delay before executing the sever

### FDAI_RepresentationHint (Representation Hint)
**Type**: `BlueprintType Struct`  
**Purpose**: Performance hint for representation optimization

**Properties**:
- `LimbID` (FName): Target limb identifier
- `SuggestedMode` (EDAI_LimbRepresentation): Recommended representation mode
- `Reason` (FString): Human-readable reason for the suggestion
- `Priority` (int32): Priority level for the hint

### FDAI_LimbHealthInfo (Limb Health Info)
**Type**: `BlueprintType Struct`  
**Purpose**: Complete health information for a limb

**Properties**:
- `LimbID` (FName): Limb identifier
- `CurrentHealth` (float): Current health value
- `MaxHealth` (float): Maximum health for this limb
- `bIsSevered` (bool): Whether this limb is currently severed
- `ResistanceTypes` (TMap<TSubclassOf<UDamageType>, float>): Damage type resistances

## Component Properties

### DAI_LimbHealth Properties

#### Limb Configuration
**Property**: `LimbID`  
**Type**: `FName`  
**Category**: `Limb Health`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Unique identifier for this limb

#### Health Settings
**Property**: `MaxHealth`  
**Type**: `float`  
**Category**: `Limb Health`  
**Blueprint Access**: `Read/Write`  
**Default**: `100.0`  
**Purpose**: Maximum health for this limb

**Property**: `CurrentHealth`  
**Type**: `float`  
**Category**: `Limb Health`  
**Blueprint Access**: `Read Only`  
**Replication**: `Yes`  
**Purpose**: Current health value (replicated for multiplayer)

#### Dismemberment Settings
**Property**: `bCanBeDismembered`  
**Type**: `bool`  
**Category**: `Limb Health`  
**Blueprint Access**: `Read/Write`  
**Default**: `true`  
**Purpose**: Whether this limb can be severed

**Property**: `DismemberThreshold`  
**Type**: `float`  
**Category**: `Limb Health`  
**Blueprint Access**: `Read/Write`  
**Default**: `0.0`  
**Purpose**: Health level below which limb is automatically severed

## Events and Delegates

### OnLimbSevered
**Type**: `Dynamic Multicast Delegate`  
**Category**: `DAI|Dismember`  
**Purpose**: Fired when a limb is successfully severed

**Parameters**:
- `Owner` (AActor): Actor that had limb severed
- `LimbID` (FName): Identifier of the severed limb
- `SeverMode` (EDAI_SeverMode): How the limb was severed

**Usage**: React to dismemberment events for gameplay consequences, effects, or achievements.

### OnLimbHealthChanged
**Type**: `Dynamic Multicast Delegate`  
**Category**: `DAI|Dismember`  
**Purpose**: Fired when limb health changes

**Parameters**:
- `LimbID` (FName): Identifier of the affected limb
- `OldHealth` (float): Previous health value
- `NewHealth` (float): New health value
- `DamageType` (TSubclassOf<UDamageType>): Type of damage that caused the change

**Usage**: Update UI, trigger visual effects, or activate gameplay mechanics based on limb damage.

### OnRepresentationChanged
**Type**: `Dynamic Multicast Delegate`  
**Category**: `DAI|Dismember`  
**Purpose**: Fired when limb representation mode changes

**Parameters**:
- `Owner` (AActor): Actor with changed representation
- `LimbID` (FName): Affected limb identifier
- `NewMode` (EDAI_LimbRepresentation): New representation mode

**Usage**: Track performance optimizations or update related systems.

## Developer Settings

Access via **Project Settings → Game → DAI Dismember**

### Performance Settings

#### Enable Performance Management
**Property**: `bEnablePerformanceManagement`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to use performance-based representation switching

Automatically switches limb representations based on distance and performance budget.

#### Max Concurrent Severs
**Property**: `MaxConcurrentSevers`  
**Type**: `int32`  
**Default**: `5`  
**Range**: `1-50`  
**Purpose**: Maximum number of limbs that can be severed simultaneously

Prevents performance spikes during mass dismemberment events.

#### Representation Distance Thresholds
**Property**: `RepresentationDistances`  
**Type**: `TArray<float>`  
**Default**: `[0, 500, 1000, 2000]`  
**Purpose**: Distance thresholds for automatic representation switching

Controls when limbs switch between full mesh, simplified, billboard, and hidden modes.

### Visual Effects Settings

#### Default Sever Effect
**Property**: `DefaultSeverEffect`  
**Type**: `UNiagaraSystem`  
**Purpose**: Default particle effect for limb severing

Used when no specific effect is provided in the sever request.

#### Default Sever Sound
**Property**: `DefaultSeverSound`  
**Type**: `USoundBase`  
**Purpose**: Default audio effect for limb severing

#### Blood Effect Settings
**Property**: `BloodEffectSettings`  
**Type**: `FDAI_BloodEffectSettings`  
**Purpose**: Configuration for blood and gore effects

Controls blood particle systems, decals, and material modifications.

### Mutable Integration Settings

#### Enable Mutable Updates
**Property**: `bEnableMutableUpdates`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to use Mutable system for dynamic mesh generation

When disabled, uses simpler mesh swapping techniques.

#### Mutable Update Timeout
**Property**: `MutableUpdateTimeout`  
**Type**: `float`  
**Default**: `5.0`  
**Range**: `1.0-30.0`  
**Purpose**: Maximum time to wait for Mutable updates before falling back

## Usage Examples

### Basic Limb Setup
```blueprint
// Add limb health component to character
UDAILimbHealthComponent* ArmHealth = CreateDefaultSubobject<UDAILimbHealthComponent>("LeftArmHealth");
ArmHealth->LimbID = "LeftArm";
ArmHealth->MaxHealth = 75.0f;
ArmHealth->bCanBeDismembered = true;
ArmHealth->DismemberThreshold = 0.0f;
```

### Combat Dismemberment
```blueprint
// In damage handling function
void OnTakeDamage(FName HitLimb, float DamageAmount, TSubclassOf<UDamageType> DamageType)
{
    UDAILimbHealthComponent* LimbHealth = GetLimbHealthComponent(HitLimb);
    if (LimbHealth)
    {
        LimbHealth->DamageLimb(HitLimb, DamageAmount, DamageType);
        
        // Check if limb should be severed
        if (LimbHealth->GetLimbHealth(HitLimb) <= 0.0f)
        {
            FDAI_SeverRequest SeverRequest;
            SeverRequest.LimbID = HitLimb;
            SeverRequest.SeverMode = EDAI_SeverMode::Cut;
            SeverRequest.SpawnSeveredPart = true;
            
            UDAI_DismemberSubsystem* DismemberSystem = GetWorld()->GetSubsystem<UDAI_DismemberSubsystem>();
            DismemberSystem->SeverLimb(this, SeverRequest);
        }
    }
}
```

### Performance Optimization
```blueprint
// Adjust representation based on distance
void UpdateLimbRepresentations(AActor* ViewerActor)
{
    float Distance = FVector::Dist(GetActorLocation(), ViewerActor->GetActorLocation());
    
    EDAI_LimbRepresentation TargetMode;
    if (Distance < 500.0f)
        TargetMode = EDAI_LimbRepresentation::FullMesh;
    else if (Distance < 1000.0f)
        TargetMode = EDAI_LimbRepresentation::SimplifiedMesh;
    else if (Distance < 2000.0f)
        TargetMode = EDAI_LimbRepresentation::Billboard;
    else
        TargetMode = EDAI_LimbRepresentation::Hidden;
    
    // Apply to all severed limbs
    for (FName SeveredLimb : SeveredLimbs)
    {
        DismemberSubsystem->SetRepresentationMode(this, SeveredLimb, TargetMode);
    }
}
```

### Healing and Restoration
```blueprint
// Magical limb restoration
void RestoreAllLimbs()
{
    UDAI_DismemberSubsystem* DismemberSystem = GetWorld()->GetSubsystem<UDAI_DismemberSubsystem>();
    
    for (FName LimbID : SeveredLimbs)
    {
        // Restore the limb
        if (DismemberSystem->RestoreLimb(this, LimbID))
        {
            // Restore health
            UDAILimbHealthComponent* LimbHealth = GetLimbHealthComponent(LimbID);
            if (LimbHealth)
            {
                LimbHealth->SetLimbHealth(LimbID, LimbHealth->MaxHealth, true);
            }
            
            // Play restoration effect
            PlayRestorationEffect(LimbID);
        }
    }
    
    SeveredLimbs.Empty();
}
```

## Integration with Other Plugins

### DAI_Hub Integration
- **Service Registration**: Dismember subsystem registers with hub for discovery
- **Event Publishing**: Dismemberment events published through hub
- **Performance Coordination**: Respects hub performance budgets

### DAI_PerfMngr Integration
- **Significance Management**: Limb representations adjust based on significance
- **Budget Monitoring**: Dismemberment operations respect performance budgets
- **Automatic Optimization**: LOD switching based on performance metrics

### DAI_Save Integration
- **State Persistence**: Dismemberment state saved automatically
- **Limb Health Saving**: Individual limb health values preserved
- **Representation State**: Current representation modes saved

### Gameplay Ability System
- **Ability Integration**: Dismemberment abilities can trigger severing
- **Attribute Effects**: Limb health can be modified through GAS attributes
- **Effect Integration**: Gameplay effects can affect dismemberment thresholds

## Best Practices

### Performance Optimization
1. **Use appropriate representation modes** based on viewing distance
2. **Limit concurrent severing operations** to prevent frame drops
3. **Cache limb health components** rather than searching repeatedly
4. **Monitor Mutable update performance** and adjust timeouts accordingly
5. **Use simplified meshes** for background characters

### Gameplay Design
1. **Design meaningful dismemberment consequences** for gameplay depth
2. **Balance limb health values** with overall character health
3. **Consider restoration mechanics** for player agency
4. **Use visual feedback** to communicate limb damage states
5. **Test dismemberment in multiplayer** for network performance

### Content Creation
1. **Create consistent limb naming conventions** across character assets
2. **Design severed part meshes** that match original geometry
3. **Prepare multiple representation LODs** for performance scaling
4. **Create appropriate blood and gore effects** for different sever modes
5. **Test with various character types** and sizes

### Technical Implementation
1. **Handle edge cases** like multiple simultaneous damage sources
2. **Implement proper cleanup** for severed part actors
3. **Use object pooling** for frequently spawned severed parts
4. **Monitor memory usage** with complex character hierarchies
5. **Test save/load thoroughly** with partial dismemberment states

## Technical Notes

- **Thread Safety**: All operations designed for game thread usage
- **Memory Management**: Automatic cleanup of temporary dismemberment data
- **Networking**: Full replication support for multiplayer dismemberment
- **Performance**: Optimized representation switching and culling
- **Mutable Integration**: Seamless dynamic mesh generation support

## Troubleshooting

### Dismemberment Not Working
1. Check that Mutable plugin is enabled and properly configured
2. Verify limb IDs match between health components and mesh data
3. Ensure dismemberment thresholds are set correctly
4. Check for conflicting performance settings

### Performance Issues
1. Monitor concurrent sever operations count
2. Check representation distance thresholds
3. Profile Mutable update performance
4. Review limb mesh complexity

### Visual Artifacts
1. Verify severed part meshes align with original geometry
2. Check material assignments on severed parts
3. Review blood effect settings and performance impact
4. Test representation switching at various distances

---

*For more information about performance management, see [DAI_PerfMngr documentation](DAI_PerfMngr.md).*  
*For hub integration details, see [DAI_Hub documentation](DAI_Hub.md).*  
*For save system integration, see [DAI_Save documentation](DAI_Save.md).*

---

Last updated: October 6, 2025