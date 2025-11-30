# DAI Console Command Index

Centralized index of runtime console commands exposed by the DAI plugin suite. Use each plugin’s DAI.<Plugin>.Help for in-editor help. Commands are grouped by plugin/namespace.

Note: Angle brackets denote parameters. Optional parameters are shown in [brackets].

## Core Help Entrypoints
- DAI.AI.Help — Show AI help
- DAI.CoreContracts.Help — Show CoreContracts help
- DAI.Dismember.Help — Show Dismember help
- DAI.Faction.Help — Show Faction help
- DAI.LoadDirector.Help — Show LoadDirector help
- DAI.MagGrab.Help — Show MagGrab help
- DAI.Map.Help — Show Map help
- DAI.Nav.Help — Show Navigation help and subcommands
- DAI.Perf.Help — Show Performance Manager help
- DAI.Save.Help — Show Save help
- DAI.SmartObject.Help — Show SmartObject help
- DAI.Spawner.Help — Show Spawner help
- DAI.Traps.Help — Show Traps help
- DAI.UltraSky.Help — Show UltraSky help
- DAI.Quest.Help — Show QuestManager help

## AI (DAI_AI)
- dai.ai.info — Display AI runtime counts
- dai.ai.perf.toggle — Toggle AI performance budgeting on/off
- dai.ai.audit.toggleverbose — Toggle verbose audit JSON output
- dai.ai.prune.movegoals — Remove invalid actor entries from move goals cache

## Navigation (DAI_Navigation)
- dai.nav.Info — Feature flags and wrapper/deprecation counts
- dai.nav.DumpPerf — Dump navigation performance metrics
- dai.nav.SetLOD <0..3> — Set visualization LOD (0=High,1=Med,2=Low,3=Hidden)
- dai.nav.ToggleMutableVis — Toggle Mutable visualization
- dai.nav.AuditDeprecated — Audit deprecated functions (if DAI_FEATURE_NAV_AUDIT)
- dai.nav.DumpAuditJson <AbsolutePath.json> — Dump wrapper/deprecation audit JSON (if DAI_FEATURE_NAV_AUDIT_JSON)

Climb aliases and tools (integrated under Navigation):
- daiclimb.info — Aggregate climb metrics (legacy)
- daiclimb.reset.instability — Reset climb instability counters (legacy)
- daiclimb.audit.json <Path.json> — Write climb audit JSON (legacy)
- dai.nav.climb.info — Alias to daiclimb.info
- dai.nav.climb.CVarAliases — List mirrored climb CVars (old->new)
- dai.nav.climb.CVarStrict 1/0 — Toggle strict mode for legacy writes
- dai.nav.climb.RedirectStats — Show legacy redirect counters

## Map (DAI_Map)
- Map.DumpPOIs — List all active map POIs
- Map.Stats — Print map subsystem stats
- Map.FlushFog — Immediately flush buffered fog section reveal events
- Map.RevealRadius <RadiusMeters> — Reveal all fog sections within the given radius of the player

## Dismember (DAI_Dismember)
- DAI.Dismember.ListSevered — List all severed limbs in the current world
- DAI.Dismember.RestoreAll [ActorName] — Restore all severed limbs (optionally for a single actor)
- DAI.Dismember.Sever <ActorName> <LimbID> — Sever a limb on the actor
- DAI.Dismember.CombineToSingleMaterial <ActorName> [MaterialPath] [Priority] — Combine meshes via Mutable
- DAI.Dismember.MarkEquipmentChanged <ActorName> [Priority] — Schedule debounced combine
- DAI.Dismember.CombineStatus <ActorName> — Print combine status for the actor

## Faction (DAI_Faction)
- DAI.Faction.AreHostile <ActorA> <ActorB> — Check hostility
- DAI.Faction.AdjustRep <ActorName> <FactionTag> <Delta> — Adjust reputation
- DAI.Faction.ListFactions <ActorName> — List faction tags on an actor

## Save (DAI_Save)
Core Save.* commands:
- Save.Fragments.List — List registered save fragments and versions
- Save.Fragments.Dump — Dump in-memory fragment keys
- Save.Export <SlotName> <UserIndex> <DestZipPath> — Export slot to zip
- Save.Import <DestSlotName> <UserIndex> <SrcZipPath> — Import slot from zip
- Save.Test.Migrate <FragmentId> <FromVersion> <ToVersion> — Simulate fragment migration
- Save.Validate <SlotName> [UserIndex] — Validate save and fragment checksums
- Save.Auth.Print <SlotName> [UserIndex] — Print auth metadata
- Save.World.Capture [TagName|NONE] [FragmentId] — Capture world state to fragment
- Save.World.Restore [TagName|NONE] [Prune(0/1)] [FragmentId] — Restore world state

DAI.* alias mirrors:
- DAI.Save.Fragments.List — alias of Save.Fragments.List
- DAI.Save.Fragments.Dump — alias of Save.Fragments.Dump
- DAI.Save.Export — alias of Save.Export
- DAI.Save.Import — alias of Save.Import
- DAI.Save.Test.Migrate — alias of Save.Test.Migrate
- DAI.Save.Validate — alias of Save.Validate
- DAI.Save.Auth.Print — alias of Save.Auth.Print
- DAI.Save.World.Capture — alias of Save.World.Capture
- DAI.Save.World.Restore — alias of Save.World.Restore

## UltraSky (DAI_UltraSky)
- UltraSky.Status — Print UltraSky service status (time, biome, condition, snow, wind)
- UltraSky.ForceCondition <Name> — Force weather condition immediately
- UltraSky.ForceBiome <BiomeAssetName> — Force biome immediately (no blend)
- UltraSky.SetSnowThresholds <v1> <v2> ... — Set snow depth thresholds (0..1)
- UltraSky.PrintSnowThresholds — List configured snow depth thresholds
- UltraSky.DumpConfig — Dump key UltraSky configuration values
- UltraSky.DumpAttrs — Log current replicated UltraSky GAS attribute values (if available)

## Load Director (DAI_LoadDirector)
- DAI.LoadDirector.Help — Show LoadDirector help
- Exec (in subsystem class): quick test helpers may exist; see `LoadDirectorServiceSubsystem.h/cpp` for details

## Spawner (DAI_Spawner)
- DAI.Spawner.Help — Show Spawner help

## SmartObject (DAI_SmartObject)
- DAI.SmartObject.Help — Show SmartObject help

## Performance Manager (DAI_PerfMngr)
- DAI.Perf.Help — Show Performance Manager help

## Core Contracts (DAI_CoreContracts)
- DAI.CoreContracts.Help — Show CoreContracts help

## Quest Manager (DAI_QuestManager)
- DAI.Quest.Help — Show QuestManager help

## MagGrab (DAI_MagGrab)
- DAI.MagGrab.Help — Show MagGrab help

## Traps (DAI_Traps)
- DAI.Traps.Help — Show Traps help

---

Last updated: October 6, 2025
