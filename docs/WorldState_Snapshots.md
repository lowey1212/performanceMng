# World State Snapshots (DAI_Save)

This guide shows how to snapshot world actors (class + transform) and optional property/component data, then restore the world later — either fully or incrementally.

## Quick Start

1. Tag actors that should be included (e.g., `Save.World`).
2. Optionally attach `DAI_SaveSnapshotComponent` to actors to capture extra data:
   - `ActorProperties`: list of property names on the Actor to persist (UPROPERTY only).
   - `bCaptureSceneComponentTransforms`: include relative transforms of scene components.
   - `ComponentClassFilter`: restrict which components are captured.
3. In Blueprints, call:
   - `DAI_SaveWorldState(FilterTag, FragmentId)`
   - `DAI_RestoreWorldState(FilterTag, bPruneMissing, FragmentId)`

If `FilterTag` is empty, the subsystem uses `DefaultWorldStateTag` from Project Settings > Save Plugin. If that’s not set, it attempts `Save.World`. If still empty, all actors are considered (subject to include/exclude filters).

## Include/Exclude Filters

Project Settings > Save Plugin:
- `IncludeActorClasses`: If set, only these Actor classes (and subclasses) are captured.
- `ExcludeActorClasses`: Excluded after includes are applied.
- `DefaultWorldStateTag`: Used when no tag is provided to the Blueprint nodes.

## What Gets Saved

- Actor class path and name (used for spawn/update)
- Actor world transform (location/rotation/scale)
- Optional `ActorProps`: arbitrary properties listed in `DAI_SaveSnapshotComponent.ActorProperties`
- Optional `Components`: per SceneComponent relative transform by component name (filtered by `ComponentClassFilter`)

## Restore Behavior

- Existing actors matched by name are updated (transform and saved properties/components).
- Missing actors are spawned using the saved class path/name and then updated.
- If `bPruneMissing = true`, actors not present in the saved fragment (within the same tag-filter scope) are destroyed.

## Incremental Diffs

To reduce fragment size on repeated captures, the subsystem caches the last snapshot per `FragmentId` and stores only changes when smaller:
- `ChangedOnly=true` + `Actors=[changed subset]`
- `Removed=[names]` for actors that no longer exist

Restore processes whatever is present — changed subset and removals are applied correctly.

## Notes

- Property capture uses Unreal's JsonObjectConverter and only works on UPROPERTY-marked fields.
- Component transforms are restored by component name.
- Name-based matching is used for actors; ensure stable names for deterministic results.
- Multi-ASC auto hooks can be enabled via `bMultiASCAutoHook` if you want tag-triggered saves across multiple ASCs.
