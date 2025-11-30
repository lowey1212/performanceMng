# Epic References Index

Focused subset of mirrored Engine ("epic docs/") content most relevant to current DAI plugins. Use alongside `ExternalReferences.md` for a narrower, engine-only view.

## Core Gameplay & Framework
- Actors & Components – Baseline lifecycle & ticking rules.
- Subsystems Overview – Cross-level manager pattern referenced by Map, Save, Quest, Navigation subsystems.
- Gameplay Tags – Naming, replication; used in Map POIs, SmartObject slots, Quests, Weather states.

## Gameplay Ability System (GAS)
- Intro / Concepts – Ability instancing & execution model (drives Ultra Sky weather ability & future trap effects).
- Attribute Sets – Weather attributes (Ultra Sky), quest reward currency, future combat stats.

## AI & Navigation
- Navigation Mesh / Path Following – Source for curved path conversion constraints.
- Crowd Avoidance – Planned upgrade path for Navigation plugin.
- Smart Objects – Feature parity comparison with lightweight DAI_SmartObject implementation.

## World & Streaming
- World Partition – Map capture tiling & future streaming of fog/POI data.
- Level Streaming Volumes – Quest phase gating & dynamic trap population.

## Saving & Persistence
- SaveGame System – Serialization boundaries versus fragment provider approach.

## Networking & Replication
- Replication Graph – Scaling traps/POIs if density increases.
- Iris Overview – Efficient property replication already leveraged; informs customization replication later.

## Rendering & Environment
- SkyAtmosphere, Volumetric Clouds – Parameter surfaces for Ultra Sky biome mapping.
- Niagara Fundamentals – FX for lightning, storms, trap visuals.

## Performance & Profiling
- Profiling Tools – Budget enforcement (Navigation ticks, Ultra Sky updates, save latency).
- Material Performance – Consolidating biome-driven shader complexity.

## Python & Automation
- Python API Essentials – Validating ScriptName usage & future automation (doc diff ingestion).

## Editor Automation & Build
- Automation Framework – Potential integration for regression testing capture + save cycles.

---
Maintenance: Generated list curated manually; update when new high-impact features are adopted (e.g., StateTree, Mass AI). For exhaustive listing use `docs/tools/GenerateEpicDocIndex.ps1`.
