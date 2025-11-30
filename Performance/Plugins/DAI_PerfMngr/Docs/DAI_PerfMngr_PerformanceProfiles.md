# DAI_PerfMngr Performance Profiles & Tuning

This document focuses on **how to size and tune performance budgets, significance curves, and adaptive LOD settings** when using the DAI_PerfMngr plugin.

It is intentionally practical: start here when you want to dial a project to a new target platform or performance budget.

## Mental Model

Think of the system as:
- A set of **per-category budgets** (in ms per frame).
- A graph of **significance scores** determining which actors deserve quality.
- A set of **adaptive LOD rules** that trade quality for time when needed.

PerfMngr coordinates these three layers.

## Budgets by Platform

Suggested starting budgets (ms per frame) for a 60 FPS target (16.67 ms) – adjust for your specific title.

| Category   | High-End PC | Console | Low-End PC / Laptop |
|-----------|-------------|---------|----------------------|
| Rendering | 9.0         | 8.0     | 6.5                  |
| Animation | 2.0         | 2.0     | 1.5                  |
| AI        | 2.5         | 2.0     | 1.5                  |
| Physics   | 1.5         | 2.0     | 2.0                  |
| Audio     | 1.0         | 1.0     | 1.0                  |
| Scripting | 1.0         | 1.0     | 1.0                  |

Use these as initial `DefaultBudgets` in the project settings, then refine per title.

## Thresholds & Emergency Mode

- `BudgetOverageThreshold` – how far a category can overshoot before considered "over budget".
- `EmergencyModeThreshold` – global threshold that triggers a more aggressive quality drop.

Recommended starting values:
- `BudgetOverageThreshold = 1.15` (allow ~15% over for short spikes).
- `EmergencyModeThreshold = 1.5` (50% over → emergency mode).

When `EmergencyModeThreshold` is crossed, design game logic to:
- Disable non-essential FX and detail.
- Increase LOD levels globally.
- Reduce spawn density / crowd size.

## Significance Tuning

### Distance-Based

For purely distance-based significance (`Distance` function):
- Choose a **reference distance** where you consider an actor "important".
- Scale significance inversely with distance up to a minimum floor.

Example heuristic (for FPS/third-person):
- < 10m: significance ≈ `BaseSignificance * 1.0`
- 10–25m: significance ≈ `BaseSignificance * 0.5`
- 25–50m: significance ≈ `BaseSignificance * 0.2`
- > 50m: clamp to 0.1–0.2

### Combined Function

For `Combined` significance:
- Combine **distance**, **importance**, and optionally **screen size**.
- Bosses: high importance, moderate distance power.
- Ambient actors: low importance, strong distance falloff.

Recommended ranges:
- Background clutter: `BaseSignificance = 0.5–1.0`
- Regular NPCs: `BaseSignificance = 2.0–4.0`
- Elite/boss NPCs: `BaseSignificance = 8.0–12.0`

## Adaptive LOD Settings

When configuring `FDAIAdaptiveLODSettings`:

### Distance Thresholds (3rd-person scale)

- `DistanceThresholds = [600, 1200, 2400, 4800]` (cm)
  - LOD0: 0–6m
  - LOD1: 6–12m
  - LOD2: 12–24m
  - LOD3: 24–48m
  - Beyond: lowest quality/fallback

### Performance Thresholds

Expressed as **budget usage fraction**:
- `PerformanceThresholds = [0.7, 0.85, 0.95]`
  - Below 70% → high quality allowed.
  - 70–85% → moderate reductions.
  - 85–95% → aggressive LODs.
  - >95% → emergency LOD and optional system disabling.

### Update Frequency & Hysteresis

- `UpdateFrequency = 0.25–0.5` seconds – updating too often can be noisy and costly.
- `HysteresisThreshold = 0.1` – prevents constant LOD flapping when metrics hover around a threshold.

## Integration Examples

### Crowd NPCs

- Attach `UDAISignificanceComponent` and `UDAIPerformanceBudgetComponent`.
- Use distance + importance (crowds around the player more important).
- LOD configuration:
  - Close: full anim blueprint, facial anim, full FX.
  - Mid: simplified anim graph (no IK, fewer blends).
  - Far: single idle loop or even static proxy.

### VFX-Heavy Areas

- Use Rendering budget as key driver.
- When `IsPerformanceBudgetExceeded(Rendering, 0.85)`:
  - Reduce Niagara spawn rates.
  - Turn off small/secondary FX systems.
  - Switch to cheaper materials where possible.

### AI Swarms

- AI budget gating:
  - Use `RequestBudgetAllocation(AI, CostMs, Priority)` before doing swarm updates.
  - On failure, skip or use cheaper high-level approximation.
- Significance:
  - High significance → precise pathfinding and behaviors.
  - Low significance → coarse steering, batched updates, or offline logic.

## Validation Checklist

1. **Profile with PerfMngr enabled** using Unreal Insights.
2. **Stress AI and FX** to push budgets over thresholds.
3. Ensure delegates (threshold/exhausted) fire as expected.
4. Confirm that quality downgrades are **visible but acceptable**, and that they revert when performance recovers.
5. Validate that no critical gameplay systems are accidentally disabled in emergency mode.

## Future Expansion

- Add project-specific budget categories (e.g. `Cinematics`, `Streaming`).
- Build a small in-game **Performance Debug Panel** wired to PerfMngr APIs.
- Hook PerfMngr into automated perf tests to track regression over time.

---
Last updated: November 30, 2025
