# DAI Native Tags Test and Validation

This document provides test examples and validation for the new native gameplay tag system.

## Test Usage Examples

### Core DAI Tags Usage

```cpp
#include "AbilitySystem/DAI_GameplayTags.h"

void TestCoreAbilities()
{
    // Attack abilities
    FGameplayTag BasicAttack = TAG_Ability_Attack_Basic;
    FGameplayTag ChargedAttack = TAG_Ability_Attack_Charged;
    
    // Movement abilities  
    FGameplayTag Sprint = TAG_Ability_Movement_Sprint;
    FGameplayTag Roll = TAG_Ability_Movement_Roll;
    
    // Check if character has ability
    if (AbilityComponent->HasMatchingGameplayTag(TAG_State_Movement_Sprinting))
    {
        // Character is currently sprinting
    }
    
    // Apply cooldown
    AbilityComponent->AddLooseGameplayTag(TAG_Cooldown_Attack_Basic);
}

void TestTagCollections()
{
    TArray<FGameplayTag> CoreAbilityTags;
    FDAIGameplayTags::GetCoreAbilityTags(CoreAbilityTags);
    
    TArray<FGameplayTag> AudioTags;
    FDAIGameplayTags::GetAudioTags(AudioTags);
    
    UE_LOG(LogTemp, Log, TEXT("Found %d core ability tags"), CoreAbilityTags.Num());
}
```

### Weather Plugin Tags Usage

```cpp
#include "DAIUltraSkyWeatherTags.h"

void TestWeatherSystem()
{
    // Weather conditions
    FGameplayTag RainyWeather = TAG_Weather_Rain;
    FGameplayTag ClearWeather = TAG_Weather_Clear;
    
    // Weather abilities
    FGameplayTag LightningAbility = TAG_Ability_Weather_Lightning;
    FGameplayTag MeteorStorm = TAG_Ability_Weather_MeteorStorm;
    
    // Time of day
    FGameplayTag CurrentTime = TAG_Time_Morning;
    
    // Get all weather condition tags
    TArray<FGameplayTag> WeatherTags = FDAIUltraSkyWeatherTags::GetAllWeatherConditionTags();
    
    for (const FGameplayTag& WeatherTag : WeatherTags)
    {
        UE_LOG(LogTemp, Log, TEXT("Weather condition: %s"), *WeatherTag.ToString());
    }
}

void TestWeatherAbilities()
{
    TArray<FGameplayTag> WeatherAbilities = FDAIUltraSkyWeatherTags::GetAllWeatherAbilityTags();
    TArray<FGameplayTag> TimeOfDayTags = FDAIUltraSkyWeatherTags::GetAllTimeOfDayTags();
    
    UE_LOG(LogTemp, Log, TEXT("Found %d weather abilities"), WeatherAbilities.Num());
    UE_LOG(LogTemp, Log, TEXT("Found %d time of day tags"), TimeOfDayTags.Num());
}
```

### MagGrab Plugin Tags Usage

```cpp
#include "DAI_MagGrabGameplayTags.h"

void TestMagGrabSystem()
{
    // MagGrab states
    FGameplayTag GrabbedTag = TAG_DAI_MagGrab_Grabbed;
    FGameplayTag ReleasedTag = TAG_DAI_MagGrab_Released;
    FGameplayTag AttachedTag = TAG_DAI_MagGrab_Attached;
    
    // Check if object is currently grabbed
    if (AbilityComponent->HasMatchingGameplayTag(TAG_DAI_MagGrab_Grabbed))
    {
        // Object is magnetically grabbed
    }
}
```

### Spawner Plugin Tags Usage

```cpp
#include "SpawnerGameplayTags.h"

void TestSpawnerSystem()
{
    FGameplayTag SpawnRequest = TAG_DAI_Spawn_Request;
    FGameplayTag SpawnApproved = TAG_DAI_Spawn_Approved;
    FGameplayTag SpawnFailed = TAG_DAI_Spawn_Failed;
    
    // Request spawn
    AbilityComponent->AddLooseGameplayTag(TAG_DAI_Spawn_Request);
}
```

## Validation Checklist

### ✅ Native Tag System Validation

1. **Core Tags Available:**
   - [ ] Attack abilities (Basic, Charged, Combo, etc.)
   - [ ] Defense abilities (Block, Parry, Shield, etc.)
   - [ ] Movement abilities (Sprint, Roll, Slide, etc.)
   - [ ] Status effects (Heal, DoT, Buff, etc.)
   - [ ] Audio events (Foley system)
   - [ ] Client/Server system tags

2. **Weather Plugin Tags Available:**
   - [ ] Weather conditions (Clear, Rain, Snow, etc.)
   - [ ] Weather abilities (Lightning, MeteorStorm, etc.)
   - [ ] Time of day tags (Dawn, Noon, Night, etc.)
   - [ ] Weather events (Changed, Storm started/ended, etc.)

3. **Plugin Integration:**
   - [ ] MagGrab tags accessible
   - [ ] Spawner tags accessible
   - [ ] All plugins initialize tags during startup

4. **INI Independence:**
   - [ ] System works with `ImportTagsFromConfig=False`
   - [ ] No dependency on DefaultGameplayTags.ini
   - [ ] Native tags load before other systems need them

### Test Commands

To validate the system is working, you can run these in the Unreal Editor console:

```
// List all gameplay tags
GameplayTags.PrintGameplayTags

// Check if specific tags exist
GameplayTags.PrintMatchingGameplayTags Weather.Rain
GameplayTags.PrintMatchingGameplayTags Ability.Attack.Basic
GameplayTags.PrintMatchingGameplayTags DAI.MagGrab
```

## Tag Organization Verification

### By Category Structure:

**✅ Core Abilities:**
- Attack: `Ability.Attack.*`, `State.Attack.*`, `Cooldown.Attack.*`, `Cue.Attack.*`
- Defense: `Ability.Defense.*`, `State.Defense.*`, `Cue.Defense.*`
- Movement: `Ability.Movement.*`, `State.Movement.*`, `Event.Movement.*`

**✅ Weather System:**
- Conditions: `Weather.*`
- Abilities: `Ability.Weather.*`
- Effects: `Effect.Weather.*`
- Time: `Time.*`
- Events: `Event.Weather.*`, `Event.Time.*`, `Event.Lightning.*`, `Event.Storm.*`

**✅ Plugin Systems:**
- MagGrab: `DAI.MagGrab.*`
- Spawner: `DAI.Spawn.*`
- Audio: `Foley.Event.*`
- Client: `Client.*`
- Server: `Server.*`
- GameplayCues: `GameplayCue.*`

## Expected Benefits Verification

- [x] **Easier Management**: No INI editing required
- [x] **Plugin Category Organization**: Weather tags in weather plugin, etc.
- [x] **Compile-time Safety**: Native tags catch errors at compile time
- [x] **Better Performance**: Native tags are more efficient
- [x] **Consistent Structure**: All plugins use same native tag approach

## Troubleshooting

If tags are not found:
1. Check that module startup initializes tags (`FDAIGameplayTags::InitializeNativeTags()`)
2. Verify build dependencies include GameplayTags module
3. Check that native tag declarations match definitions
4. Ensure `ImportTagsFromConfig=False` in DefaultGameplayTags.ini

## Migration Status

- ✅ Core ability system tags converted to native
- ✅ Weather system tags converted to native  
- ✅ MagGrab plugin tags already native
- ✅ Spawner plugin tags already native
- 🔄 Client/Server tags converted to native (testing needed)
- 🔄 Audio/Foley tags converted to native (testing needed)
- 🔄 GameplayCue tags converted to native (testing needed)