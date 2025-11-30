# UltraSky Weather ⇆ Sequencer Bridge

This note documents the new flow that lets weather presets drive Level Sequence variables (and therefore the GAS attributes that replicate to clients).

## Overview

1. `UUltraSkyWeatherManager` now looks for a `UUltraSkyWeatherToSequencerBridge` at runtime.
2. Every blended weather attribute is written into the Sequencer bridge as an override **before** the GAS attributes are touched.
3. `UUltraSkyGASBridge::UpdateFromSequencer()` now resolves the overrides so that Sequencer curves are modulated by the active preset before they propagate into the `UUltraSkyAttributeSet`.
4. Anything still reading the raw Sequencer variables continues to function—presets simply nudge the values without needing to edit curves in the asset.

## Setup Checklist

- Add **one** `UUltraSkyWeatherToSequencerBridge` component to the UltraSky actor and assign its `UltraSkyActorReference`.
- Leave `bAutoFindSequencerBridge` enabled on both the Weather Manager and the GAS bridge so they will bind automatically.
- Populate `AttributeMappings` on the bridge (or click *Add Default Mappings*) so every preset field you care about has a named Sequencer variable target.

> Tip: Only the attributes that appear in the mapping table need Sequencer counterparts. Everything else continues to flow directly from GAS like before.

### Default Sequencer Variables

The *Add Default Mappings* button now seeds **every** weather attribute with a well-defined Sequencer variable. The catalog lives in `FUtraSkySequencerVariableCatalog` so runtime and editor tooling stay in sync.

| Attribute (Weather Preset) | Sequencer Variable | Category | Baseline Value |
| --- | --- | --- | --- |
| `TimeOfDayHours` | `TimeOfDayVar` | Time | `6.0` |
| `CloudCoverage` | `CloudCoverageVar` | Clouds | `0.35` |
| `CloudDensity` | `CloudDensityVar` | Clouds | `0.35` |
| `CloudLayerBottomM` | `CloudLayerBottomVar` | Clouds | `1500` |
| `CloudLayerHeightM` | `CloudLayerHeightVar` | Clouds | `2500` |
| `FogDensity` | `FogDensityVar` | Fog | `0.02` |
| `FogStartDistance` | `FogStartDistanceVar` | Fog | `75` |
| `FogHeightFalloff` | `FogHeightFalloffVar` | Fog | `0.2` |
| `FogMaxOpacity` | `FogMaxOpacityVar` | Fog | `0.9` |
| `WindBaseIntensity` | `WindSpeedVar` | Wind | `0.25` |
| `WindGustStrength` | `WindGustVar` | Wind | `0.35` |
| `WindDirectionDegrees` | `WindDirectionVar` | Wind | `0.0` |
| `RayleighScale` | `SkyBrightnessVar` | Atmosphere | `1.0` |
| `MieScale` | `AtmosphereHazeVar` | Atmosphere | `1.0` |
| `Wetness` | `RainIntensityVar` | Precipitation | `0.0` |
| `SnowAccumulation` | `SnowIntensityVar` | Precipitation | `0.0` |
| `Temperature` | `TemperatureVar` | Precipitation | `20.0` |
| `LightningFrequency` | `LightningFrequencyVar` | Storm | `0.0` |
| `StormIntensity` | `StormIntensityVar` | Storm | `0.0` |
| `MoonPhase` | `MoonPhaseVar` | Celestial | `0.5` |
| `MoonBaseIntensity` | `MoonIntensityVar` | Celestial | `0.05` |
| `StarVisibility` | `StarVisibilityVar` | Celestial | `0.75` |

## Runtime Flow

| Step | Component | Responsibility |
| --- | --- | --- |
| 1 | `UUltraSkyWeatherManager` | Blends the active preset(s), pushes GAS attributes, and calls `ApplyAttributeValueByName` for each weather field. |
| 2 | `UUltraSkyWeatherToSequencerBridge` | Caches per-variable overrides (after multiplier/offset) and keeps them ready for Sequencer consumers. |
| 3 | `UUltraSkyGASBridge::UpdateFromSequencer` | Called by Level Sequence tick. Each incoming timeline value is run through `ResolveSequencerValue`, so preset overrides win. |
| 4 | `UUltraSkyAttributeSet` | Replicates the resolved values to every client, keeping visuals/network deterministic. |

## Key APIs

- `UUltraSkyWeatherManager::ApplyPreset(...)` – now works even if GAS is absent (Sequencer-only mode) as long as a bridge is present.
- `UUltraSkyWeatherManager::ApplyAttributesToBridge(...)` – routes every attribute into the Sequencer bridge while still updating the Ability System when available.
- `UUltraSkyWeatherToSequencerBridge::ApplyAttributeValueByName` – accepts already-blended values (from the manager) and stores normalized overrides.
- `UUltraSkyWeatherToSequencerBridge::ResolveSequencerValue` – queried by `UUltraSkyGASBridge` (and any other Sequencer listener) to fetch the currently forced value.

## Troubleshooting

| Symptom | Likely Cause | Fix |
| --- | --- | --- |
| Sequencer still ignores presets | No mapping for that attribute name | Add a `FWeatherAttributeToSequencerMapping` entry or rename to match the preset property. |
| Values snap back after a frame | GAS bridge not referencing the same Sequencer bridge | Ensure `bAutoFindSequencerBridge` is true or assign the component reference manually. |
| Nothing drives GAS when presets change | Running on client or no Sequencer bridge available | Weather manager only pushes overrides on the authority. Verify ownership and that at least one bridge exists. |

## Next Steps

- Replace the temporary `SetSequencerVariableInternal` logging path with proper MovieScene variable tracks.
- Add unit tests around `ResolveSequencerValue` to guard the override math once a lightweight test target exists.
