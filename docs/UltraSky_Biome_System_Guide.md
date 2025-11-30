# UltraSky Biome Volume System - Complete Guide

**Date:** November 6, 2025  
**Status:** ✅ **COMPLETE** - Lightweight regional weather with intensity falloff

---

## Overview

The **Biome Volume System** provides **regional weather zones** with:

- ✅ **Volume-based weather** - Different weather in different areas
- ✅ **Random weather changes** - Weighted probability system per biome
- ✅ **Smooth intensity falloff** - Full strength at center, fades at edges
- ✅ **Gradual particle ramping** - Weather effects start light and build up
- ✅ **Automatic transitions** - Seamless weather changes when entering/exiting
- ✅ **Priority system** - Control overlapping biomes
- ✅ **Lightweight** - Efficient overlap checks with configurable update rates

---

## Key Features

### 1. **Edge Intensity Falloff**
Weather is **full strength at center**, gradually fades at edges:
```
Center (100%) ───► Mid (75%) ───► Edge (25%) ───► Outside (0%)
```

### 2. **Particle Ramp-Up**
When weather changes, particles don't appear instantly:
```
Weather Change → 0% → 25% → 50% → 75% → 100% (over 5 seconds)
```

### 3. **Random Weather Selection**
Each biome can have multiple possible weathers with chance weights:
```
Desert Biome:
  - Clear Sunny:     70% chance
  - Light Dust Storm: 20% chance
  - Sandstorm:       10% chance
```

### 4. **Priority System**
When volumes overlap, highest priority wins:
```
Mountain Biome (Priority 10) overlaps Desert Biome (Priority 5)
→ Mountain weather takes precedence
```

---

## Files Created

1. **UltraSkyBiomeVolume.h/cpp** - Volume actor for regional weather
2. **UltraSkyBiomeManager.h/cpp** - Component that tracks player location and applies intensity

---

## Quick Start

### Step 1: Place a Biome Volume

1. **Add to Level:**
  - Place > Volumes > **DAI UltraSky Biome Volume**
   - Or search: `AUltraSkyBiomeVolume`

2. **Scale the Volume:**
   - Use Transform tools to cover desired region
   - Larger = bigger weather zone

3. **Configure Identity:**
   ```
   Biome Name: "Desert Region"
   Biome Tag: "Biome.Desert"
   Priority: 0 (higher = wins overlaps)
   ```

### Step 2: Add Weather Presets

1. **Add Possible Weathers:**
   ```
   Possible Weathers:
   [0]
     Preset: WP_Clear
     Chance Weight: 70.0
     Min Duration: 300.0 (5 minutes)
     Max Duration: 600.0 (10 minutes)
   
   [1]
     Preset: WP_LightSandstorm
     Chance Weight: 20.0
     Min Duration: 180.0 (3 minutes)
     Max Duration: 300.0 (5 minutes)
   
   [2]
     Preset: WP_Sandstorm
     Chance Weight: 10.0
     Min Duration: 120.0 (2 minutes)
     Max Duration: 240.0 (4 minutes)
   ```

2. **Configure Intensity:**
   ```
   Edge Falloff Distance: 2000.0 (20 meters fade)
   Particle Ramp Up Time: 5.0 (particles build over 5 seconds)
   Use Eased Falloff: true (smooth transition)
   ```

3. **Enable Random Weather:**
   ```
   Random Weather Changes: true
   Random Seed: 0 (0 = random, >0 = deterministic)
   ```

### Step 3: Add Biome Manager to UltraSky

1. **Find your UltraSky Actor**
2. **Add Component:** `UltraSkyBiomeManager`
3. **Configure:**
   ```
   Update Interval: 0.1 (seconds between location checks)
   Auto Find Biomes: true
   Use Owner Location: true
   Auto Modulate Particles: true
   ```

### Step 4: Test!

1. **Play in Editor**
2. **Walk into the biome volume**
3. **Weather automatically changes** based on:
   - Current active biome
   - Random selection from possible weathers
   - Your distance from center (intensity falloff)

---

## Example Setups

### ❄️ Tundra Biome (Snowy Region)

```
Biome Name: "Frozen Wasteland"
Priority: 0

Possible Weathers:
  WP_LightSnow:    60% (300-600s)
  WP_Snowstorm:    30% (180-300s)
  WP_Blizzard:     10% (120-180s)

Edge Falloff Distance: 3000.0 (30m)
Particle Ramp Up Time: 8.0 (slow buildup)
```

### 🏜️ Desert Biome (Hot & Dry)

```
Biome Name: "Scorching Sands"
Priority: 0

Possible Weathers:
  WP_Clear:           70% (600-1200s)
  WP_Windy:           15% (300-600s)
  WP_Sandstorm:       10% (180-300s)
  WP_HeavySandstorm:   5% (120-240s)

Edge Falloff Distance: 2000.0 (20m)
Particle Ramp Up Time: 5.0
```

### 🌲 Forest Biome (Temperate)

```
Biome Name: "Misty Woods"
Priority: 0

Possible Weathers:
  WP_Overcast:       40% (400-800s)
  WP_LightRain:      30% (300-600s)
  WP_Foggy:          20% (300-600s)
  WP_HeavyRain:      10% (180-300s)

Edge Falloff Distance: 1500.0 (15m)
Particle Ramp Up Time: 4.0
```

### ⛰️ Mountain Peak (High Priority)

```
Biome Name: "Storm Summit"
Priority: 10 (overrides other biomes)

Possible Weathers:
  WP_Windy:         50% (300-600s)
  WP_Blizzard:      30% (180-300s)
  WP_Thunderstorm:  20% (120-240s)

Edge Falloff Distance: 4000.0 (40m - large fade)
Particle Ramp Up Time: 10.0 (very gradual)
```

---

## Advanced Usage

### Overlapping Biomes

When biomes overlap, **priority determines winner**:

```
Desert (Priority 0) overlaps with Oasis (Priority 5)
→ Inside overlap: Oasis weather wins
→ Outside overlap: Each biome has its own weather
```

**Tip:** Use priority to create:
- Micro-climates (high priority small volumes)
- Weather "pockets" (caves, valleys, clearings)
- Story-driven zones (boss arena with permanent storm)

### Smooth Transitions

Players experience gradual weather changes:

```
Player walks from Desert → Forest:

Desert edge:   Sandstorm at 25% intensity
Border:        50% sand, 50% rain (blended)
Forest edge:   Rain at 25% intensity
Forest center: Rain at 100% intensity
```

### Particle System Integration

The **BiomeManager** automatically modulates particle spawn rates:

```cpp
// Register your weather particle system
BiomeManager->RegisterParticleSystem(RainParticles, "Intensity");
BiomeManager->RegisterParticleSystem(SnowParticles, "Intensity");

// Intensity parameter (0.0-1.0) automatically set based on:
// - Distance from biome center
// - Particle ramp-up progress
```

**In your Niagara System:**
1. Add a **User Parameter** named `Intensity` (float)
2. Use it to scale **Spawn Rate:**
   ```
   Spawn Rate = Base Rate * Intensity
   ```

### Manual Weather Changes

Force specific weather in a biome:

```cpp
// Blueprint
BiomeVolume->TriggerWeatherChange();

// C++
if (AUltraSkyBiomeVolume* Biome = GetActiveBiome())
{
    Biome->TriggerWeatherChange();
}
```

### Event-Driven Weather

React to biome/weather changes:

```cpp
// Blueprint: Bind to events
BiomeVolume->OnBiomeWeatherChanged.AddDynamic(this, &AMyActor::OnWeatherChanged);
BiomeVolume->OnPlayerEnteredBiome.AddDynamic(this, &AMyActor::OnEnterBiome);
BiomeVolume->OnPlayerExitedBiome.AddDynamic(this, &AMyActor::OnExitBiome);

BiomeManager->OnActiveBiomeChanged.AddDynamic(this, &AMyActor::OnActiveBiomeChanged);
BiomeManager->OnIntensityChanged.AddDynamic(this, &AMyActor::OnIntensityChanged);
```

---

## Configuration Reference

### UltraSkyBiomeVolume Properties

| Property | Type | Description | Default |
|----------|------|-------------|---------|
| **BiomeName** | Text | Display name for UI/debug | "Unnamed Biome" |
| **BiomeTag** | GameplayTag | Tag for identification | None |
| **PossibleWeathers** | Array | List of weather presets with chance weights | Empty |
| **EdgeFalloffDistance** | Float | Distance in cm where intensity fades | 2000.0 (20m) |
| **ParticleRampUpTime** | Float | Seconds for particles to reach full strength | 5.0 |
| **Priority** | Int32 | Priority for overlapping volumes | 0 |
| **bRandomWeatherChanges** | Bool | Enable automatic weather cycling | true |
| **RandomSeed** | Int32 | Seed for deterministic selection (0=random) | 0 |
| **bUseEasedFalloff** | Bool | Smooth easing (vs linear) for falloff | true |
| **bDebugDraw** | Bool | Show debug visualization | false |

### FWeatherPresetChance Properties

| Property | Type | Description | Default |
|----------|------|-------------|---------|
| **Preset** | UUltraSkyWeatherPreset* | Weather preset to apply | None |
| **ChanceWeight** | Float | Probability weight (0-100) | 50.0 |
| **MinDuration** | Float | Minimum seconds before change | 300.0 (5 min) |
| **MaxDuration** | Float | Maximum seconds before change | 600.0 (10 min) |

### UltraSkyBiomeManager Properties

| Property | Type | Description | Default |
|----------|------|-------------|---------|
| **UpdateInterval** | Float | Seconds between location checks | 0.1 |
| **bAutoFindBiomes** | Bool | Find volumes on BeginPlay | true |
| **bUseOwnerLocation** | Bool | Use owner pawn's location | true |
| **bAutoModulateParticles** | Bool | Auto-apply intensity to particles | true |
| **bDebugDraw** | Bool | Show debug visualization | false |

---

## Blueprint API

### Biome Volume Functions

```
// Query
IsLocationInBiome(Vector) → Bool
GetWeatherIntensityAtLocation(Vector) → Float (0-1)
GetCurrentWeatherPreset() → UltraSkyWeatherPreset
GetCurrentIntensityMultiplier() → Float (0-1)

// Control
TriggerWeatherChange()  // Force immediate weather change

// Events
OnBiomeWeatherChanged(OldWeather, NewWeather)
OnPlayerEnteredBiome(Player)
OnPlayerExitedBiome(Player)
```

### Biome Manager Functions

```
// Query
GetActiveBiome() → UltraSkyBiomeVolume (highest priority)
GetActiveBiomes() → Array<FActiveBiomeInfo>
GetCurrentIntensityMultiplier() → Float (0-1)

// Control
SetTargetLocation(Vector)  // Override auto-detection
ClearTargetLocation()       // Return to auto-detection
RegisterParticleSystem(NiagaraComponent, ParameterName)
UnregisterParticleSystem(NiagaraComponent)

// Events
OnActiveBiomeChanged(OldBiome, NewBiome)
OnIntensityChanged(NewIntensity)
```

---

## Performance Tips

### Optimize Update Rate

```cpp
// For distant NPCs or slow-moving weather:
BiomeManager->UpdateInterval = 0.5f;  // Update twice per second

// For player character (responsive):
BiomeManager->UpdateInterval = 0.1f;  // 10 times per second
```

### Particle System Optimization

- Use **distance-based culling** on particle systems
- Set **Max Particles** based on intensity:
  ```
  Max Particles = Base Max * Intensity
  ```
- Use **LODs** for particles (fewer particles at distance)

### Biome Volume Optimization

- Use **simple box/sphere volumes** (faster than complex shapes)
- Avoid **overlapping many high-priority volumes**
- Disable `bRandomWeatherChanges` for static weather zones

---

## Troubleshooting

### Weather Not Changing

**Issue:** Biome volume not applying weather  
**Solution:**
1. Check `PossibleWeathers` array has valid presets
2. Verify `bRandomWeatherChanges` is enabled
3. Check `UltraSkyBiomeManager` component exists on UltraSky actor
4. Ensure player is inside volume (use debug draw)

### Intensity Always 1.0 or 0.0

**Issue:** No edge falloff  
**Solution:**
1. Increase `EdgeFalloffDistance` (default 2000 = 20m)
2. Ensure volume is larger than falloff distance
3. Check player is within falloff region
4. Enable `bDebugDraw` to visualize

### Particles Not Ramping

**Issue:** Particles appear instantly  
**Solution:**
1. Increase `ParticleRampUpTime` (default 5 seconds)
2. Register particle systems with BiomeManager:
   ```cpp
   BiomeManager->RegisterParticleSystem(ParticleComp, "Intensity");
   ```
3. Verify Niagara system has `Intensity` user parameter
4. Check spawn rate uses intensity multiplier

### Overlapping Biomes Fighting

**Issue:** Weather flickering between biomes  
**Solution:**
1. Set different **priorities** (higher = wins)
2. Reduce overlap area
3. Increase `UpdateInterval` to reduce update frequency

---

## Example: Story-Driven Weather

Create a boss arena with dynamic weather phases:

```cpp
// Boss Arena Biome (High Priority)
Priority: 100  // Always overrides other biomes

Possible Weathers:
  WP_Calm:         100% (phase 1 - boss idle)
  WP_Thunderstorm: 100% (phase 2 - boss enraged)
  WP_Tornado:      100% (phase 3 - final phase)

// Controlled by boss AI:
void ABossCharacter::OnPhaseChange(int32 NewPhase)
{
    if (AUltraSkyBiomeVolume* ArenaBiome = GetArenaBiome())
    {
        // Force weather change based on phase
        ArenaBiome->TriggerWeatherChange();
    }
}
```

---

## Example: Procedural World Biomes

Generate biomes based on noise:

```cpp
void AWorldGenerator::GenerateBiomes()
{
    FRandomStream NoiseStream(WorldSeed);
    
    for (int32 X = 0; X < GridSize; ++X)
    {
        for (int32 Y = 0; Y < GridSize; ++Y)
        {
            float NoiseValue = GetPerlinNoise(X, Y);
            
            FVector Location(X * TileSize, Y * TileSize, 0);
            AUltraSkyBiomeVolume* Biome = SpawnBiomeVolume(Location);
            
            // Assign weather based on noise
            if (NoiseValue < 0.3f)
            {
                Biome->PossibleWeathers = DesertWeathers;
            }
            else if (NoiseValue < 0.6f)
            {
                Biome->PossibleWeathers = ForestWeathers;
            }
            else
            {
                Biome->PossibleWeathers = TundraWeathers;
            }
        }
    }
}
```

---

## Next Steps

### Recommended Enhancements

1. **Biome Blending** - Smooth transitions between adjacent biomes
2. **Seasonal Variations** - Change weather weights based on time of year
3. **Weather Forecast** - Predict upcoming weather for player planning
4. **Climate Zones** - Group biomes into larger climate regions
5. **Weather Persistence** - Save/load weather state across sessions

### Integration Ideas

- **Sound System** - Fade ambient sounds based on intensity
- **Post-Process** - Modulate fog/color grading with biome intensity
- **Gameplay** - Temperature/wetness systems affected by biome weather
- **AI Navigation** - NPCs avoid/seek specific weather conditions
- **Material Effects** - Wetness/snow accumulation scaled by intensity

---

## Conclusion

The **Biome Volume System** provides:

✅ **Lightweight** - Efficient overlap checks with configurable update rates  
✅ **Regional Weather** - Different weather zones across your world  
✅ **Smooth Transitions** - Gradual intensity falloff at edges  
✅ **Random Selection** - Weighted probability for dynamic weather  
✅ **Easy Setup** - Place volume, add presets, done!  

**Basic Usage:**
1. Place `UltraSkyBiomeVolume` in level
2. Add weather presets to `PossibleWeathers`
3. Add `UltraSkyBiomeManager` to UltraSky actor
4. Walk into volume → Weather changes automatically!

---

**Implementation completed by:** GitHub Copilot  
**Date:** November 6, 2025  
**Files changed:** 4 files created (Biome Volume + Manager)  
**Ready for:** Testing and iteration
