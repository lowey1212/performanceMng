# UltraSky Weather Effects & Materials System

## Overview

The `UltraSkyWeatherParticleComponent` now supports automatic application of **Gameplay Effects** and **Material Parameters** when actors are inside active weather particle areas. This enables dynamic snow coverage, wetness effects, temperature changes, and other weather-driven gameplay mechanics.

## Features

### 1. Gameplay Effect Application

Each weather type (Rain, Snow, Fog) can apply a Gameplay Effect to actors within the particle effect radius:

- **Automatic Detection**: System checks if actors are inside weather effect areas
- **Configurable Intervals**: Apply effects continuously or on entry
- **Intensity-Based**: Effect magnitude scales with weather intensity
- **GAS Integration**: Works with Unreal's Gameplay Ability System

### 2. Material Parameter Updates

Weather effects can dynamically update Material Parameter Collections:

- **Snow Coverage**: Gradually apply snow material based on snow intensity
- **Wetness**: Add rain wetness to surfaces
- **Fog Density**: Adjust fog materials for atmosphere
- **Per-Effect Control**: Each weather type has its own MPC and parameter

## Configuration

### Per-Weather Configuration (`FWeatherParticleConfig`)

#### Gameplay Effects

```cpp
// Enable gameplay effect application
RainConfig.bApplyGameplayEffect = true;

// Set the effect to apply
RainConfig.WeatherGameplayEffect = UGE_RainWetness::StaticClass();

// Application interval (0 = apply once on entry, >0 = continuous)
RainConfig.EffectApplicationInterval = 1.0f; // Every second
```

#### Material Parameters

```cpp
// Enable material parameter updates
SnowConfig.bUpdateMaterialParameters = true;

// Set the Material Parameter Collection
SnowConfig.MaterialParameterCollection = SnowMPC;

// Parameter name to update (e.g., "SnowCoverage", "WetnessAmount")
SnowConfig.MaterialIntensityParameter = FName("SnowCoverage");
```

## Usage Examples

### Example 1: Snow Coverage Material

**Setup:**
1. Create a Material Parameter Collection: `MPC_SnowWeather`
2. Add scalar parameter: `SnowCoverage` (0-1 range)
3. In your landscape/mesh materials, sample this parameter:
   ```
   MPC Parameter (SnowCoverage) -> Lerp (A=Base, B=Snow) -> BaseColor
   ```

**Component Configuration:**
```cpp
SnowConfig.bUpdateMaterialParameters = true;
SnowConfig.MaterialParameterCollection = MPC_SnowWeather;
SnowConfig.MaterialIntensityParameter = FName("SnowCoverage");
```

**Result:**
- As `SnowIntensity` increases (0-1), the `SnowCoverage` parameter updates globally
- All materials using `MPC_SnowWeather` automatically blend to snow appearance
- Effect is visible across entire level within the weather particle area

### Example 2: Rain Wetness Gameplay Effect

**Setup:**
1. Create Gameplay Effect: `GE_RainWetness`
2. Add attribute modifier: `Movement.WalkSpeed` *= 0.9 (slip on wet ground)
3. Add attribute modifier: `Character.Temperature` -= 5 (cooling effect)
4. Set duration: Infinite (while in rain)

**Component Configuration:**
```cpp
RainConfig.bApplyGameplayEffect = true;
RainConfig.WeatherGameplayEffect = UGE_RainWetness::StaticClass();
RainConfig.EffectApplicationInterval = 0.0f; // Apply once on entry
```

**Result:**
- Characters entering rain area get the wetness effect
- Movement speed reduced while in rain
- Temperature attribute decreased
- Effect removed automatically when leaving rain area

### Example 3: Fog Vision Reduction

**Setup:**
1. Create Material Parameter Collection: `MPC_FogWeather`
2. Add scalar parameter: `FogDensity`
3. Use in post-process volume or fog materials

**Gameplay Effect:**
1. Create `GE_FogVision`
2. Reduce `Vision.Range` attribute
3. Add `Status.InFog` tag

**Component Configuration:**
```cpp
FogConfig.bApplyGameplayEffect = true;
FogConfig.WeatherGameplayEffect = UGE_FogVision::StaticClass();
FogConfig.EffectApplicationInterval = 2.0f; // Re-apply every 2 seconds

FogConfig.bUpdateMaterialParameters = true;
FogConfig.MaterialParameterCollection = MPC_FogWeather;
FogConfig.MaterialIntensityParameter = FName("FogDensity");
```

**Result:**
- Fog visuals appear via material parameter
- Characters in fog have reduced vision range
- Effect intensity scales with fog density
- Can check `Status.InFog` tag for AI behavior changes

## Blueprint API

### Check if Location is in Weather Effect

```cpp
UFUNCTION(BlueprintCallable)
bool IsLocationInsideWeatherEffect(const FVector& Location, float& OutIntensity, FName& OutWeatherType) const;
```

**Usage:**
```blueprint
// Check if a specific location has weather effects
IsLocationInsideWeatherEffect(TargetLocation) -> Is Inside?, Intensity, Weather Type ("Rain", "Snow", "Fog")
```

### Get Actors Currently in Weather

```cpp
UFUNCTION(BlueprintCallable)
void GetActorsInWeatherEffect(TArray<AActor*>& OutActors) const;
```

**Usage:**
```blueprint
// Get all actors currently experiencing weather effects
GetActorsInWeatherEffect() -> Actors Array
ForEach Actor -> Apply custom logic (damage, buffs, VFX, etc.)
```

## System Behavior

### Actor Tracking

The component automatically:
1. **Scans** for actors near particle instances each frame
2. **Checks** if actor location is within weather effect radius (GridSpacing * 0.5)
3. **Tracks** actors in `ActorsInWeatherEffect` map with current intensity
4. **Updates** timers for effect application intervals
5. **Removes** actors when they leave the weather area

### Effect Application Flow

```
Tick Component
  └─> UpdateWeatherEffectActors(DeltaTime)
        ├─> For each actor in range:
        │     ├─> Check if inside weather effect area
        │     ├─> Add to tracked actors
        │     └─> Apply gameplay effect (if interval passed)
        │
        └─> Remove actors no longer in range
```

### Material Update Flow

```
Tick Component
  └─> UpdateMaterialParameters()
        ├─> Rain: Set RainConfig.MaterialIntensityParameter = RainIntensity
        ├─> Snow: Set SnowConfig.MaterialIntensityParameter = SnowIntensity
        └─> Fog:  Set FogConfig.MaterialIntensityParameter = FogIntensity
```

## Performance Considerations

### Actor Iteration

- **Concern**: `TActorIterator` scans all actors in world
- **Mitigation**: Only checks actors within max visible distance of player
- **Optimization**: Consider using collision volumes for smaller search space

### Effect Application Rate

- **Recommendation**: Use `EffectApplicationInterval > 0` to limit GAS overhead
- **Balance**: Shorter intervals = more responsive, but higher cost
- **Typical Values**:
  - Entry effects: `0.0f` (apply once)
  - Status effects: `1.0f - 2.0f` (every 1-2 seconds)
  - Damage effects: `0.5f - 1.0f` (frequent updates)

### Material Parameters

- **Cost**: Material Parameter Collections are very efficient
- **Update Rate**: Updated every frame when weather is active
- **Impact**: Minimal - MPC updates are cheap global operations

## Integration with GAS

### SetByCaller Magnitude

The system sets intensity via SetByCaller with tag: `Data.Weather.Intensity`

**In your Gameplay Effect:**
1. Add Modifier with `SetByCaller` magnitude
2. Use tag: `Data.Weather.Intensity`
3. Value will be `0.0 - 1.0` based on weather intensity

**Example:**
```cpp
// In GE_RainWetness
Modifier: Character.Temperature
Magnitude: SetByCaller (Data.Weather.Intensity)
  └─> Formula: -10 * Magnitude (reduces temp by 0-10 based on rain intensity)
```

## Advanced Scenarios

### Multiple Weather Types

If actor is in overlapping weather areas:
- System prioritizes: Rain > Snow > Fog
- Only one effect type applied at a time
- Intensity uses the detected weather type

### Custom Weather Effects

Add custom weather types via `CustomConfigs` array:

```cpp
FWeatherParticleConfig LightningConfig;
LightningConfig.NiagaraSystem = LightningNiagara;
LightningConfig.bApplyGameplayEffect = true;
LightningConfig.WeatherGameplayEffect = UGE_ElectricDamage::StaticClass();
LightningConfig.EffectApplicationInterval = 0.0f; // Instant damage

CustomConfigs.Add(LightningConfig);
```

### Material Blending

For smooth transitions, use material lerp nodes:

```
Current Value = Lerp(Current, Target, DeltaTime * BlendSpeed)
```

This prevents sudden snow coverage and creates gradual accumulation.

## Debugging

### Log Weather Effects

Add debug prints in `ApplyWeatherEffectToActor`:

```cpp
UE_LOG(LogUltraSky, Log, TEXT("Applied %s effect to %s (Intensity: %.2f)"),
    *GetNameSafe(Config.WeatherGameplayEffect),
    *Actor->GetName(),
    Intensity);
```

### Visualize Effect Radius

Enable debug drawing for effect areas:

```cpp
// In UpdateWeatherEffectActors
DrawDebugSphere(World, Instance.CurrentLocation, EffectRadius, 16, FColor::Blue, false, UpdateInterval);
```

### Check Active Actors

Use Blueprint API:

```blueprint
GetActorsInWeatherEffect() -> Print String (Count: X actors in weather)
```

## Summary

The weather effects & materials system provides:
- ✅ Automatic gameplay effect application to actors in weather
- ✅ Dynamic material parameter updates for visual feedback
- ✅ Per-weather type configuration (rain/snow/fog)
- ✅ GAS integration with intensity scaling
- ✅ Blueprint query API for custom logic
- ✅ Efficient tracking and application system

Use this to create immersive weather gameplay with visual and mechanical impact!
