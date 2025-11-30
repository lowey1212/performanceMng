# DAI_UltraSky Plugin Guide

## Overview
**DAI_UltraSky** is a comprehensive weather and atmospheric system with Gameplay Ability System (GAS) integration, providing dynamic time-of-day cycles, weather conditions, biome blending, and celestial effects.

## Architecture

### Core Components
- **ADAIUltraSkyActor** - Main weather actor managing all atmospheric systems
- **UDAIUltraSkyAttributeSet** - 37 replicated GAS attributes for weather state
- **UDAIUltraSkyBiomeData** - Reusable weather configuration data assets
- **ADAIUltraSkyBiomeVolume** - Spatial triggers for biome application

### Key Features
1. **Time-of-Day System**
   - Automatic or manual time progression
   - Physical sun positioning (latitude/longitude/date)
   - Sidereal time for star rotation

2. **Weather System**
   - Biome-based weather zones
   - Smooth blending between biomes
   - Dynamic precipitation, fog, clouds, wind

3. **GAS Integration**
   - Weather attributes exposed as gameplay attributes
   - Abilities can modify weather (TriggerWeather, TriggerLightning, MeteorStorm)
   - Network replicated with proper clamping

4. **Celestial Effects**
   - Moon phases with material parameters
   - Star dome with twinkle effects
   - Milky Way overlay support

5. **Performance Optimization**
   - Configurable tick intervals
   - Optional tick disabling
   - Multiple performance profiles (HighQuality, Balanced, LowCost)

## File Structure

### Public Headers (27 files)
```
DAI_UltraSky/Source/DAI_UltraSky/Public/
├── Core/
│   ├── DAIUltraSkyActor.h               # Main weather actor
│   ├── DAIUltraSkyAttributeSet.h        # GAS attribute set
│   ├── DAIUltraSkySettings.h            # Project settings
│   ├── DAIUltraSkyLog.h                 # Log categories
│   └── UltraSkyTypes.h                  # Shared enums
│
├── Data Assets/
│   ├── DAIUltraSkyBiomeData.h           # Biome configuration
│   ├── DAIUltraSkyClimatePreset.h       # Climate settings
│   ├── DAIUltraSkyWeatherPreset.h       # Weather presets
│   ├── DAIUltraSkyWeatherTuningData.h   # Tuning parameters
│   └── DAIUltraSkyWeatherLibrary.h      # Weather library asset
│
├── Abilities/
│   ├── GA_DAIUltraSky_TriggerWeather.h  # Weather change ability
│   ├── GA_DAIUltraSky_TriggerLightning.h # Lightning ability
│   ├── GA_DAIUltraSky_MeteorStorm.h     # Meteor storm ability
│   └── DAIUltraSkyWeatherAbilityManager.h # Ability manager component
│
├── Actors/
│   ├── DAIUltraSkyBiomeVolume.h         # Biome volume trigger
│   ├── DAIUltraSkyWeatherOverrideVolume.h # Weather override volume
│   ├── DAIUltraSkyLightningController.h # Lightning effect controller
│   ├── DAIUltraSkyTornado.h             # Tornado actor
│   ├── DAIUltraSkyRadialStorm.h         # Radial storm actor
│   └── DAIUltraSkyFootprintMask.h       # Footprint mask actor
│
├── Components/
│   ├── DAIUltraSkyFootprintApplierComponent.h # Footprint effects
│   └── DAIUltraSkyEnvironmentSoundComponent.h # Ambient sounds
│
├── Utilities/
│   ├── DAIUltraSkyFunctionLibrary.h     # Blueprint utilities
│   ├── DAIUltraSkyBlueprintLibrary.h    # Additional BP functions
│   ├── DAIUltraSkyMaterialLibrary.h     # Material utilities
│   └── DAIUltraSkyWeatherTags.h         # Gameplay tags
│
├── Interfaces/
│   └── DAIUltraSkyService.h             # Weather service interface
│
├── Services/
│   └── DAI_WeatherService.h             # BP weather interface
│
└── StateTree/
    ├── UltraSkyStateTreeNodes.h         # StateTree integration
    └── UltraSkyStateTreeLog.h           # StateTree logging
```

## Usage Examples

### Basic Setup
```cpp
// Place ADAIUltraSkyActor in level
// Configure basic settings:
ADAIUltraSkyActor* UltraSky = GetWorld()->SpawnActor<ADAIUltraSkyActor>();
UltraSky->bAutoRunDayNight = true;
UltraSky->DayLengthSeconds = 600.0f; // 10 minutes per day
UltraSky->TimeOfDay = 8.0f; // Start at 8 AM
```

### Blueprint Function Library
```cpp
// Get weather state from Blueprints without actor reference
float TimeOfDay = UDAIUltraSkyFunctionLibrary::GetTimeOfDayHours(WorldContext);
float CloudCoverage = UDAIUltraSkyFunctionLibrary::GetCloudCoverage(WorldContext);
float FogDensity = UDAIUltraSkyFunctionLibrary::GetFogDensity(WorldContext);
```

### Applying Biomes
```cpp
// Create biome volume in level
ADAIUltraSkyBiomeVolume* DesertBiome = SpawnActor<ADAIUltraSkyBiomeVolume>();
DesertBiome->Biome = LoadObject<UDAIUltraSkyBiomeData>(nullptr, TEXT("/Game/Weather/Biomes/DA_Desert"));
DesertBiome->Priority = 10;

// Or force biome change via code
UltraSky->ForceApplyBiome(DesertBiomeData, 5.0f); // 5 second blend
```

### Weather Abilities
```cpp
// Grant weather ability to ASC
UAbilitySystemComponent* ASC = UltraSky->GetAbilitySystemComponent();
ASC->GiveAbility(FGameplayAbilitySpec(UGA_DAIUltraSky_TriggerWeather::StaticClass()));

// Trigger weather change via gameplay event
FGameplayEventData EventData;
EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Weather.Storm"));
ASC->TriggerAbilityFromGameplayEvent(AbilityHandle, ActorInfo, EventData.EventTag, &EventData, *ASC);
```

### Accessing GAS Attributes
```cpp
// Read attributes
float Precipitation = UltraSky->GetAttrCloudCoverage();
float Temperature = UltraSky->GetAttrTemperatureC();
float WindSpeed = UltraSky->GetAttrWindSpeedKph();

// Modify attributes via gameplay effect
FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(RainEffect, 1.0f, Context);
ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
```

## Epic Best Practices Implemented

### GAS AttributeSet
✅ **PreAttributeChange Override** - Runtime clamping for all 37 attributes with circular wrapping  
✅ **PostGameplayEffectExecute Override** - Extensible callback for attribute changes  
✅ **Proper Replication** - DOREPLIFETIME_CONDITION_NOTIFY with REPNOTIFY_Always  
✅ **ATTRIBUTE_ACCESSORS Macro** - Correct getter/setter/initter generation  

### Actor Performance
✅ **Tick Interval Configuration** - Adjustable via TickInterval property  
✅ **Conditional Tick Disabling** - Optional tick control via bAllowTickDisable  
✅ **PrimaryActorTick.TickInterval** - Properly set in BeginPlay  

### Interface Design
✅ **Virtual Destructors** - Handled by GENERATED_BODY() in UE5  
✅ **C++ and Blueprint Interfaces** - Dual interface support (IDAIUltraSkyService, IDAI_WeatherService)  

## Configuration

### Project Settings (Edit -> Project Settings -> Game -> DAI UltraSky)
- **Default Performance Profile** - HighQuality/Balanced/LowCost
- **Replication Delta Thresholds** - Minimum change before replication
- **Global Random Seed** - Deterministic weather for testing
- **Default Weather Tuning Data** - Soft reference to tuning asset

### Performance Profiles
```cpp
EUltraSkyPerformanceProfile::HighQuality  // Full quality, every frame tick
EUltraSkyPerformanceProfile::Balanced     // Moderate quality, reduced tick
EUltraSkyPerformanceProfile::LowCost      // Minimal quality, sparse ticks
```

## Network Replication

All weather attributes replicate automatically via GAS:
- **Authority**: Server modifies attributes via gameplay effects
- **Clients**: Receive replicated attribute changes with REPNOTIFY_Always
- **Prediction**: Not enabled (weather is environment state, not player action)

## Integration with Other Systems

### StateTree Integration
- **FUltraSkySnapshotEvaluator** - Provides weather state to StateTree
- **FUltraSkySetTimeTask** - Change time-of-day from StateTree
- **FUltraSkyWeatherCondition** - Condition checks (IsPrecipitating, IsStorming, etc.)

### Material Integration
- **Material Parameter Collections** - Drive material params from weather
- **Footprint System** - Dynamic snow/water footprints
- **Wetness/Snow** - Surface material effects via attributes

## Debugging

### Console Commands
```
// Enable verbose logging
Log LogDAIUltraSky Verbose

// Check current weather state
UltraSky.DumpCloudMaterialStatus
UltraSky.PrintBindingStatus

// Force time of day
UltraSky.SetTimeOfDay 18.0
```

### Log Categories
- **LogDAIUltraSky** - Main plugin logging
- **LogUltraSkyStateTree** - StateTree-specific logs

## Known Limitations

1. **Single UltraSky per World** - Only one active weather actor supported
2. **No Multi-Level Support** - Weather state doesn't persist across level streaming
3. **Light Mixer Compatibility** - Requires manual binding when using Light Mixer workflow
4. **Physics-Based Weather** - No actual fluid simulation (visual only)

## Migration Notes

### From Previous Versions
- Deprecated shim files removed (UltraSkyWeatherLibrary.h, etc.)
- AbilityTask_PeriodicMeteor renamed to AbilityTask_PeriodicMeteorUltraSky
- UltraSkyTypes.h intentionally lacks DAI prefix (shared enum design)

## Dependencies

### Required Plugins
- GameplayAbilities (GAS)
- Niagara (weather effects)

### Optional Plugins
- StateTree (AI integration)
- Mutable (Not used, safe to disable)

## Performance Considerations

### Tick Optimization
```cpp
// For distant/background weather actors
UltraSky->TickInterval = 0.5f; // Update every 0.5 seconds instead of every frame

// For static weather (no time progression)
UltraSky->bAllowTickDisable = true;
UltraSky->SetTickEnabled(false);
```

### SkyLight Recapture
```cpp
// Reduce recapture frequency for performance
UltraSky->SkyLightRecaptureInterval = 10.0f; // Every 10 seconds (default 5)
```

## Future Enhancements

- Multi-level weather state persistence
- Weather prediction system
- More complex weather patterns (fronts, pressure systems)
- GPU-accelerated cloud simulation
- Audio occlusion based on weather
