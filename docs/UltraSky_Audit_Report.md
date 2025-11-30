# DAI_UltraSky Code Audit (2025-10-03)

## Scope
Full pass over plugin `DAI_UltraSky` focusing on:
- Naming consistency & duplication
- API surface clarity (Blueprint vs C++)
- Performance (hot path lookups & per-tick patterns)
- Gameplay Ability / Attribute integration correctness
- Tag usage, DataAssets, and caching
- Maintainability & deprecation strategy

## Key Immediate Adjustments Applied
1. Consolidated sky actor lookup exclusively in `UDAIUltraSkyFunctionLibrary::GetUltraSkyActor` (old WeatherLibrary variant removed pre-release).
2. Added lightweight cached lookup in `UDAIUltraSkyFunctionLibrary` using `TWeakObjectPtr` + world hash to avoid repeated `TActorIterator` scans each BP call.
3. Removed duplicate function prior to any external adoption; no redirectors required.

## Findings & Recommendations
| Area | Issue / Observation | Recommendation | Priority |
|------|---------------------|----------------|----------|
| Lookup Duplication | (Resolved) Single authoritative `UDAIUltraSkyFunctionLibrary::GetUltraSkyActor` | None (already consolidated) | Closed |
| Data Library Naming | `UDAIUltraSkyWeatherLibrary` now only weather DataAsset; no conflicting util class remains | None | Closed |
| Attribute Replication | All attributes replicate with `REPNOTIFY_Always` | Evaluate frequency of change; use `CONDITIONAL` or reduce update rate for slow-changing (e.g., DayLengthSeconds) | Medium |
| Caching Patterns | Many pure BP accessors iterate actors each call | Apply caching pattern used in FunctionLibrary to other frequently queried systems (e.g., lightning controller) | Medium |
| Weather Ability Manager | Grants abilities once, lacks re-grant on ASC late attachment | Listen for ASC initialization or expose manual re-init function (Add delegate binding) | Medium |
| Naming Consistency | Most runtime classes prefixed `DAIUltraSky` but core helpers use `UltraSky` (missing DAI) | Decide style: either all runtime UObject/UClass begin with `DAIUltraSky` or keep `UltraSky` for lightweight statics. Document standard. | Low |
| Deprecated Paths | Docs reference `DAIUltraSkyManager` which isn't present in code | Update docs to reflect `ADAIUltraSkyActor` as canonical manager anchor. | High |
| Weather Tuning Soft Reference | `DefaultTuningDataClass` uses a fixed path under `/Game/UltraSkyModule/Data/...` | Make path configurable via project settings struct + console var override. | Low |
| Tag Initialization | `FDAIUltraSkyWeatherTags::InitializeTags()` declaration present; ensure called early (GameInstance/Module Startup). | If not already in module startup, add call in `StartupModule()`. | High (if missing) |
| Ability Classes | `GA_DAIUltraSky_*` do not use new universal `UDAI_` prefix scheme | Migrate to `UGA_DAI_UltraSky_*` with redirects if standard must apply uniformly. | Medium |
| Weather Chains | `FUtraSkyWeatherChain` manual name search O(n) | If scale grows, build TMap cache on first access. | Low |
| Hardcoded Magic Defaults | Many default floats in actor for intensities / speeds | Centralize into config struct or DataAsset for tuning without recompiles. | Low |
| Moon / Star Material Param Names | Exposed as FName but no validation if parameter exists | Optionally add editor-time validation (PostEditChangeProperty) | Low |
| StateTree Nodes | Large monolithic header (`UltraSkyStateTreeNodes.h`) | Consider splitting by category if growth continues; keep single log category | Low |
| Logging | General logging pattern appears minimal; debug categories grouped | Add verbosity-gated logging for expensive operations (cloud blend, biome apply) | Low |
| Performance Profiles | Enum exists, ensure hot paths respect profile (star twinkle, rotation, attribute replication frequency) | Audit tick to skip cosmetic updates in LowCost | Medium |
| Replication Granularity | All attributes replicated even if rarely viewed (e.g., RayleighScale every frame) | Consider on-change threshold or server-side rate limiting (accumulate & batch) | Medium |

## Suggested Next Steps (Optional Patches)
1. Add module startup call for `FDAIUltraSkyWeatherTags::InitializeTags()` if not already invoked.
2. Add config-driven tuning path (Project Settings: `UDaiUltraSkySettings`).
3. Introduce prefix alignment migration for GA classes (with CoreRedirects) if global naming standard enforced.
4. Implement attribute replication optimization pass (throttle stable values).
5. Provide Blueprint utility to invalidate cached UltraSky actor (e.g., after level streaming) or auto-clear on `FWorldDelegates::OnWorldCleanup`.

## Deprecation Plan
Legacy duplicate lookup removed before distribution; no redirect or staged deprecation required. Future deprecations will follow a two-phase (Warn -> Remove) path only once external content exists.

## Verification Checklist
- Build after changes: (Pending user build) – Expect no API break.
- Blueprint nodes: Deprecated node should display warning string.
- No changes to DataAsset serialization.

## Appendix: Removed Duplicate (Historical Note)
Previous planning suggested a redirect for `UUltraSkyWeatherLibrary::GetUltraSkyActor`; since it was excised prior to first external use, a redirect was intentionally omitted to keep configuration lean.

---
Generated automatically as part of UltraSky audit.
