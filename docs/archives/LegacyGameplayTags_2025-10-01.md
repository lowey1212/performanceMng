# Legacy Gameplay Tags Archive (2025-10-01)

This file preserves gameplay tag entries removed from `Config/DefaultGameplayTags.ini` to keep the active configuration lean. If any referenced assets break due to missing config-defined (now native or deprecated) tags, consult this list to restore specific entries.

> NOTE: Many of these have native counterparts now (declared via UE_DECLARE/DEFINE in C++). Do NOT reintroduce duplicates of native tags in the config; only restore if the tag truly no longer exists anywhere.

## Removed Commented Tags (General Ability & State Examples)
```
Ability.Attack.Aim
State.Attack.Aiming
Ability.Attack.Basic
State.Attack.WindingUp
Cooldown.Attack.Basic
Cue.Attack.Basic.Hit
Ability.Attack.Charged
State.Attack.Charging
Cooldown.Attack.Charged
Cue.Attack.Charged.Hit
```

## Removed (Mantle / Movement / Example) – Already Native or Superseded
```
Ability.Movement.Mantle
State.Movement.Mantling
Cooldown.Mantle
Event.Movement.Mantle.End
Ability.Movement.Blink
Cue.Movement.Blink
```

## Weather / Time / Environmental (Now Native in UltraSky)
```
Weather.Clear
Weather.PartlyCloudy
Weather.Overcast
Weather.Rain
Weather.HeavyRain
Weather.Thunderstorm
Weather.Snow
Weather.Blizzard
Weather.Fog
Ability.Weather.Lightning
Ability.Weather.MeteorStorm
Ability.Weather.ControlWeather
Ability.Weather.SummonStorm
Effect.Weather.LightningStrike
Effect.Weather.WindGust
Effect.Weather.Precipitation
Time.Dawn
Time.Morning
Time.Noon
Time.Afternoon
Time.Dusk
Time.Night
Event.Weather.Changed
Event.Time.Changed
Event.Lightning.Struck
Event.Storm.Started
Event.Storm.Ended
```

## Restore Procedure
1. Confirm tag truly absent at runtime: enable verbose tag logging or attempt `FGameplayTag::RequestGameplayTag` in a test harness.
2. If absent and required only as a placeholder for assets, re-add a single line to `DefaultGameplayTags.ini` in the `[GameplayTagsSettings]` section:
   ```ini
   +GameplayTagList=(Tag="<TagName>",DevComment="Restored from archive 2025-10-01")
   ```
3. Re-run headless startup + log scan scripts.

## Rationale for Removal
- Eliminates noise and prevents divergence between native and config-defined tags.
- Reduces risk of mismatched capitalization or legacy naming patterns.
- Encourages consolidation of heavily used tags into native C++ for compile-time safety and discoverability.

---
Generated on 2025-10-01.
