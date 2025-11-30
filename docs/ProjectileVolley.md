# Projectile Volley System (UE 5.5)

High-scale, server-authoritative projectile volleys that render as efficient client-side Niagara visuals. Designed for hundreds to thousands of arrows per second with pierce, stick, and pickup options, GAS integration, and FastArray replication.

This doc covers how to use it, what each property does (with tooltips), the Niagara parameter contract, replication, and performance tuning.

---

## Overview

- Server does gameplay: movement, collision (CPU sweeps), pierce accounting, and GAS effects/cues.
- Clients render visuals only: a Niagara GPU system draws the “volley” with distance-based LOD.
- Replication uses a lightweight Replicator actor + FastArray to push spawn and impact events to clients.
- Data-driven: author physics/damage defaults in a `UProjectileVolleyProfile` DataAsset; override per-ability if needed.

Key classes
- `UProjectileVolleySubsystem` (server, tickable world subsystem): spawns and simulates CPU proxies, applies gameplay, replicates cosmetic events
- `UArrowVisualManagerSubsystem` (client world subsystem): spawns/updates Niagara volleys and impact cosmetics
- `UDAI_BaseProjectileAbility` (ability entry point): builds a `FVolleySpawnRequest` from ability fields and calls `StartVolley`
- `UProjectileVolleyProfile` (DataAsset): shared defaults for physics, collision, GAS, and visuals
- `AProjectileVolleyReplicator`: owner/cull-aware relay for FastArray events (spawn/impact) to clients

---

## Quick start (Blueprint ability)

1) In your projectile ability (derived from `UDAI_BaseProjectileAbility`):
- Enable “Use Volley Mode”
- Set InitialSpeed and ProjectileLifeSpan (used by the server and sent to clients)
- Set `VolleyVisualCount` (cosmetic count clients should render)
- Pick or create a `UProjectileVolleyProfile` and assign it to `TypedVolleyProfile`
- Assign Niagara systems: `VolleyNiagaraSystem` and optional `ImpactNiagaraSystem`
- Configure collision channel and optional GAS effect/cue if you want gameplay on impact

2) Call the ability (e.g., from input). The ability will route to `UProjectileVolleySubsystem::StartVolley` on the server and replicate a `FVolleySpawnEvent` for clients.

3) Tune server-side limits in `UProjectileVolleySubsystem` (MaxActiveProxies, MaxSweepsPerFrame, async sweeps) and client visual LOD in `UArrowVisualManagerSubsystem`.

---

## Niagara parameter contract (client)

Your volley Niagara system should expose the following User parameters that are set per spawn/update:
- User.StartLocation (Vec3)
- User.Direction (Vec3, normalized)
- User.Speed (Float)
- User.MaxLifetime (Float)
- User.Count (Int) — may be scaled down by distance-based LOD
- User.VisualProfileId (Int)

The subsystem will spawn or reuse one Niagara component per VisualProfileId and update these parameters at a throttled cadence.

File: `Plugins/DAI/Source/DAI/Private/AbilitySystem/ArrowVisualManagerSubsystem.cpp`

---

## Ability properties (volley mode)

Class: `UDAI_BaseProjectileAbility` in `AbilitySystem/BaseProjectileAbility.h`

- Use Volley Mode
  - UPROPERTY: `bUseVolleyMode`
  - Tooltip: Route firing through a server volley subsystem that scales to hundreds/thousands; clients render Niagara visuals.
  - Default: false

- Visual Count
  - UPROPERTY: `VolleyVisualCount` (ClampMin=1)
  - Tooltip: How many visual arrows the client Niagara system should spawn for this volley (cosmetic).
  - Default: 20

- Visual Profile Id
  - UPROPERTY: `VisualProfileId` (ClampMin=0)
  - Tooltip: Visual profile identifier used by clients to pick meshes/materials/trails.
  - Default: 0

- Gameplay Profile (generic)
  - UPROPERTY: `GameplayProfile`
  - Tooltip: Gameplay DataAsset with damage/pierce/drag/gravity; used by the server volley subsystem.

- Typed Volley Profile (preferred)
  - UPROPERTY: `TypedVolleyProfile`
  - Tooltip: Typed volley profile; if set, its values are used unless overridden on the request.

- Volley Niagara System (clients)
  - UPROPERTY: `VolleyNiagaraSystem`
  - Tooltip: Niagara GPU system that renders the volley on clients.

- Impact Niagara System (clients)
  - UPROPERTY: `ImpactNiagaraSystem`
  - Tooltip: Niagara burst played at impact locations on clients (short-lived, pooled).

- Proxy Collision Radius (cm)
  - UPROPERTY: `ProxyCollisionRadius` (ClampMin=0.1)
  - Tooltip: Sphere/capsule sweep radius used by server CPU proxies (in cm).
  - Default: 1.5

- Max Pierces
  - UPROPERTY: `MaxPierces` (ClampMin=0)
  - Tooltip: Maximum pierces resolved by the server per proxy before stopping.
  - Default: 0

- Stick On Hit
  - UPROPERTY: `bStickOnHit`
  - Tooltip: Enable sticking to static geometry on hit (server-side).
  - Default: true

- Enable Pickup
  - UPROPERTY: `bEnablePickup`
  - Tooltip: Register stuck arrows with a pickup manager (server-side).
  - Default: false

- Projectile Collision Channel
  - UPROPERTY: `ProjectileCollisionChannel`
  - Tooltip: Collision channel used by server sweeps for this volley.
  - Default: ECC_GameTraceChannel1

- GAS Damage Effect Class (optional)
  - UPROPERTY: `DamageEffectClass`
  - Tooltip: Optional GameplayEffect to apply on hit (server). If unset, only GameplayCue plays.

- GAS Damage Magnitude
  - UPROPERTY: `DamageMagnitude`
  - Tooltip: Damage magnitude sent as SetByCaller to the effect (see DamageSetByCallerTag).
  - Default: 0

- GAS SetByCaller Tag
  - UPROPERTY: `DamageSetByCallerTag`
  - Tooltip: SetByCaller tag used to supply DamageMagnitude (e.g., SetByCaller.Damage).
  - Default: SetByCaller.Damage

- GAS Impact Cue Tag
  - UPROPERTY: `ImpactCueTag`
  - Tooltip: GameplayCue tag to send on impact (e.g., Cue.Projectile.Impact).
  - Default: Cue.Projectile.Impact

Execution hook
- The ability calls `FireVolleyFromAbility(AvatarActor)`, which builds a `FVolleySpawnRequest` and calls `UProjectileVolleySubsystem::StartVolley` on the server.
- Source: `Plugins/DAI/Source/DAI/Private/AbilitySystem/BaseProjectileAbility.cpp` (see `FireVolleyFromAbility`).

---

## Volley spawn request (server)

Struct: `FVolleySpawnRequest` in `AbilitySystem/ProjectileVolleySubsystem.h` (BlueprintType)

- StartLocation (Vec3)
- Direction (Vec3, normalized)
- Speed (float)
- Count (int32)
- MaxLifetime (float seconds)
- VisualProfileId (int32)
- ProxyCollisionRadius (float cm)
- MaxPierces (int32)
- bStickOnHit (bool)
- bEnablePickup (bool)
- GameplayProfile (TSoftObjectPtr<UDataAsset>)
- TypedProfile (TSoftObjectPtr<UProjectileVolleyProfile>)
- VolleyNiagaraSystem (TSoftObjectPtr<UNiagaraSystem>)
- ImpactNiagaraSystem (TSoftObjectPtr<UNiagaraSystem>)
- OwnerActor (Transient AActor*, not replicated)
- CollisionChannel (ECollisionChannel)
- DamageEffectClass (TSubclassOf<UGameplayEffect>)
- DamageMagnitude (float)
- DamageSetByCallerTag (FName)
- ImpactCueTag (FName)

Server uses TypedProfile if present to seed physics/damage defaults (gravity, drag, radius, pierces, channel, GAS).

---

## Server subsystem settings

Class: `UProjectileVolleySubsystem` in `AbilitySystem/ProjectileVolleySubsystem.h`

- MaxActiveProxies (int32, ClampMin=1)
  - Tooltip: Max active CPU proxies on the server.
  - Default: 64

- MaxSweepsPerFrame (int32, ClampMin=1)
  - Tooltip: Max collision sweeps per frame on the server.
  - Default: 64

- MaxServerRelevanceDistance (float cm, ClampMin=1000)
  - Tooltip: Beyond this distance from any player, server may skip sampling.
  - Default: 50000

- NearImpactTimeWindow (float seconds, ClampMin=0.01)
  - Tooltip: Entities with remaining life below this are prioritized.
  - Default: 0.25

- NearPlayerDistance (float cm, ClampMin=100)
  - Tooltip: Entities closer than this to players are prioritized.
  - Default: 3000

- bEnableAsyncSweeps (bool)
  - Tooltip: Enable async sweeps to move collision off the game thread.
  - Default: true

- MaxAsyncSweepsPerFrame (int32, ClampMin=1)
  - Tooltip: Max async sweeps to dispatch per frame.
  - Default: 64

- bReplicatorUseOwnerRelevancy (bool)
  - Tooltip: If true, the replicator uses owner relevancy instead of being always relevant. Set owner from volley request's OwnerActor.
  - Default: false

- ReplicatorCullDistance (float cm)
  - Tooltip: If >0, replicator is only relevant to players within this distance (cm). Requires custom cull distance setup.
  - Default: 0

Primary API
- StartVolley(const FVolleySpawnRequest&)
- Tick(float DeltaTime) — advances proxies, sweeps, applies GAS/cues, replicates `FImpactEvent`

---

## Client visual manager settings

Class: `UArrowVisualManagerSubsystem` in `AbilitySystem/ArrowVisualManagerSubsystem.h`

Impact cosmetics (optional, by physical surface index)
- ImpactDustBySurface: TMap<int32, UNiagaraSystem>
- ImpactDebrisBySurface: TMap<int32, UNiagaraSystem>
- ImpactSoundBySurface: TMap<int32, USoundBase>
- ImpactDecalBySurface: TMap<int32, UMaterialInterface>
- DecalSize (FVector), DecalLifetime (float), bRandomizeDecalRotation (bool)

Visual LOD
- VisualLODDistanceStart (cm): begin reducing Count
- VisualLODDistanceEnd (cm): at/beyond this, Count reaches minimum
- VisualLODMinFraction (0..1): minimum fraction of requested Count
- VisualParamUpdateInterval (seconds): throttle Niagara parameter updates

Methods
- OnVolleySpawn(const FVolleySpawnEvent&)
- OnImpactEvent(const FImpactEvent&)
- SpawnOrUpdateVolleyNiagara, SpawnImpactNiagara, SpawnImpactDustDebrisSound, SpawnImpactDecal

---

## Replication model

- Server spawns/owns a single `AProjectileVolleyReplicator` per world (as needed).
- Spawn events: `FVolleySpawnEvent` contain StartLocation, Direction, Speed, Lifetime, Count, VisualProfileId, and soft references to Niagara systems.
- Impact events: `FImpactEvent` carry location/normal, surface type, VisualProfileId, VolleyId, and flags (stuck, pierce-continues).
- Both are sent via FastArray for efficiency; clients call into `UArrowVisualManagerSubsystem` to render.
- Relevancy/cull
  - Optional: owner-only relevancy via `bReplicatorUseOwnerRelevancy` with `OwnerActor` on the request
  - Optional: cull distance via `ReplicatorCullDistance`

---

## Data profile (`UProjectileVolleyProfile`)

File: `AbilitySystem/ProjectileVolleyProfile.h`

Physics
- GravityZOverride (float); if 0, use world gravity
- DragCoefficient (float >= 0)
- ProxyCollisionRadius (float cm >= 0.1)
- MaxPierces (int32 >= 0)

Gameplay
- CollisionChannel (ECollisionChannel)
- DamageEffectClass (UGameplayEffect)
- DamageMagnitude (float)
- DamageSetByCallerTag (FName)
- ImpactCueTag (FName)

Visuals (optional)
- VisualProfileId (int32)
- VolleyNiagaraSystem (Niagara)
- ImpactNiagaraSystem (Niagara)

Preferred use: set common defaults in the profile and reference it from abilities via `TypedVolleyProfile`.

---

## Testing and tools

- Console command: `dai.TestVolley [Count] [Speed] [Lifetime]`
  - Spawns a test volley from the local player camera.
  - Source: `Plugins/DAI/Source/DAI/Private/DAI.cpp`

- Test actor: `AVolleyTestActor`
  - Drop in a level, configure params (Count, Speed, Life, etc.), and call FireVolley on begin play or via timer.
  - Files: `AbilitySystem/VolleyTestActor.h/.cpp`

---

## Performance tuning checklist

Server
- Limit MaxActiveProxies to keep CPU in check
- Cap MaxSweepsPerFrame; turn on bEnableAsyncSweeps and set MaxAsyncSweepsPerFrame
- Use relevance knobs: MaxServerRelevanceDistance, NearImpactTimeWindow, NearPlayerDistance
- Prefer TypedProfile to avoid per-request overrides

Client
- Set appropriate VisualLODDistanceStart/End and VisualLODMinFraction
- Keep User parameter updates minimal; VisualParamUpdateInterval throttles updates
- Use pooled or lightweight Impact Niagara bursts

Networking
- Consider `bReplicatorUseOwnerRelevancy` for owner-only volleys (e.g., local-only training)
- Set `ReplicatorCullDistance` if the effect is only meaningful nearby

---

## Edge cases and notes

- Gameplay logic is server-only; clients should not rely on Niagara for hit logic.
- If `ImpactNiagaraSystem` isn’t set, only dust/debris/sound/decals (if configured) will play on impact.
- `OwnerActor` in `FVolleySpawnRequest` is transient and not replicated; it’s used to set relevancy/cull owner.
- If `TypedVolleyProfile` is provided, subsystem loads it (synchronously if needed) to fill runtime params.
- `VisualProfileId` is used as the key for persistent volley Niagara components and impact system lookup.

---

## API reference (files and symbols)

- Ability
  - `UDAI_BaseProjectileAbility` — `AbilitySystem/BaseProjectileAbility.h/.cpp`
  - `void FireVolleyFromAbility(AActor* AvatarActor)` — builds `FVolleySpawnRequest` and calls `StartVolley`

- Subsystem (server)
  - `UProjectileVolleySubsystem` — `AbilitySystem/ProjectileVolleySubsystem.h/.cpp`
  - `void StartVolley(const FVolleySpawnRequest& Request)`
  - Tick/Initialize/Deinitialize; async sweep handling `OnAsyncSweepComplete`

- Replicator
  - `AProjectileVolleyReplicator` — `AbilitySystem/ProjectileVolleyReplicator.h/.cpp`
  - Sends `FVolleySpawnEvent`/`FImpactEvent` via FastArray; relevant settings on the actor and subsystem

- Visuals (client)
  - `UArrowVisualManagerSubsystem` — `AbilitySystem/ArrowVisualManagerSubsystem.h/.cpp`
  - `OnVolleySpawn`, `OnImpactEvent`, and helpers for Niagara/decals/sound

- Data
  - `UProjectileVolleyProfile` — `AbilitySystem/ProjectileVolleyProfile.h`

---

## How to extend

- Add new surface responses: extend `ImpactDustBySurface`, `ImpactDebrisBySurface`, `ImpactSoundBySurface`, `ImpactDecalBySurface` maps.
- More gameplay on hit: add new fields to `FVolleySpawnRequest` and consume in `OnProxyHit_ApplyGameplayAndReplicate` (server).
- Visual variety: use different `VisualProfileId` values for different arrow types; point them at different Niagara systems.
- Mass/Entities: if migrating to Mass for very large counts, keep server-authoritative collision and use this replication model for visuals.

---

## Changelog

- UE 5.5 compliance: `UTickableWorldSubsystem` tick; async trace uses `EAsyncTraceType::Single`; GAS uses `ExecuteGameplayCue` and `MakeOutgoingSpec` flows; Niagara parameter helpers updated.
