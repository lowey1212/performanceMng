# External References Index

Curated index of high‑value Unreal Engine and related technology documents locally mirrored under `epic docs/` and `mutable docs/`. Each section lists: Title (Local File) – Rationale / Use Within Project. Prefer this file for a quick jump rather than trawling raw folders. The automation script `docs/tools/GenerateDocIndex.ps1` can regenerate a JSON summary consumed by future in‑editor tooling.

## Gameplay Framework & Abilities
- Gameplay Ability System Overview (GAS_Overview.pdf) – Core concepts: abilities, attribute sets, effects; informs Ultra Sky weather attribute integration & any combat/quest reward effects.
- StateTree Introduction (StateTree_Overview.html) – Future AI behavior orchestration for Navigation + Smart Object usage coordination.
- Gameplay Tags (GameplayTags.html) – Authoritative reference for tag creation & replication semantics; relevant to every DAI_* plugin exposing tags (Map POI tags, SmartObject slot tags, Quest condition tags).

## Input & Interaction
- Enhanced Input Guide (EnhancedInput.html) – Basis for binding trap placement / map commands without legacy input system coupling.
- Smart Objects (SmartObjects.html) – Engine reference vs our lightweight SmartObject component to identify potential feature gaps (cooldowns, claim policies).

## Navigation & Movement
- Path Following & Navigation Mesh (NavigationMesh.html) – Low‑level expectations for navmesh queries before curved path conversion in DAI Navigation.
- Crowd Avoidance (CrowdAvoidance.html) – Future upgrade path from simple separation steering to Detour/engine hybrid.

## Rendering & Performance
- Profiling Overview (ProfilingTools.html) – CPU/GPU profiling steps; connect to Navigation stat group & Ultra Sky tick budget audits.
- Shader Compile & Material Optimization (MaterialPerformance.html) – Guideline for future Ultra Sky biome material parameter consolidation.

## World Composition / Streaming
- World Partition Basics (WorldPartition.html) – Informs Map capture rig partition boundaries & future tiled map streaming.
- Level Streaming Volumes (LevelStreamingVolumes.html) – Potential synergy with quest phase gating & trap population control.

## Saving & Persistence
- SaveGame Serialization (SaveGameSystem.html) – Engine canonical serialization pipeline to validate our fragment approach and versioning suggestions.

## Networking & Replication
- Replication Graph (ReplicationGraph.html) – Prospective optimization for high density trap / smart object / map POI replication.
- Iris Replication (IrisOverview.pdf) – Confirms best practices for replicated properties already leveraged by Traps & future Mutable asset streaming metadata.

## Mutable (Character/Asset Customization)
- Mutable 5.6 Overview (Mutable_Overview.pdf) – Baseline pipeline for dynamic mesh generation; informs Phase 1 integration plan.
- Mutable Texture Streaming (Mutable_TextureStreaming.pdf) – Guides memory budgeting & save fragment capture of customization state.
- Mutable Replication Strategies (Mutable_Replication.pdf) – Reference for efficient network synchronization of parameter deltas.

## FX & Environment
- Niagara Basics (NiagaraBasics.html) – Alignment with Ultra Sky weather FX spawn patterns.
- Volumetric Clouds (VolumetricClouds.html) – Cloud density/coverage parameter mapping to biome data assets.

## Audio
- Audio Mixing & Subsystems (AudioSubsystem.html) – Potential integration for environment/condition sound crossfades in Ultra Sky.

## Python & Scripting
- Unreal Python API (UnrealPythonAPI.html) – Cross‑check naming collisions; complements `PythonExposureGuidelines.md`.

## Editor Automation
- Automation & Build Cook Run (AutomationBCR.html) – Future harness for regression validating map capture + save load integration.

## Data Assets & Asset Management
- Primary Asset Types (PrimaryAssetTypes.html) – Guidance for quest asset classification & save referencing.

## Tagging Key (Internal)
Tag Roots in DAI project (illustrative; keep updated):
- DAI.Map.* – Map subsystem runtime POI/icon semantic tags.
- DAI.SmartObject.* – Smart object slot & type tags.
- DAI.Quest.* – Quest objectives, conditions.
- DAI.State.* – Temporary state tags (sitting, interacting).
- DAI.Weather.* – Ultra Sky condition / biome descriptors (future).

---
Maintenance: Run the automation script when adding new mirrored docs; then adjust this curated list (we only list the top, not every file). Keep rationale lines short; deeper commentary belongs in feature‑specific docs.
Supplemental scripts:
- `docs/tools/GenerateDocIndex.ps1` – regenerates JSON index.
- `docs/tools/GenerateDocDelta.ps1` – creates `ExternalReferences.delta.md` & refreshes snapshot (omit snapshot with -SkipSnapshot for CI use).

CI: GitHub Actions workflow `doc-index.yml` runs index + delta generation on pushes/PRs and publishes the delta as an artifact.

