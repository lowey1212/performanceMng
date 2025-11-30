# UltraSky Weather Preset System - Quick Start Guide

## Overview

The **Weather Preset System** provides an easy way to switch between pre-configured weather conditions with smooth transitions.

## Usage

### Quick Method (Blueprint)

```
Get Weather Manager
  → Set Weather Thunderstorm (10.0)  // 10 second transition
```

```
Get Weather Manager  
  → Set Weather Sunny (5.0)  // Clear skies in 5 seconds
```

### Using Presets (Blueprint)

```
Get Weather Manager
  → Apply Preset (MyCustomStorm, 15.0)  // Custom preset, 15 second transition
```

### C++ Usage

```cpp
// Quick preset
WeatherManager->SetWeatherThunderstorm(10.0f);

// Custom preset
WeatherManager->ApplyPreset(MyPreset, 15.0f);

// By tag
WeatherManager->ApplyPresetByTag(FGameplayTag::RequestGameplayTag("Weather.Rain.Heavy"), 10.0f);
```

---

## Built-in Quick Presets

| Function | Weather | Typical Values |
|----------|---------|----------------|
| `SetWeatherClear()` | ☀️ Clear/Sunny | CloudCoverage: 0.1, FogDensity: 0.0, Wind: Low |
| `SetWeatherPartlyCloudy()` | ⛅ Partly Cloudy | CloudCoverage: 0.4, FogDensity: 0.05 |
| `SetWeatherOvercast()` | ☁️ Overcast | CloudCoverage: 0.9, FogDensity: 0.1, Dark clouds |
| `SetWeatherLightRain()` | 🌦️ Light Rain | CloudCoverage: 0.7, Wetness: 0.4, Wind: Med |
| `SetWeatherHeavyRain()` | 🌧️ Heavy Rain | CloudCoverage: 0.95, Wetness: 0.9, Wind: High |
| `SetWeatherThunderstorm()` | ⛈️ Thunderstorm | CloudCoverage: 1.0, StormIntensity: 0.8, Lightning |
| `SetWeatherLightSnow()` | 🌨️ Light Snow | CloudCoverage: 0.6, SnowAccum: 0.3, Temp: -5°C |
| `SetWeatherSnowstorm()` | ❄️ Snowstorm/Blizzard | CloudCoverage: 1.0, SnowAccum: 0.9, Wind: Extreme |
| `SetWeatherFoggy()` | 🌫️ Fog | FogDensity: 0.7, CloudCoverage: 0.8, Low visibility |
| `SetWeatherWindy()` | 💨 Windy | WindIntensity: 2.0, Gusts: 1.5 |

---

## Creating Custom Presets

### Step 1: Create Preset Asset

1. **Content Browser** → Right-click → **UltraSky** → **Weather Preset**
2. Name it (e.g., `WP_MyThunderstorm`)
3. Open the asset

### Step 2: Configure Values

**Value Rules:**
- `-1` = Don't change this attribute (leave as-is)
- `0-1` = Set to specific value (most attributes are normalized)
- Positive values = Actual values (wind, temperature, etc.)

### Example: Custom Thunderstorm

```
Display Name: "Epic Thunderstorm"
Description: "Intense storm with heavy rain and frequent lightning"

--- Clouds ---
Cloud Coverage: 1.0       (fully covered)
Cloud Density: 0.9        (thick, dark clouds)
Cloud Layer Bottom: 2000  (low clouds)

--- Fog ---
Fog Density: 0.3          (reduced visibility)
Fog Start Distance: 0

--- Wind ---
Wind Base Intensity: 1.5  (strong winds)
Wind Gust Strength: 2.0   (powerful gusts)

--- Storm ---
Storm Intensity: 0.9      (very intense)
Lightning Frequency: 0.7  (frequent strikes)

--- Precipitation ---
Wetness: 1.0              (everything soaked)
Temperature: 15           (cool, 15°C)

--- Transition ---
Transition Duration: 12.0 (12 seconds to full storm)
```

### Step 3: Add to Weather Manager

**Option A: Set as Built-in Preset**
1. Select your UltraSky actor
2. Find **Weather Manager** component
3. Set `Thunderstorm Preset` = `WP_MyThunderstorm`

**Option B: Add to Preset Library**
1. Weather Manager → **Preset Library**
2. Add entry: Key = `"MyStorm"`, Value = `WP_MyThunderstorm`
3. Call: `ApplyPresetByName("MyStorm")`

**Option C: Apply Directly**
```cpp
WeatherManager->ApplyPreset(MyThunderstormPreset, 12.0f);
```

---

## Common Preset Recipes

### ☀️ **Clear Sunny Day**
```
CloudCoverage: 0.0
FogDensity: 0.0
WindBaseIntensity: 0.2
RayleighScale: 1.2 (bright blue sky)
Temperature: 25
```

### 🌦️ **Light Drizzle**
```
CloudCoverage: 0.6
FogDensity: 0.15
Wetness: 0.3
WindBaseIntensity: 0.4
Temperature: 18
TransitionDuration: 8.0
```

### ⛈️ **Severe Thunderstorm**
```
CloudCoverage: 1.0
CloudDensity: 1.0
FogDensity: 0.4
WindBaseIntensity: 2.5
WindGustStrength: 3.0
StormIntensity: 1.0
LightningFrequency: 0.9
Wetness: 1.0
RayleighScale: 0.3 (dark sky)
Temperature: 12
TransitionDuration: 15.0
```

### ❄️ **Blizzard**
```
CloudCoverage: 1.0
CloudDensity: 0.9
FogDensity: 0.8 (whiteout)
WindBaseIntensity: 3.0
WindGustStrength: 4.0
SnowAccumulation: 1.0
Temperature: -15
TransitionDuration: 20.0
```

### 🌫️ **Dense Fog**
```
CloudCoverage: 0.7
FogDensity: 0.9
FogStartDistance: 0
FogMaxOpacity: 1.0
WindBaseIntensity: 0.1 (calm)
RayleighScale: 0.5 (muted sky)
Temperature: 8
TransitionDuration: 10.0
```

### 🌅 **Sunset (Clear)**
```
TimeOfDayHours: 18.5 (6:30 PM)
CloudCoverage: 0.2
RayleighScale: 1.5 (vibrant colors)
MieScale: 1.2 (atmospheric haze)
WindBaseIntensity: 0.3
Temperature: 22
TransitionDuration: 30.0 (slow, cinematic)
```

### 🌙 **Clear Night (Full Moon)**
```
TimeOfDayHours: 23.0 (11 PM)
CloudCoverage: 0.1
MoonPhase: 1.0 (full moon)
MoonBaseIntensity: 1.5 (bright moonlight)
StarVisibility: 1.0
WindBaseIntensity: 0.2
Temperature: 12
```

---

## Transition Curves

**Linear (default):** Smooth, constant rate  
**Ease In:** Starts slow, speeds up  
**Ease Out:** Starts fast, slows down  
**Ease In-Out:** S-curve (smooth start and end)

To use:
1. Create **Float Curve** asset
2. Set curve shape (0.0 → 1.0)
3. Assign to preset's **Transition Curve**

---

## Dynamic Weather Example

### Blueprint: Random Weather Every 5 Minutes

```
Event Begin Play
  → Set Timer by Event (300.0, Looping)
    → On Timer:
      Random Integer (0, 9)
        → Switch:
          0 → Set Weather Clear
          1 → Set Weather Partly Cloudy
          2 → Set Weather Overcast
          3 → Set Weather Light Rain
          4 → Set Weather Heavy Rain
          5 → Set Weather Thunderstorm
          6 → Set Weather Light Snow
          7 → Set Weather Snowstorm
          8 → Set Weather Foggy
          9 → Set Weather Windy
```

### C++ Example: Storm Approaching

```cpp
// Day starts clear
WeatherManager->SetWeatherClear(0.0f);

// After 10 minutes, clouds roll in
FTimerHandle Timer1;
GetWorld()->GetTimerManager().SetTimer(Timer1, [this]()
{
    WeatherManager->SetWeatherPartlyCloudy(120.0f); // 2 minute transition
}, 600.0f, false);

// After 20 minutes, storm hits
FTimerHandle Timer2;
GetWorld()->GetTimerManager().SetTimer(Timer2, [this]()
{
    WeatherManager->SetWeatherThunderstorm(180.0f); // 3 minute buildup
}, 1200.0f, false);

// After 30 minutes, storm passes
FTimerHandle Timer3;
GetWorld()->GetTimerManager().SetTimer(Timer3, [this]()
{
    WeatherManager->SetWeatherLightRain(120.0f); // Rain continues
}, 1800.0f, false);

// After 40 minutes, clear again
FTimerHandle Timer4;
GetWorld()->GetTimerManager().SetTimer(Timer4, [this]()
{
    WeatherManager->SetWeatherClear(300.0f); // 5 minute clearing
}, 2400.0f, false);
```

---

## Combining with Spells

Presets and spells **stack**:

```
Current: SetWeatherOvercast (CloudCoverage = 0.9)
+ Spell: Summon Fog (FogDensity +0.5)
= Result: Overcast + Dense Fog
```

```
Current: SetWeatherClear (StormIntensity = 0.0)
+ Spell: Lightning Strike (StormIntensity +0.5 for 10s)
= Result: Sunny day with temporary lightning (spell effect)
```

---

## Console Commands (Testing)

```
// Apply preset by name
UltraSky.ApplyPreset ThunderstormPreset 10.0

// Quick weather change
UltraSky.SetWeather Thunderstorm
UltraSky.SetWeather Clear
UltraSky.SetWeather Snowstorm

// Show current weather
UltraSky.ShowCurrentWeather
```

---

## Best Practices

✅ **Use -1 for unchanged attributes** - Only set what you need  
✅ **Longer transitions for dramatic changes** - Storm: 15s, Clear→Cloudy: 5s  
✅ **Use curves for cinematic transitions** - Ease in/out for cutscenes  
✅ **Group related presets** - Morning variants, night variants, seasonal variants  
✅ **Test transitions in PIE** - Scrub through to verify smoothness  
✅ **Network-friendly** - Presets replicate automatically via GAS  

❌ **Don't change too many attributes** - Overcast only needs CloudCoverage+Density  
❌ **Don't use 0-duration for gameplay** - Instant changes are jarring  
❌ **Don't stack rapid preset changes** - Wait for transition to complete  

---

## Troubleshooting

**Q: Preset doesn't change anything**  
A: Check all values aren't -1. At least one attribute must be ≥ 0.

**Q: Transition is instant even with duration set**  
A: Make sure you're calling on server/authority.

**Q: Quick presets don't work**  
A: Assign preset assets to Weather Manager's built-in preset slots.

**Q: Values snap instead of transitioning**  
A: Check TransitionDuration is > 0 in the preset asset.

---

**Status:** ✅ System complete and ready to use  
**Created:** November 6, 2025
