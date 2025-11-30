# UltraSky → DaySequence Modifier Pattern Refactor Plan

## Executive Summary

Refactor UltraSky's custom `UltraSkyWeatherToSequencerBridge` pattern to use DaySequence's proven `UDaySequenceModifierComponent` subsection-based approach. This eliminates custom override resolution code and leverages Unreal's native MovieScene subsection blending system.

---

## Current UltraSky Pattern (To Remove)

### Components
1. **UltraSkyWeatherToSequencerBridge** - Custom component that stores override values
2. **UUltraSkyWeatherManager** - Pushes preset values to bridge via `ApplyAttributeValueByName`
3. **UUltraSkyGASBridge** - Calls `ResolveSequencerOverride` to get blended values

### Flow
```
WeatherManager (Preset) 
  → SequencerBridge (Store Override) 
  → GASBridge calls ResolveSequencerOverride 
  → Returns blended value
  → Apply to GAS + Materials
```

### Problems
- Custom override resolution logic
- Manual value caching and blending
- Bridge component couples weather to sequencer
- No native Sequencer subsection support

---

## DaySequence Pattern (To Adopt)

### Components
1. **UDaySequenceModifierComponent** - Creates subsections in root sequence
2. **Volume/Global Modes** - Automatic blend weight calculation
3. **Native MovieScene Blending** - Sequencer handles all value blending

### Flow
```
ModifierComponent (User Sequence) 
  → Create SubSection in Root Sequence 
  → Set HierarchicalBias + BlendWeight 
  → Sequencer evaluates and blends 
  → Values propagate to bound tracks
```

### Benefits
- Uses Unreal's MovieScene subsection system
- Automatic hierarchical bias blending
- Volume-based blend weights built-in
- No custom override resolution code
- Editor preview support
- Proper subsection lifecycle management

---

## Refactor Steps

### 1. Create UltraSky Modifier Component

**New File:** `UltraSkyWeatherModifierComponent` (inherits `UDaySequenceModifierComponent`)

```cpp
UCLASS()
class UUltraSkyWeatherModifierComponent : public UDaySequenceModifierComponent
{
    GENERATED_BODY()
    
public:
    /** Bind to UltraSky actor instead of DaySequence actor */
    UFUNCTION(BlueprintCallable)
    void BindToUltraSkyActor(AUltraSkyActor* UltraSkyActor);
    
    /** Apply a weather preset as a transient sequence */
    UFUNCTION(BlueprintCallable)
    void ApplyWeatherPreset(UUltraSkyWeatherPreset* Preset, float TransitionDuration = 5.0f);
    
protected:
    /** Generate a transient sequence from preset values */
    UUltraSky* GenerateSequenceFromPreset(UUltraSkyWeatherPreset* Preset, float Duration);
};
```

### 2. Create Weather Modifier Volume

**New File:** `AUltraSkyWeatherModifierVolume` (similar to `ADaySequenceModifierVolume`)

```cpp
UCLASS()
class AUltraSkyWeatherModifierVolume : public AActor
{
    GENERATED_BODY()
    
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UUltraSkyWeatherModifierComponent> WeatherModifier;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UBoxComponent> VolumeShape;
    
    /** Weather preset to apply when player enters volume */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UUltraSkyWeatherPreset> WeatherPreset;
};
```

### 3. Update Weather Manager

**Modify:** `UUltraSkyWeatherManager::ApplyPreset`

```cpp
// OLD: Push to SequencerBridge + GAS
SequencerBridge->ApplyAttributeValueByName(Name, Value);
GASBridge->UpdateFromSequencerMap(Values);

// NEW: Generate transient sequence and bind to modifier
UUltraSky* TransientSeq = GenerateSequenceFromPreset(Preset, TransitionDuration);
WeatherModifier->SetTransientSequence(TransientSeq);
WeatherModifier->EnableModifier();
```

**Remove:**
- `SequencerBridge` property
- `ApplyAttributesToBridge` method
- All bridge-related initialization

### 4. Update GAS Bridge

**Modify:** `UUltraSkyGASBridge`

**Remove:**
- `SequencerBridge` property
- `ResolveSequencerOverride` method
- All override resolution logic

**Simplify:** Values come directly from sequencer evaluation (no custom resolution)

```cpp
// OLD: Resolve overrides manually
const float Resolved = ResolveSequencerOverride(VarName, BaseValue);

// NEW: Trust sequencer-evaluated values
// Sequencer handles blending via subsections automatically
```

### 5. Sequence Generation from Presets

**New Utility:** Create transient UUltraSky sequences from preset data

```cpp
UUltraSky* UUltraSkyWeatherModifierComponent::GenerateSequenceFromPreset(
    UUltraSkyWeatherPreset* Preset, float Duration)
{
    UUltraSky* Sequence = NewObject<UUltraSky>(this, NAME_None, RF_Transient);
    UMovieScene* MovieScene = Sequence->GetMovieScene();
    
    // Set playback range
    FFrameRate FrameRate(24, 1);
    int32 DurationFrames = Duration * FrameRate.AsDecimal();
    MovieScene->SetPlaybackRange(0, DurationFrames);
    
    // For each preset attribute, create a float track
    if (Preset->CloudCoverage >= 0.0f)
    {
        AddFloatTrack(MovieScene, "Cloud_GlobalCoverage", Preset->CloudCoverage);
    }
    if (Preset->CloudDensity >= 0.0f)
    {
        AddFloatTrack(MovieScene, "Cloud_GlobalDensity", Preset->CloudDensity);
    }
    // ... etc for all attributes
    
    return Sequence;
}

void UUltraSkyWeatherModifierComponent::AddFloatTrack(
    UMovieScene* MovieScene, FName TrackName, float Value)
{
    // Create bound float track for the variable
    UMovieSceneFloatTrack* Track = MovieScene->AddTrack<UMovieSceneFloatTrack>();
    Track->SetPropertyNameAndPath(TrackName, TrackName.ToString());
    
    UMovieSceneFloatSection* Section = Cast<UMovieSceneFloatSection>(Track->CreateNewSection());
    Section->SetRange(MovieScene->GetPlaybackRange());
    
    // Set constant value
    FMovieSceneFloatChannel* Channel = Section->GetChannelProxy().GetChannel<FMovieSceneFloatChannel>(0);
    Channel->SetDefault(Value);
    
    Track->AddSection(*Section);
}
```

### 6. Migration Path

**Phase 1:** Add new components alongside existing system
- Create `UUltraSkyWeatherModifierComponent`
- Create `AUltraSkyWeatherModifierVolume`
- Test with simple weather volumes

**Phase 2:** Update Weather Manager to use modifiers
- Add `WeatherModifier` property
- Implement preset → sequence generation
- Test preset transitions

**Phase 3:** Remove old bridge system
- Delete `UUltraSkyWeatherToSequencerBridge`
- Remove bridge references from GASBridge
- Clean up unused override resolution code

**Phase 4:** Documentation and examples
- Update setup guides
- Create weather volume examples
- Migrate existing projects

---

## Key Advantages

### 1. **Native Sequencer Integration**
- Subsections are first-class Sequencer citizens
- Editor shows weather overrides in timeline
- Preview works automatically

### 2. **Hierarchical Bias System**
- Multiple weather modifiers can coexist
- Automatic priority resolution
- No custom blend logic needed

### 3. **Volume-Based Blending**
- Built-in distance-to-volume blending
- Smooth transitions across boundaries
- Easing functions included

### 4. **Simplified Architecture**
- Removes 300+ lines of bridge code
- No manual override caching
- Sequencer does the heavy lifting

### 5. **Consistency with Ecosystem**
- Uses same pattern as DaySequence
- Familiar to developers using day/night
- Can leverage existing tools/examples

---

## Files to Modify

### Delete
- `UltraSkyWeatherToSequencerBridge.h/.cpp`
- `docs/UltraSky_WeatherSequencerBridge.md`

### Create
- `UltraSkyWeatherModifierComponent.h/.cpp`
- `AUltraSkyWeatherModifierVolume.h/.cpp`
- `docs/UltraSky_Weather_Modifiers.md`

### Modify
- `UltraSkyWeatherManager.h/.cpp` (remove bridge, add modifier)
- `UltraSkyGASBridge.h/.cpp` (remove override resolution)
- `UltraSkyActor.h/.cpp` (if binding modifier to actor)
- `UltraSkyEditorModule.cpp` (remove bridge setup, add modifier setup)

---

## Testing Checklist

- [ ] Weather presets create valid subsections
- [ ] Preset transitions blend smoothly
- [ ] Volume blend weights calculate correctly
- [ ] Multiple modifiers respect hierarchical bias
- [ ] GAS attributes receive correct values
- [ ] Material parameters update properly
- [ ] Network replication works (server authority)
- [ ] Editor preview shows modifiers
- [ ] Existing maps migrate cleanly

---

## Risks & Mitigations

| Risk | Impact | Mitigation |
|------|--------|-----------|
| Subsection creation overhead | Performance | Pool/reuse transient sequences |
| Preset → Sequence conversion complexity | Development time | Start with scalar tracks only, add curves later |
| Breaking existing projects | User frustration | Provide migration guide + compatibility shim |
| Learning curve for volumes | Adoption | Create tutorial content + example map |

---

## Timeline Estimate

- **Phase 1** (Components): 2-3 days
- **Phase 2** (Manager Integration): 2-3 days  
- **Phase 3** (Remove Bridge): 1 day
- **Phase 4** (Documentation): 1-2 days

**Total: ~1 week** for complete refactor + testing

---

## Conclusion

Adopting the DaySequence modifier pattern eliminates custom code, leverages proven Unreal systems, and provides a better developer experience. The refactor is straightforward because UltraSky already has the infrastructure (presets, weather manager, GAS bridge) - we're just changing *how* values flow from presets to the sequencer.
