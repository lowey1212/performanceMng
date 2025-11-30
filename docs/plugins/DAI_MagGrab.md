# DAI_MagGrab Plugin Documentation

## Overview

**DAI_MagGrab** is a magnetic attraction and pickup system for Unreal Engine 5.5 that provides automatic object collection, magnetic attraction effects, and configurable interaction behaviors. The system is designed for efficient handling of pickups, collectibles, and magnetic interactions in games with performance optimization built-in.

### Key Features
- 🧲 **Magnetic Attraction**: Automatic object attraction with multiple movement styles
- 🎯 **Smart Pickup System**: Tag-based filtering and gating for precise control
- ⚡ **Performance Optimized**: Spatial grid and FPS-aware processing
- 🔧 **Configurable Presets**: Reusable settings for consistent behaviors
- 📊 **Multiple Movement Styles**: Straight, Spiral, Arc, Ease, and Wobble patterns
- 🏷️ **Tag-Based Filtering**: Gameplay tag integration for selective interactions
- 🔄 **State Management**: Clear state tracking for attracted objects

## Architecture

The DAI_MagGrab system consists of:
- **Attractor Components**: Objects that attract other objects
- **Attracted Components**: Objects that can be attracted
- **Magnetic Pickup Subsystem**: Global coordinator and performance manager
- **Preset System**: Reusable configuration templates
- **Tag Gating System**: Filter interactions based on gameplay tags

## Core Components

### DAI_MagneticAttractorComponent
*Component that attracts nearby compatible objects*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `Magnetic Attractor`  
**File**: `DAI_MagneticAttractorComponent.h`

Creates a magnetic field that attracts compatible objects within range.

### DAI_MagneticAttractedComponent
*Component that allows objects to be attracted by magnetic attractors*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `Magnetic Attracted`  
**File**: `DAI_MagneticAttractedComponent.h`

Makes an object capable of being attracted by magnetic attractor components.

### DAI_MagneticPickupSubsystem
*World subsystem managing global magnetic interaction processing*

**Type**: `Tickable World Subsystem`  
**Category**: `Magnetic Pickup`  
**File**: `DAI_MagneticPickupSubsystem.h`

Coordinates all magnetic interactions with performance budgeting and spatial optimization.

## Blueprint Functions

### Attractor Component Functions

#### ApplyPreset
**Type**: `BlueprintCallable`  
**Category**: `Magnetic Attractor`  
**Purpose**: Apply settings from a magnetic attractor preset

```cpp
void ApplyPreset();
```

**Usage**: Applies all settings from the assigned preset to this attractor component. Useful for runtime configuration changes.

## Blueprint Data Types

### EDAI_MagneticAttractorStyle (Attractor Style)
**Type**: `BlueprintType Enum`  
**Purpose**: Defines how attracted objects move toward the attractor

**Values**:
- `Straight`: Direct linear movement toward attractor
- `Spiral`: Spiral movement pattern while approaching
- `Arc`: Curved arc movement toward attractor
- `Ease`: Smooth easing movement with acceleration/deceleration
- `Wobble`: Oscillating movement pattern

### EDAI_MagneticAttractedState (Attracted State)
**Type**: `BlueprintType Enum`  
**Purpose**: Current state of an attracted object

**Values**:
- `Inactive`: Object is not currently being attracted
- `Attracting`: Object is moving toward an attractor
- `Snapped`: Object has reached the attractor and snapped to it

## Component Properties

### DAI_MagneticAttractorComponent Properties

#### Radius
**Property**: `Radius`  
**Type**: `float`  
**Category**: `Magnetic Attractor`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Maximum distance at which objects can be attracted

**Usage**: Objects within this radius will begin attraction. Larger values affect more objects but may impact performance.

#### Inner Radius
**Property**: `InnerRadius`  
**Type**: `float`  
**Category**: `Magnetic Attractor`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Distance at which attracted objects snap to the attractor

**Usage**: When objects get closer than this distance, they immediately snap to the attractor position.

#### Strength
**Property**: `Strength`  
**Type**: `float`  
**Category**: `Magnetic Attractor`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Force of magnetic attraction

**Usage**: Higher values cause faster attraction. Affects how quickly objects move toward the attractor.

#### Enabled
**Property**: `bEnabled`  
**Type**: `bool`  
**Category**: `Magnetic Attractor`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Whether this attractor is currently active

**Usage**: Can be toggled at runtime to enable/disable magnetic effects.

#### Movement Style
**Property**: `Style`  
**Type**: `EDAI_MagneticAttractorStyle`  
**Category**: `Magnetic Attractor`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Movement pattern for attracted objects

**Usage**: Changes how objects move toward the attractor (straight, spiral, arc, etc.).

#### Preset
**Property**: `Preset`  
**Type**: `UDAI_MagneticAttractorPreset*`  
**Category**: `Magnetic Attractor`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Preset configuration to apply to this attractor

**Usage**: Reference to a preset asset containing predefined settings.

### DAI_MagneticAttractedComponent Properties

#### Target Primitive
**Property**: `TargetPrimitive`  
**Type**: `UPrimitiveComponent*`  
**Category**: `Magnetic Attracted`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Specific primitive component to move (if not root)

**Usage**: If set, only this component moves. If null, the entire actor moves.

#### Allow Physics
**Property**: `bAllowPhysics`  
**Type**: `bool`  
**Category**: `Magnetic Attracted`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Whether physics objects can be attracted

**Usage**: When true, objects with physics simulation can be magnetically attracted.

#### Allow Kinematic
**Property**: `bAllowKinematic`  
**Type**: `bool`  
**Category**: `Magnetic Attracted`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Whether kinematic objects can be attracted

**Usage**: When true, kinematic objects (non-physics) can be magnetically attracted.

#### Allow Snap
**Property**: `bAllowSnap`  
**Type**: `bool`  
**Category**: `Magnetic Attracted`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Whether object can snap to attractor when close

**Usage**: When true, object snaps to attractor position when within inner radius.

#### Move Root Component
**Property**: `bMoveRootComponent`  
**Type**: `bool`  
**Category**: `Movement`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Move the actor's root component instead of target primitive

**Usage**: Override to move the entire actor rather than a specific component.

#### Require Enabled Tag
**Property**: `bRequireEnabledTag`  
**Type**: `bool`  
**Category**: `Filtering`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Whether attractor owners must have enabled tag

**Usage**: When true, only attractors with the enabled tag can affect this object.

#### Enabled Tag
**Property**: `EnabledTag`  
**Type**: `FName`  
**Category**: `Filtering`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Tag required on attractors for interaction

**Usage**: Attractor actors must have this tag to attract this object.

#### Use Blocked Tag
**Property**: `bUseBlockedTag`  
**Type**: `bool`  
**Category**: `Filtering`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Whether to check for blocked tags on attractors

**Usage**: When true, attractors with blocked tag cannot affect this object.

#### Blocked Tag
**Property**: `BlockedTag`  
**Type**: `FName`  
**Category**: `Filtering`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Tag that prevents interaction with attractors

**Usage**: Attractor actors with this tag cannot attract this object.

### DAI_MagneticPickupSubsystem Properties

#### Update Rate Hz
**Property**: `UpdateRateHz`  
**Type**: `float`  
**Category**: `Magnetic Pickup`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Frequency of magnetic system updates per second

**Usage**: Higher values provide smoother attraction but use more performance.

#### Max Pairs Per Step
**Property**: `MaxPairsPerStep`  
**Type**: `int32`  
**Category**: `Magnetic Pickup`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Maximum attractor-attracted pairs processed per update

**Usage**: Limits processing load per frame to maintain performance.

#### Max Targets Per Attractor
**Property**: `MaxTargetsPerAttractor`  
**Type**: `int32`  
**Category**: `Magnetic Pickup`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Maximum objects one attractor can affect simultaneously

**Usage**: Prevents single attractors from overwhelming the system.

#### Soft FPS Threshold
**Property**: `SoftFPSThreshold`  
**Type**: `float`  
**Category**: `Magnetic Pickup|Performance`  
**Blueprint Access**: `Read/Write`  
**Purpose**: FPS level at which to begin reducing magnetic processing

**Usage**: Performance optimization trigger for gradual load reduction.

#### Hard FPS Threshold
**Property**: `HardFPSThreshold`  
**Type**: `float`  
**Category**: `Magnetic Pickup|Performance`  
**Blueprint Access**: `Read/Write`  
**Purpose**: FPS level at which to severely limit magnetic processing

**Usage**: Emergency performance protection threshold.

#### Grid Cell Size
**Property**: `GridCellSize`  
**Type**: `float`  
**Category**: `Magnetic Pickup|Grid`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Size of spatial grid cells for optimization

**Usage**: Larger cells reduce overhead but may be less precise for small objects.

## Developer Settings

Access via **Project Settings → Game → DAI MagGrab**

### Filtering Settings

#### Required Tag
**Property**: `RequiredTag`  
**Type**: `FName`  
**Default**: `(empty)`  
**Purpose**: Global tag required for magnetic interactions

When set, actors must have this gameplay tag (on actor, component, or Ability System Component) to participate in magnetic interactions.

#### Blocked Tag
**Property**: `BlockedTag`  
**Type**: `FName`  
**Default**: `(empty)`  
**Purpose**: Global tag that prevents magnetic interactions

When set, actors with this gameplay tag cannot participate in magnetic interactions.

#### Search Gameplay Tags
**Property**: `bSearchGameplayTags`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to search Ability System Component tags

When enabled, the system searches ASC-owned gameplay tags if direct actor/component tag search fails.

#### Publish Failure Events
**Property**: `bPublishFailureEvents`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to publish hub events for gating failures

When enabled, publishes hub events when interactions fail due to tag gating (useful for debugging).

## Usage Examples

### Basic Magnetic Pickup Setup
```blueprint
// On pickup object (coin, health pack, etc.)
UDAIMagneticAttractedComponent* AttractedComp = CreateDefaultSubobject<UDAIMagneticAttractedComponent>("MagneticAttracted");
AttractedComp->bAllowPhysics = true;
AttractedComp->bAllowSnap = true;

// On player character
UDAIMagneticAttractorComponent* AttractorComp = CreateDefaultSubobject<UDAIMagneticAttractorComponent>("MagneticAttractor");
AttractorComp->Radius = 500.0f;
AttractorComp->InnerRadius = 50.0f;
AttractorComp->Strength = 1000.0f;
AttractorComp->Style = EDAI_MagneticAttractorStyle::Ease;
```

### Tag-Based Filtering
```blueprint
// Only attract objects with specific tags
AttractedComp->bRequireEnabledTag = true;
AttractedComp->EnabledTag = "Pickup.Magnetic";

// Prevent attraction by certain attractors
AttractedComp->bUseBlockedTag = true;
AttractedComp->BlockedTag = "Player.Sneaking";
```

### Runtime Configuration
```blueprint
// Toggle magnetic attraction at runtime
AttractorComp->bEnabled = false; // Disable attraction
AttractorComp->bEnabled = true;  // Re-enable attraction

// Apply preset configuration
AttractorComp->Preset = LoadObject<UDAI_MagneticAttractorPreset>("MyPreset");
AttractorComp->ApplyPreset();

// Dynamic strength adjustment
AttractorComp->Strength = FMath::Lerp(100.0f, 2000.0f, PowerLevel);
```

### Performance Tuning
```blueprint
// Access subsystem for performance tuning
UDAI_MagneticPickupSubsystem* MagSystem = GetWorld()->GetSubsystem<UDAI_MagneticPickupSubsystem>();

// Reduce update rate for better performance
MagSystem->UpdateRateHz = 30.0f; // Down from default 60

// Limit processing per frame
MagSystem->MaxPairsPerStep = 50;
MagSystem->MaxTargetsPerAttractor = 10;
```

### State Monitoring
```blueprint
// Check attraction state
EDAI_MagneticAttractedState CurrentState = AttractedComp->GetCurrentState();
switch (CurrentState)
{
    case EDAI_MagneticAttractedState::Inactive:
        // Object not being attracted
        break;
    case EDAI_MagneticAttractedState::Attracting:
        // Object moving toward attractor
        PlayAttractingEffect();
        break;
    case EDAI_MagneticAttractedState::Snapped:
        // Object reached attractor
        OnPickupCollected();
        break;
}
```

## Integration with Other Plugins

### DAI_Hub Integration
- **Tag Gating**: Uses hub's gameplay tag services for filtering
- **Event Publishing**: Can publish failure events through hub when enabled
- **Performance Coordination**: Respects hub performance budgets

### DAI_PerfMngr Integration  
- **FPS Monitoring**: Uses performance manager for frame rate tracking
- **Adaptive Processing**: Reduces load based on performance metrics
- **Budget Allocation**: Coordinates with performance budgeting system

### Gameplay Ability System
- **Tag Searching**: Can search ASC tags for filtering
- **Attribute Integration**: Can be gated by GAS attributes
- **Effect Integration**: Magnetic attraction can trigger GAS effects

## Best Practices

### Performance Optimization
1. **Tune update rates** based on your game's needs
2. **Use appropriate grid cell sizes** for your world scale
3. **Set reasonable radius limits** to avoid excessive processing
4. **Monitor FPS thresholds** and adjust as needed
5. **Limit targets per attractor** to prevent overload

### Design Guidelines
1. **Use consistent tag naming** for filtering systems
2. **Group similar objects** with shared settings via presets
3. **Provide visual feedback** for different attraction states
4. **Test with many objects** to ensure performance stability
5. **Consider audio feedback** for attraction events

### Tag System Usage
1. **Create hierarchical tags** (e.g., Pickup.Magnetic.Coin)
2. **Use blocked tags** for special game states (stealth, cutscenes)
3. **Enable ASC tag search** if using Gameplay Ability System
4. **Test tag interactions** thoroughly in multiplayer scenarios

### Movement Style Selection
- **Straight**: Best for fast, direct collection (ammo, health)
- **Spiral**: Good for magical/energy effects
- **Arc**: Natural feeling for thrown objects
- **Ease**: Smooth for polished user experience
- **Wobble**: Fun for comedic or chaotic effects

## Common Patterns

### Collectible Items
```blueprint
// Standard collectible setup
AttractedComp->bAllowPhysics = true;
AttractedComp->bAllowSnap = true;
AttractorComp->Style = EDAI_MagneticAttractorStyle::Ease;
AttractorComp->Radius = 300.0f;
AttractorComp->InnerRadius = 30.0f;
```

### Power-Up Based Attraction
```blueprint
// Only attract when player has magnetic power-up
AttractedComp->bRequireEnabledTag = true;
AttractedComp->EnabledTag = "PowerUp.Magnetism";

// Enable magnetism when power-up is collected
void OnMagnetismPowerUp()
{
    Player->Tags.AddTag("PowerUp.Magnetism");
}
```

### Stealth Mode Interaction
```blueprint
// Disable attraction during stealth
AttractedComp->bUseBlockedTag = true;
AttractedComp->BlockedTag = "Player.Stealth";

// Add stealth tag when sneaking
void OnStealthModeEnter()
{
    Player->Tags.AddTag("Player.Stealth");
}
```

## Technical Notes

- **Thread Safety**: All operations are designed for game thread usage
- **Memory Management**: Subsystem efficiently manages spatial grid data
- **Networking**: Component states can be replicated
- **Performance**: Spatial optimization reduces complexity from O(n²) to O(n)
- **Physics Integration**: Works with both physics and kinematic objects

## Troubleshooting

### Objects Not Being Attracted
1. Check that attractor `bEnabled` is true
2. Verify objects are within attractor `Radius`
3. Check tag gating settings (RequiredTag/BlockedTag)
4. Ensure attracted component has appropriate `bAllow*` flags
5. Verify subsystem performance limits aren't being hit

### Performance Issues
1. Reduce `UpdateRateHz` for less frequent updates
2. Decrease `MaxPairsPerStep` to spread load across frames
3. Increase `GridCellSize` for broader spatial optimization
4. Lower `MaxTargetsPerAttractor` to prevent hotspots
5. Adjust FPS thresholds for better adaptation

### Unexpected Behavior
1. Check preset settings if using `ApplyPreset()`
2. Verify movement style settings match intended behavior
3. Test tag interactions in isolation
4. Enable failure event publishing for debugging
5. Monitor attraction states for proper transitions

---

*For more information about tag systems, see [DAI_Hub documentation](DAI_Hub.md).*  
*For performance management details, see [DAI_PerfMngr documentation](DAI_PerfMngr.md).*

---

Last updated: October 6, 2025