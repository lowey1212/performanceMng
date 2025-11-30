# UltraSky StateTree Nodes Guide

This document describes the custom UltraSky StateTree evaluator, tasks, and conditions, including the advanced metric, range, inversion, composite, and debugging features.

## 1. Snapshot Evaluator
`UltraSky Snapshot Evaluator`
Captures a per-tick snapshot of atmospheric & weather state for fast, allocation-free access in conditions and tasks.

Captured fields:
- `TimeOfDayHours` (0-24 float)
- `Condition` (FName active weather condition)
- `Biome` (FName active biome)
- `bPrecipitating` (bool)
- `bStorming` (bool)
- `StarVisibility` (0..1)
- `MoonPhase` (0..1; 0 new, 0.5 full, 1 new)
- `SnowAccumulation`
- `Wetness`
- `WeatherChangeAgeSeconds` (seconds since last weather condition change; -1 if unknown)
- `BiomeChangeAgeSeconds` (seconds since last biome change; -1 if unknown)

Add this evaluator at the root of a StateTree to enable meaningful WeatherAge / BiomeAge and accurate MoonPhase comparisons.

## 2. Core Tasks
- `UltraSky Set TimeOfDay` – Instantly sets time-of-day (wraps to 0-24).
- `UltraSky Add TimeOfDay Delta` – Adds hours (can be fractional); wraps 0-24.
- `UltraSky Lerp TimeOfDay` – Smoothly interpolates time-of-day over `DurationSeconds`.
  - `bWrapShortest` chooses the direction across midnight producing the smallest absolute time delta.
- `UltraSky Set Weather Preset` – Requests weather preset with optional blend seconds.
- `UltraSky Start Weather Chain` – Starts a named preset chain.
- `UltraSky Force Condition` – Forces a specific condition immediately.
- `UltraSky Apply Performance Profile` – Applies HighQuality / Balanced / LowCost.
- `UltraSky Trigger Random Weather Pick` – Forces immediate stochastic selection.
- `UltraSky Temporary Epsilon Override` – Temporarily scales internal adaptive epsilon logic.
- `UltraSky Wait For Event` – Waits until an UltraSky event tag fires (or timeout).
- `UltraSky Apply Biome` – Applies a biome (optionally blended).
- `UltraSky Dump Snapshot` – Logs current state for diagnostics.

## 3. Basic Conditions
- `UltraSky Condition Is` – Weather condition name match.
- `UltraSky Biome Is` – Biome name match.
- `UltraSky Is Precipitating` – True if any precipitation active.
- `UltraSky Is Storming` – True if storm flagged.
- `UltraSky TimeOfDay In Range` – Inclusive range (supports wrap by specifying Start > End).
- `UltraSky Event Occurred Within Seconds` – Event tag fired within MaxAgeSeconds.
- `UltraSky SnowDepth Above` / `Below`
- `UltraSky Wetness Above` / `Below`

## 4. Advanced Metric System
### 4.1 Metrics
Enumerated by `EUltraSkyMetric`:
`TimeOfDay, SnowDepth, Wetness, StarVisibility, MoonPhase, WeatherAge, BiomeAge`.

### 4.2 Single Metric Comparison
`UltraSky Metric Compare`
Fields:
- `Metric` – Which metric to test.
- `Op` – <, <=, >, >=, ==, !=
- `Value` – Comparison reference value.
- `bInvert` – Inverts the final boolean result.
- `bDebugLog` – Emits a log line with pass/fail.

Example: Trigger a dawn logic branch when TimeOfDay >= 6.

### 4.3 Metric Range
`UltraSky Metric Range` (`UltraSky Metric Range` condition)
- `Metric`
- `Min` / `Max`
- `bInclusiveMin` / `bInclusiveMax`
- `bInvert` – Invert entire in-range result.
- `bDebugLog`

Example: Evening window (18–22 hrs inclusive). To cover a wrap window (e.g., 21 -> 4) split into two range conditions combined upstream with OR:
- Range A: 21–24
- Range B: 0–4

### 4.4 Composite Predicate
`UltraSky Composite Condition`
Aggregates:
- `MetricComparisons` (array of individual comparisons)
- `RangeComparisons` (array of range tests)
- `Logic` (AND / OR)
- `bRequirePrecipitating`
- `bRequireStorming`
- `bDebugLog`

Evaluation order:
1. Fold all `MetricComparisons` under selected Logic.
2. Fold all `RangeComparisons` with running result using same Logic.
3. Apply precipitation and storm requirement flags.
4. Optional debug log.

Tips:
- Use AND when all must be true (e.g., Dark + Clear + LateNight window).
- Use OR for any-of branching (e.g., Multiple acceptable biomes or time windows).
- Inversion on individual comparisons/ranges lets you avoid creating “Not” variants.

## 5. Time-of-Day Lerp Task Details
`UltraSky Lerp TimeOfDay` fields:
- `TargetTimeOfDay` (0–24)
- `DurationSeconds` (<=0 => instant)
- `bWrapShortest` ensures interpolation crosses midnight if shorter.
Return statuses:
- Running until elapsed >= duration; then Succeeded.
- Fails immediately only if actor required and missing with `bFailIfNoActor` = true.

Use Cases:
- Cinematic transitions (skip manual per-frame adjustments).
- Gradual dawn/dusk time shifts triggered by gameplay events.

## 6. Weather & Biome Age Usage
Examples:
- Stall transitions until weather has stabilized for 30 seconds: Metric Compare (WeatherAge >= 30).
- Avoid biome-dependent logic for initial spawn: Require (BiomeAge >= 5) before heavy FX spawn.

## 7. Moon Phase Examples
- Full Moon Window: Metric Range (MoonPhase Min=0.45 Max=0.55).
- Lunar Eclipse Simulation: Sequence tasks adjusting MoonPhase plus performance profile tweaks.
- Night Event Trigger only on waning phases: Metric Compare (MoonPhase < 0.5) AND Time window.

## 8. Debug Logging
Enable `bDebugLog` on compare/range/composite to output evaluation:
- MetricCompare: "UltraSky MetricCompare <ActorName> Metric=<index> Value=<v> Pass=TRUE/FALSE"
- MetricRange: "UltraSky MetricRange Metric=<index> Min=.. Max=.. Pass=.."
- Composite: "UltraSky Composite Predicate Result=TRUE/FALSE"

For production you can switch to a custom log category (replace `LogTemp`).

## 9. Best Practices
- Always include the Snapshot Evaluator when relying on WeatherAge / BiomeAge (otherwise they remain -1).
- Prefer ranges to multiple ANDed comparisons (cleaner designer UX).
- For wrap-around time windows, split into two ranges; let a higher-level OR combine them.
- Use `bInvert` to reduce node proliferation (instead of creating explicit “Not” conditions).
- Gate expensive VFX spawn states with both `WeatherAge` and `BiomeAge` to avoid thrash during rapid transitions.

## 10. Example: Night Clear Stargazing State
Composite Condition (Logic=AND):
- Range(TimeOfDay 21–24)
- Range(TimeOfDay 0–4)   (placed in a parent OR group or separate branch)
- MetricCompare(StarVisibility >= 0.8)
- MetricCompare(Wetness < 0.2)
- MetricCompare(MoonPhase <= 0.25)  // early waxing/waning
- bRequireStorming = false
- bRequirePrecipitating = false

## 11. Troubleshooting
- WeatherAge / BiomeAge always -1: Ensure evaluator is present and actually seeing a first condition/biome value.
- Composite always failing: Check if Logic=AND and one inverted comparison (`bInvert` true) is unintentionally negating success.
- Time-of-day lerp snapping: Duration <= 0 or actor missing; ensure `bFailIfNoActor` false if optional.
- MoonPhase not changing: Confirm attribute or manual setter is called; see `SetAttrMoonPhase` logic.

## 12. Future Extension Ideas
- Nested composite predicates (tree evaluation).
- Weighted selection or fuzzy thresholds.
- Time-since last precipitation or storm event metrics.
- Exposure of sunrise/sunset computed times for more semantic conditions.

---
## 13. Logging & File Layout (Maintenance Reference)

Canonical locations:
- Log category definition: `Plugins/DAI_UltraSky/Source/DAI_UltraSky/Private/DAIUltraSkyLog.cpp`
- Log category header: `Plugins/DAI_UltraSky/Source/DAI_UltraSky/Public/StateTree/UltraSkyStateTreeLog.h`
- StateTree nodes (evaluator, tasks, conditions): `Plugins/DAI_UltraSky/Source/DAI_UltraSky/Public/StateTree/UltraSkyStateTreeNodes.h` (declarations) and `.../Private/StateTree/UltraSkyStateTreeNodes.cpp` (implementations).

Removed legacy files (DO NOT REINTRODUCE):
- `Private/UltraSkyStateTreeNodes.cpp` (stale duplicate) – caused override/signature drift.
- Old root `Public/UltraSkyStateTreeLog.h` and `Private/UltraSkyStateTreeLog*.cpp` duplicates – caused multiple `DEFINE_LOG_CATEGORY` conflicts.

When adding new nodes:
1. Declare in the existing `UltraSkyStateTreeNodes.h` under a clearly labeled section.
2. Implement in the matching `Private/StateTree/UltraSkyStateTreeNodes.cpp` keeping grouping & comments consistent.
3. Use the existing `LogUltraSkyStateTree` category for debug; avoid creating new categories unless semantically distinct.
4. Match base class signatures exactly (note `const` on `Tick`/`EnterState` for evaluator/tasks) to avoid `C3668`.

Mutable usage note:
- Snapshot evaluator & certain tasks mark state members `mutable` solely to satisfy const override requirements. Reassess before broadening mutable usage; prefer local temporaries when possible.

Verification checklist before commit:
- One `DEFINE_LOG_CATEGORY(LogUltraSkyStateTree)` only (search the module).
- No new files duplicating existing node or log file names in root `Private`.
- Build with `/WX` (warnings as errors) remains clean.

---
_Last maintenance section update: 2025-09-21_
