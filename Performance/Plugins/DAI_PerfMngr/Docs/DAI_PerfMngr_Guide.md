# DAI_PerfMngr Plugin Guide

## Overview
**DAI_PerfMngr** is a world-level performance management system built on top of Unreal Engine's Significance Manager and timing/budget primitives. It provides a central budget service, significance tracking, and adaptive LOD hooks that other DAI plugins and game code can opt into.

This guide focuses on **how to use the plugin inside a game project**—what to drop in the level, how to wire Blueprints, and how to reason about budgets and significance—while keeping details consistent with the top-level docs in `docs/plugins/DAI_PerfMngr.md`.

## Architecture

### Core Pieces
- **`UDAIPerfMngrSubsystem`** – World subsystem and primary entry point for C++.
- **`UDAIPerfMngrBlueprintLibrary`** – Static Blueprint functions for monitoring and control.
- **`UDAISignificanceComponent`** – Actor component for significance tracking.
- **`UDAIPerformanceBudgetComponent`** – Actor component for budget-aware work.
- **Significance Manager Bridge** – Integration with UE's `USignificanceManager` for distance/importance based scoring.

### Typical Flow
1. **Subsystem boot** – On world start, `UDAIPerfMngrSubsystem` initializes budgets and hooks into SignificanceManager.
2. **Actors register** – Actors add `UDAISignificanceComponent` and/or `UDAIPerformanceBudgetComponent`.
3. **Budgets configured** – Project settings define per-category ms budgets; game code/Blueprints can override per world.
4. **Runtime decisions** – Systems call into PerfMngr to query budgets, significance, and recommended LODs before doing expensive work.

## Setup

### 1. Enable the Plugin
- In Unreal Editor, open **Edit → Plugins**.
- Enable **DAI_PerfMngr**.
- Restart the editor if prompted.

### 2. Configure Project Settings
Open **Edit → Project Settings → Game → DAI Performance Manager**.

Key properties:
- `bEnablePerformanceMonitoring` – Turn on frame/budget tracking (recommended: **true**).
- `bEnableSignificanceManager` – Enable significance-based optimization.
- `DefaultBudgets` – Per-category ms budgets (Rendering, AI, Physics, etc.).
- `bEnforceBudgets` – Whether budget checks should gate expensive work.
- `LODUpdateFrequency` – Seconds between adaptive LOD evaluations.

Use conservative defaults for new projects, then tighten budgets as you profile.

### 3. Level Integration
No dedicated "manager" actor is required; the system is a **World Subsystem**.

For debugging and visualization, you can:
- Use the **Performance HUD** (see Debug section below).
- Attach components to key actors (player, NPCs, big FX actors) to see how they behave under pressure.

## Using the Subsystem in C++

```cpp
#include "DAIPerfMngrSubsystem.h"

void AMyGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (UWorld* World = GetWorld())
    {
        if (UDAIPerfMngrSubsystem* Perf = World->GetSubsystem<UDAIPerfMngrSubsystem>())
        {
            // Example: tighten AI budget at runtime
            Perf->SetPerformanceBudget(EDAIBudgetCategory::AI, 1.5f /* ms */);
        }
    }
}
```

From the subsystem, you can:
- Query frame rate and frame time.
- Read current per-category budget usage.
- Register/unregister significance actors.
- Subscribe to delegates like `OnPerformanceThresholdExceeded`.

## Blueprint Usage

Most gameplay teams will primarily interact with **`UDAIPerfMngrBlueprintLibrary`** in Blueprint.

### Monitoring Frame Rate

Use in e.g. your game mode or performance controller Blueprint:

```text
Event Tick
  → GetCurrentFrameRate
  → If FPS < TargetFPS → Reduce quality
```

Suggested pseudograph:
- **Input**: `TargetFPS` (e.g. 60).
- **If** `CurrentFPS < TargetFPS` → ask PerfMngr if Rendering or AI budgets are over threshold.
- Adjust quality, spawn density, AI tick rate, etc.

### Budget-Aware Operations (Blueprint)

Use `RequestBudgetAllocation` and `ReleaseBudgetAllocation` when running expensive logic:

1. **Before work** – call `RequestBudgetAllocation` with category + estimated ms.
2. **If true** – run work; optionally measure and `ReleaseBudgetAllocation` unused ms.
3. **If false** – skip, defer, or run a cheaper version.

This pattern works well for:
- Expensive AI perception or pathfinding bursts.
- Bulk Mutable character re-customization.
- High-cost VFX sequences.

### Significance-Based Decisions

Attach `UDAISignificanceComponent` to actors that can dynamically change quality:
- Enemy characters.
- Crowd / ambient NPCs.
- Large decorative assets with multiple LODs.

At runtime, you can:
- Query `GetActorSignificance` to determine if an actor should be **Full Quality**, **Medium**, or **Cheap**.
- Feed that into your own LOD swaps, animation state complexity, audio detail, etc.

Example flow for a crowd NPC Blueprint:
- Every few seconds, call `GetActorSignificance`.
- If significance is very low → switch to idle-only animation and cheapest materials.
- If significance is high → restore full animation blueprint and FX.

## Significance Component Patterns

### Adding Significance to an Actor (C++)

```cpp
#include "DAISignificanceComponent.h"

AMyEnemy::AMyEnemy()
{
    SignificanceComp = CreateDefaultSubobject<UDAISignificanceComponent>(TEXT("SignificanceComp"));
    SignificanceComp->SignificanceFunction = EDAISignificanceFunction::Distance;
    SignificanceComp->BaseSignificance = 3.0f;
}
```

### Blueprint Configuration Suggestions
- `SignificanceFunction = Distance` for simple NPCs.
- `SignificanceFunction = Combined` for bosses or interactables where gameplay importance matters.
- `BaseSignificance` higher for more important actors.

Recommended value ranges:
- Ambient / background: **0.5 – 1.0**
- Standard enemies: **2.0 – 4.0**
- Boss / critical: **8.0+**

## Budget Component Patterns

### Marking Expensive Systems

Add `UDAIPerformanceBudgetComponent` to actors that own heavy logic (e.g. swarm controller, complex manager).

Example usage:
- `RequiredBudgetCategory = AI`
- `EstimatedCostMs = 2.0f`
- `bRequireBudget = true`

Then in your tick/update:
- If `bRequireBudget` is true and budget not granted, **skip or cheapen** the update.
- Use `bCanBeDeferred` to mark work that can be run later when budget frees up.

## Adaptive LOD Hooks

The plugin exposes helpers like `GetRecommendedLODLevel` and `EnableAdaptiveLOD` that you can feed into:
- Skeletal mesh LOD selection.
- Niagara system detail levels.
- Static mesh replacement (proxy vs hero mesh).

Suggested pattern:
- For important characters, enable Adaptive LOD with both distance and performance.
- For background crowds, use performance-only LOD to throttle quality under pressure.

## Debugging & Tools

### Console Commands

Use Unreal's log categories and console for quick diagnostics:

```text
// Enable verbose logging for PerfMngr
Log LogDAIPerfMngr Verbose

// (If exposed) show performance overlay
PerfMngr.ShowHUD 1

// Dump current budget usage
PerfMngr.DumpBudgets
```

(Exact command names may vary; see in-editor auto-complete after typing `PerfMngr.`.)

### Visualizing Significance / LOD

If your project hooks these up:
- Toggle `bShowSignificanceVisualization` and `bShowLODVisualization` in project settings.
- Use on-screen debug to see which actors are being throttled or downgraded.

## Integration with Other DAI Plugins

The PerfMngr plugin is intended to be **central glue** for performance across other DAI modules:

- **DAI_UltraSky** – Uses attribute gating and timers instead of per-tick brute force, sized by budgets.
- **DAI_Spawner** – Can use budgets to limit spawn waves or async batch size.
- **DAI_Dismember** / **Mutable** – Schedule heavy mesh operations based on render/Mutable budgets.
- **DAI_AI** – Scale AI tick frequency, perception, and behavior depth based on performance pressure.

When adding a new DAI plugin, design APIs so they can **ask PerfMngr**before doing expensive work rather than guessing.

## Best Practices

- **Think in budgets, not FPS** – Treat each expensive system as a budget consumer; PerfMngr helps you track and gate that.
- **Tag your heavy actors** – Add significance/budget components early so profiling shows where time goes.
- **Use events/delegates** – React to `OnPerformanceThresholdExceeded` and `OnBudgetExhausted` instead of polling on Tick.
- **Start conservative** – Begin with stricter budgets and loosen them once you confirm performance headroom.
- **Profile regularly** – Use Unreal Insights and in-editor stats with PerfMngr enabled to ensure behavior matches expectations.

---
Last updated: November 30, 2025
