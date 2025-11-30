# DAI_UltraSky Plugin Documentation

## Overview

**DAI_UltraSky** is a lightweight, extensible dynamic sky and atmosphere system for Unreal Engine 5.5 that leverages UE5 built-in atmospheric rendering systems. The plugin provides comprehensive sky management, dynamic weather systems, time-of-day simulation, and seamless integration with Niagara effects and Gameplay Ability System for immersive environmental experiences.

### Key Features

### Replication & Performance Optimizations

UltraSky integrates tightly with the Gameplay Ability System (GAS) via a dedicated attribute set. To reduce network bandwidth while keeping visuals responsive, two complementary systems are used:

1. Replication Delta Thresholds
     Each replicated scalar attribute (TimeOfDay, CloudCoverage, CloudDensity, FogDensity, MoonPhase, MoonBaseIntensity, StarVisibility) only pushes an update when the value changes by at least a configurable minimum delta. These thresholds live in `UDAIUltraSkySettings` (Project Settings -> DAI -> UltraSky). Setting a threshold to 0 (or nearly 0) reverts to eager updates; increasing it coalesces small changes.

2. Attribute Batching
     When enabled, rapid successive changes across selected attributes are aggregated into a transient map and pushed on a timed flush interval instead of immediately. This cuts per-frame replication chatter for smoothly animated environmental parameters.

#### Settings Summary (UDAIUltraSkySettings)
Global Toggles:
- `bEnableAttributeBatching`: Master switch for batching system.
- `BatchedAttributeFlushInterval` (seconds, on actor): Cadence to auto-flush pending attributes (default 0.25s). Force flush manually any time (see Exec).

Per-Attribute Replication Min Deltas:
- `MinTimeOfDayRepDelta`
- `MinCloudCoverageRepDelta`
- `MinCloudDensityRepDelta`
- `MinFogDensityRepDelta`
- `MinMoonPhaseRepDelta`
- `MinMoonBaseIntensityRepDelta`
- `MinStarVisibilityRepDelta`

Dynamic Scaling Multipliers:
- `StormReplicationDeltaScale` (applies when a storm is active; scales the above deltas smaller)
- `GlobalEventReplicationDeltaScale` (applies while a global weather event gameplay tag is present; stacks by taking the minimum with storm scale)

Per-Attribute Batching Flags (all respect the global batching enable):
- `bBatchCloudCoverage`
- `bBatchCloudDensity`
- `bBatchFogDensity`
- `bBatchMoonPhase`
- `bBatchMoonBaseIntensity`
- `bBatchStarVisibility`

Only attributes with both (global enable && specific flag) set are deferred into the batch; others replicate immediately (still honoring their delta threshold).

#### Flush Mechanics
- Automatic: Occurs when `BatchedAttributeFlushInterval` elapses AND at least one pending entry exists.
- Manual Blueprint: Call `FlushBatchedAttributesImmediate()` on the actor.
- Exec Command: `UltraSkyFlushAttributes` (e.g., from in-editor console) to force a server-side flush now.

#### Debugging / Inspection
- Exec Command: `UltraSkyPrintPending` lists current pending (unflushed) attributes and their latest values.
- Logging: Add custom `UE_LOG(LogDAIUltraSky, Verbose, ...)` where needed during tuning.

#### Typical Tuning Workflow
1. Start with modest thresholds (e.g., CloudCoverage 0.01–0.02, FogDensity 0.0005–0.001, StarVisibility 0.01).
2. Enable batching for attributes that change smoothly every tick (cloud, fog, star visibility, moon intensity during transitions).
3. Observe replication with `Stat Net` or packet captures – increase thresholds if still too chatty.
4. Use `UltraSkyPrintPending` while animating weather to confirm coalescing.
5. Manually `UltraSkyFlushAttributes` when orchestrating cinematic beats that must sync instantly.

#### Edge Cases & Notes
- A forced flush (manual/exec) will immediately push all pending attributes even if their delta thresholds were just barely exceeded at enqueue time.
- Setting a threshold extremely low (≈0) while batching enabled still leverages batching; the change is just admitted to the pending map earlier.
- Pending values overwrite earlier ones per attribute key (last-wins before flush).
- If no Ability System Component is present / resolved, batching map is cleared safely with no replication.

#### Example Blueprint Usage
```blueprint
Event Tick:
    NewCoverage = FInterpTo(CurrentCoverage, TargetCoverage, DeltaSeconds, 0.2)
    UltraSkyActor->SetAttrCloudCoverage(NewCoverage)   // May batch depending on settings

Every 5 seconds (Timer):
    UltraSkyActor->FlushBatchedAttributesImmediate()   // Optional manual sync
```

#### Console Examples
```
UltraSkyPrintPending
UltraSkyFlushAttributes
UltraSkyPrintTimeBand
```

Keep replication lean: prefer raising thresholds slightly before disabling batching; batching reduces bursts while thresholds limit noise.

### Time Bands & Gameplay Tags
UltraSky segments the day into named time bands: Dawn, Morning, Noon, Afternoon, Dusk, Night. When a band transition occurs:
- `OnTimeBandChanged` delegate broadcasts (PreviousBand, NewBand)
- Gameplay tags are updated on the actor's ASC:
    - Removes any prior `Time.*` band tag
    - Adds `Event.Time.Changed` plus the new band tag (e.g. `Time.Dawn`)
You can query the current band via:
- `UDAIUltraSkyFunctionLibrary::GetCurrentTimeBand(WorldContext)` (FName)
- `UDAIUltraSkyFunctionLibrary::GetCurrentTimeBandTag(WorldContext)` (GameplayTag)
- Exec: `UltraSkyPrintTimeBand`

These tags enable ability / effect systems to react without manual Blueprint wiring.

### Dynamic Replication Scaling Details
During storms and global events, replication min deltas are automatically reduced to increase visual fidelity for rapidly changing atmospheric conditions. EffectiveMinDelta = BaseDelta * Scale, where Scale is the minimum of active context multipliers (storm, global event). Attributes affected: TimeOfDay, CloudCoverage, CloudDensity, FogDensity, StarVisibility, MoonPhase, MoonBaseIntensity.

### Replication Introspection & Counters
For live tuning you can inspect how aggressively attributes are replicating:

- Blueprint (or C++): `GetEffectiveReplicationDelta(AttributeName)` returns the currently computed min delta after contextual scaling (storm/global event). Valid names: `TimeOfDay`, `CloudCoverage`, `CloudDensity`, `FogDensity`, `StarVisibility`, `MoonPhase`, `MoonBaseIntensity`.
- Debug Counters (server-only, optionally exposed to editor via details panel when `bEnableReplicationCountDebug` in settings):
    - `RepCount_TimeOfDay`
    - `RepCount_CloudCoverage`
    - `RepCount_CloudDensity`
    - `RepCount_FogDensity`
    - `RepCount_StarVisibility`
    - `RepCount_MoonPhase`
    - `RepCount_MoonBaseIntensity`

Use these to compare different threshold/scaling configurations over a fixed gameplay interval (e.g. 5 real minutes) to quantify bandwidth impact.

Console helper: `UltraSkyDumpReplicationThresholds` prints each attribute's current effective threshold (post scaling) to log.

### Removed Legacy Shim Headers
Earlier versions provided unprefixed shim headers (e.g. `UltraSkyFunctionLibrary.h`, `UltraSkyWeatherLibrary.h`, `UltraSkyWeatherTuningData.h`) to satisfy strict include-order tooling after a mass rename. These shims have been fully removed; always include the prefixed headers directly:

```
#include "DAIUltraSkyFunctionLibrary.h"
#include "DAIUltraSkyWeatherLibrary.h"
#include "DAIUltraSkyWeatherTuningData.h"
```

If any external code still references the old names, update those includes accordingly; redirectors were intentionally not created.


## Architecture

The DAI_UltraSky system consists of:
- **Sky Manager**: Central coordination of sky and atmospheric systems
- **Time System**: Day/night cycle and seasonal progression
- **Weather System**: Dynamic weather pattern management
- **Atmospheric Renderer**: Integration with UE5 atmospheric rendering
- **Effect Integration**: Niagara and GAS system coordination

## Core Components

### DAIUltraSkyManager
*Primary actor managing sky and atmosphere systems*

**Type**: `Actor`  
**Interfaces**: `IDAISkyService`  
**File**: `DAIUltraSkyManager.h`

Central manager for all sky, weather, and atmospheric rendering operations.

### DAITimeOfDayComponent
    ADAIUltraSkyActor* Sky = GetWorld()->SpawnActor<ADAIUltraSkyActor>();

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `UltraSky|Time`  
**File**: `DAITimeOfDayComponent.h`

Manages time of day progression, sun/moon positioning, and seasonal variations.

### DAIWeatherComponent
*Component managing dynamic weather systems*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `UltraSky|Weather`  
**File**: `DAIWeatherComponent.h`

Handles weather pattern changes, precipitation, wind, and atmospheric conditions.

### DAIAtmosphericRenderingComponent
*Component interfacing with UE5 atmospheric systems*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `UltraSky|Atmosphere`  
**File**: `DAIAtmosphericRenderingComponent.h`

Manages atmospheric scattering, fog, and volumetric rendering integration.

### DAISkyEffectsComponent
*Component coordinating Niagara weather effects*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `UltraSky|Effects`  
**File**: `DAISkyEffectsComponent.h`

Handles Niagara-based weather effects, lightning, aurora, and atmospheric particles.

## Blueprint Functions

### Time Management

#### SetTimeOfDay
**Type**: `BlueprintCallable`  
**Category**: `UltraSky|Time`  
**Purpose**: Set current time of day

**Parameters**:
- `Hour` (float): Hour of day (0-24)
- `bSmoothTransition` (bool): Whether to smoothly transition to new time
- `TransitionDuration` (float): Duration of transition in seconds

```cpp
void SetTimeOfDay(float Hour, bool bSmoothTransition = true, float TransitionDuration = 5.0f);
```

**Usage**: Set specific times for scripted events or level initialization.

#### GetTimeOfDay
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `UltraSky|Time`  
**Returns**: `float`  
**Purpose**: Get current time of day in hours

```cpp
float GetTimeOfDay() const;
```

**Usage**: Query current time for gameplay logic or UI display.

#### SetTimeSpeed
**Type**: `BlueprintCallable`  
**Category**: `UltraSky|Time`  
**Purpose**: Set speed of time progression

**Parameters**:
- `TimeMultiplier` (float): Speed multiplier for time progression (1.0 = real time)

```cpp
void SetTimeSpeed(float TimeMultiplier);
```

**Usage**: Accelerate or slow time progression for gameplay or cinematic purposes.

#### PauseTime
**Type**: `BlueprintCallable`  
**Category**: `UltraSky|Time`  
**Purpose**: Pause or resume time progression

**Parameters**:
- `bPause` (bool): Whether to pause time progression

```cpp
void PauseTime(bool bPause);
```

**Usage**: Freeze time for cutscenes, menus, or special gameplay mechanics.

### Weather Control

#### SetWeatherType
**Type**: `BlueprintCallable`  
**Category**: `UltraSky|Weather`  
**Purpose**: Change current weather pattern

**Parameters**:
- `WeatherType` (EDAIWeatherType): Type of weather to activate
- `Intensity` (float): Intensity of weather effect (0-1)
- `TransitionTime` (float): Time to transition to new weather

```cpp
void SetWeatherType(EDAIWeatherType WeatherType, float Intensity = 1.0f, float TransitionTime = 10.0f);
```

**Usage**: Trigger specific weather for atmosphere, gameplay, or story events.

#### GetCurrentWeather
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `UltraSky|Weather`  
**Returns**: `FDAIWeatherInfo`  
**Purpose**: Get current weather conditions

```cpp
FDAIWeatherInfo GetCurrentWeather() const;
```

**Usage**: Query weather for gameplay mechanics, AI behavior, or UI display.

#### TriggerLightning
**Type**: `BlueprintCallable`  
**Category**: `UltraSky|Weather`  
**Purpose**: Manually trigger lightning effect

**Parameters**:
- `StrikeLocation` (FVector): Location for lightning strike (optional)
- `Intensity` (float): Intensity of lightning effect

```cpp
void TriggerLightning(const FVector& StrikeLocation = FVector::ZeroVector, float Intensity = 1.0f);
```

**Usage**: Create dramatic lightning effects for events or abilities.

#### SetWindParameters
**Type**: `BlueprintCallable`  
**Category**: `UltraSky|Weather`  
**Purpose**: Configure wind effects

**Parameters**:
- `WindDirection` (FVector): Direction of wind
- `WindStrength` (float): Strength of wind effects
- `WindVariation` (float): Random variation in wind

```cpp
void SetWindParameters(const FVector& WindDirection, float WindStrength, float WindVariation = 0.3f);
```

**Usage**: Control wind for weather effects, foliage animation, and audio.

### Atmospheric Control

#### SetAtmosphericParameters
**Type**: `BlueprintCallable`  
**Category**: `UltraSky|Atmosphere`  
**Purpose**: Configure atmospheric rendering parameters

**Parameters**:
- `AtmosphereParams` (FDAIAtmosphericParameters): Atmospheric configuration

```cpp
void SetAtmosphericParameters(const FDAIAtmosphericParameters& AtmosphereParams);
```

**Usage**: Customize atmospheric appearance for different environments or moods.

#### SetSunIntensity
**Type**: `BlueprintCallable`  
**Category**: `UltraSky|Atmosphere`  
**Purpose**: Set sun light intensity

**Parameters**:
- `Intensity` (float): Sun light intensity multiplier
- `bAffectAtmosphere` (bool): Whether to affect atmospheric scattering

```cpp
void SetSunIntensity(float Intensity, bool bAffectAtmosphere = true);
```

**Usage**: Adjust lighting for different times of day or weather conditions.

#### SetFogDensity
**Type**: `BlueprintCallable`  
**Category**: `UltraSky|Atmosphere`  
**Purpose**: Control atmospheric fog density

**Parameters**:
- `FogDensity` (float): Density of atmospheric fog (0-1)
- `FogHeight` (float): Height distribution of fog

```cpp
void SetFogDensity(float FogDensity, float FogHeight = 1000.0f);
```

**Usage**: Create fog effects for weather, mood, or visibility gameplay.

### Sky Appearance

#### SetSkyboxMaterial
**Type**: `BlueprintCallable`  
**Category**: `UltraSky|Appearance`  
**Purpose**: Set custom skybox material

**Parameters**:
- `SkyboxMaterial` (UMaterialInterface): Material to use for skybox
- `BlendTime` (float): Time to blend to new material

```cpp
void SetSkyboxMaterial(UMaterialInterface* SkyboxMaterial, float BlendTime = 2.0f);
```

**Usage**: Switch between different sky appearances for various environments.

#### SetStarVisibility
**Type**: `BlueprintCallable`  
**Category**: `UltraSky|Appearance`  
**Purpose**: Control visibility of stars and celestial objects

**Parameters**:
- `StarVisibility` (float): Visibility of stars (0-1)
- `bAffectMoon` (bool): Whether to affect moon visibility

```cpp
void SetStarVisibility(float StarVisibility, bool bAffectMoon = false);
```

**Usage**: Adjust night sky appearance based on atmospheric conditions.

#### SetHorizonColor
**Type**: `BlueprintCallable`  
**Category**: `UltraSky|Appearance`  
**Purpose**: Set horizon color tint

**Parameters**:
- `HorizonColor` (FLinearColor): Color tint for horizon
- `BlendFactor` (float): Strength of color tint

```cpp
void SetHorizonColor(const FLinearColor& HorizonColor, float BlendFactor = 0.5f);
```

**Usage**: Create atmospheric color effects for different environments.

## Blueprint Data Types

### EDAIWeatherType (Weather Type)
**Type**: `BlueprintType Enum`  
**Purpose**: Types of weather patterns

**Values**:
- `Clear`: Clear skies with no precipitation
- `PartlyCloudy`: Scattered clouds with good visibility
- `Overcast`: Heavy cloud cover blocking sun
- `Rain`: Light to moderate rainfall
- `HeavyRain`: Intense rainfall with reduced visibility
- `Thunderstorm`: Storm with lightning and heavy rain
- `Snow`: Light to moderate snowfall
- `Blizzard`: Heavy snow with strong winds
- `Fog`: Heavy fog with low visibility
- `Sandstorm`: Desert sandstorm conditions

### EDAITimeOfDay (Time of Day)
**Type**: `BlueprintType Enum`  
**Purpose**: Broad time categories for gameplay

**Values**:
- `Dawn`: Early morning hours (5-7 AM)
- `Morning`: Morning hours (7-11 AM)
- `Noon`: Midday hours (11 AM-1 PM)
- `Afternoon`: Afternoon hours (1-5 PM)
- `Dusk`: Evening hours (5-7 PM)
- `Night`: Night hours (7 PM-5 AM)

### FDAIWeatherInfo (Weather Information)
**Type**: `BlueprintType Struct`  
**Purpose**: Complete weather state information

**Properties**:
- `WeatherType` (EDAIWeatherType): Current weather pattern
- `Intensity` (float): Intensity of weather effects (0-1)
- `Temperature` (float): Environmental temperature
- `Humidity` (float): Atmospheric humidity level
- `WindDirection` (FVector): Current wind direction
- `WindSpeed` (float): Wind speed in units per second
- `Visibility` (float): Atmospheric visibility distance
- `CloudCover` (float): Percentage of sky covered by clouds

### FDAIAtmosphericParameters (Atmospheric Parameters)
**Type**: `BlueprintType Struct`  
**Purpose**: Configuration for atmospheric rendering

**Properties**:
- `RayleighScatteringScale` (float): Scale for Rayleigh scattering
- `MieScatteringScale` (float): Scale for Mie scattering
- `HazeHeight` (float): Height of atmospheric haze layer
- `OzoneAbsorption` (float): Ozone absorption factor
- `SunDiscScale` (float): Size scale of sun disc
- `AtmosphereHeight` (float): Height of atmosphere in kilometers
- `PlanetRadius` (float): Radius of planet in kilometers

### FDAISolarParameters (Solar Parameters)
**Type**: `BlueprintType Struct`  
**Purpose**: Sun and moon positioning configuration

**Properties**:
- `Latitude` (float): Geographic latitude for solar calculations
- `Longitude` (float): Geographic longitude
- `TimeZone` (float): Time zone offset from UTC
- `DayOfYear` (int32): Current day of year (1-365)
- `bUseRealisticSolarPath` (bool): Whether to use realistic solar calculations
- `SolarElevationOverride` (float): Manual override for sun elevation
- `SolarAzimuthOverride` (float): Manual override for sun azimuth

### FDAIWeatherTransition (Weather Transition)
**Type**: `BlueprintType Struct`  
**Purpose**: Configuration for weather pattern transitions

**Properties**:
- `FromWeather` (EDAIWeatherType): Starting weather pattern
- `ToWeather` (EDAIWeatherType): Target weather pattern
- `TransitionDuration` (float): Time to complete transition
- `TransitionCurve` (UCurveFloat): Curve controlling transition timing
- `bTriggerEffects` (bool): Whether to trigger transition effects
- `IntermediateWeather` (EDAIWeatherType): Optional intermediate weather state

### FDAISkyPreset (Sky Preset)
**Type**: `BlueprintType Struct`  
**Purpose**: Complete sky configuration preset

**Properties**:
- `PresetName` (FString): Name identifier for this preset
- `TimeOfDay` (float): Associated time of day
- `WeatherInfo` (FDAIWeatherInfo): Weather configuration
- `AtmosphericParams` (FDAIAtmosphericParameters): Atmospheric settings
- `SkyboxMaterial` (UMaterialInterface): Optional custom skybox material
- `PostProcessSettings` (FPostProcessSettings): Associated post-process settings

## Component Properties

### DAITimeOfDayComponent Properties

#### Time Configuration
**Property**: `CurrentTimeOfDay`  
**Type**: `float`  
**Category**: `Time`  
**Blueprint Access**: `Read/Write`  
**Replication**: `Yes`  
**Default**: `12.0`  
**Purpose**: Current time of day in hours (0-24)

**Property**: `TimeSpeed`  
**Type**: `float`  
**Category**: `Time`  
**Blueprint Access**: `Read/Write`  
**Default**: `1.0`  
**Purpose**: Speed multiplier for time progression

**Property**: `bTimeProgression`  
**Type**: `bool`  
**Category**: `Time`  
**Blueprint Access**: `Read/Write`  
**Default**: `true`  
**Purpose**: Whether time automatically progresses

#### Solar Settings
**Property**: `SolarParameters`  
**Type**: `FDAISolarParameters`  
**Category**: `Solar`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Configuration for sun and moon positioning

**Property**: `bUseRealisticSolarPath`  
**Type**: `bool`  
**Category**: `Solar`  
**Blueprint Access**: `Read/Write`  
**Default**: `true`  
**Purpose**: Whether to use realistic solar position calculations

### DAIWeatherComponent Properties

#### Weather Settings
**Property**: `CurrentWeather`  
**Type**: `FDAIWeatherInfo`  
**Category**: `Weather`  
**Blueprint Access**: `Read Only`  
**Replication**: `Yes`  
**Purpose**: Current weather state information

**Property**: `bAutoWeatherProgression`  
**Type**: `bool`  
**Category**: `Weather`  
**Blueprint Access**: `Read/Write`  
**Default**: `false`  
**Purpose**: Whether weather automatically changes over time

**Property**: `WeatherChangeInterval`  
**Type**: `float`  
**Category**: `Weather`  
**Blueprint Access**: `Read/Write`  
**Default**: `1800.0`  
**Purpose**: Time between automatic weather changes (seconds)

#### Wind Configuration
**Property**: `WindDirection`  
**Type**: `FVector`  
**Category**: `Wind`  
**Blueprint Access**: `Read/Write`  
**Default**: `(1, 0, 0)`  
**Purpose**: Current wind direction vector

**Property**: `WindStrength`  
**Type**: `float`  
**Category**: `Wind`  
**Blueprint Access**: `Read/Write`  
**Default**: `100.0`  
**Purpose**: Wind force strength

### DAIAtmosphericRenderingComponent Properties

#### Atmosphere Settings
**Property**: `AtmosphericParameters`  
**Type**: `FDAIAtmosphericParameters`  
**Category**: `Atmosphere`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Current atmospheric rendering configuration

**Property**: `bUseVolumetricFog`  
**Type**: `bool`  
**Category**: `Atmosphere`  
**Blueprint Access**: `Read/Write`  
**Default**: `true`  
**Purpose**: Whether to enable volumetric fog rendering

#### Lighting Integration
**Property**: `SunLightActor`  
**Type**: `ADirectionalLight*`  
**Category**: `Lighting`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Directional light representing the sun

**Property**: `MoonLightActor`  
**Type**: `ADirectionalLight*`  
**Category**: `Lighting`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Directional light representing the moon

## Events and Delegates

### OnTimeOfDayChanged
**Type**: `Dynamic Multicast Delegate`  
**Category**: `UltraSky|Time`  
**Purpose**: Fired when time of day changes significantly

**Parameters**:
- `NewTimeOfDay` (float): New time in hours
- `TimeCategory` (EDAITimeOfDay): Broad time category

**Usage**: Update lighting, spawn systems, or trigger time-based events.

### OnWeatherChanged
**Type**: `Dynamic Multicast Delegate`  
**Category**: `UltraSky|Weather`  
**Purpose**: Fired when weather pattern changes

**Parameters**:
- `OldWeather` (EDAIWeatherType): Previous weather type
- `NewWeather` (EDAIWeatherType): New weather type
- `TransitionDuration` (float): Time to complete transition

**Usage**: Trigger weather-related gameplay effects or AI behavior changes.

### OnSunrise
**Type**: `Dynamic Multicast Delegate`  
**Category**: `UltraSky|Time`  
**Purpose**: Fired at sunrise each day

**Parameters**:
- `SunriseTime` (float): Exact time of sunrise

**Usage**: Trigger daily events, creature behaviors, or environmental changes.

### OnSunset
**Type**: `Dynamic Multicast Delegate`  
**Category**: `UltraSky|Time`  
**Purpose**: Fired at sunset each day

**Parameters**:
- `SunsetTime` (float): Exact time of sunset

**Usage**: Activate night behaviors, lighting changes, or nocturnal events.

### OnLightningStrike
**Type**: `Dynamic Multicast Delegate`  
**Category**: `UltraSky|Weather`  
**Purpose**: Fired when lightning strikes

**Parameters**:
- `StrikeLocation` (FVector): Location of lightning strike
- `Intensity` (float): Intensity of the strike

**Usage**: Trigger audio, visual effects, or lightning-related gameplay.

## Developer Settings

Access via **Project Settings → Game → DAI UltraSky**

### General Settings

#### Sky System
**Property**: `bEnableSkySystem`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to enable the UltraSky system

**Property**: `UpdateFrequency`  
**Type**: `float`  
**Default**: `0.1`  
**Range**: `0.01-1.0`  
**Purpose**: Seconds between sky system updates

**Property**: `bAutoCreateSkyManager`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to automatically create sky manager in levels

### Time Settings

#### Time Progression
**Property**: `DefaultTimeSpeed`  
**Type**: `float`  
**Default**: `1.0`  
**Range**: `0.0-100.0`  
**Purpose**: Default speed multiplier for time progression

**Property**: `DayDurationMinutes`  
**Type**: `float`  
**Default**: `24.0`  
**Range**: `1.0-1440.0`  
**Purpose**: Real-time minutes for one game day

#### Solar Configuration
**Property**: `DefaultLatitude`  
**Type**: `float`  
**Default**: `40.0`  
**Range**: `-90.0-90.0`  
**Purpose**: Default latitude for solar calculations

**Property**: `DefaultLongitude`  
**Type**: `float`  
**Default**: `-74.0`  
**Range**: `-180.0-180.0`  
**Purpose**: Default longitude for solar calculations

### Weather Settings

#### Weather System
**Property**: `bEnableWeatherSystem`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to enable dynamic weather

**Property**: `bReplicateWeather`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to replicate weather in multiplayer

#### Weather Transitions
**Property**: `DefaultWeatherTransitionTime`  
**Type**: `float`  
**Default**: `30.0`  
**Range**: `1.0-300.0`  
**Purpose**: Default time for weather transitions

**Property**: `WeatherRandomization`  
**Type**: `float`  
**Default**: `0.3`  
**Range**: `0.0-1.0`  
**Purpose**: Amount of randomization in weather patterns

### Performance Settings

#### Optimization
**Property**: `bUseLODSystem`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to use LOD for sky effects

**Property**: `MaxEffectDistance`  
**Type**: `float`  
**Default**: `10000.0`  
**Range**: `1000.0-50000.0`  
**Purpose**: Maximum distance for weather effects

#### Quality Settings
**Property**: `AtmosphericQuality`  
**Type**: `EDAIAtmosphericQuality`  
**Default**: `High`  
**Purpose**: Quality level for atmospheric rendering

**Property**: `WeatherEffectQuality`  
**Type**: `EDAIEffectQuality`  
**Default**: `High`  
**Purpose**: Quality level for weather effects

### Integration Settings

#### Niagara Integration
**Property**: `bEnableNiagaraWeather`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to use Niagara for weather effects

**Property**: `MaxConcurrentWeatherEffects`  
**Type**: `int32`  
**Default**: `10`  
**Range**: `1-50`  
**Purpose**: Maximum simultaneous weather effects

#### GAS Integration
**Property**: `bEnableWeatherAbilities`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to enable weather-based abilities

**Property**: `WeatherEffectTags`  
**Type**: `FGameplayTagContainer`  
**Purpose**: Tags for weather-related gameplay effects

### Debug Settings

#### Visualization
**Property**: `bDrawSkyDebug`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to display sky system debug information

**Property**: `bShowSolarPath`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to visualize sun/moon paths

#### Logging
**Property**: `bLogWeatherChanges`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to log weather transition events

**Property**: `bLogTimeProgression`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to log time progression events

## Usage Examples

### Basic Sky Setup
```blueprint
// Initialize UltraSky system
void InitializeUltraSky()
{
    // Spawn sky manager
    ADAIUltraSkyManager* SkyManager = GetWorld()->SpawnActor<ADAIUltraSkyManager>();
    
    // Configure time of day
    UDAITimeOfDayComponent* TimeComp = SkyManager->FindComponentByClass<UDAITimeOfDayComponent>();
    if (TimeComp)
    {
        TimeComp->CurrentTimeOfDay = 8.0f; // 8 AM start
        TimeComp->TimeSpeed = 60.0f; // 1 real minute = 1 game hour
        
        // Set geographic location
        FDAISolarParameters SolarParams;
        SolarParams.Latitude = 37.7749f; // San Francisco
        SolarParams.Longitude = -122.4194f;
        SolarParams.TimeZone = -8.0f; // PST
        SolarParams.DayOfYear = 180; // Summer
        TimeComp->SolarParameters = SolarParams;
    }
    
    // Set initial weather
    UDAIWeatherComponent* WeatherComp = SkyManager->FindComponentByClass<UDAIWeatherComponent>();
    if (WeatherComp)
    {
        SkyManager->SetWeatherType(EDAIWeatherType::Clear, 1.0f, 5.0f);
    }
}
```

### Dynamic Weather System
```blueprint
// Create dynamic weather progression
void SetupDynamicWeather()
{
    // Enable automatic weather changes
    WeatherComponent->bAutoWeatherProgression = true;
    WeatherComponent->WeatherChangeInterval = 900.0f; // 15 minutes
    
    // Bind to weather change events
    SkyManager->OnWeatherChanged.AddDynamic(this, &AMyGameMode::OnWeatherTransition);
    
    // Create weather pattern sequence
    TArray<EDAIWeatherType> WeatherSequence = {
        EDAIWeatherType::Clear,
        EDAIWeatherType::PartlyCloudy,
        EDAIWeatherType::Overcast,
        EDAIWeatherType::Rain,
        EDAIWeatherType::Clear
    };
    
    // Schedule weather changes
    ScheduleWeatherSequence(WeatherSequence);
}

UFUNCTION()
void OnWeatherTransition(EDAIWeatherType OldWeather, EDAIWeatherType NewWeather, float TransitionDuration)
{
    // Handle weather-specific effects
    switch (NewWeather)
    {
        case EDAIWeatherType::Rain:
            EnableRainEffects();
            ModifyNPCBehaviorForRain();
            break;
            
        case EDAIWeatherType::Thunderstorm:
            StartThunderstormEffects();
            TriggerIndoorSeeking();
            break;
            
        case EDAIWeatherType::Clear:
            DisableWeatherEffects();
            RestoreNormalBehavior();
            break;
    }
    
    // Update post-process effects
    UpdatePostProcessForWeather(NewWeather);
}

// Trigger dramatic lightning
void CreateLightningStorm()
{
    // Set storm weather
    SkyManager->SetWeatherType(EDAIWeatherType::Thunderstorm, 1.0f, 10.0f);
    
    // Schedule multiple lightning strikes
    GetWorld()->GetTimerManager().SetTimer(
        LightningTimer,
        FTimerDelegate::CreateUObject(this, &AMyGameMode::TriggerRandomLightning),
        FMath::RandRange(3.0f, 8.0f),
        true
    );
}

void TriggerRandomLightning()
{
    // Find random location for lightning
    FVector PlayerLocation = GetPlayerLocation();
    FVector LightningLocation = PlayerLocation + FVector(
        FMath::RandRange(-2000.0f, 2000.0f),
        FMath::RandRange(-2000.0f, 2000.0f),
        FMath::RandRange(500.0f, 1500.0f)
    );
    
    // Trigger lightning with effects
    SkyManager->TriggerLightning(LightningLocation, FMath::RandRange(0.7f, 1.0f));
    
    // Add gameplay effects
    ApplyLightningGameplayEffects(LightningLocation);
}
```

### Time-Based Gameplay
```blueprint
// Time-dependent NPC and world behavior
void HandleTimeBasedEvents()
{
    float CurrentTime = SkyManager->GetTimeOfDay();
    EDAITimeOfDay TimeCategory = GetTimeCategory(CurrentTime);
    
    switch (TimeCategory)
    {
        case EDAITimeOfDay::Dawn:
            HandleDawnEvents();
            break;
            
        case EDAITimeOfDay::Noon:
            HandleNoonEvents();
            break;
            
        case EDAITimeOfDay::Dusk:
            HandleDuskEvents();
            break;
            
        case EDAITimeOfDay::Night:
            HandleNightEvents();
            break;
    }
}

void HandleDawnEvents()
{
    // NPCs wake up and start daily routines
    for (ANPC* NPC : AllNPCs)
    {
        NPC->StartDailyRoutine();
    }
    
    // Monsters retreat to dark places
    for (AMonster* Monster : NocturnalMonsters)
    {
        Monster->SeekShelter();
    }
    
    // Shops open
    for (AShop* Shop : AllShops)
    {
        Shop->OpenForBusiness();
    }
}

void HandleNightEvents()
{
    // Street lights turn on
    for (AStreetLight* Light : StreetLights)
    {
        Light->TurnOn();
    }
    
    // Nocturnal creatures become active
    for (AMonster* Monster : NocturnalMonsters)
    {
        Monster->BecomeActive();
    }
    
    // NPCs go to sleep
    for (ANPC* NPC : AllNPCs)
    {
        NPC->GoToSleep();
    }
}

// Bind to time events
void BeginPlay()
{
    Super::BeginPlay();
    
    SkyManager->OnSunrise.AddDynamic(this, &AMyGameMode::OnDayStart);
    SkyManager->OnSunset.AddDynamic(this, &AMyGameMode::OnNightStart);
    SkyManager->OnTimeOfDayChanged.AddDynamic(this, &AMyGameMode::OnTimeChanged);
}

UFUNCTION()
void OnDayStart(float SunriseTime)
{
    // Daily reset events
    ResetDailyQuests();
    RefreshShopInventories();
    SpawnDaytimeCreatures();
}

UFUNCTION()
void OnNightStart(float SunsetTime)
{
    // Night-specific events
    SpawnNocturnalCreatures();
    EnableNightVision();
    ActivateNightQuests();
}
```

### GAS Weather Integration
```blueprint
// Weather-based ability system
UCLASS()
class MYGAME_API UWeatherAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weather")
    EDAIWeatherType RequiredWeather;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weather")
    float WeatherIntensityThreshold = 0.5f;

protected:
    virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
                                   const FGameplayAbilityActivationInfo ActivationInfo, FGameplayEventData* OptionalPayload) const override
    {
        if (!Super::CanActivateAbility(Handle, ActorInfo, ActivationInfo, OptionalPayload))
            return false;
        
        // Check weather conditions
    ADAIUltraSkyActor* Sky = GetUltraSkyActor(ActorInfo->AvatarActor.Get());
        if (SkyManager)
        {
            FDAIWeatherInfo CurrentWeather = SkyManager->GetCurrentWeather();
            
            return CurrentWeather.WeatherType == RequiredWeather && 
                   CurrentWeather.Intensity >= WeatherIntensityThreshold;
        }
        
        return false;
    }
};

// Lightning-based ability
UCLASS()
class MYGAME_API ULightningStrikeAbility : public UWeatherAbility
{
    GENERATED_BODY()

public:
    ULightningStrikeAbility()
    {
        RequiredWeather = EDAIWeatherType::Thunderstorm;
        WeatherIntensityThreshold = 0.7f;
    }

protected:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
                                const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override
    {
        Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
        
        // Get target location
        FVector TargetLocation = GetTargetLocationFromPayload(TriggerEventData);
        
        // Trigger lightning through sky system
    ADAIUltraSkyActor* Sky = GetUltraSkyActor(ActorInfo->AvatarActor.Get());
        if (SkyManager)
        {
            SkyManager->TriggerLightning(TargetLocation, 1.0f);
            
            // Apply damage at target location
            ApplyLightningDamage(TargetLocation);
        }
        
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
    }
};
```

### Custom Sky Presets
```blueprint
// Create and apply sky presets
void CreateSkyPresets()
{
    // Dawn preset
    FDAISkyPreset DawnPreset;
    DawnPreset.PresetName = "Dawn";
    DawnPreset.TimeOfDay = 6.0f;
    DawnPreset.WeatherInfo.WeatherType = EDAIWeatherType::Clear;
    DawnPreset.WeatherInfo.CloudCover = 0.3f;
    DawnPreset.AtmosphericParams.RayleighScatteringScale = 1.2f;
    DawnPreset.AtmosphericParams.MieScatteringScale = 0.8f;
    
    // Stormy preset
    FDAISkyPreset StormPreset;
    StormPreset.PresetName = "Storm";
    StormPreset.TimeOfDay = 15.0f;
    StormPreset.WeatherInfo.WeatherType = EDAIWeatherType::Thunderstorm;
    StormPreset.WeatherInfo.CloudCover = 0.9f;
    StormPreset.WeatherInfo.Visibility = 2000.0f;
    StormPreset.AtmosphericParams.RayleighScatteringScale = 0.6f;
    
    // Store presets
    SkyPresets.Add("Dawn", DawnPreset);
    SkyPresets.Add("Storm", StormPreset);
}

void ApplySkyPreset(const FString& PresetName)
{
    if (FDAISkyPreset* Preset = SkyPresets.Find(PresetName))
    {
        // Apply time
        SkyManager->SetTimeOfDay(Preset->TimeOfDay, true, 5.0f);
        
        // Apply weather
        SkyManager->SetWeatherType(
            Preset->WeatherInfo.WeatherType,
            Preset->WeatherInfo.Intensity,
            10.0f
        );
        
        // Apply atmospheric parameters
        SkyManager->SetAtmosphericParameters(Preset->AtmosphericParams);
        
        // Apply custom skybox if specified
        if (Preset->SkyboxMaterial)
        {
            SkyManager->SetSkyboxMaterial(Preset->SkyboxMaterial, 3.0f);
        }
    }
}
```

## Integration with Other Plugins

### DAI_Hub Integration
- **Service Registration**: UltraSky manager registers with hub for discovery
- **Event Publishing**: Time and weather events published through hub
- **Performance Coordination**: Sky updates respect hub performance budgets

### Niagara Integration
- **Weather Effects**: Comprehensive Niagara effects for all weather types
- **Dynamic Parameters**: Weather parameters drive Niagara system properties
- **Performance Scaling**: Effect complexity scales with performance settings

### Gameplay Ability System
- **Weather Abilities**: Abilities that require specific weather conditions
- **Environmental Effects**: Weather applies gameplay effects to characters
- **Ability Modifiers**: Weather conditions modify ability effectiveness

### DAI_AI Integration
- **Behavior Modification**: Weather affects AI decision making and pathfinding
- **Shelter Seeking**: AI can seek shelter during storms
- **Activity Patterns**: Time of day affects AI activity levels

## Best Practices

### Performance Optimization
1. **Use LOD systems** for distant weather effects
2. **Limit concurrent effects** during intense weather
3. **Optimize atmospheric calculations** for performance
4. **Cache frequent queries** like time of day
5. **Profile sky system impact** on overall performance

### Visual Design
1. **Create smooth transitions** between weather states
2. **Design consistent lighting** for different times of day
3. **Balance atmospheric effects** with gameplay visibility
4. **Test weather effects** across different environments
5. **Provide accessibility options** for weather sensitivity

### Gameplay Integration
1. **Design meaningful weather impact** on gameplay
2. **Provide weather forecasting** for player planning
3. **Balance weather frequency** to maintain interest
4. **Consider multiplayer synchronization** of weather
5. **Test time progression rates** for game flow

### Technical Implementation
1. **Handle edge cases** like extreme weather transitions
2. **Implement proper cleanup** for weather effects
3. **Test with various hardware** configurations
4. **Monitor memory usage** with complex weather systems
5. **Plan for save/load** of weather and time state

## Technical Notes

- **Thread Safety**: Sky operations designed for game thread usage
- **Memory Management**: Efficient cleanup of weather effects and atmospheric data
- **Platform Support**: Cross-platform sky rendering with platform-specific optimizations
- **Performance**: Optimized atmospheric calculations and effect management
- **Integration**: Clean interfaces for extending sky and weather functionality

---

*For more information about hub integration, see [DAI_Hub documentation](DAI_Hub.md).*  
*For Niagara integration details, consult the Unreal Engine 5.5 Niagara documentation.*  
*For GAS integration, see [DAI documentation](DAI.md).*

---

Last updated: October 6, 2025