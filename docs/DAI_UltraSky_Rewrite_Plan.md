# DAI_UltraSky Complete Rewrite Plan
## Based on DaySequence Plugin Template Architecture

**Purpose:** Restructure DAI_UltraSky to follow Epic's DaySequence plugin patterns for better editor integration, sequencer support, modularity, and maintainability.

**Status:** Architecture Planning Phase  
**Last Updated:** November 4, 2025  
**Target Engine:** UE 5.5+

---

## Table of Contents

1. [Executive Summary](#executive-summary)
2. [Current Architecture Analysis](#current-architecture-analysis)
3. [DaySequence Template Patterns](#daysequence-template-patterns)
4. [Proposed New Architecture](#proposed-new-architecture)
5. [Module Structure](#module-structure)
6. [Core Classes Mapping](#core-classes-mapping)
7. [Editor Integration](#editor-integration)
8. [Migration Strategy](#migration-strategy)
9. [Implementation Phases](#implementation-phases)
10. [API Compatibility](#api-compatibility)
11. [Testing Strategy](#testing-strategy)

---

## Executive Summary

### Why Rewrite?

**Current Pain Points:**
- Monolithic ADAIUltraSkyActor (4700+ lines) doing too much
- Manual component binding/spawning logic fragile and crash-prone
- No sequencer integration for cinematic time-of-day control
- Editor tools scattered; no unified workflow
- GAS integration mixed with rendering concerns
- Difficult to extend or modify without touching core actor

**DaySequence Benefits:**
- Clean separation: Player → Subsystem → Provider → Modifiers
- Sequencer integration out-of-the-box (keyframe sun, weather, etc.)
- Provider pattern allows multiple environment actors
- Modifier components for modular features (weather volumes, biomes)
- Dedicated editor module with custom toolkit
- Cheat manager extensions for runtime testing

### Goals

1. **Modularity:** Separate time-of-day, weather, rendering, and gameplay concerns
2. **Editor UX:** Unified sequencer timeline for all sky properties
3. **Performance:** Better tick management via subsystem + modifiers
4. **Extensibility:** Plugin-friendly architecture (biomes, weather as separate systems)
5. **Compatibility:** Maintain GAS attribute exposure; provide migration path

---

## Current Architecture Analysis

### Existing Structure

```
DAI_UltraSky/
├── Source/DAI_UltraSky/           (Runtime only)
│   ├── Public/
│   │   ├── DAIUltraSkyActor.h     ← MONOLITH (1063 lines header, 4738 lines cpp)
│   │   ├── DAIUltraSkyAttributeSet.h
│   │   ├── DAIUltraSkyBiomeData.h
│   │   ├── DAIUltraSkyBiomeVolume.h
│   │   ├── DAIUltraSkyWeatherPreset.h
│   │   ├── DAIUltraSkyWeatherOverrideVolume.h
│   │   ├── Services/DAI_WeatherService.h
│   │   ├── AbilitySystem/ (GA_*, Tags)
│   │   └── StateTree/ (Weather state tree nodes)
│   └── Private/
│       └── (corresponding .cpp files)
└── (no Editor module)
```

### Key Responsibilities (All in One Actor)

1. **Time Management:** TimeOfDay cycle, day length, physical sun positioning
2. **Component Management:** Sun, Moon, Sky, Atmosphere, Clouds, Fog (spawn or bind)
3. **Weather System:** Presets, transitions, biome blending, GAS attributes
4. **Rendering:** Cloud MIDs, MPC updates, material parameters
5. **Effects:** Lightning, meteor storms, tornados (via GAS abilities)
6. **Replication:** Networked weather state, attribute changes
7. **Debug:** On-screen overlay, console commands
8. **Editor:** OnConstruction binding, property refresh hacks

### Problems

- **Tight Coupling:** Can't change weather without touching time-of-day or rendering
- **Testing:** Hard to test weather logic without full actor
- **Sequencer:** No way to keyframe time or weather in cinematics
- **Editor:** No custom UI; all properties in Details panel (cluttered)
- **Crashes:** Rename logic, component binding race conditions
- **GAS Overhead:** ASC required even if only using time-of-day

---

## DaySequence Template Patterns

### Architecture Overview

```
DaySequence Plugin
├── Runtime Module (DaySequence)
│   ├── ADaySequenceActor (Info actor, orchestrator)
│   ├── UDaySequencePlayer (Sequence playback, IMovieScenePlayer)
│   ├── UDaySequenceSubsystem (WorldSubsystem, singleton per level)
│   ├── ADaySequenceProvider (Base for environment actors)
│   ├── UDaySequenceModifierComponent (Extensible modifiers)
│   ├── UDaySequence (Asset, MovieSceneSequence)
│   └── Tracks/Sections (Custom sequencer tracks)
└── Editor Module (DaySequenceEditor)
    ├── FDaySequenceEditorModule
    ├── FDaySequenceEditorToolkit (Custom asset editor)
    ├── Track Editors (Sequencer UI extensions)
    └── Details Customizations
```

### Key Patterns

#### 1. **Subsystem Pattern**

- `UDaySequenceSubsystem` (WorldSubsystem)
  - Singleton per world
  - Registers/unregisters DaySequenceActor
  - Provides global access: `GetWorld()->GetSubsystem<UDaySequenceSubsystem>()`
  - Broadcasts events when active actor changes
  - Cheat manager extensions

**Application to UltraSky:**
- `UUltraSkySubsystem` (WorldSubsystem)
  - Track active UltraSky actor per level
  - Manage weather state transitions globally
  - Coordinate biome volumes and weather overrides
  - Expose Blueprint/C++ API for gameplay queries

#### 2. **Provider Pattern**

- `ADaySequenceProvider` (base class)
  - `AEnvironmentLightingActor` (concrete provider with components)
  - Owns components: SkyAtmosphere, SkyLight, Sun, Fog, Clouds
  - Sequencer can keyframe component properties
  - Multiple providers can exist (different lighting setups)

**Application to UltraSky:**
- `AUltraSkyProvider` (base, replaces current monolithic actor)
  - Owns core components (Sun, Moon, Sky, Atmosphere, Clouds, Fog)
  - Minimal logic (just component ownership + sequencer interface)
  - Variants: `AUltraSkyEnvironmentActor` (full), `AUltraSkyLightingOnly` (minimal)

#### 3. **Modifier Component Pattern**

- `UDaySequenceModifierComponent`
  - Attached to actors to add behaviors
  - Modifies sequence playback or adds constraints
  - Examples: `UDaySequenceConditionModifier`, `UDaySequenceTimeModifier`

**Application to UltraSky:**
- `UUltraSkyModifierComponent` (base)
  - `UUltraSkyBiomeModifier` (attached to volumes, modifies weather/atmosphere by region)
  - `UUltraSkyWeatherOverrideModifier` (force local weather)
  - `UUltraSkyClimateModifier` (seasonal/temperature curves)
  - `UUltraSkyLightningModifier` (trigger lightning in radius)

#### 4. **Sequence Asset + Player**

- `UDaySequence` (asset, inherits UMovieSceneSequence)
  - Contains tracks for time-of-day, sun angle, fog density, etc.
  - Keyframeable in Sequencer
- `UDaySequencePlayer` (runtime playback)
  - Implements IMovieScenePlayer
  - Drives sequence evaluation each tick
  - Networked playback state

**Application to UltraSky:**
- `UUltraSkySequence` (asset)
  - Tracks: TimeOfDay, SunPitch/Yaw, CloudCoverage, FogDensity, Temperature, etc.
  - Can reference weather presets by GameplayTag
- `UUltraSkySequencePlayer`
  - Tick-driven playback
  - Optional GAS attribute bindings (expose tracks → attributes)

#### 5. **Editor Toolkit**

- `FDaySequenceEditorToolkit`
  - Custom asset editor for UDaySequence
  - Embeds Sequencer widget
  - Toolbar actions: preview time, snap to sunrise/sunset
- Track editors for custom properties

**Application to UltraSky:**
- `FUltraSkySequenceEditorToolkit`
  - Timeline UI for weather + time-of-day
  - Weather preset selector
  - Live preview in editor viewport
  - Biome/climate curve editors

---

## Proposed New Architecture

### High-Level Design

```
DAI_UltraSky (Rewrite)
├── DAI_UltraSky (Runtime)
│   ├── Subsystem/
│   │   └── UUltraSkySubsystem (WorldSubsystem)
│   ├── Actors/
│   │   ├── AUltraSkyProvider (base)
│   │   ├── AUltraSkyEnvironmentActor (full sky components)
│   │   └── AUltraSkyLightingOnlyActor (sun/moon only)
│   ├── Components/
│   │   ├── UUltraSkyModifierComponent (base)
│   │   ├── UUltraSkyBiomeModifier
│   │   ├── UUltraSkyWeatherOverrideModifier
│   │   ├── UUltraSkyClimateModifier
│   │   └── UUltraSkyLightningModifier
│   ├── Sequence/
│   │   ├── UUltraSkySequence (asset)
│   │   ├── UUltraSkySequencePlayer (runtime player)
│   │   └── Tracks/ (custom sequencer tracks)
│   ├── Weather/
│   │   ├── UUltraSkyWeatherPreset (DataAsset)
│   │   ├── UUltraSkyWeatherLibrary (static functions)
│   │   └── FUltraSkyWeatherState (struct)
│   ├── Biomes/
│   │   ├── UUltraSkyBiomeData (DataAsset)
│   │   ├── AUltraSkyBiomeVolume (volume)
│   │   └── UUltraSkyClimatePreset (DataAsset)
│   └── GAS/ (optional, decoupled)
│       ├── UUltraSkyAttributeSet
│       ├── UUltraSkyAbilityManager
│       └── GA_UltraSky_* (abilities)
└── DAI_UltraSkyEditor (Editor)
    ├── Toolkit/
    │   └── FUltraSkySequenceEditorToolkit
    ├── Customizations/
    │   ├── FUltraSkyProviderDetails
    │   └── FUltraSkyModifierDetails
    ├── TrackEditors/
    │   ├── FUltraSkyTimeOfDayTrackEditor
    │   ├── FUltraSkyWeatherTrackEditor
    │   └── FUltraSkyCelestialTrackEditor
    └── UI/
        └── SUltraSkySequencerToolbar
```

### Separation of Concerns

| **Concern**             | **Old (Monolith)**              | **New (Modular)**                          |
|-------------------------|---------------------------------|-------------------------------------------|
| Time of Day             | ADAIUltraSkyActor               | UUltraSkySequencePlayer + Track           |
| Component Ownership     | ADAIUltraSkyActor               | AUltraSkyProvider subclasses              |
| Weather Logic           | ADAIUltraSkyActor               | UUltraSkySubsystem + Weather Presets      |
| Biome Blending          | ADAIUltraSkyActor + Volumes     | UUltraSkyBiomeModifier + Subsystem        |
| GAS Integration         | Tightly coupled in Actor        | Optional UUltraSkyAbilityManager service  |
| Effects (Lightning)     | GA_ abilities in Actor          | UUltraSkyLightningModifier + Niagara      |
| Editor Preview          | Hacks in OnConstruction         | FUltraSkySequenceEditorToolkit            |
| Replication             | Custom NetSerialize in Actor    | Sequencer replication + Subsystem state   |

---

## Module Structure

### 1. DAI_UltraSky (Runtime)

**Purpose:** Core runtime systems (no editor dependencies)

**Build.cs Dependencies:**
```csharp
PublicDependencyModuleNames.AddRange(new string[] {
    "Core", "CoreUObject", "Engine", 
    "MovieScene", "MovieSceneTracks", "LevelSequence",
    "Niagara", "GameplayTags"
});

PrivateDependencyModuleNames.AddRange(new string[] {
    "RenderCore", "RHI", "Projects"
});

// Optional (if GAS integration enabled)
if (Target.bBuildEditor || bEnableGAS)
{
    PublicDependencyModuleNames.Add("GameplayAbilities");
}
```

**Key Classes:**

- **Subsystem:** `UUltraSkySubsystem`
- **Providers:** `AUltraSkyProvider`, `AUltraSkyEnvironmentActor`
- **Player:** `UUltraSkySequencePlayer`, implements `IMovieScenePlayer`
- **Sequence Asset:** `UUltraSkySequence` (inherits `UMovieSceneSequence`)
- **Modifiers:** `UUltraSkyModifierComponent` + subclasses
- **Tracks:** `UMovieSceneUltraSkyTimeTrack`, `UMovieSceneUltraSkyWeatherTrack`
- **Data:** Weather presets, biome data, climate presets

### 2. DAI_UltraSkyEditor (Editor)

**Purpose:** Sequencer integration, custom editors, details panels

**Build.cs Dependencies:**
```csharp
PrivateDependencyModuleNames.AddRange(new string[] {
    "DAI_UltraSky", // Runtime module
    "UnrealEd", "Slate", "SlateCore", "ToolMenus",
    "Sequencer", "MovieSceneTools", "LevelSequenceEditor",
    "PropertyEditor", "DetailCustomizations",
    "AssetTools", "ContentBrowser"
});
```

**Key Classes:**

- **Module:** `FDAIUltraSkyEditorModule`
- **Toolkit:** `FUltraSkySequenceEditorToolkit` (asset editor for UUltraSkySequence)
- **Track Editors:** Sequencer UI for custom tracks
- **Details:** Customizations for Provider actor and Modifier components
- **Factories:** `UUltraSkySequenceFactoryNew` (Content Browser "Add New" menu)

---

## Core Classes Mapping

### ADAIUltraSkyActor → Multiple Classes

| **Old Responsibility**                     | **New Class(es)**                                                                 |
|--------------------------------------------|-----------------------------------------------------------------------------------|
| Component ownership (Sun, Moon, Sky, etc.) | `AUltraSkyProvider` → `AUltraSkyEnvironmentActor`                                 |
| Time-of-day cycle                          | `UUltraSkySequencePlayer` + `UMovieSceneUltraSkyTimeTrack`                        |
| Weather preset application                 | `UUltraSkySubsystem` + `UUltraSkyWeatherPreset`                                   |
| Biome blending                             | `UUltraSkyBiomeModifier` (component on volumes) + Subsystem coordinator           |
| GAS attributes                             | `UUltraSkyAttributeSet` + optional `UUltraSkyAbilityManagerComponent`             |
| Lightning/effects                          | `UUltraSkyLightningModifier` + Niagara systems                                    |
| Cloud MID/MPC updates                      | `AUltraSkyProvider::UpdateMaterialParameters()` (called by sequence player)       |
| Replication                                | Sequencer networked playback + Subsystem state replication                        |
| Debug display                              | Subsystem + modifier debug entries (registered via `FUltraSkyDebugEntry`)         |
| Editor preview                             | `FUltraSkySequenceEditorToolkit` + preview world                                  |

### New Class Details

#### UUltraSkySubsystem (WorldSubsystem)

```cpp
UCLASS()
class DAYSEQUENCE_API UUltraSkySubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    // Subsystem interface
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    virtual bool DoesSupportWorldType(EWorldType::Type WorldType) const override;

    // Active provider management
    UFUNCTION(BlueprintCallable)
    AUltraSkyProvider* GetActiveProvider() const;

    UFUNCTION(BlueprintCallable)
    void SetActiveProvider(AUltraSkyProvider* NewProvider);

    // Weather state (replicated via subsystem)
    UFUNCTION(BlueprintCallable)
    FUltraSkyWeatherState GetCurrentWeatherState() const;

    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
    void SetWeatherPreset(UUltraSkyWeatherPreset* Preset, float TransitionDuration);

    // Biome queries
    UFUNCTION(BlueprintCallable)
    UUltraSkyBiomeData* GetBiomeAtLocation(FVector WorldLocation) const;

    // Time queries (delegates to sequence player if active)
    UFUNCTION(BlueprintCallable)
    float GetTimeOfDay() const;

    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
    void SetTimeOfDay(float Hours);

    // Event broadcasts
    UPROPERTY(BlueprintAssignable)
    FOnUltraSkyProviderChanged OnProviderChanged;

    UPROPERTY(BlueprintAssignable)
    FOnWeatherStateChanged OnWeatherStateChanged;

private:
    TWeakObjectPtr<AUltraSkyProvider> ActiveProvider;
    FUltraSkyWeatherState CurrentWeatherState;
    TArray<TWeakObjectPtr<AUltraSkyBiomeVolume>> RegisteredBiomes;

    void OnLevelActorAdded(AActor* Actor);
    void OnLevelActorRemoved(AActor* Actor);
};
```

#### AUltraSkyProvider (Base)

```cpp
UCLASS(Abstract)
class DAYSEQUENCE_API AUltraSkyProvider : public AInfo
{
    GENERATED_BODY()

public:
    AUltraSkyProvider(const FObjectInitializer& Init);

    // Component accessors (pure virtual in base, implemented by subclasses)
    virtual USkyAtmosphereComponent* GetSkyAtmosphere() const PURE_VIRTUAL(AUltraSkyProvider::GetSkyAtmosphere, return nullptr;);
    virtual USkyLightComponent* GetSkyLight() const PURE_VIRTUAL(AUltraSkyProvider::GetSkyLight, return nullptr;);
    virtual UDirectionalLightComponent* GetSunLight() const PURE_VIRTUAL(AUltraSkyProvider::GetSunLight, return nullptr;);
    virtual UDirectionalLightComponent* GetMoonLight() const { return nullptr; } // Optional
    virtual UVolumetricCloudComponent* GetVolumetricClouds() const { return nullptr; } // Optional
    virtual UExponentialHeightFogComponent* GetFog() const { return nullptr; } // Optional

    // Sequencer binding interface
    virtual UObject* GetSequenceBindingContext() const { return (UObject*)this; }

    // Material parameter updates (called by sequence player after evaluation)
    virtual void UpdateMaterialParameters(const FUltraSkyEvaluatedState& State);

protected:
    // Registered with subsystem on BeginPlay
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
```

#### AUltraSkyEnvironmentActor (Concrete Provider)

```cpp
UCLASS(Blueprintable)
class DAYSEQUENCE_API AUltraSkyEnvironmentActor : public AUltraSkyProvider
{
    GENERATED_BODY()

public:
    AUltraSkyEnvironmentActor(const FObjectInitializer& Init);

    // Components (public, sequencer can keyframe)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<USkyAtmosphereComponent> SkyAtmosphere;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<USkyLightComponent> SkyLight;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<USceneComponent> SunRoot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UDirectionalLightComponent> SunLight;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<USceneComponent> MoonRoot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UDirectionalLightComponent> MoonLight;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UVolumetricCloudComponent> VolumetricClouds;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UExponentialHeightFogComponent> Fog;

    // Optional: Moon mesh, star dome (cosmetic, not sequencer-driven)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UStaticMeshComponent> MoonMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UStaticMeshComponent> StarDome;

    // Override accessors
    virtual USkyAtmosphereComponent* GetSkyAtmosphere() const override { return SkyAtmosphere; }
    virtual USkyLightComponent* GetSkyLight() const override { return SkyLight; }
    virtual UDirectionalLightComponent* GetSunLight() const override { return SunLight; }
    virtual UDirectionalLightComponent* GetMoonLight() const override { return MoonLight; }
    virtual UVolumetricCloudComponent* GetVolumetricClouds() const override { return VolumetricClouds; }
    virtual UExponentialHeightFogComponent* GetFog() const override { return Fog; }

protected:
    virtual void UpdateMaterialParameters(const FUltraSkyEvaluatedState& State) override;
};
```

#### UUltraSkySequencePlayer

```cpp
UCLASS()
class DAYSEQUENCE_API UUltraSkySequencePlayer : public UObject, public IMovieScenePlayer
{
    GENERATED_BODY()

public:
    // Initialize with sequence asset
    void Initialize(UUltraSkySequence* InSequence, AUltraSkyProvider* InProvider);

    // Tick-driven evaluation
    void Tick(float DeltaTime);

    // Time control
    UFUNCTION(BlueprintCallable)
    void SetTimeOfDay(float Hours);

    UFUNCTION(BlueprintCallable)
    float GetTimeOfDay() const;

    UFUNCTION(BlueprintCallable)
    void SetDayLength(float Seconds);

    // Playback control
    UFUNCTION(BlueprintCallable)
    void Play();

    UFUNCTION(BlueprintCallable)
    void Pause();

    // IMovieScenePlayer interface
    virtual UObject* GetPlaybackContext() const override;
    virtual TArray<UObject*> GetEventContexts() const override;
    // ... (other IMovieScenePlayer methods)

private:
    UPROPERTY()
    TObjectPtr<UUltraSkySequence> Sequence;

    TWeakObjectPtr<AUltraSkyProvider> Provider;

    FMovieSceneRootEvaluationTemplateInstance RootTemplateInstance;
    FUltraSkyEvaluatedState LastEvaluatedState;

    float CurrentTimeHours;
    float DayLengthSeconds;
    bool bIsPlaying;
};
```

#### UUltraSkyModifierComponent (Base)

```cpp
UCLASS(Abstract, Blueprintable)
class DAYSEQUENCE_API UUltraSkyModifierComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Called by subsystem after sequence evaluation, before applying to provider
    virtual void ModifyState(FUltraSkyEvaluatedState& InOutState) {}

    // Priority (lower = earlier)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Modifier")
    int32 Priority = 100;

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
```

#### UUltraSkyBiomeModifier (Example Subclass)

```cpp
UCLASS(ClassGroup=(UltraSky), meta=(BlueprintSpawnableComponent))
class DAYSEQUENCE_API UUltraSkyBiomeModifier : public UUltraSkyModifierComponent
{
    GENERATED_BODY()

public:
    // Biome data to apply when actor is in this volume
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Biome")
    TObjectPtr<UUltraSkyBiomeData> BiomeData;

    // Blend weight (distance-based fade)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Biome")
    float BlendRadius = 5000.0f;

    virtual void ModifyState(FUltraSkyEvaluatedState& InOutState) override;

private:
    float ComputeBlendWeight(FVector QueryLocation) const;
};
```

---

## Editor Integration

### Sequencer Tracks

#### 1. UMovieSceneUltraSkyTimeTrack

**Purpose:** Keyframe time-of-day (hours 0-24)

**Sections:**
- `UMovieSceneUltraSkyTimeSection`
  - Float curve for Hours
  - Optional: sunrise/sunset markers

**Track Editor:**
- `FUltraSkyTimeTrackEditor`
  - Custom icons, colors
  - Toolbar buttons: "Snap to Sunrise", "Snap to Sunset", "Add Day Cycle"

#### 2. UMovieSceneUltraSkyWeatherTrack

**Purpose:** Keyframe weather properties (cloud coverage, fog density, wind, etc.)

**Sections:**
- `UMovieSceneUltraSkyWeatherSection`
  - Float curves: CloudCoverage, CloudDensity, FogDensity, Temperature, WindSpeed
  - Optional: Weather preset selector (tag-based)

**Track Editor:**
- `FUltraSkyWeatherTrackEditor`
  - Custom UI for preset selection
  - Preview weather in editor viewport

#### 3. UMovieSceneUltraSkyCelestialTrack

**Purpose:** Keyframe sun/moon properties (not needed if using time → rotation binding)

**Sections:**
- `UMovieSceneUltraSkyCelestialSection`
  - Float curves: SunPitch, SunYaw, MoonPhase, StarVisibility

**Track Editor:**
- `FUltraSkyCelestialTrackEditor`

### Custom Asset Editor

#### FUltraSkySequenceEditorToolkit

**Features:**
- Embedded Sequencer widget (shows all UltraSky tracks)
- Toolbar:
  - "Preview Time" slider (scrub time in editor viewport)
  - "Play/Pause" (live preview)
  - "Snap to Sunrise/Noon/Sunset/Midnight"
  - "Add Weather Preset Keyframe"
- Outliner:
  - Shows bound provider actor
  - Lists all active modifiers
- Details:
  - Selected keyframe properties
  - Weather preset details (when preset keyframe selected)

### Details Customizations

#### FUltraSkyProviderDetails

**Purpose:** Custom layout for `AUltraSkyEnvironmentActor` Details panel

**Features:**
- Component group (collapsible)
- "Open in Sequencer" button
- Quick actions: "Reset to Defaults", "Capture Current State as Preset"

#### FUltraSkyModifierDetails

**Purpose:** Custom layout for modifier components

**Features:**
- Priority slider with visual indicator
- "Test Modifier" button (force apply in editor)
- Debug visualization toggle

---

## Migration Strategy

### Phase 1: Coexistence (Compatibility Layer)

**Goal:** New architecture available alongside old monolith; users can migrate at their own pace.

**Approach:**

1. **Rename old actor:** `ADAIUltraSkyActor` → `ADAIUltraSkyActorLegacy` (deprecated)
2. **Create adapter:** `ADAIUltraSkyActorV2` (thin wrapper around new subsystem + provider)
   - Exposes old API (ForceApplyBiome, etc.)
   - Internally delegates to subsystem
   - Includes deprecation warnings in logs
3. **Content migration tool:** Editor utility widget to convert old actors to new providers

**Benefits:**
- Existing projects don't break
- Can test new system in same level
- Gradual migration

### Phase 2: Deprecation (1-2 releases later)

**Goal:** Encourage migration; mark legacy clearly.

**Actions:**
- Log warnings on legacy actor BeginPlay
- Add editor notification: "This actor is deprecated. Use Migration Tool."
- Update docs/examples to new system only

### Phase 3: Removal (Major version bump)

**Goal:** Clean codebase; remove legacy.

**Actions:**
- Delete legacy classes
- Content redirectors for old class names → new providers
- Final migration tool run

---

## Implementation Phases

### Phase 1: Foundation (2-3 weeks)

**Goals:**
- Module structure
- Subsystem + Provider pattern
- Basic sequence playback

**Tasks:**
1. Create module scaffolding (Runtime + Editor)
2. Implement `UUltraSkySubsystem`
3. Implement `AUltraSkyProvider` (abstract) + `AUltraSkyEnvironmentActor`
4. Implement `UUltraSkySequence` (asset boilerplate)
5. Implement `UUltraSkySequencePlayer` (basic tick + time-of-day)
6. Hook subsystem into world lifecycle

**Deliverable:** Can place provider actor, subsystem registers it, time-of-day updates sun rotation.

### Phase 2: Sequencer Integration (2-3 weeks)

**Goals:**
- Custom tracks visible in Sequencer
- Keyframe time + weather properties

**Tasks:**
1. Implement `UMovieSceneUltraSkyTimeTrack` + Section
2. Implement `FUltraSkyTimeTrackEditor` (Sequencer UI)
3. Implement `UMovieSceneUltraSkyWeatherTrack` + Section
4. Implement `FUltraSkyWeatherTrackEditor`
5. Register track editors with Sequencer module
6. Test: keyframe time, scrub in editor, see sun move

**Deliverable:** Can create UUltraSkySequence asset, add tracks, keyframe properties, preview in editor.

### Phase 3: Modifiers (2 weeks)

**Goals:**
- Component-based extensibility
- Biome blending working

**Tasks:**
1. Implement `UUltraSkyModifierComponent` (base)
2. Implement `UUltraSkyBiomeModifier` (component on volumes)
3. Implement modifier registration in subsystem
4. Implement priority sorting + state modification pipeline
5. Test: place biome volume, attach modifier, see blended weather

**Deliverable:** Biome volumes work; modifiers can override weather.

### Phase 4: Editor Toolkit (2 weeks)

**Goals:**
- Custom asset editor for UUltraSkySequence
- Polish editor UX

**Tasks:**
1. Implement `FUltraSkySequenceEditorToolkit`
2. Embed Sequencer widget
3. Add toolbar (time scrubber, play/pause, snap buttons)
4. Implement details customizations (Provider, Modifier)
5. Add Content Browser factory (New UUltraSkySequence)
6. Test: double-click sequence, edit in custom editor, save

**Deliverable:** UUltraSkySequence has dedicated editor; feels like Level Sequence workflow.

### Phase 5: GAS Integration (Optional, 1 week)

**Goals:**
- Expose weather state as GAS attributes
- Decouple from core (optional plugin dependency)

**Tasks:**
1. Move GAS code to separate module or plugin (`DAI_UltraSky_GAS`)
2. Implement `UUltraSkyAbilityManagerComponent` (optional component on provider)
3. Bridge: sequence player → attributes
4. Test: abilities can read/modify weather

**Deliverable:** GAS users can opt-in; non-GAS users have zero overhead.

### Phase 6: Weather Effects (1-2 weeks)

**Goals:**
- Lightning, meteor storms, tornados as modifiers
- Niagara integration

**Tasks:**
1. Implement `UUltraSkyLightningModifier` (triggers Niagara lightning)
2. Implement `UUltraSkyMeteorModifier` (spawn meteors)
3. Implement `UUltraSkyTornadoModifier` (radial storm)
4. Hook into weather state (auto-trigger based on conditions)
5. Test: heavy rain → lightning

**Deliverable:** Weather effects modular; can be added/removed via components.

### Phase 7: Migration Tool (1 week)

**Goals:**
- Convert old actors to new providers
- Content upgrade path

**Tasks:**
1. Implement Editor Utility Widget: "UltraSky Migration Tool"
2. Scan level for `ADAIUltraSkyActorLegacy`
3. For each: spawn `AUltraSkyEnvironmentActor`, copy properties, delete old
4. Convert biome volumes (attach modifiers)
5. Test: migrate sample project

**Deliverable:** Users can migrate projects with one click.

### Phase 8: Polish & Docs (1-2 weeks)

**Goals:**
- Complete documentation
- Example content
- Performance testing

**Tasks:**
1. Write comprehensive plugin README
2. Create example maps (Day/Night Cycle, Weather Presets, Biomes, Cinematics)
3. Record tutorial videos (optional)
4. Performance profiling + optimization
5. Final bug fixes

**Deliverable:** Production-ready plugin with full docs.

---

## API Compatibility

### Blueprint API Mapping

| **Legacy API**                                         | **New API (Subsystem)**                                          |
|--------------------------------------------------------|------------------------------------------------------------------|
| `ADAIUltraSkyActor::SetTimeOfDay(float)`              | `UUltraSkySubsystem::SetTimeOfDay(float)`                        |
| `ADAIUltraSkyActor::GetTimeOfDay()`                   | `UUltraSkySubsystem::GetTimeOfDay()`                             |
| `ADAIUltraSkyActor::ForceApplyBiome(UBiomeData*)`     | `UUltraSkySubsystem::SetWeatherPreset(UWeatherPreset*, float)`   |
| `ADAIUltraSkyActor::TriggerLightning()`               | Attach `UUltraSkyLightningModifier` or call modifier function    |
| `ADAIUltraSkyActor::GetCloudCoverage()`               | `UUltraSkySubsystem::GetCurrentWeatherState().CloudCoverage`     |

### C++ API Mapping

```cpp
// Legacy
ADAIUltraSkyActor* Sky = ...; // find in level
Sky->SetTimeOfDay(12.0f);

// New
UUltraSkySubsystem* Subsystem = World->GetSubsystem<UUltraSkySubsystem>();
Subsystem->SetTimeOfDay(12.0f);
```

### Adapter Class (Compatibility Shim)

```cpp
UCLASS(Deprecated)
class ADAIUltraSkyActorV2 : public AActor
{
    GENERATED_BODY()

public:
    // Old API (deprecated but functional)
    UFUNCTION(BlueprintCallable, meta=(DeprecatedFunction, DeprecationMessage="Use UUltraSkySubsystem instead"))
    void SetTimeOfDay(float Hours)
    {
        if (UUltraSkySubsystem* Subsystem = GetWorld()->GetSubsystem<UUltraSkySubsystem>())
        {
            Subsystem->SetTimeOfDay(Hours);
        }
    }

    // ... (other shim methods)
};
```

---

## Testing Strategy

### Unit Tests

**Module:** `DAI_UltraSkTests` (separate test module)

**Coverage:**
- Subsystem registration/unregistration
- Sequence player time calculations
- Modifier priority sorting
- Weather state blending (biome + override)
- Sequence asset serialization

**Example:**
```cpp
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUltraSkySubsystemTest, "UltraSky.Subsystem.RegisterProvider", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FUltraSkySubsystemTest::RunTest(const FString& Parameters)
{
    UWorld* World = GetTestWorld();
    UUltraSkySubsystem* Subsystem = World->GetSubsystem<UUltraSkySubsystem>();
    TestNotNull("Subsystem should exist", Subsystem);

    AUltraSkyEnvironmentActor* Provider = World->SpawnActor<AUltraSkyEnvironmentActor>();
    Subsystem->SetActiveProvider(Provider);

    TestEqual("Active provider set", Subsystem->GetActiveProvider(), Provider);

    return true;
}
```

### Integration Tests

**Scenarios:**
1. Place provider actor → subsystem auto-registers
2. Create sequence asset → can add tracks → can keyframe
3. Play sequence → provider components update
4. Place biome volume with modifier → weather blends near volume
5. Replicate sequence playback → clients see synchronized time

### Editor Tests

**Manual QA Checklist:**
- [ ] Create UUltraSkySequence asset via Content Browser
- [ ] Open sequence in custom editor (double-click)
- [ ] Add Time track, keyframe 0-24 hours
- [ ] Scrub timeline → sun rotates in editor viewport
- [ ] Add Weather track, keyframe CloudCoverage
- [ ] Play in PIE → time advances, clouds appear
- [ ] Place provider in level with existing Light Mixer sun → no conflicts
- [ ] Attach biome modifier to volume → entering volume changes weather
- [ ] Use migration tool on legacy actor → converts to new provider
- [ ] Network test: server sets time → clients see same sun position

---

## Benefits Summary

### For Developers

- **Modularity:** Easy to add new weather effects, tracks, or modifiers without touching core
- **Testability:** Can unit test subsystem, player, modifiers in isolation
- **Maintainability:** 10 small classes vs. 1 giant actor
- **Extensibility:** Plugin authors can add custom tracks, modifiers without forking

### For Designers

- **Sequencer Workflow:** Familiar timeline UI for time-of-day + weather
- **Keyframing:** Can keyframe any weather property for cinematics
- **Live Preview:** Scrub timeline in editor, see changes instantly
- **Presets:** Drag-drop weather presets onto timeline

### For Technical Artists

- **Material Control:** MPC updates hooked into sequence evaluation
- **Niagara Integration:** Weather modifiers can spawn/control Niagara systems
- **Flexibility:** Can have multiple providers with different setups (day/night variants)

### For Gameplay Programmers

- **GAS Optional:** Can use UltraSky without GAS; GAS users opt-in via component
- **Clean API:** Subsystem provides global access; no actor-finding needed
- **Events:** Subscribe to weather changes, time changes via delegates

---

## Open Questions / Decisions Needed

1. **GAS Integration:**
   - Keep in core module (conditional compilation)?
   - Separate plugin (`DAI_UltraSky_GAS`)?
   - **Recommendation:** Separate optional plugin for clean dependency graph.

2. **Weather Presets:**
   - Still DataAssets?
   - Move to tracks as "preset keyframes"?
   - **Recommendation:** Hybrid—presets are assets; can keyframe preset selection on track.

3. **Replication:**
   - Rely on Sequencer's built-in network sync?
   - Custom subsystem state replication?
   - **Recommendation:** Use Sequencer replication for time; custom for weather state (lower bandwidth).

4. **Backward Compatibility:**
   - How long support legacy actor?
   - **Recommendation:** 2 releases (coexistence) → deprecation warnings → removal.

5. **Performance:**
   - Tick subsystem or providers?
   - **Recommendation:** Providers tick only if sequence playing; subsystem coordinates.

---

## References

- **DaySequence Plugin Source:** `Plugins/DaySequence/` (UE 5.5)
- **Epic's Sequencer Docs:** [Cinematics & Sequencer](epic docs/documentation-en-us-unreal-engine-cinematics-*.html)
- **MovieScene API:** [Programming Sequencer](epic docs/documentation-en-us-unreal-engine-sequencer-scripting-*.html)
- **Subsystem Pattern:** [Subsystems](epic docs/documentation-en-us-unreal-engine-subsystems-*.html)
- **UltraSky Legacy Docs:** `docs/plugins/DAI_UltraSky_Legacy.md` (to be created post-rewrite)

---

## Next Steps

1. **Review this plan** with team; gather feedback
2. **Prototype Phase 1** (subsystem + provider) in isolated branch
3. **Validate sequencer integration** (Phase 2 proof-of-concept)
4. **Decide on GAS strategy** (separate plugin vs. conditional)
5. **Kick off implementation** following phase schedule

---

**Status:** 🟡 Awaiting Approval  
**Owner:** [Your Name]  
**Contact:** [Your Email/Discord]
