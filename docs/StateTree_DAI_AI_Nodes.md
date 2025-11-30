# DAI_AI StateTree Nodes Reference

This guide documents the custom StateTree nodes provided by the `DAI_AI` plugin. Nodes are grouped by category (Evaluators, Tasks, Conditions, Decorators) and thematic domains (Context, Movement, Interaction & Companion, Temporal, Perception, Performance & Scalability, Emotion & Affect, Alerts & Communication, Budgeting & Throttling, Analytics & Debug).

> NOTE: Feature flags such as `DAI_AI_FEATURE_STATETREE`, `DAI_AI_FEATURE_PERF_VERBOSE`, and `DAI_AI_FEATURE_AI_AUDIT` may gate availability or logging behavior.

---
## Conventions
- Result semantics follow standard StateTree patterns: `Succeeded`, `Failed`, or `Running` for tasks; boolean return for conditions.
- Most instant/one-shot tasks return `Succeeded` on `EnterState` or first `Tick` if their work is complete.
- Tasks with asynchronous movement or waiting logic generally return `Running` until completion criteria are met.
- Unless stated otherwise, distance units are Unreal world units (centimeters) and times are in seconds of game time.

---
## Evaluators
| Evaluator | Purpose | Key Outputs / Notes |
|-----------|---------|---------------------|
| `DAI_ST_AgentContextEvaluator` | Caches and exposes owning pawn, controller, affect & performance components. | Use as root evaluator to avoid redundant component lookups. |
| `DAI_ST_MovementStatusEvaluator` | Tracks active movement request, last destination, remaining distance. | Enables conditions checking arrival or path status. |
| `DAI_ST_FollowContextEvaluator` | Maintains follow target handle, last known location, leash metrics. | Pair with companion/follow tasks & leash conditions. |
| `DAI_ST_TimeSliceEvaluator` | Provides fractional day, world time markers, elapsed computations. | Supports time-of-day & elapsed-since marker conditions. |
| `DAI_ST_NearbyTaggedActorsEvaluator` | Maintains a cached list of actors with specified gameplay tag(s) near the agent. | Shared cache for perception conditions/tasks. |
| `DAI_ST_ImportanceEvaluator` | Computes importance heuristic (e.g., distance & LOD weighted). | Feed gating conditions for performance scaling. |
| `DAI_ST_PerformanceStatsEvaluator` | Exposes performance budget usage, rolling averages, violation counts. | Base for budget usage & trend conditions. |
| `DAI_ST_EmotionDeltaEvaluator` | Captures per-tick and historical emotion deltas, volatility metrics. | Supports emotion delta & volatility conditions. |

---
## Tasks
### Movement
| Task | Description | Key Params |
|------|-------------|------------|
| `DAI_ST_MoveToLocationTask` | Issues AI move to a world position. | Destination (Vector), AcceptanceRadius, bAllowPartial |
| `DAI_ST_MoveToActorTask` | Move toward target actor, tracking dynamic actor location. | Target Actor Handle, AcceptanceRadius |
| `DAI_ST_WanderWithinRadiusTask` | Picks random reachable point within radius & moves there. | Center Source (Actor/Origin), WanderRadius |
| `DAI_ST_ReturnToHomeAnchorTask` | Return to predefined home/anchor point. | Home Tag/Transform Source |
| `DAI_ST_FollowActorTask` | Follow target maintaining leash distance & update cadence. | Target, DesiredDistance, HardLeashDistance |
| `DAI_ST_WaitGameTimeSecondsTask` | Waits a specified game time duration (not real time). | DurationSeconds |
| `DAI_ST_WaitRandomTask` | Wait random duration between min/max bounds. | MinDelay, MaxDelay |

### Interaction & Companion
| Task | Description | Key Params |
|------|-------------|------------|
| `DAI_ST_InteractWithActorTask` | Calls interact interface on target if available & in range. | InteractionDistance |
| `DAI_ST_PickupNearbyActorTask` | Finds qualifying nearby pickup actor & triggers pickup logic. | SearchRadius, RequiredTag |

### Emotion & Affect
| Task | Description | Key Params |
|------|-------------|------------|
| `DAI_ST_InjectEmotionTask` | Injects emotion stimulus into affect system. | EmotionTag, Intensity, DecayProfile |
| `DAI_ST_BlendEmotionTowardsTargetTask` | Gradually moves current emotion intensity toward target value. | EmotionTag, TargetValue, BlendRate |

### Alerts & Communication
| Task | Description | Key Params |
|------|-------------|------------|
| `DAI_ST_SendAlertTask` | Broadcasts an alert message to nearby agents. | AlertTag, Radius, Payload Context |

### Performance & Scalability
| Task | Description | Key Params |
|------|-------------|------------|
| `DAI_ST_SetLODOverrideTask` | Applies a temporary AI LOD override/hint. | LODLevel, Duration |
| `DAI_ST_AdjustUpdateFrequencyTask` | Adjusts tick/update frequency based on importance. | ImportanceThresholds |
| `DAI_ST_DeferHeavyWorkSliceTask` | Spreads heavy computation across frames using slice index. | WorkItems, MaxPerFrame |

### Perception
| Task | Description | Key Params |
|------|-------------|------------|
| `DAI_ST_ScanForTaggedActorsTask` | Scans world (or partition) for actors with tag(s) & caches them. | TagFilter(s), MaxRange, MaxActors |

### Budgeting & Throttling
| Task | Description | Key Params |
|------|-------------|------------|
| `DAI_ST_AcquireThrottleTicketTask` | Attempts to acquire named throttle ticket (rate limiting). | ThrottleName, MaxConcurrent |

### Analytics & Debug
| Task | Description | Key Params |
|------|-------------|------------|
| `DAI_ST_LogStateEntryTask` | Emits log when state entered (optionally with structured context). | LogVerbosity, CustomMessage |
| `DAI_ST_EmitTelemetryEventTask` | Sends telemetry payload (if analytics enabled). | EventName, KeyValues |

---
## Conditions
### Movement & Spatial
| Condition | Purpose | Key Params |
|-----------|---------|------------|
| `DAI_ST_IsAtLocationCondition` | True if within tolerance of location. | Target, Tolerance |
| `DAI_ST_PathRemainingBelowCondition` | Remaining path distance below threshold. | DistanceThreshold |
| `DAI_ST_TargetWithinLeashCondition` | Target within allowed leash distance. | HardLeashDistance |

### Interaction & Tags
| Condition | Purpose | Key Params |
|-----------|---------|------------|
| `DAI_ST_InteractionAvailableCondition` | Actor implements interface & usable. | RequiredInterface, Distance |
| `DAI_ST_ActorHasGameplayTagCondition` | Actor has gameplay tag (optionally exact match). | Tag, bExact |
| `DAI_ST_NearbyActorWithTagCondition` | Any cached nearby actor has tag(s). | Tag(s), Range |

### Emotion & Affect
| Condition | Purpose | Key Params |
|-----------|---------|------------|
| `DAI_ST_EmotionAboveCondition` | Emotion intensity >= threshold. | EmotionTag, Threshold |
| `DAI_ST_EmotionBelowCondition` | Emotion intensity <= threshold. | EmotionTag, Threshold |
| `DAI_ST_EmotionWindowCondition` | Emotion within inclusive min/max window. | EmotionTag, Min, Max |
| `DAI_ST_EmotionDeltaAboveCondition` | Change since last tick/history >= delta. | EmotionTag, Delta |
| `DAI_ST_EmotionVolatilityBelowCondition` | Rolling std-dev/variance below limit. | EmotionTag, VolatilityThreshold |

### Temporal
| Condition | Purpose | Key Params |
|-----------|---------|------------|
| `DAI_ST_TimeOfDayInRangeCondition` | Fractional day between start & end. | StartFrac, EndFrac, bWrap |
| `DAI_ST_ElapsedSinceMarkerAboveCondition` | Elapsed time since named marker >= threshold. | MarkerName, Seconds |
| `DAI_ST_TimeInStateCondition` | Time spent in current state operator check. | Comparator, Seconds |

### Perception & Alerts
| Condition | Purpose | Key Params |
|-----------|---------|------------|
| `DAI_ST_RecentAlertCondition` | Received alert with tag within recent window. | AlertTag, WindowSeconds |
| `DAI_ST_PendingAlertCondition` | Has a pending (unprocessed) alert of tag. | AlertTag |

### Performance & LOD
| Condition | Purpose | Key Params |
|-----------|---------|------------|
| `DAI_ST_ActorImportanceBelowCondition` | Importance metric below threshold. | Threshold |
| `DAI_ST_BudgetUsagePctBelowCondition` | Budget usage % < value. | BudgetName, Percent |
| `DAI_ST_BudgetUsagePctAboveCondition` | Budget usage % > value. | BudgetName, Percent |
| `DAI_ST_BudgetTrendCondition` | Usage trend direction (Up/Down/Stable). | BudgetName, Direction |
| `DAI_ST_BudgetViolationCountCondition` | Violations in window >= count. | BudgetName, Count, Window |
| `DAI_ST_ThrottleTicketAvailableCondition` | Ticket available for name. | ThrottleName |

### Debug & Control
| Condition | Purpose | Key Params |
|-----------|---------|------------|
| `DAI_ST_CooldownCondition` | Cooldown ready for named key. | CooldownName, Interval |
| `DAI_ST_DebugFlagEnabledCondition` | Named debug flag active. | FlagName |

---
## Decorators
| Decorator | Purpose | Key Params |
|-----------|---------|------------|
| `DAI_ST_TimeBudgetGuard` | Fails branch if time budget exceeded. | BudgetName, MaxMsPerFrame |
| `DAI_ST_RateLimitExecutionDecorator` | Suppresses node execution if called too frequently. | Key, MinInterval |

---
## Implementation Notes
- Emotion volatility uses historical ring buffer maintained by emotion evaluator/component; ensure evaluator precedes volatility conditions.
- Importance heuristic defaults: distance weighting + LOD factor; tune in evaluator or expose via data asset for balancing.
- Perception scanning is intentionally coarse: pair `ScanForTaggedActorsTask` with evaluator for cached queries instead of repeated world scans.
- Rate limiting & throttle tickets are complementary: rate limit = temporal frequency; throttle = concurrency cap.
- Time-of-day fractional calculation assumes 24h = 1.0; wrapping supported for ranges crossing midnight.

## Recommended Root Evaluators
Typical root setup:
1. `DAI_ST_AgentContextEvaluator`
2. `DAI_ST_TimeSliceEvaluator` (if any temporal logic)
3. `DAI_ST_PerformanceStatsEvaluator` (if performance/budget gating)
4. `DAI_ST_EmotionDeltaEvaluator` (if emotion-based decisions)
5. Domain-specific (e.g., `DAI_ST_NearbyTaggedActorsEvaluator`, `DAI_ST_ImportanceEvaluator`)

## Composition Patterns
### Follow & Leash
- Evaluators: AgentContext + FollowContext + MovementStatus
- Tasks: FollowActorTask
- Conditions: TargetWithinLeashCondition (guard), PathRemainingBelowCondition (arrival refinement)

### Emotion-Gated Interaction
- Evaluators: AgentContext + EmotionDelta
- Conditions: EmotionWindowCondition, InteractionAvailableCondition
- Task: InteractWithActorTask

### Performance-Aware Behavior Scaling
- Evaluators: PerformanceStats + Importance
- Conditions: ActorImportanceBelowCondition, BudgetUsagePctBelowCondition
- Tasks: AdjustUpdateFrequencyTask, DeferHeavyWorkSliceTask

### Time-Directed Routine
- Evaluators: TimeSlice
- Conditions: TimeOfDayInRangeCondition, ElapsedSinceMarkerAboveCondition
- Tasks: WaitGameTimeSecondsTask + SetLODOverrideTask (optional for off-peak)

## Debugging Tips
- Enable verbose logging via feature flag to trace performance adaptation decisions.
- Use RateLimitExecutionDecorator around noisy logging tasks to reduce spam.
- Leverage TimeBudgetGuard to isolate frames where heavy AI tasks exceed budget.
- Inspect EmotionDeltaEvaluator outputs to tune stimulus intensities.

## Future Extensions (Roadmap Candidates)
- Spatial partition-aware perception scanning.
- DataAsset-driven importance heuristic configuration.
- Unified cache manager for all static node-level buffers.
- Automated doc generation from reflection metadata.
- MassEntity integration for large population optimization.

---
Generated automatically – keep sections alphabetically ordered within tables when adding new nodes. Ensure any new node updates this document in the appropriate category.
