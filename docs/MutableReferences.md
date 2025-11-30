# Mutable References Index

Curated subset of mirrored "mutable docs/" content for planned customization integration (see `Mutable_Integration_Plan.md`).

## Core Fundamentals
- Mutable Overview – Conceptual pipeline (parameters → graph → generated assets).
- Quickstart / Getting Started – Minimal end-to-end build; baseline for Phase 1 integration.

## Parameters & Graph Authoring
- Parameter Types & Ranges – Guides struct design for save fragments.
- Material & Texture Nodes – Map to appearance layering (dirt, biome weathering).

## Performance & Streaming
- Texture Streaming Strategies – Pre-warm & mip residency recommendations (Fog-of-war / Ultra Sky memory interplay).
- Build Caching & Reuse – Foundation for mesh result pooling (Phase 4 performance).

## Replication & Networking
- Replication Models – Differential parameter sync guidelines (diff vs full state, reliability trade-offs).

## Advanced Features
- Morph Targets & Deformers – Injury / condition overlays (weather + quest reward unlocks).
- Runtime LOD Adjustments – Adaptive cost control for high population scenarios.

---
Maintenance: Update when additional Mutable documents mirrored (grooms, cloth, advanced parameter binding). For a complete list use `GenerateMutableDocIndex.ps1`.
