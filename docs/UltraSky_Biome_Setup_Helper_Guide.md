# UltraSky Biome Setup Helper - Quick Start Guide

**One-Click Example Biome Generation!** 🎯

---

## What It Does

The **Biome Setup Helper** automatically creates 4 example biomes in your level:

1. 🏜️ **Desert** - Clear (70%) / Sandstorm (30%)
2. 🌲 **Forest** - Overcast (40%) / Rain (40%) / Fog (20%)
3. ❄️ **Tundra** - Light Snow (60%) / Snowstorm (30%) / Blizzard (10%)
4. ⛰️ **Mountain** - Windy (50%) / Blizzard (30%) / Storm (20%)

All with proper intensity falloff, particle ramping, and random weather cycling!

---

## Quick Start (3 Steps)

### Step 1: Place the Helper Actor

1. Open your level in Unreal Editor
2. **Place Actors Panel** → Search: `UltraSkyBiomeSetupHelper`
3. Drag into your level at desired location
   - Biomes will be created in a 2x2 grid around this point
   - Default spacing: 500 meters apart

### Step 2: Assign Weather Presets

In the **Details Panel**, assign your weather presets:

```
Weather Presets | Clear:
  - Clear Preset: WP_Clear

Weather Presets | Clouds:
  - Partly Cloudy Preset: WP_PartlyCloudy
  - Overcast Preset: WP_Overcast

Weather Presets | Rain:
  - Light Rain Preset: WP_LightRain
  - Heavy Rain Preset: WP_HeavyRain

Weather Presets | Storm:
  - Thunderstorm Preset: WP_Thunderstorm

Weather Presets | Snow:
  - Light Snow Preset: WP_LightSnow
  - Snowstorm Preset: WP_Snowstorm
  - Blizzard Preset: WP_Blizzard

Weather Presets | Other:
  - Foggy Preset: WP_Foggy
  - Windy Preset: WP_Windy
  - Sandstorm Preset: WP_Sandstorm
```

**Note:** If you haven't created presets yet, the helper will use whatever you have assigned. Missing presets are skipped.

### Step 3: Generate Biomes

**Method 1: Editor Button (Recommended)**
- In Details Panel → Click **"Generate Example Biomes"**
- 4 biomes instantly created and selected!

**Method 2: Auto-Generate on Play**
- Set `Auto Generate On Begin Play: true`
- Hit Play → Biomes automatically spawn

---

## Configuration Options

### Biome Layout Settings

| Property | Description | Default |
|----------|-------------|---------|
| **Biome Spacing** | Distance between biomes (cm) | 50000 (500m) |
| **Biome Size** | Radius of each biome (cm) | 30000 (300m) |
| **Edge Falloff Distance** | Fade distance at edges (cm) | 2000 (20m) |
| **Particle Ramp Up Time** | Seconds for particles to build | 5.0 |
| **Create Debug Markers** | Show debug spheres at centers | true |
| **Auto Generate On Begin Play** | Spawn biomes when playing | false |

### Example: Larger Biomes with More Spacing

```
Biome Spacing: 100000 (1km apart)
Biome Size: 50000 (500m radius)
Edge Falloff Distance: 5000 (50m fade)
Particle Ramp Up Time: 8.0 (slower buildup)
```

---

## Generated Biome Details

### 🏜️ Desert Biome
```
Location: Southwest (-X, -Y)
Weather:
  - Clear:      70% (10-20 min)
  - Sandstorm:  30% (3-5 min)
Priority: 0
```

### 🌲 Forest Biome
```
Location: Southeast (+X, -Y)
Weather:
  - Overcast:   40% (6-13 min)
  - Light Rain: 40% (5-10 min)
  - Fog:        20% (5-10 min)
Priority: 0
```

### ❄️ Tundra Biome
```
Location: Northwest (-X, +Y)
Weather:
  - Light Snow: 60% (5-10 min)
  - Snowstorm:  30% (3-5 min)
  - Blizzard:   10% (2-4 min)
Priority: 0
```

### ⛰️ Mountain Biome
```
Location: Northeast (+X, +Y)
Weather:
  - Windy:      50% (5-10 min)
  - Blizzard:   30% (3-5 min)
  - Storm:      20% (2-4 min)
Priority: 10 (overrides others when overlapping)
```

---

## Testing Your Biomes

### 1. Add Biome Manager to UltraSky

```
1. Find your UltraSky Actor
2. Add Component → UltraSky Biome Manager
3. Set Update Interval: 0.1
```

### 2. Enable Debug Visualization

```
Each Biome Volume:
  - Set "Debug Draw: true"

Biome Manager:
  - Set "Debug Draw: true"
```

### 3. Play and Explore

```
1. Hit Play
2. Walk into each biome
3. Observe:
   - Weather changes automatically
   - Intensity fades at edges
   - Particles ramp up smoothly
   - Different weather per region
```

---

## Customization

### Change Weather Mix

After generation, select any biome and modify:

```
Possible Weathers:
[0] Clear:      70% → Change to 50%
[1] Sandstorm:  30% → Change to 40%
[2] Add new:    Windy 10%
```

### Adjust Timings

```
Clear:
  - Min Duration: 600 → 300 (change every 5 min)
  - Max Duration: 1200 → 600

Sandstorm:
  - Min Duration: 180 → 60 (shorter storms)
  - Max Duration: 300 → 120
```

### Change Size/Intensity

```
Edge Falloff Distance:
  - 2000 (20m) → 5000 (50m) for gradual fade

Particle Ramp Up Time:
  - 5.0s → 10.0s for very slow buildup
```

---

## Clear and Regenerate

**Clear Existing:**
- Click **"Clear Generated Biomes"** button
- All helper-created biomes are destroyed

**Regenerate:**
- Adjust settings
- Move helper to new location
- Click **"Generate Example Biomes"** again

---

## Blueprint Workflow

You can also spawn biomes from Blueprint:

```
Event BeginPlay
  → Spawn Actor (UltraSky Biome Setup Helper)
  → Set Actor Location (X=0, Y=0, Z=0)
  → Set Biome Spacing (50000)
  → Set Biome Size (30000)
  → Assign Weather Presets
  → Call "Generate Example Biomes"
```

---

## Tips & Tricks

### Tip 1: Create Custom Layouts

Disable auto-layout and manually position biomes:
```cpp
// Create individual biomes at specific locations
AUltraSkyBiomeVolume* OasisBiome = CreateForestBiome(FVector(10000, 0, 0));
AUltraSkyBiomeVolume* DuneBiome = CreateDesertBiome(FVector(-10000, 0, 0));
```

### Tip 2: Test Different Presets

Quickly swap presets to see how they affect each biome:
```
1. Generate biomes
2. Change Clear Preset → WP_PartlyCloudy
3. Clear and regenerate
4. Compare results
```

### Tip 3: Use for Level Design

Place helper at key locations:
```
- Town Center: Forest biome (calm weather)
- Wilderness: Tundra biome (harsh weather)
- Boss Arena: Mountain biome (dramatic storm)
- Safe Zone: Desert biome (clear skies)
```

---

## Troubleshooting

**Issue:** No biomes appear  
**Fix:** Check Output Log for errors, ensure world is valid

**Issue:** Biomes spawn but no weather changes  
**Fix:** Assign weather presets in helper details panel

**Issue:** Can't see biomes in editor  
**Fix:** Enable "Show" → "Volumes" in viewport

**Issue:** Weather same in all biomes  
**Fix:** Ensure each biome has different Possible Weathers array

---

## Next Steps

After generating example biomes:

1. ✅ **Test** - Walk through each biome, observe weather changes
2. ✅ **Customize** - Adjust weather mix, timings, intensities
3. ✅ **Expand** - Add more biomes manually with specific configurations
4. ✅ **Integrate** - Connect to gameplay (temperature, visibility, buffs/debuffs)
5. ✅ **Polish** - Fine-tune particle systems, sound effects, post-processing

---

## Summary

The **Biome Setup Helper** gives you:

✅ **4 ready-to-use example biomes** in seconds  
✅ **Proper weather configuration** with realistic probabilities  
✅ **Adjustable layout** - spacing, size, intensity  
✅ **Easy cleanup** - clear and regenerate anytime  
✅ **Blueprint support** - spawn biomes from code  

**Usage:**
1. Place helper actor
2. Assign weather presets
3. Click "Generate Example Biomes"
4. Done! 🎉

Now go explore your dynamic weather world!
