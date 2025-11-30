# DAI Plugin System Documentation

Welcome to the comprehensive documentation for the DAI (Dynamic AI) plugin system for Unreal Engine 5.5.

## Overview

The DAI system is a modular plugin architecture designed to provide advanced AI, gameplay mechanics, and utility systems for Unreal Engine projects. The system consists of specialized plugins that can work independently or together to create sophisticated game experiences.

Note: Climbing is fully integrated into DAI_Navigation; there is no standalone DAI_Climb plugin. Refer to DAI_Navigation docs for any climb-related settings or commands.

## Plugin Categories

### Core System
- **[DAI](plugins/DAI.md)** - Main inventory and combat system

### AI & Navigation
- **[DAI_AI](plugins/DAI_AI.md)** - AI system with StateTree integration
- **[DAI_Navigation](plugins/DAI_Navigation.md)** - Advanced navigation system (previously DAI__Navigation)

### Gameplay Mechanics
- **[DAI_MagGrab](plugins/DAI_MagGrab.md)** - Magnetic grab system
- **[DAI_Map](plugins/DAI_Map.md)** - Map and minimap system
- **[DAI_Traps](plugins/DAI_Traps.md)** - Trap mechanics system
- **[DAI_SmartObject](plugins/DAI_SmartObject.md)** - Smart object integration

### Management Systems
- **[DAI_Faction](plugins/DAI_Faction.md)** - Faction management system
- **[DAI_QuestManager](plugins/DAI_QuestManager.md)** - Quest management system
- **[DAI_Spawner](plugins/DAI_Spawner.md)** - Entity spawning system
- **[DAI_Save](plugins/DAI_Save.md)** - Save and load system

### Technical Systems
- **[DAI_PerfMngr](plugins/DAI_PerfMngr.md)** - Performance management system
- **[DAI_LoadDirector](plugins/DAI_LoadDirector.md)** - Load management system
- **[DAI_Dismember](plugins/DAI_Dismember.md)** - Dismemberment system
- **[DAI_UltraSky](plugins/DAI_UltraSky.md)** - Sky and weather system
- **[DAI_Utility](plugins/DAI_Utility.md)** - Utility functions and helpers

### Online Services
- **[DAI_EOS](plugins/DAI_EOS.md)** - Epic Online Services integration

## Getting Started

1. **Installation**: All plugins are included in the DAI Example Project
2. **Configuration**: Each plugin has its own developer settings accessible through Project Settings
3. **Integration**: Plugins can be used independently; cross-plugin coordination is handled via direct service interfaces or local callbacks (DAI_Hub removed; soft-reference helper remains for optional discovery patterns)
4. **Blueprint Usage**: All plugins expose Blueprint-friendly functions and components

## Architecture

The DAI system follows a modular architecture where:
- Each plugin functions independently (no hub requirement)
- Plugins communicate through direct service interfaces
- All functionality is accessible via Blueprints

## Documentation Format

Each plugin documentation includes:
- **Overview**: Purpose and key features
- **Components**: Main classes and their roles
- **Blueprint Nodes**: Detailed function references
- **Properties**: Configurable settings and variables
- **Developer Settings**: Project Settings configuration
- **Usage Examples**: Practical implementation guides
- **Best Practices**: Recommended usage patterns

See also:
- [Console Command Index](Console_Command_Index.md) — complete list of runtime console commands across plugins

## UltraSky StateTree Reference
For environment-driven logic, see `docs/StateTree_UltraSky_Nodes.md`.

Maintenance pointers:
- Single log category definition lives in `DAIUltraSkyLog.cpp`.
- All UltraSky StateTree nodes are centralized; do not add parallel duplicate cpp files.

## Support

For questions, issues, or contributions, please refer to the individual plugin documentation or contact the development team.

---

_Last updated: October 6, 2025_  
_Compatible with: Unreal Engine 5.5_

---

## Runtime Health Automation

Two scripts provide automated startup validation:

1. `Build/Scripts/Scan-DAILog.ps1`
	- Scans a produced log for: Ensures, Fatal errors, Missing Gameplay Tags (and optionally Warnings)
	- Exit codes: 0 = clean, 1 = issues, 2+ = operational error (missing file, etc.)

2. `Build/Scripts/Invoke-HeadlessRunAndScan.ps1`
	- Launches the editor headless (`-NullRHI -Unattended -Execcmds=quit`) and pipes output to a timestamped log, then invokes the scanner.
	- Arguments:
	  - `-UnrealEditorPath <path>` (defaults to F:/UE_5_Versions/UE_5.5/...)
	  - `-ProjectFile <uproject>` (auto-resolves relative one by default)
	  - `-FailOnWarning` (optional strict mode)

### Example Usage

```powershell
# Quick scan of an existing log
powershell -ExecutionPolicy Bypass -File .\DAIExampleProject` 5.5\Build\Scripts\Scan-DAILog.ps1 -LogPath .\DAIExampleProject` 5.5\Saved\Logs\DAIExampleProject.log

# Full headless launch + scan
powershell -ExecutionPolicy Bypass -File .\DAIExampleProject` 5.5\Build\Scripts\Invoke-HeadlessRunAndScan.ps1

# Strict (warnings fail build)
powershell -ExecutionPolicy Bypass -File .\DAIExampleProject` 5.5\Build\Scripts\Invoke-HeadlessRunAndScan.ps1 -FailOnWarning
```

### CI Integration

The workflow `.github/workflows/runtime-log-scan.yml` demonstrates wiring the scanner in GitHub Actions. To perform a real engine startup in CI you must provision an Unreal build agent with the editor binary available and replace the placeholder step with the headless invocation script.

---

## Integrated Ability Examples (Migration Note)
---

## DAI_AI Console Commands

The following runtime console commands are available for the `DAI_AI` plugin (requires appropriate feature compile flags where noted):

| Command | Description |
|---------|-------------|
| `dai.ai.info` | Prints world and registered AI component counts (agents, comm, affect). |
| `dai.ai.perf.toggle` | Toggles AI performance budgeting instrumentation (enables/disables perf collection). |
| `dai.ai.audit.toggleverbose` | Toggles verbose audit output (affects JSON command detail and pruning logs). |
| `dai.ai.prune.movegoals` | Manually prunes stale entries in the global movement goal cache. |
| `dai.ai.audit.json` | Writes JSON snapshot to Saved/DAI_AI_Audit.json (includes sample move goals when verbose). |

### Automatic Move Goal Pruning

In addition to the manual prune command, a world subsystem (`UDAI_AIMoveGoalPrunerSubsystem`) automatically prunes invalid move goal entries every 10 seconds. Verbose audit mode logs each pruning event with counts removed.

### JSON Audit Output Fields

| Field | Meaning |
|-------|---------|
| `PerfEnabled` | Whether performance budgeting instrumentation is active. |
| `AuditVerbose` | Whether verbose auditing mode is enabled. |
| `Worlds` | Number of active game/PIE worlds scanned. |
| `Agents`, `Comm`, `Affect` | Counts of registered agent, communication, and affect components. |
| `MoveGoalCount` | Number of active entries in movement goal cache. |
| `MoveGoalsSample` | (Verbose) Up to 32 sampled actors and their current goal vectors. |

Future expansion may add LOD override statistics once a persistent override registry is introduced.

## DAI_Navigation Console Commands
Canonical navigation-scoped commands mirror AI naming (`dai.nav.*`).

| Command | Description | Notes |
|---------|-------------|-------|
| `DAI.Nav.Help` | Lists common navigation console commands. | Always available in this plugin. |
| `dai.nav.Info` | Prints navigation feature flags and wrapper counts. | Present when compiled with audit features. |
| `dai.nav.AuditDeprecated` | Legacy audit of deprecated navigation Blueprint functions (should be zero). | Requires `DAI_FEATURE_NAV_AUDIT=1`. |
| `dai.nav.DumpAuditJson <Path>` | Writes navigation audit JSON (wrappers & deprecated) to path. | Requires `DAI_FEATURE_NAV_AUDIT_JSON=1`. |
| `dai.nav.DumpPerf` | Logs navigation performance metrics (path build avg, active count, frame budget usage). | Requires perf feature flag. |
| `dai.nav.SetLOD <0-3>` | Sets visualization LOD (0 High .. 3 Hidden). | Runtime only. |
| `dai.nav.ToggleMutableVis` | Toggles Mutable visualization on/off. | Debug aid. |


The temporary `DAI_AbilityExamples` plugin has been fully merged into the core `DAI` plugin. All illustrative Gameplay Ability System archetypes (projectile, AOE, channel, aura, buff/debuff, crowd control, resource drain, clone summon, teleport, ultimate, time manipulation) now live under:

`Plugins/DAI/Source/DAI/Public|Private/AbilitySystem/Examples/`

Gameplay tags for these examples are declared natively in `AbilitySystem/AbilityTags.h/.cpp` (see the block labeled Integrated Example Ability Archetype Tags). Two generic AbilityTasks were also migrated:

- `UAbilityTask_DelayedImpact` – delayed single-shot execution (e.g., Meteor Strike)
- `UAbilityTask_PeriodicChannelTick` – interval ticking for channel/aura/drain styles

Legacy example tags like `Ability.Example.MeteorStrike` are still requested for backward compatibility if any assets reference them, but systems should pivot to the new structured native tags (`Ability.MeteorStrike.Impact`, `Ability.Channel.Tick`, etc.).

You may safely delete the old plugin directory (`Plugins/DAI_AbilityExamples`) after confirming it is removed from the `.uproject` (already done). Perform a full rebuild to clear stale binaries.

If any blueprint or data assets referenced classes from the removed plugin, reassign them to the corresponding classes inside the `Examples` folder.