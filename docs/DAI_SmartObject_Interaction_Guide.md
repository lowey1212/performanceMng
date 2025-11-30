# DAI SmartObject Interaction System Guide

## Overview

The DAI SmartObject Interaction System provides a camera-based, motion-warped interaction framework for context-sensitive gameplay actions. The system uses sphere tracing from the camera to detect interactable objects and automatically plays synchronized animations with smooth character positioning via Motion Warping.

## Key Features

- **Camera-Based Detection**: Sphere trace from camera center detects what the player is looking at
- **Distance-Based Slot Selection**: Automatically selects the closest usable slot from detected SmartObjects
- **Motion Warping Integration**: Smoothly transitions character to interaction point during animation
- **Animation Montage Support**: Each slot can have its own interaction animation
- **Configurable Parameters**: All detection and animation settings exposed to Blueprints
- **Tag-Based Filtering**: Filter slots by gameplay tags for specific interaction types
- **Networking Support**: Built for multiplayer with slot reservation system

---

## Quick Start

### 1. Set Up a SmartObject Actor

Add a `DAISmartObjectComponent` to your interactable actor (door, lever, chest, etc.):

```cpp
// In your actor's constructor
SmartObjectComp = CreateDefaultSubobject<UDAISmartObjectComponent>(TEXT("SmartObject"));
```

### 2. Configure Interaction Slots

In the SmartObject component, add slots with:
- **SlotName**: Logical identifier (e.g., "DoorHandle", "ChestLid")
- **RelativeTransform**: Position/rotation relative to the component
- **InteractionMontage**: Animation to play when character interacts
- **SlotTags**: Semantic tags for filtering (e.g., "DAI.SmartObject.Function.Door")

### 3. Set Up Collision

Ensure your SmartObject actor has collision components that respond to the `DAI_Interactable` trace channel (ECC_GameTraceChannel1).

### 4. Add Interaction Ability to Character

Grant the `UDAIInteractAbility` to your character's Ability System Component:

```cpp
// In Blueprint or C++
AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(UDAIInteractAbility::StaticClass(), 1, INDEX_NONE, this));
```

### 5. Add Motion Warping Component

Your character needs a `UMotionWarpingComponent` for smooth transitions:

```cpp
MotionWarpingComp = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping"));
```

### 6. Set Up Animation Montage

In your interaction montage, add a Motion Warping notify with:
- **Warp Target Name**: "InteractionTarget" (default, configurable in ability)
- Configure the warp window to cover the approach animation frames

---

## Detection System

### Sphere Trace Configuration

The ability uses a sphere sweep from the camera to detect interactables:

```cpp
/** Length of sphere trace from camera (units) */
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
float TraceLength = 500.f;

/** Radius of sphere trace for detecting interactables */
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
float SphereRadius = 100.f;

/** Collision channel for sphere trace */
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
TEnumAsByte<ECollisionChannel> TraceChannel = ECC_GameTraceChannel1; // DAI_Interactable
```

**How It Works:**
1. Trace originates from camera position
2. Sweeps forward along camera direction for `TraceLength` units
3. Sphere with `SphereRadius` detects objects along the path
4. First SmartObject hit is selected
5. Closest usable slot from that SmartObject is chosen

**Recommended Values:**
- **TraceLength**: 500-800 for general interactions, 1000+ for vehicle entry
- **SphereRadius**: 100-150 for precise interactions, 200+ for larger objects
- **TraceChannel**: Use `DAI_Interactable` (ECC_GameTraceChannel1)

---

## Slot Selection Logic

Once a SmartObject is detected, the system:

1. **Filters slots by tags** (if `DesiredSlotTags` is set)
2. **Checks usability** (via `IsSlotUsableBy`)
3. **Calculates distance** from character to each slot
4. **Selects closest slot** as the interaction target

### Tag Filtering Example

```cpp
// Only interact with door slots
InteractAbility->DesiredSlotTags.AddTag(FGameplayTag::RequestGameplayTag("DAI.SmartObject.Function.Door"));

// Or utility slots (levers, switches, etc.)
InteractAbility->DesiredSlotTags.AddTag(FGameplayTag::RequestGameplayTag("DAI.SmartObject.Slot.Utility"));
```

---

## Motion Warping

Motion Warping smoothly moves the character from their current position to the slot's transform during the animation.

### Configuration Properties

```cpp
/** Enable/disable motion warping (falls back to instant teleport if false) */
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|MotionWarping")
bool bUseMotionWarping = true;

/** Target name used in animation montage Motion Warp notify */
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|MotionWarping")
FName MotionWarpTargetName = "InteractionTarget";

/** Animation blend-in time */
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|MotionWarping")
float BlendInTime = 0.25f;

/** Animation blend-out time */
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|MotionWarping")
float BlendOutTime = 0.25f;

/** Animation playback speed multiplier */
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|MotionWarping")
float PlayRate = 1.0f;
```

### Setting Up Motion Warp in Animation

1. Open your interaction animation montage
2. Add a **Motion Warping** notify track
3. Add a **Warp Target** notify:
   - **Warp Target Name**: Match `MotionWarpTargetName` (default: "InteractionTarget")
   - **Start Time**: Beginning of approach animation
   - **End Time**: When character reaches final position
4. Configure warp settings (translation, rotation, scale warping as needed)

### Motion Warp Behavior

**When Enabled (`bUseMotionWarping = true`):**
- Sets warp target to slot transform
- Plays montage with motion warping active
- Character smoothly transitions during animation

**When Disabled (`bUseMotionWarping = false`):**
- Falls back to legacy instant teleport (if `bTeleportToSlot = true`)
- Instant rotation alignment (if `bAlignRotationToSlot = true`)
- Still plays montage, but without smooth transition

---

## Legacy Alignment (Non-Motion Warp)

For instant positioning without motion warping:

```cpp
/** Instantly rotate player to slot orientation on activation */
UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction|Alignment")
bool bAlignRotationToSlot = true;

/** Instantly teleport player to slot position on activation */
UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction|Alignment")
bool bTeleportToSlot = true;
```

**Note:** These only apply when `bUseMotionWarping = false`. With motion warping enabled, the animation handles positioning.

---

## UI Integration

Use `QueryInteractionTarget` to check if a valid interaction is available (for displaying prompts):

```cpp
// In your UI widget or HUD tick
FTransform SlotTransform;
AActor* TargetActor;
FName SlotName;

if (InteractAbility->QueryInteractionTarget(SlotTransform, TargetActor, SlotName))
{
    // Valid target found - show "Press E to Interact" prompt
    ShowInteractionPrompt(TargetActor, SlotName);
}
else
{
    // No valid target - hide prompt
    HideInteractionPrompt();
}
```

### Blueprint Example

```
Tick Event
  → Get Ability System Component
    → Get Interact Ability
      → Query Interaction Target
        → Branch (Return Value)
          TRUE → Set Widget Visibility (Visible) + Update Text
          FALSE → Set Widget Visibility (Hidden)
```

---

## Execution Flow

### 1. Can Activate Check
```
Player presses interact key
  → CanActivateAbility called
    → FindCandidate performs sphere trace
      → Detects SmartObject
        → Filters usable slots by tags
          → Selects closest slot
            → Caches transform, actor, slot name, montage
              → Returns true if valid candidate found
```

### 2. Activation
```
Ability activates
  → Checks for cached target (or re-finds if needed)
    → If motion warping enabled:
      → Finds MotionWarpingComponent on character
        → Clears existing warp targets
          → Adds new warp target with slot transform
            → Plays interaction montage
    → If motion warping disabled:
      → Instant teleport/rotation (legacy mode)
        → Plays montage without warping
    → Reserves slot on SmartObject component
```

### 3. During Animation
```
Montage plays
  → Motion Warp notify active
    → Character smoothly transitions to slot position
      → Animation reaches interaction point
        → Gameplay logic executes (open door, etc.)
```

### 4. End Ability
```
Interaction completes
  → EndAbility called
    → Releases slot on SmartObject
      → Slot becomes available for reuse
```

---

## Collision Setup

### Project Settings

Ensure `DAI_Interactable` channel is configured:

**DefaultEngine.ini:**
```ini
[/Script/Engine.CollisionProfile]
+DefaultChannelResponses=(Channel=ECC_GameTraceChannel1,DefaultResponse=ECR_Block,bTraceType=True,bStaticObject=False,Name="DAI_Interactable")
```

### SmartObject Actor Collision

Your interactable actors need collision primitives that respond to `DAI_Interactable`:

```cpp
// Example: Box collision on door
BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionCollision"));
BoxCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
```

Or in Blueprint:
- Add collision component (Box, Sphere, Capsule, or Mesh)
- Set collision response to `DAI_Interactable` → **Block**

---

## Common Use Cases

### Door Interaction

**SmartObject Setup:**
- **Slot Name**: "DoorHandle"
- **Relative Transform**: Position at door handle, rotation facing door
- **Interaction Montage**: Open door animation with reach/pull
- **Slot Tags**: "DAI.SmartObject.Function.Door"

**Motion Warp Window:**
- Start: Beginning of reach animation
- End: When hand touches handle

### Chest/Container Looting

**SmartObject Setup:**
- **Slot Name**: "ChestFront"
- **Relative Transform**: Kneel position in front of chest
- **Interaction Montage**: Kneel down and open animation
- **Slot Tags**: "DAI.SmartObject.Function.Container"

**Motion Warp Window:**
- Start: Beginning of kneel approach
- End: When character is in kneeling position

### Lever/Switch

**SmartObject Setup:**
- **Slot Name**: "LeverPull"
- **Relative Transform**: Standing position at lever
- **Interaction Montage**: Pull lever animation
- **Slot Tags**: "DAI.SmartObject.Slot.Utility"

**Motion Warp Window:**
- Start: Step forward
- End: Hand on lever

### Ladder Mounting

**SmartObject Setup:**
- **Slot Name**: "LadderBottom"
- **Relative Transform**: Base of ladder, facing ladder
- **Interaction Montage**: Mount ladder animation
- **Slot Tags**: "DAI.SmartObject.Function.Climb"

**Motion Warp Window:**
- Start: Approach ladder
- End: Hands on first rung

---

## Multiplayer Considerations

### Slot Reservation
- Slots are automatically reserved on activation
- Prevents multiple players from using same slot simultaneously
- Released on `EndAbility`

### Network Authority
- Ability uses `LocalPredicted` execution policy
- Client predicts interaction, server validates
- Slot reservation is replicated via SmartObject component

### Best Practices
- Keep animations deterministic for client prediction
- Use server-validated slot usability checks
- Handle reservation failures gracefully (slot taken, cooldown active)

---

## Performance Optimization

### Trace Efficiency
- Sphere trace is **O(log N)** spatial query (much faster than iterating all SmartObjects)
- Only processes first SmartObject hit (not all objects in scene)
- Trace typically checks 5-20 actors vs 100-1000 with global iteration

### Recommended Settings
- **TraceLength**: Keep reasonable (500-1000) to avoid long traces
- **SphereRadius**: Use smallest radius that feels responsive
- **Update Frequency**: UI queries can run every 0.1-0.2 seconds instead of every tick

### Caching
- FindCandidate results are cached between `CanActivate` and `Activate`
- Avoids redundant trace queries
- UI queries use same cached results

---

## Troubleshooting

### "No interaction prompt showing"
- Check SmartObject actor has collision responding to `DAI_Interactable` channel
- Verify `TraceLength` is long enough to reach object
- Check `DesiredSlotTags` matches slot's `SlotTags` (if filtering)
- Ensure slot passes `IsSlotUsableBy` check

### "Character teleports instead of smooth movement"
- Verify `bUseMotionWarping = true` in ability settings
- Check character has `UMotionWarpingComponent` attached
- Confirm montage has Motion Warp notify with matching target name
- Ensure warp window covers transition frames

### "Wrong animation plays"
- Check slot's `InteractionMontage` is set correctly
- Verify closest slot is the intended one (check distances)
- Use tag filtering to restrict to specific slot types

### "Character positioned incorrectly"
- Adjust slot's `RelativeTransform` in SmartObject component
- Fine-tune motion warp settings in animation montage
- Check character's root bone alignment in animation

### "Interaction doesn't work in multiplayer"
- Verify ability is granted on both client and server
- Check slot reservation replication in SmartObject component
- Ensure `NetExecutionPolicy = LocalPredicted`

---

## Advanced Configuration

### Custom Trace Channels

To use a different trace channel:

```cpp
// In ability configuration
InteractAbility->TraceChannel = ECC_GameTraceChannel2; // Your custom channel
```

Then update collision responses accordingly.

### Multiple Slot Types per Object

A single SmartObject can have multiple slot types:

```cpp
// Door with multiple interaction points
Slots[0]: Name="Handle", Tags="DAI.SmartObject.Function.Door.Open"
Slots[1]: Name="Lockpick", Tags="DAI.SmartObject.Function.Door.Lockpick"
Slots[2]: Name="Peek", Tags="DAI.SmartObject.Function.Door.Peek"
```

Use `DesiredSlotTags` in different abilities to target specific slots.

### Dynamic Montage Selection

Override `FindCandidate` or handle montage selection in Blueprint to choose animations based on game state:

```cpp
// Example: Different animations based on equipped weapon
if (IsWeaponDrawn())
    Slot.InteractionMontage = OpenDoorArmedMontage;
else
    Slot.InteractionMontage = OpenDoorUnarmedMontage;
```

---

## API Reference

### UDAIInteractAbility

#### Public Properties

| Property | Type | Default | Description |
|----------|------|---------|-------------|
| `TraceLength` | float | 500.0 | Sphere trace distance from camera |
| `SphereRadius` | float | 100.0 | Sphere trace radius |
| `TraceChannel` | ECollisionChannel | ECC_GameTraceChannel1 | Collision channel for trace |
| `DesiredSlotTags` | FGameplayTagContainer | Empty | Filter slots by tags |
| `bUseMotionWarping` | bool | true | Enable motion warping |
| `MotionWarpTargetName` | FName | "InteractionTarget" | Warp target name in montage |
| `BlendInTime` | float | 0.25 | Animation blend-in time |
| `BlendOutTime` | float | 0.25 | Animation blend-out time |
| `PlayRate` | float | 1.0 | Animation playback speed |
| `bAlignRotationToSlot` | bool | true | Instant rotation (non-warp mode) |
| `bTeleportToSlot` | bool | true | Instant teleport (non-warp mode) |

#### Public Methods

**QueryInteractionTarget**
```cpp
bool QueryInteractionTarget(
    FTransform& OutSlotTransform,
    AActor*& OutTargetActor,
    FName& OutSlotName
) const;
```
Queries for valid interaction target without activating ability. Use for UI prompts.

**Returns:** `true` if valid target found, `false` otherwise

---

### FDAISmartObjectSlotSyncPoint

#### Properties

| Property | Type | Description |
|----------|------|-------------|
| `SlotName` | FName | Logical slot identifier |
| `RelativeTransform` | FTransform | Position/rotation relative to component |
| `RequiredUserTags` | FGameplayTagContainer | Tags user must have to use slot |
| `GrantedTagsWhileUsing` | FGameplayTagContainer | Tags applied to user during interaction |
| `SlotTags` | FGameplayTagContainer | Semantic tags for filtering |
| `InteractionMontage` | UAnimMontage* | Animation to play when interacting |
| `CooldownDuration` | float | Seconds before slot can be reused |

---

## Best Practices

1. **Use Motion Warping**: Provides much smoother player experience than instant teleport
2. **Configure Warp Windows Carefully**: Start warp at beginning of approach, end when character reaches position
3. **Keep Trace Parameters Reasonable**: Avoid excessively long traces or large radii
4. **Use Tag Filtering**: Filter slots by type to prevent wrong interactions
5. **Set Up Collision Properly**: Ensure all interactables respond to `DAI_Interactable` channel
6. **Cache Query Results**: Don't call `QueryInteractionTarget` every frame, use 0.1-0.2s intervals
7. **Test in Multiplayer**: Verify slot reservation and animation synchronization
8. **Provide Visual Feedback**: Use query results to highlight interactable objects
9. **Handle Edge Cases**: What happens if slot becomes unavailable during activation?
10. **Adjust Per Interaction Type**: Different montages, blend times, and warp settings for different interactions

---

## Related Documentation

- [DAI_SmartObject_Component_Guide.md](DAI_SmartObject_Component_Guide.md) - Full SmartObject component documentation
- [DAI_Hub_Soft_Reference_Architecture.md](DAI_Hub_Soft_Reference_Architecture.md) - Plugin dependency patterns
- [GameplayTags_Implementation.md](GameplayTags_Implementation.md) - Gameplay tag setup and usage

---

## Version History

- **v1.0** (Nov 2025) - Initial implementation with camera-based sphere trace detection
- **v1.1** (Nov 2025) - Added Motion Warping support with animation montage integration
- **v1.2** (Nov 2025) - Simplified to distance-based slot selection, removed complex scoring
