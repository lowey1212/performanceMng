# Mutable Integration Plan

Goal: Introduce Mutable (dynamic mesh & material customization) into the DAI project in staged phases without creating hard plugin dependencies.

## Phase 0 – Foundations (Current)
- No runtime dependency; planning only.
- Identify character classes and equipment pieces needing dynamic appearance (body morphs, armor variants, decals).
- Ensure Save System fragment architecture can persist: source mesh IDs, parameter sets, applied morph weights.

## Phase 1 – Read-Only Preview
- Add optional soft dependency detection (`__has_include` for Mutable headers) in a new `DAI_Customization` plugin.
- Implement a `UMutablePreviewComponent` wrapper (if headers present) with Blueprint accessors: `ApplyParameterSet`, `RebuildIfDirty`.
- Map a minimal Parameter Set (e.g., BodyType, ArmorColorPrimary, DecalID) to in‑game appearance.
- Save Fragment: `FCustomizationSaveData` with version + arrays (Name, Value/Color/Float) – integrated if component exists.

## Phase 2 – Runtime Authoring
- Add UI tooling to modify parameters (sliders/color pickers) in PIE.
- Introduce async build queue with budget (max builds per second) to avoid frame spikes.
- Add incremental save on confirm; rollback on cancel.
- Tag propagation: customization changes raise a Gameplay Tag (e.g., `DAI.Customization.Changed`) for abilities reacting to appearance state.

## Phase 3 – Networking & Replication
- Determine minimal replication: only parameter diffs (Name + new value) broadcast via reliable RPC or replicated array with change mask.
- Integrate Iris if needed for high churn customization sessions.
- Conflict resolution: last writer wins + optional authoritative server sanitize pass.

## Phase 4 – Performance & Streaming
- Pool common generated meshes; introduce reference counting to avoid duplicate builds for identical parameter sets.
- Use Mutable texture streaming doc to prefetch MIPs before swapping appearance in view of camera.
- Add performance telemetry: avg build ms, memory footprint per unique build (stat group `DAI_Customization`).

## Phase 5 – Advanced Features
- Conditional morph stacking (injury overlays, weathering from Ultra Sky conditions).
- Integration with Quest rewards (unlock new customization parameters or palettes).
- Integration with Traps / Smart Objects (contextual dirt or scorch decals after events).

## Save System Interaction
On Load: If Mutable present, reconstruct parameter set, schedule rebuilds in batches (limit per frame). If absent, gracefully skip (appearance defaults).

## Risks & Mitigations
- Build Hitches: Use async + queue budget + warm caches on map load.
- Data Bloat: Compress parameter sets or store only deltas from base template asset.
- Version Drift: Include schema version; supply migration functions (e.g., rename parameter or clamp old ranges).

## Metrics To Track
- Average Build Time (ms)
- Peak Concurrent Builds
- Unique Parameter Set Count
- Mesh / Texture Memory (per unique build)

## Open Questions
- Do we require designer-friendly DataAsset wrappers for predefined customization presets? (Likely Phase 2.)
- Will quest or ability systems dynamically gate parameter visibility? (Integrate tags if yes.)

## Next Immediate Steps
1. Create `DAI_Customization` plugin skeleton (no hard dependency) – not yet implemented.
2. Draft `FCustomizationSaveData` struct & bridge header.
3. Prototype parameter apply path with a simple color swap.
