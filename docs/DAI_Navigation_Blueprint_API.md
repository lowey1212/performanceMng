# DAI Navigation Blueprint API (Prefixed Wrappers)

This document lists the DAI_ prefixed Blueprint-accessible wrappers for rapid discoverability. Use the Blueprint Palette search filter `DAI_` to view only these nodes. All designer-facing nodes in this plugin are exposed via DAI_ wrappers; legacy non-prefixed nodes were removed.

## Subsystem (UDAI_NavigationSubsystem)
- DAI_EnableNavDebug(bool bEnableFlag)
- DAI_IsNavDebugEnabled() : bool
- DAI_EnablePerformanceBudgeting(bool bEnableFlag)
- DAI_GetPerformanceMetrics() : FDAINavigationPerformanceMetrics
- DAI_SetFrameTimeBudget(float NewBudgetMs)
- DAI_EnableMutableVisualization(bool bEnableFlag)
- DAI_SetVisualizationLODLevel(EDAINavVisualizationLOD LOD)
- DAI_BuildCurvedPath(Start, End, OutPath) : bool
- DAI_BuildCurvedPathAndSpeed(Start, End, OutPath, OutSpeed) : bool
- DAI_MoveActorAlongCurvedPath(Actor, Destination) : bool
- DAI_MoveActorAlongCurvedPathDynamic(Actor, Destination, bAutoRepath) : bool
- DAI_MoveActorAlongCurvedPathToActor(Actor, GoalActor, bAutoRepath) : bool
- DAI_BuildSpiderPath(Start, Goal, Params, OutPath) : EDAISpiderPathResult
- DAI_MoveActorAlongSpiderPath(Actor, GoalLocation, CrawlSpeed) : bool

## Curved Path Following (UDAI_CurvedPathFollowingComponent)
- DAI_GetCurrentS() : float
- DAI_GetPathLength() : float
- DAI_GetLookAheadPoint() : FVector
- DAI_GetCurrentTangent() : FVector
- DAI_GetDesiredVelocity() : FVector
- DAI_GetGoalLocation() : FVector
- DAI_GetGoalActor() : AActor*
- DAI_CancelPath()
- DAI_GetLastCancelReason() : EDAICurvedCancelReason
- DAI_SetPaused(bPaused)
- DAI_IsPaused() : bool
- DAI_TryMidPathSpliceTo(NewGoal) : bool

## Spider Path Following (UDAI_SpiderPathFollowingComponent)
- DAI_HasPath() : bool
- DAI_GetPathLength() : float
- DAI_GetCurrentS() : float
- DAI_GetCurrentTangent() : FVector
- DAI_GetCurrentSpeed() : float
- DAI_GetBaseSpeed() : float
- DAI_CancelSpiderPath()
- DAI_SetPaused(bPaused)
- DAI_IsPaused() : bool

## Spline Follow (UDAI_SplineFollowComponent)
- DAI_HasSpline() : bool
- DAI_GetDistanceAlongSpline() : float
- DAI_GetSplineLength() : float
- DAI_GetCurrentSpeed() : float
- DAI_SetTargetBaseSpeed(NewBase)
- DAI_CancelFollow()
- DAI_SetPaused(bPaused)
- DAI_IsPaused() : bool
- DAI_SetNoiseParams(LatAmp, LatFreq, FwdAmp, FwdFreq)
- DAI_IsWaiting() : bool
- DAI_ForceEndWait()
- DAI_GetCurrentWaitIndex() : int32

## Visualization & Budgeting
- Use subsystem nodes for visualization and perf budgeting (preferred):
	- DAI_EnableMutableVisualization(bool bEnableFlag)
	- DAI_SetVisualizationLODLevel(EDAINavVisualizationLOD LOD)
	- DAI_EnablePerformanceBudgeting(bool bEnableFlag)
	- DAI_GetPerformanceMetrics() : FDAINavigationPerformanceMetrics
	- DAI_SetFrameTimeBudget(float NewBudgetMs)

Note: The former Mutable Bridge Blueprint nodes were removed; internal bridge logic remains in C++.

## Spline Navigation Library (UDAI_SplineNavigationLibrary)
- DAI_FollowBetweenPoints(Actor, Start, End, Speed=300)
- DAI_FollowSpline(Actor, Spline, Speed=300, bLoop)

## Console Commands
- DAI.Nav.Help : Show DAI_Navigation console help
- dai.nav.DumpPerf : Dump performance metrics
- dai.nav.SetLOD <0-3> : Set visualization LOD (High/Med/Low/Hidden)
- dai.nav.ToggleMutableVis : Toggle mutable visualization globally
- dai.nav.Info : Show feature flags & dynamic wrapper counts
- dai.nav.AuditDeprecated : (Requires DAI_FEATURE_NAV_AUDIT=1) Legacy audit of deprecated functions (typically zero in current builds)

## Feature Flags
Compile-time flags (set in `DAI_Navigation.Build.cs`):
- DAI_FEATURE_NAV_PERF (1/0) : Enables performance metrics & budgeting timers.
- DAI_FEATURE_NAV_VERBOSE (1/0) : Includes or strips VeryVerbose logging blocks.
- DAI_FEATURE_NAV_AUDIT (1/0) : Enables runtime audit console command(s) & dynamic reflection summaries.

## Usage Notes
- Wrappers are thin; no added overhead beyond a trivial inline call.
- Only DAI_ prefixed nodes are exposed in Blueprints. Non-prefixed nodes have been removed to simplify the designer surface.
- For automated QA, prefer the DAI_ prefix set—its stability makes script-based reflection filtering simpler.
- Use `dai.nav.Info` during development to verify wrapper counts.

## Future Extensions (Suggestions)
- Add DAI_ wrappers for any future SmartObject navigation or crowd systems.
- Provide a DAI_NavigationSettings asset + Blueprint library for bulk toggles (perf/debug) if designer demand grows.

---
Generated on demand. Update this file when adding/removing wrappers.

## Deprecation Policy (Current)
- Designer-facing deprecated Blueprint nodes have been removed. Prefer direct use of the DAI_ wrappers.
- C++ surface uses `UE_DEPRECATED` where needed; Blueprint metadata DeprecationMessage is avoided.
- The audit commands remain for diagnostics, but should report zero deprecated nodes in normal builds.

## Troubleshooting
| Symptom | Likely Cause | Fix |
|--------|--------------|-----|
| UHT error: 'UFUNCTION must not be inside preprocessor blocks' | Attempted to wrap UFUNCTION declarations with custom macro | Keep declarations always visible; move conditional logic to implementation or bodies |
| `dai.nav.AuditDeprecated` missing | `DAI_FEATURE_NAV_AUDIT` disabled | Set define to 1 in Build.cs and rebuild |
| Deprecated count non-zero unexpectedly | A lingering Blueprint or plugin map references removed nodes | Run a full asset scan/load all persistent levels and re-run audit; replace calls with DAI_ nodes |

---
Last updated: October 6, 2025
