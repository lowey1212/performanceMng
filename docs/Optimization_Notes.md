# UltraSky Optimization Notes

Date: 2025-09-21

## Summary
This pass focused on reducing per-tick overhead, unnecessary replicated attribute churn, and redundant material / reflection calls inside `ADAIUltraSkyActor` and related weather systems.

## Key Changes
1. Attribute Delta Suppression
   - Added `SetASCAttrIfChanged` helper with epsilon (`kAttrEpsilon=0.0005f`) to avoid setting Gameplay Ability System attributes when the value change is insignificant.
   - Applied in `ApplyPresetImmediate` and `BlendTowardsPreset` to cut network traffic during long blends.
2. Material Parameter Throttling
   - Cached last cloud coverage & density values (`LastMIDCloudCoverage`, `LastMIDCloudDensity`) so cloud material parameters only update when changed beyond `kParamEpsilon`.
   - Star dome opacity & yaw now gate updates (`LastStarOpacitySent`, `LastStarDomeYawDeg`).
3. Celestial MPC Gated Writes
   - Each scalar write to the Celestial MPC now gated by cached last value (with larger epsilon for geometry meters to avoid spam).
4. Fog Reflection Caching
   - Replaced repeated `FindFunctionByName` calls with static cached UFunction pointers & properties in `ApplyFogSettings`.
5. Weather Preset Blending
   - Introduced per-attribute epsilon selection (e.g., 0.25° for wind direction, 5 m for cloud geometry) to prevent micro-step replication over multi‑second blends.
6. Consistent Constants
   - Added constexpr thresholds (`kAttrEpsilon`, `kParamEpsilon`, `kYawParamEpsilon`) to header private section.
7. Build Fixes & Compatibility
   - Reverted `Engine/PrimaryDataAsset.h` usage to `Engine/DataAsset.h` for broader engine compatibility.
   - Removed Blueprint exposure of a pointer-returning struct function (`GetChainByName`).
   - Corrected `TObjectPtr` iteration and validity checks.

## Expected Impact
| Area | Prior Behavior | After Optimization | Benefit |
|------|----------------|--------------------|---------|
| Weather blending replication | Every tick sets all attributes | Only changed values beyond epsilon | Less network & server ASC work |
| Cloud material param updates | Always set both scalars per tick | Only on value delta | Fewer render thread parameter updates |
| Star dome updates | Always sets opacity & rotation | Gated by epsilon | Reduced MID churn & component transform updates |
| Fog updates | Repeated reflection lookups | Cached function/property pointers | Less CPU per tick |
| Celestial MPC | Always wrote all values | Per-parameter gating | Reduced MPC instance updates |

## Tunable Epsilons
- Attribute generic: 0.0005
- Cloud geometry meters: 1–5 m depending on context
- Wind direction: 0.25°
- Star opacity: 0.0005
- Star dome yaw: 0.05°

Adjust in `ADAIUltraSkyActor.h` if visual precision requirements change.

## Newly Added (Second Optimization Wave)
8. Performance Profiles
   - Added `EUltraSkyPerformanceProfile` (HighQuality, Balanced, LowCost) controlling snow/wetness cadence, biome blend step rate, and cosmetic toggles (star rotation & twinkle).
9. Snow / Wetness Throttling
   - Simulation moved to `UpdateSnowAndWetness` with configurable interval (`SnowWetnessUpdateInterval`). Profiles set this to 0.10s (HQ), 0.25s (Balanced), 0.50s (LowCost).
10. Biome Blend Throttling
   - Biome blending now steps at `BiomeBlendTickInterval` rather than every frame for non‑HQ profiles (Balanced: 0.05s, LowCost: 0.10s) reducing per-frame lerp math & attribute checks.
11. Timer-Based Random Weather
   - Replaced per-tick RNG decrement with `FTimerHandle` scheduling (no CPU work between picks). Deterministic via `RandomSeed` when non‑zero.

## Further Opportunities (Next Pass)
1. Event Publishing Throttling: Reintroduce tag-based gameplay event broadcast with rate limiting.
2. Async Astronomical Prep: Precompute solar positions off-thread if physical model complexity increases.
3. Adaptive Epsilons: Dynamically scale epsilons based on network saturation or performance metrics.
4. Material Update Batching: Batch multiple MPC / MID param writes via a staging struct to reduce instance fetch overhead further.
5. Conditional Tick Disable: Auto-disable Tick when TimeOfDay progression & weather systems are inactive (completely static sky scene mode).

## Validation
- Full project build succeeded after changes (Editor Development Win64).
- UHT header parse succeeded, no new reflection warnings.
- No changes to public Blueprint API except removal of unsupported pointer-returning function.

## Migration Notes
If upgrading from earlier commit:
- Review new Performance Profile setting (defaults to HighQuality). Adjust in actor or via Blueprint runtime call `ApplyPerformanceProfile`.
- Random weather now uses a timer. If you previously relied on per-tick patterning, behavior timing variation remains but with lower CPU.
- Snow / wetness changes appear in steps at configured intervals for Balanced / LowCost profiles (tweak if smoother ramps required).

## Troubleshooting
- If attributes appear to "lag": reduce `kAttrEpsilon` thresholds.
- If star opacity seems to stutter at very low fade speeds: lower `kParamEpsilon`.
- If cloud geometry smoothing feels unresponsive: decrease geometry epsilons in logic (`BlendTowardsPreset` geometry sections) or expose as settings.

---
Generated automatically during optimization pass.
