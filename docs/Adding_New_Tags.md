# Adding New Gameplay Tags - Easy Guide

This guide shows how easy it is to add new gameplay tags with the new native system.

## Before (INI-based System)

To add new tags, you had to:

1. Edit `DefaultGameplayTags.ini` 
2. Find the right section
3. Add the tag with correct syntax
4. Hope you didn't make typos
5. No compile-time checking
6. No organization by plugin

```ini
; Had to manually edit INI file
+GameplayTagList=(Tag="Ability.Magic.Fireball",DevComment="Fireball spell")
+GameplayTagList=(Tag="Ability.Magic.IceSpike",DevComment="Ice spike spell") 
+GameplayTagList=(Tag="State.Magic.Casting",DevComment="Currently casting magic")
```

## After (Native System)

Now adding new tags is simple and organized by plugin category:

### 1. For Core DAI Abilities

Edit `DAI_GameplayTags.h`:
```cpp
// Add to appropriate category section
// Magic Abilities
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Ability_Magic_Fireball);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Ability_Magic_IceSpike);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Ability_Magic_Healing);

// Magic States  
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Magic_Casting);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Magic_Channeling);
```

Edit `DAI_GameplayTags.cpp`:
```cpp
// Add definitions
UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_Magic_Fireball, "Ability.Magic.Fireball");
UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_Magic_IceSpike, "Ability.Magic.IceSpike");
UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_Magic_Healing, "Ability.Magic.Healing");

UE_DEFINE_GAMEPLAY_TAG(TAG_State_Magic_Casting, "State.Magic.Casting");
UE_DEFINE_GAMEPLAY_TAG(TAG_State_Magic_Channeling, "State.Magic.Channeling");
```

### 2. For Weather Plugin

Edit `DAIUltraSkyWeatherTags.h`:
```cpp
// New weather conditions
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Weather_Sandstorm);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Weather_Hail);

// New weather abilities
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Ability_Weather_Tornado);
```

Edit `DAIUltraSkyWeatherTags.cpp`:
```cpp
UE_DEFINE_GAMEPLAY_TAG(TAG_Weather_Sandstorm, "Weather.Sandstorm");
UE_DEFINE_GAMEPLAY_TAG(TAG_Weather_Hail, "Weather.Hail");
UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_Weather_Tornado, "Ability.Weather.Tornado");
```

### 3. For New Plugin Categories

Create new plugin with its own tag file:

`DAI_CraftingGameplayTags.h`:
```cpp
#pragma once
#include "NativeGameplayTags.h"

// Crafting System Tags
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Ability_Crafting_Forge);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Ability_Crafting_Enchant);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Crafting_Working);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Cue_Crafting_Complete);
```

`DAI_CraftingGameplayTags.cpp`:
```cpp
#include "DAI_CraftingGameplayTags.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_Crafting_Forge, "Ability.Crafting.Forge");
UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_Crafting_Enchant, "Ability.Crafting.Enchant");
UE_DEFINE_GAMEPLAY_TAG(TAG_State_Crafting_Working, "State.Crafting.Working");
UE_DEFINE_GAMEPLAY_TAG(TAG_Cue_Crafting_Complete, "Cue.Crafting.Complete");
```

## Benefits of New System

✅ **Organized by Plugin Category**: All weather tags in weather plugin, all crafting tags in crafting plugin

✅ **Compile-time Safety**: Typos caught at compile time

✅ **Easy to Find**: Tags logically grouped by system

✅ **No INI Editing**: All tags in code where they belong

✅ **Better IntelliSense**: Auto-completion works properly

✅ **Refactoring Safe**: Renaming works across entire codebase

## Tag Naming Conventions

Follow these patterns for consistency:

### Core DAI Plugin Categories:
- **Abilities**: `TAG_Ability_[System]_[Action]`
  - `TAG_Ability_Attack_Basic`
  - `TAG_Ability_Magic_Fireball`
  - `TAG_Ability_Crafting_Forge`

- **States**: `TAG_State_[System]_[Condition]`
  - `TAG_State_Movement_Sprinting`
  - `TAG_State_Magic_Casting`
  - `TAG_State_Crafting_Working`

- **Cooldowns**: `TAG_Cooldown_[System]_[Action]`
  - `TAG_Cooldown_Attack_Basic`
  - `TAG_Cooldown_Magic_Fireball`

- **Cues**: `TAG_Cue_[System]_[Event]`
  - `TAG_Cue_Attack_Hit`
  - `TAG_Cue_Magic_Cast`

### Weather Plugin Categories:
- **Conditions**: `TAG_Weather_[Type]`
  - `TAG_Weather_Rain`
  - `TAG_Weather_Sandstorm`

- **Abilities**: `TAG_Ability_Weather_[Action]`
  - `TAG_Ability_Weather_Lightning`
  - `TAG_Ability_Weather_Tornado`

### Plugin-Specific Tags:
- **MagGrab**: `TAG_DAI_MagGrab_[State]`
- **Spawner**: `TAG_DAI_Spawn_[Action]`
- **Custom Plugin**: `TAG_[PluginName]_[Category]_[Action]`

## Quick Reference

To add tags to existing category:
1. Add declaration to `.h` file
2. Add definition to `.cpp` file  
3. Compile and use immediately

To create new category:
1. Create new tag files for plugin
2. Follow naming conventions
3. Initialize in plugin startup
4. Reference in your systems

**No more INI editing required!** 🎉