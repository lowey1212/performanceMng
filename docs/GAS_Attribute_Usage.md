# UltraSky GAS Attribute Usage

This document describes how to drive UltraSky environment parameters via the Gameplay Ability System (GAS) attributes defined in `UDAIUltraSkyAttributeSet`.

## Core Concepts
UltraSky mirrors most sky, weather, fog, wind and celestial runtime values into replicated GAS attributes. This lets you:
- Apply Gameplay Effects (GE) to smoothly modify environment factors (e.g., increase cloud coverage during a spell).
- Use Modifiers & Execution Calculations to derive secondary effects (e.g., reduce visibility when FogDensity rises).
- Replicate authoritative changes to all clients without custom RPC code.

## Key Attributes (abbrev.)
- TimeOfDayHours, DayLengthSeconds
- CloudCoverage, CloudDensity, CloudLayerBottomM, CloudLayerHeightM
- FogDensity, FogStartDistance, FogHeightFalloff, FogMaxOpacity
- RayleighScale, MieScale (atmospheric scattering)
- WindBaseIntensity, WindGustStrength, WindDirectionDegrees
- SnowAccumulation, Wetness
- MoonPhase, MoonBaseIntensity, StarVisibility

## Applying a Gameplay Effect (Example)
1. Create a Gameplay Effect asset `GE_ThickFog`.
2. Add a modifier:
   - Attribute: FogDensity
   - Modifier Op: Add
   - Magnitude: Scalable Float (e.g., +0.02)
3. (Optional) Add a second modifier for FogStartDistance (subtract to bring fog closer).
4. Apply the effect from an ability or a simple blueprint using `ApplyGameplayEffectToTarget` where the target is the UltraSky weather anchor actor's ASC.

Result: Fog density increases; UltraSky Tick / `ApplyFogSettings` reads the attribute and updates the fog component.

## Time Acceleration Ability Example
Create `GE_TimeAccel`:
- Attribute: DayLengthSeconds
- Op: Multiply
- Magnitude: 0.5  (half the day length -> doubles perceived speed).
Applying this effect shortens the length of a full 24h cycle. UltraSky's Tick reads DayLengthSeconds each frame so acceleration is immediate.

## Transient Spells (e.g., Darken Clouds)
- Create `GE_DarkenClouds` with Add or Multiply modifiers to CloudCoverage & CloudDensity.
- Duration: 10 seconds with an exponential decay curve if desired (use custom execution or stacking). After expiration, attributes return to baseline (or whatever other active effects dictate).

## Moon Phase Control
To produce an eclipse sequence:
1. `GE_StartEclipse`: Set MoonPhase to 0.5 (full) if not already.
2. Over time apply a series of effects reducing `MoonBaseIntensity` and/or altering `MoonPhase` toward 0.0.
3. Remove effects to restore natural cycle (or script progression by abilities).

## Star Visibility Link
`StarVisibility` is updated on server each night tick. You can reference it in abilities that scale night-specific effects (e.g., nocturnal creature buffs).

## Wind Driven Projectile Drift
Use `WindDirectionDegrees` and `WindBaseIntensity` attributes inside an Ability Task or Gameplay Cue to bias projectile trajectories or particle systems.

## Best Practices
- Clamp in Gameplay Effects: Add `Meta Attribute` style execution or custom calculation to ensure values remain within plausible ranges (e.g., FogDensity 0..1). UltraSky also clamps internally where critical.
- Authority Only Writes: Only the server (authority) should apply or remove effects that change these attributes.
- Avoid Rapid Attribute Thrash: If driving highly dynamic values (e.g., gust simulation), feed only base intensities to GAS and perform high-frequency noise locally like UltraSky does for gusts.
- Bundling: Group related weather shifts into a single GE (e.g., StormFront) instead of many small effects to minimize replication overhead.

## Debugging
Console commands:
- `UltraSky.DumpAttrs` – Logs current attribute values.
- `UltraSky.Status` – High-level state (time, biome, condition).

If an attribute isn't changing:
1. Confirm the Weather Anchor actor actually owns an ASC.
2. Ensure the attribute is initialized (server seeding occurs in `SeedAttributesIfNeeded`).
3. Check Gameplay Effect spec: correct attribute, stacking rules, magnitude sign.
4. Verify replication by observing server log vs. client log (`UltraSky.DumpAttrs`).

## Extending
When adding new UltraSky attributes:
1. Add `FGameplayAttributeData` + accessor macros to `UDAIUltraSkyAttributeSet`.
2. Add replication macro in .cpp.
3. Seed default in `SeedAttributesIfNeeded`.
4. Replace direct property usage in actor logic with getter / setter pair.
5. (Optional) Expose to materials via MPC if relevant.

## Example Blueprint Usage (High Level)
1. Place UltraSky actor & designate WeatherAnchor (e.g., a persistent GameState or Manager actor with an ASC).
2. From any ability, call `GetActorOfClass -> DAIUltraSkyActor` (or store a reference) then fetch its ASC via `Get Ability System Component` (interface call) and apply your GE.
3. Use attributes to drive UI (e.g., a weather widget) via ASC attribute change delegates.

---
With this system, designers & abilities can orchestrate complex, network-replicated environmental storytelling without custom RPCs.

## Blueprint Convenience Library
UltraSky ships with `UUltraSkyFunctionLibrary` exposing lightweight pure functions that locate the first `ADAIUltraSkyActor` in the world and return key replicated values. These are read-only accessors intended for UI, VFX and simple blueprint logic where you do not need to manually bind to the actor.

Available functions (all WorldContext):
- `GetTimeOfDayHours`
- `GetCloudCoverage`
- `GetCloudDensity`
- `GetFogDensity`
- `GetStarVisibility`
- `GetCloudLayerBottomMeters`
- `GetCloudLayerHeightMeters`

Usage Example (UI Widget Blueprint):
```
Event Tick -> GetTimeOfDayHours -> Format Text -> Set Text (ClockLabel)
```

If you need writable access (e.g., to force TimeOfDay) call the actor's setter blueprint callable functions or apply a Gameplay Effect rather than directly changing properties.

## Cloud Layer Geometry via Attributes
`CloudLayerBottomM` and `CloudLayerHeightM` (meters) mirror the editor-friendly kilometer properties `CloudLayerBottomKm` / `CloudLayerHeightKm`.

Update Flow:
1. Server seeds attributes (meters) from km properties if unset.
2. `ApplyCloudSettings` reads attribute values (if present) and converts to km for cached change detection.
3. If `bPreserveExistingCloudGeometry` is true on initial bind, UltraSky adopts the component's existing geometry unless attributes explicitly override (non-zero).

Driving Geometry at Runtime:
- Preferred: Apply a Gameplay Effect modifying `CloudLayerBottomM` / `CloudLayerHeightM` (Add, Override or Multiply style).
- Direct API: Call `SetAttrCloudLayerBottomM` / `SetAttrCloudLayerHeightM` on the actor (server only) for scripted transitions.

Best Practices:
- Clamp altitude ranges in your GE (e.g., 1000m – 20000m) to avoid extreme scattering artifacts.
- For smooth transitions, apply a timed GE with a curve-based magnitude or run an ability that lerps and periodically updates the attribute base value.
- Keep bottom < bottom+height; if designing dynamic compression effects ensure height never drops below a practical minimum (e.g., 500m) to avoid visual aliasing.

Material Considerations:
If your volumetric cloud material references layer altitude, read component values directly (they are kept in sync) or pass attributes into a Material Parameter Collection if you need them in other materials.

---
Revision: Added blueprint function library & cloud geometry guidance.
