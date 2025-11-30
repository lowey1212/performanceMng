# DAI Gameplay Tags - Hard-coded Native Implementation

This document outlines the new hard-coded native gameplay tag system for the DAI project, replacing the INI-based configuration.

## Overview

All gameplay tags are now hard-coded as native tags organized by plugin categories, making them easier to manage and providing compile-time safety.

## Tag Organization by Plugin Category

### Core DAI Plugin (`DAI_GameplayTags.h/.cpp`)

**Attack System:**
- `Ability.Attack.*` - Attack abilities (Basic, Charged, Combo, Ranged, etc.)
- `State.Attack.*` - Attack states (Aiming, WindingUp, Charging, etc.)
- `Cooldown.Attack.*` - Attack cooldowns
- `Cue.Attack.*` - Attack audio/visual cues

**Defense System:**
- `Ability.Defense.*` - Defense abilities (Block, Parry, Shield, etc.)
- `State.Defense.*` - Defense states
- `Cue.Defense.*` - Defense cues

**Movement System:**
- `Ability.Movement.*` - Movement abilities (Glide, Grapple, Roll, Sprint, etc.)
- `State.Movement.*` - Movement states
- `Cooldown.*` - Movement cooldowns
- `Event.Movement.*` - Movement events

**Status Effects:**
- `Ability.Status.*` - Status effect abilities (Heal, DoT, Debuff, etc.)
- `Cue.Status.*` - Status effect cues

**Team System:**
- `Ability.Team.*` - Team abilities (AuraBuff, Carry, Link, Revive)
- `State.Team.*` - Team states
- `Cue.Team.*` - Team cues

**Utility System:**
- `Ability.Utility.*` - Utility abilities (Build, Hack, Interact, Tame, etc.)
- `State.Utility.*` - Utility states
- `Cue.Utility.*` - Utility cues

**Audio System (Foley):**
- `Foley.Event.*` - Audio events (Jump, Land, Run, Walk, etc.)

**Client System:**
- `Client.Ability.*` - Client-specific abilities
- `Client.Character.*` - Character equipment, types
- `Client.Environment.*` - Environment effects
- `Client.Inventory.*` - Inventory interactions

**Server System:**
- `Server.AI.*` - AI-related tags
- `Server.Resources.*` - Resource management tags

**GameplayCue System:**
- `GameplayCue.*` - Gameplay effect cues

### Weather Plugin (`DAIUltraSkyWeatherTags.h/.cpp`)

**Weather Conditions:**
- `Weather.Clear`, `Weather.Rain`, `Weather.Snow`, etc.

**Weather Abilities:**
- `Ability.Weather.Lightning`, `Ability.Weather.MeteorStorm`, etc.

**Weather Effects:**
- `Effect.Weather.LightningStrike`, `Effect.Weather.WindGust`, etc.

**Time System:**
- `Time.Dawn`, `Time.Morning`, `Time.Noon`, etc.

**Weather Events:**
- `Event.Weather.Changed`, `Event.Lightning.Struck`, etc.

### MagGrab Plugin (`DAI_MagGrabGameplayTags.h/.cpp`)

**MagGrab System:**
- `DAI.MagGrab.*` - Magnetic grabbing system tags

### Spawner Plugin (`SpawnerGameplayTags.h/.cpp`)

**Spawn System:**
- `DAI.Spawn.*` - Entity spawning system tags

## Benefits

1. **Easier Management**: No more editing INI files
2. **Plugin Organization**: Tags are organized by their respective plugin categories
3. **Compile-time Safety**: Native tags provide better error checking
4. **Better Performance**: Native tags are more efficient than INI-based tags
5. **Categorized Structure**: Weather tags are in weather category, abilities in ability categories, etc.

## Migration from INI

The system now uses `ImportTagsFromConfig=False` in DefaultGameplayTags.ini and initializes all tags natively during module startup.

## Usage

Access tags via their native constants:
```cpp
// Core abilities
TAG_Ability_Attack_Basic
TAG_State_Movement_Sprinting

// Weather system
TAG_Weather_Rain
TAG_Ability_Weather_Lightning

// MagGrab system
TAG_DAI_MagGrab_Grabbed
```

All plugin systems initialize their tags during module startup automatically.