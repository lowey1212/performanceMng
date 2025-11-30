# DAI_PerfMngr API Reference

This document summarizes the most important C++ and Blueprint-facing APIs exposed by **DAI_PerfMngr** for in-project use. It is intentionally narrower than the full top-level doc in `docs/plugins/DAI_PerfMngr.md`, focusing on what you commonly call from gameplay code.

## World Subsystem: `UDAIPerfMngrSubsystem`

**Header**: `DAIPerfMngrSubsystem.h`  
**Type**: `UWorldSubsystem`  
**Implements**: `IDAIPerformanceService`

### Accessing the Subsystem
```cpp
UDAIPerfMngrSubsystem* Perf = World->GetSubsystem<UDAIPerfMngrSubsystem>();
```

### Key Functions (C++)

> Names are representative and should follow the actual header. Use this as a mental map when searching.

- `float GetCurrentFrameRate() const;`
- `float GetFrameTimeMs() const;`
- `float GetPerformanceBudgetUsage(EDAIBudgetCategory Category) const;`
- `bool IsPerformanceBudgetExceeded(EDAIBudgetCategory Category, float Threshold = 0.9f) const;`
- `void SetPerformanceBudget(EDAIBudgetCategory Category, float BudgetMs);`
- `bool RequestBudgetAllocation(EDAIBudgetCategory Category, float RequestedMs, EDAIBudgetPriority Priority);`
- `void ReleaseBudgetAllocation(EDAIBudgetCategory Category, float ReleasedMs);`

Significance helpers (may also live in Blueprint library):
- `bool RegisterSignificanceActor(AActor* Actor, EDAISignificanceFunction Function, float BaseSignificance = 1.0f);`
- `void UnregisterSignificanceActor(AActor* Actor);`
- `float GetActorSignificance(const AActor* Actor) const;`

LOD helpers:
- `int32 GetRecommendedLODLevel(const AActor* Actor, const FVector& ViewerLocation) const;`

### Delegates

- `FOnPerformanceThresholdExceeded OnPerformanceThresholdExceeded;`
- `FOnBudgetExhausted OnBudgetExhausted;`

See `docs/plugins/DAI_PerfMngr.md` for full parameter breakdowns.

## Blueprint Library: `UDAIPerfMngrBlueprintLibrary`

**Header**: `DAIPerfMngrBlueprintLibrary.h`  
**Type**: `UBlueprintFunctionLibrary`

### Monitoring

- `GetCurrentFrameRate(WorldContextObject) → float`
- `GetFrameTimeMs(WorldContextObject) → float`
- `GetPerformanceBudgetUsage(WorldContextObject, BudgetCategory) → float`
- `IsPerformanceBudgetExceeded(WorldContextObject, BudgetCategory, Threshold = 0.9) → bool`

### Budgets

- `SetPerformanceBudget(WorldContextObject, BudgetCategory, BudgetMs)`
- `RequestBudgetAllocation(WorldContextObject, BudgetCategory, RequestedMs, Priority) → bool`
- `ReleaseBudgetAllocation(WorldContextObject, BudgetCategory, ReleasedMs)`

### Significance

- `RegisterSignificanceActor(WorldContextObject, Actor, SignificanceFunction, BaseSignificance = 1.0) → bool`
- `UnregisterSignificanceActor(WorldContextObject, Actor)`
- `GetActorSignificance(WorldContextObject, Actor) → float`

### LOD

- `GetRecommendedLODLevel(WorldContextObject, Actor, ViewerLocation) → int32`
- `SetActorLODLevel(Actor, LODLevel, bForceUpdate = false)`
- `EnableAdaptiveLOD(Actor, bEnable, LODSettings)`

## Components

### `UDAISignificanceComponent`

**Header**: `DAISignificanceComponent.h`  
**Base**: `UActorComponent`

Key properties (Blueprint-visible):
- `SignificanceFunction` (`EDAISignificanceFunction`)
- `BaseSignificance` (`float`)
- `bOverrideSignificance` (`bool`)
- `PerformanceWeight` (`float`)
- `bCanBeOptimized` (`bool`)

Usage:
- Attach to any actor that should be part of significance-based quality scaling.
- Configure function and base significance in Blueprint details.

### `UDAIPerformanceBudgetComponent`

**Header**: `DAIPerformanceBudgetComponent.h`  
**Base**: `UActorComponent`

Key properties (Blueprint-visible):
- `RequiredBudgetCategory` (`EDAIBudgetCategory`)
- `EstimatedCostMs` (`float`)
- `Priority` (`EDAIBudgetPriority`)
- `bRequireBudget` (`bool`)
- `bCanBeDeferred` (`bool`)

Usage:
- Attach to actors that own significant work.
- In `Tick` or custom update, query PerfMngr/budgets before running heavy logic.

## Enums & Structs (Blueprint Types)

### `EDAIBudgetCategory`

Budget buckets; project can extend in C++.
- `Rendering`
- `Animation`
- `AI`
- `Physics`
- `Audio`
- `Networking`
- `Scripting`
- `Custom`

### `EDAISignificanceFunction`

- `Distance`
- `ScreenSize`
- `Importance`
- `Combined`
- `Custom`

### `EDAIBudgetPriority`

- `Critical`
- `High`
- `Normal`
- `Low`
- `Background`

### `FDAIAdaptiveLODSettings`

Struct for `EnableAdaptiveLOD`:
- `bEnableDistanceLOD`
- `bEnablePerformanceLOD`
- `DistanceThresholds` (`TArray<float>`)
- `PerformanceThresholds` (`TArray<float>`)
- `UpdateFrequency` (`float`)
- `HysteresisThreshold` (`float`)

### `FDAIPerformanceMetrics`

Often returned from C++/exposed as struct:
- `FrameRate`
- `FrameTimeMs`
- `RenderTimeMs`
- `GameThreadTimeMs`
- `GPUTimeMs`
- `MemoryUsageMB`
- `BudgetUsage` (`TMap<EDAIBudgetCategory,float>`)

## Events / Delegates (Gameplay Integration)

You can bind these in C++ or Blueprint (if exposed as dynamic multicast delegates):

### `OnPerformanceThresholdExceeded`

```cpp
void AMyGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (UDAIPerfMngrSubsystem* Perf = GetWorld()->GetSubsystem<UDAIPerfMngrSubsystem>())
    {
        Perf->OnPerformanceThresholdExceeded.AddDynamic(this, &AMyGameMode::HandlePerfPressure);
    }
}

void AMyGameMode::HandlePerfPressure(EDAIBudgetCategory Category, float CurrentUsage, float Threshold)
{
    // e.g. lower AI quality or reduce FX
}
```

### `OnBudgetExhausted`

Use this for **last-resort** fallbacks—turning off cosmetic systems or enabling an "emergency performance mode".

## Integration Notes

- Treat this API as the **single source of truth** for runtime performance decisions.
- Prefer using enums/structs (e.g. `EDAIBudgetCategory`, `EDAIBudgetPriority`) rather than raw floats/strings.
- When in doubt, look up the exact function signatures in the headers under `DAI_PerfMngr/Source/DAI_PerfMngr/Public/`.

---
Last updated: November 30, 2025
