# DAI_LoadDirector Plugin Documentation

## Overview

**DAI_LoadDirector** is a comprehensive loading orchestration system for Unreal Engine 5.5 that manages coordinated level and asset loading sequences with progress tracking, event publishing, and user feedback. The system provides intelligent loading management, progress reporting, and seamless integration with other DAI plugins for complex loading scenarios.

### Key Features
- 🎬 **Orchestrated Loading**: Coordinated multi-stage loading sequences
- 📊 **Progress Tracking**: Detailed progress reporting with customizable events
- 🎯 **Smart Prioritization**: Intelligent asset loading priority management
- 🔄 **Async Operations**: Non-blocking background loading operations
- 📡 **Event Integration**: Hub-based event publishing for loading states
- 🎮 **User Feedback**: Built-in loading screen and progress UI support
- ⚡ **Performance Optimized**: Memory and CPU conscious loading management
- 🔧 **Configurable**: Extensive settings for different loading scenarios

## Architecture

The DAI_LoadDirector system consists of:
- **Load Director Subsystem**: Central loading coordination
- **Loading Sequences**: Structured multi-stage loading processes
- **Progress Tracking**: Real-time loading progress monitoring
- **Event System**: Hub integration for loading notifications
- **Asset Management**: Intelligent asset loading and prioritization

## Core Components

### LoadDirectorSubsystem
*World subsystem managing all loading operations*

**Type**: `World Subsystem`  
**Interfaces**: `IDAILoadDirectorService`  
**File**: `LoadDirectorSubsystem.h`

Central service for orchestrating loading sequences, tracking progress, and managing loading resources.

### LoadingSequence
*Structured loading process with multiple stages*

**Type**: `UObject`  
**Blueprint Type**: `Yes`  
**File**: `LoadingSequence.h`

Defines a complete loading process with stages, dependencies, and progress tracking.

### LoadingStage
*Individual stage within a loading sequence*

**Type**: `UObject`  
**Blueprint Type**: `Yes`  
**File**: `LoadingStage.h`

Represents a single loading operation within a larger sequence.

## Blueprint Functions

### Core Loading Operations

#### StartLoadingSequence
**Type**: `BlueprintCallable`  
**Category**: `Loading`  
**Returns**: `bool`  
**Purpose**: Begin a structured loading sequence

**Parameters**:
- `SequenceName` (FString): Name identifier for the loading sequence
- `LoadingStages` (TArray<FLoadingStageInfo>): Stages to execute in order
- `bShowProgress` (bool): Whether to display loading progress UI
- `Priority` (ELoadingPriority): Priority level for this loading sequence

```cpp
bool StartLoadingSequence(UObject* WorldContextObject, const FString& SequenceName, const TArray<FLoadingStageInfo>& LoadingStages, bool bShowProgress = true, ELoadingPriority Priority = ELoadingPriority::Normal);
```

**Usage**: Initiate complex loading operations with multiple coordinated stages.

#### LoadLevel
**Type**: `BlueprintCallable`  
**Category**: `Loading`  
**Returns**: `bool`  
**Purpose**: Load a specific level with progress tracking

**Parameters**:
- `LevelName` (FString): Name of the level to load
- `bLoadAsynchronously` (bool): Whether to load in background
- `LoadType` (ELevelLoadType): How to handle the level loading (additive, replace, etc.)

```cpp
bool LoadLevel(UObject* WorldContextObject, const FString& LevelName, bool bLoadAsynchronously = true, ELevelLoadType LoadType = ELevelLoadType::Replace);
```

**Usage**: Load individual levels with integrated progress tracking and event notification.

#### LoadAssets
**Type**: `BlueprintCallable`  
**Category**: `Loading`  
**Returns**: `bool`  
**Purpose**: Load a collection of assets with progress tracking

**Parameters**:
- `AssetPaths` (TArray<FSoftObjectPath>): Paths to assets to load
- `LoadGroup` (FString): Group name for organizing loaded assets
- `Priority` (EAssetLoadPriority): Loading priority for these assets

```cpp
bool LoadAssets(UObject* WorldContextObject, const TArray<FSoftObjectPath>& AssetPaths, const FString& LoadGroup, EAssetLoadPriority Priority = EAssetLoadPriority::Normal);
```

**Usage**: Preload assets needed for upcoming gameplay sections.

### Progress Monitoring

#### GetLoadingProgress
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `Loading`  
**Returns**: `float`  
**Purpose**: Get overall loading progress as percentage

**Parameters**:
- `SequenceName` (FString): Name of the sequence to check (empty for overall progress)

```cpp
float GetLoadingProgress(UObject* WorldContextObject, const FString& SequenceName = "");
```

**Usage**: Display loading progress in UI elements.

#### GetCurrentLoadingStage
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `Loading`  
**Returns**: `FString`  
**Purpose**: Get description of currently executing loading stage

**Parameters**:
- `SequenceName` (FString): Name of the sequence to check

```cpp
FString GetCurrentLoadingStage(UObject* WorldContextObject, const FString& SequenceName);
```

**Usage**: Show detailed loading information to users.

#### IsLoading
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `Loading`  
**Returns**: `bool`  
**Purpose**: Check if any loading operations are currently active

```cpp
bool IsLoading(UObject* WorldContextObject);
```

**Usage**: Determine if gameplay should be paused for loading operations.

### Loading Management

#### SetLoadingPriority
**Type**: `BlueprintCallable`  
**Category**: `Loading`  
**Purpose**: Adjust priority of active loading operations

**Parameters**:
- `SequenceName` (FString): Name of the sequence to modify
- `NewPriority` (ELoadingPriority): New priority level

```cpp
void SetLoadingPriority(UObject* WorldContextObject, const FString& SequenceName, ELoadingPriority NewPriority);
```

**Usage**: Dynamically adjust loading priorities based on user actions.

#### CancelLoading
**Type**: `BlueprintCallable`  
**Category**: `Loading`  
**Returns**: `bool`  
**Purpose**: Cancel an active loading sequence

**Parameters**:
- `SequenceName` (FString): Name of the sequence to cancel
- `bForceCancel` (bool): Whether to force cancellation even if not safely cancellable

```cpp
bool CancelLoading(UObject* WorldContextObject, const FString& SequenceName, bool bForceCancel = false);
```

**Usage**: Allow users to cancel long-running loading operations.

#### PauseLoading
**Type**: `BlueprintCallable`  
**Category**: `Loading`  
**Purpose**: Temporarily pause loading operations

**Parameters**:
- `bPause` (bool): Whether to pause or resume loading

```cpp
void PauseLoading(UObject* WorldContextObject, bool bPause);
```

**Usage**: Pause loading during critical gameplay moments.

## Blueprint Data Types

### FLoadingStageInfo (Loading Stage Information)
**Type**: `BlueprintType Struct`  
**Purpose**: Configuration for a single loading stage

**Properties**:
- `StageName` (FString): Human-readable name for this stage
- `Description` (FString): Detailed description for progress display
- `StageType` (ELoadingStageType): Type of loading operation
- `TargetAssets` (TArray<FSoftObjectPath>): Assets to load in this stage
- `LevelName` (FString): Level to load (if stage type is level loading)
- `ExpectedDuration` (float): Estimated duration in seconds
- `Weight` (float): Relative weight for progress calculation
- `bCanSkip` (bool): Whether this stage can be skipped
- `bIsOptional` (bool): Whether failure of this stage should stop the sequence

### ELoadingStageType (Loading Stage Type)
**Type**: `BlueprintType Enum`  
**Purpose**: Type of operation performed in a loading stage

**Values**:
- `AssetLoading`: Load specific assets
- `LevelLoading`: Load a game level
- `DataInitialization`: Initialize game data structures
- `SystemStartup`: Start up game systems
- `CustomOperation`: Execute custom loading function

### ELoadingPriority (Loading Priority)
**Type**: `BlueprintType Enum`  
**Purpose**: Priority level for loading operations

**Values**:
- `Critical`: Highest priority, cannot be interrupted
- `High`: High priority loading
- `Normal`: Standard priority loading
- `Low`: Background loading when resources are available
- `Deferred`: Load only when explicitly requested

### ELevelLoadType (Level Load Type)
**Type**: `BlueprintType Enum`  
**Purpose**: How to handle level loading

**Values**:
- `Replace`: Unload current level and load new one
- `Additive`: Load level additively to current world
- `Background`: Load level in background for later activation
- `Streaming`: Use level streaming for seamless transitions

### FLoadingProgressInfo (Loading Progress Information)
**Type**: `BlueprintType Struct`  
**Purpose**: Detailed progress information for UI display

**Properties**:
- `OverallProgress` (float): Overall loading progress (0.0 to 1.0)
- `CurrentStage` (FString): Name of currently executing stage
- `StageProgress` (float): Progress of current stage (0.0 to 1.0)
- `EstimatedTimeRemaining` (float): Estimated seconds until completion
- `LoadedAssetCount` (int32): Number of assets successfully loaded
- `TotalAssetCount` (int32): Total number of assets to load
- `ErrorCount` (int32): Number of loading errors encountered

### FLoadingSequenceConfig (Loading Sequence Configuration)
**Type**: `BlueprintType Struct`  
**Purpose**: Configuration for entire loading sequence

**Properties**:
- `SequenceName` (FString): Unique identifier for the sequence
- `DisplayName` (FString): Human-readable name for UI
- `Stages` (TArray<FLoadingStageInfo>): Ordered list of loading stages
- `bAllowCancellation` (bool): Whether sequence can be cancelled
- `bShowDetailedProgress` (bool): Whether to show detailed stage information
- `TimeoutSeconds` (float): Maximum time before sequence is considered failed
- `RetryAttempts` (int32): Number of retry attempts for failed stages

## Events and Delegates

### OnLoadingSequenceStarted
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Loading`  
**Purpose**: Fired when a loading sequence begins

**Parameters**:
- `SequenceName` (FString): Name of the started sequence
- `EstimatedDuration` (float): Expected loading duration in seconds

**Usage**: Update UI to show loading has begun.

### OnLoadingSequenceCompleted
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Loading`  
**Purpose**: Fired when a loading sequence completes successfully

**Parameters**:
- `SequenceName` (FString): Name of the completed sequence
- `ActualDuration` (float): Actual time taken to complete

**Usage**: Hide loading UI and transition to gameplay.

### OnLoadingSequenceFailed
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Loading`  
**Purpose**: Fired when a loading sequence fails

**Parameters**:
- `SequenceName` (FString): Name of the failed sequence
- `ErrorMessage` (FString): Description of the failure
- `FailedStage` (FString): Stage where failure occurred

**Usage**: Display error messages and provide retry options.

### OnLoadingStageChanged
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Loading`  
**Purpose**: Fired when loading moves to a new stage

**Parameters**:
- `SequenceName` (FString): Name of the sequence
- `OldStage` (FString): Previous stage name
- `NewStage` (FString): New stage name
- `Progress` (float): Overall progress percentage

**Usage**: Update loading screen with current stage information.

### OnLoadingProgressUpdate
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Loading`  
**Purpose**: Fired periodically during loading for progress updates

**Parameters**:
- `ProgressInfo` (FLoadingProgressInfo): Detailed progress information

**Usage**: Update progress bars and loading animations.

## Developer Settings

Access via **Project Settings → Game → DAI Load Director**

### General Settings

#### Default Loading Behavior
**Property**: `bEnableProgressEvents`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to publish loading progress events

**Property**: `ProgressUpdateInterval`  
**Type**: `float`  
**Default**: `0.1`  
**Range**: `0.01-1.0`  
**Purpose**: Seconds between progress update events

**Property**: `DefaultLoadingTimeout`  
**Type**: `float`  
**Default**: `300.0`  
**Range**: `30.0-1800.0`  
**Purpose**: Default timeout for loading sequences in seconds

#### Performance Settings
**Property**: `MaxConcurrentLoads`  
**Type**: `int32`  
**Default**: `3`  
**Range**: `1-10`  
**Purpose**: Maximum number of simultaneous loading operations

**Property**: `AsyncLoadingBudgetMs`  
**Type**: `float`  
**Default**: `16.0`  
**Range**: `5.0-33.0`  
**Purpose**: Maximum milliseconds per frame for async loading

**Property**: `bUseBackgroundLoading`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to perform loading operations on background threads

### UI Integration Settings

#### Loading Screen Configuration
**Property**: `DefaultLoadingScreenClass`  
**Type**: `TSubclassOf<UUserWidget>`  
**Purpose**: Default widget class for loading screens

**Property**: `bAutoShowLoadingScreen`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to automatically show loading screen during sequences

**Property**: `MinLoadingScreenTime`  
**Type**: `float`  
**Default**: `1.0`  
**Range**: `0.0-10.0`  
**Purpose**: Minimum time to show loading screen (prevents flashing)

#### Progress Display
**Property**: `bShowPercentageProgress`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to display numerical progress percentages

**Property**: `bShowStageDetails`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to show current stage information

**Property**: `bShowTimeEstimates`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to display estimated time remaining

### Memory Management

#### Asset Loading Limits
**Property**: `MaxPreloadedAssets`  
**Type**: `int32`  
**Default**: `1000`  
**Range**: `100-10000`  
**Purpose**: Maximum number of assets to keep preloaded

**Property**: `AssetUnloadDelaySeconds`  
**Type**: `float`  
**Default**: `30.0`  
**Range**: `5.0-300.0`  
**Purpose**: Delay before automatically unloading unused assets

#### Memory Monitoring
**Property**: `bMonitorMemoryUsage`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to monitor memory usage during loading

**Property**: `MemoryPressureThresholdMB`  
**Type**: `int32`  
**Default**: `512`  
**Range**: `100-2048`  
**Purpose**: Memory usage threshold that triggers aggressive cleanup

### Debug Settings

#### Logging Configuration
**Property**: `bEnableDetailedLogging`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to enable verbose loading operation logging

**Property**: `bLogProgressUpdates`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to log every progress update

#### Development Tools
**Property**: `bSimulateSlowLoading`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to artificially slow loading for testing

**Property**: `SimulatedLoadingDelay`  
**Type**: `float`  
**Default**: `1.0`  
**Range**: `0.1-10.0`  
**Purpose**: Artificial delay to add to loading operations

## Usage Examples

### Basic Level Loading
```blueprint
// Simple level transition with loading screen
void LoadNewLevel(const FString& LevelName)
{
    // Create loading stage for level
    FLoadingStageInfo LevelStage;
    LevelStage.StageName = "Loading Level";
    LevelStage.Description = "Loading " + LevelName;
    LevelStage.StageType = ELoadingStageType::LevelLoading;
    LevelStage.LevelName = LevelName;
    LevelStage.Weight = 1.0f;
    
    TArray<FLoadingStageInfo> Stages;
    Stages.Add(LevelStage);
    
    // Start loading sequence
    ULoadDirectorBlueprintLibrary::StartLoadingSequence(
        this,
        "LevelTransition",
        Stages,
        true, // Show progress
        ELoadingPriority::High
    );
}
```

### Complex Multi-Stage Loading
```blueprint
// Load new area with assets, data, and systems
void LoadGameArea(const FString& AreaName)
{
    TArray<FLoadingStageInfo> Stages;
    
    // Stage 1: Load required assets
    FLoadingStageInfo AssetStage;
    AssetStage.StageName = "Loading Assets";
    AssetStage.Description = "Loading textures and models...";
    AssetStage.StageType = ELoadingStageType::AssetLoading;
    AssetStage.TargetAssets = GetRequiredAssetsForArea(AreaName);
    AssetStage.Weight = 0.4f;
    Stages.Add(AssetStage);
    
    // Stage 2: Load level
    FLoadingStageInfo LevelStage;
    LevelStage.StageName = "Loading Level";
    LevelStage.Description = "Loading game world...";
    LevelStage.StageType = ELoadingStageType::LevelLoading;
    LevelStage.LevelName = AreaName;
    LevelStage.Weight = 0.3f;
    Stages.Add(LevelStage);
    
    // Stage 3: Initialize game systems
    FLoadingStageInfo SystemStage;
    SystemStage.StageName = "Initializing Systems";
    SystemStage.Description = "Starting game systems...";
    SystemStage.StageType = ELoadingStageType::SystemStartup;
    SystemStage.Weight = 0.3f;
    Stages.Add(SystemStage);
    
    // Start the sequence
    ULoadDirectorBlueprintLibrary::StartLoadingSequence(
        this,
        "AreaTransition_" + AreaName,
        Stages,
        true,
        ELoadingPriority::Normal
    );
}
```

### Asset Preloading
```blueprint
// Preload assets for upcoming gameplay
void PreloadUpcomingAssets()
{
    // Get assets needed for next quest
    TArray<FSoftObjectPath> UpcomingAssets;
    UpcomingAssets.Add("/Game/Characters/Boss/BossCharacter.BossCharacter");
    UpcomingAssets.Add("/Game/VFX/Explosions/BigExplosion.BigExplosion");
    UpcomingAssets.Add("/Game/Audio/Music/BossTheme.BossTheme");
    
    // Load with low priority so it doesn't impact current gameplay
    ULoadDirectorBlueprintLibrary::LoadAssets(
        this,
        UpcomingAssets,
        "BossEncounter",
        EAssetLoadPriority::Low
    );
}
```

### Progress Monitoring
```blueprint
// Update loading screen UI
void UpdateLoadingUI()
{
    if (ULoadDirectorBlueprintLibrary::IsLoading(this))
    {
        // Get progress information
        float Progress = ULoadDirectorBlueprintLibrary::GetLoadingProgress(this);
        FString CurrentStage = ULoadDirectorBlueprintLibrary::GetCurrentLoadingStage(this, CurrentSequenceName);
        
        // Update UI elements
        LoadingProgressBar->SetPercent(Progress);
        LoadingStageText->SetText(FText::FromString(CurrentStage));
        
        // Show/hide loading screen
        if (!LoadingScreen->IsVisible())
        {
            LoadingScreen->SetVisibility(ESlateVisibility::Visible);
        }
    }
    else
    {
        // Hide loading screen when complete
        LoadingScreen->SetVisibility(ESlateVisibility::Hidden);
    }
}

// Bind to loading events
void BeginPlay()
{
    Super::BeginPlay();
    
    ULoadDirectorSubsystem* LoadDirector = GetWorld()->GetSubsystem<ULoadDirectorSubsystem>();
    LoadDirector->OnLoadingProgressUpdate.AddDynamic(this, &AMyGameMode::OnLoadingProgress);
    LoadDirector->OnLoadingSequenceCompleted.AddDynamic(this, &AMyGameMode::OnLoadingComplete);
}

UFUNCTION()
void OnLoadingProgress(const FLoadingProgressInfo& ProgressInfo)
{
    // Update detailed progress information
    LoadingProgressBar->SetPercent(ProgressInfo.OverallProgress);
    LoadingStageText->SetText(FText::FromString(ProgressInfo.CurrentStage));
    
    if (ProgressInfo.EstimatedTimeRemaining > 0)
    {
        TimeRemainingText->SetText(FText::Format(
            FText::FromString("Est. {0}s remaining"),
            FText::AsNumber(FMath::CeilToInt(ProgressInfo.EstimatedTimeRemaining))
        ));
    }
}

UFUNCTION()
void OnLoadingComplete(const FString& SequenceName, float ActualDuration)
{
    // Transition to gameplay
    LoadingScreen->SetVisibility(ESlateVisibility::Hidden);
    StartGameplay();
}
```

## Integration with Other Plugins

### DAI_Hub Integration
- **Service Registration**: Load director registers with hub for discovery
- **Event Publishing**: Loading progress and completion events published through hub
- **Performance Coordination**: Respects hub performance budgets during loading

### DAI_Save Integration
- **Save Progress**: Loading sequences can trigger auto-saves on completion
- **Loading Checkpoints**: Implement checkpoint loading through load director
- **Progress Persistence**: Save loading progress for resumable operations

### DAI_Map Integration
- **Level Loading**: Coordinate map POI updates during level loading
- **Asset Discovery**: Automatically register map-related assets for loading

### DAI_PerfMngr Integration
- **Performance Budgeting**: Loading operations respect performance constraints
- **Priority Management**: Dynamic priority adjustment based on performance metrics

## Best Practices

### Loading Sequence Design
1. **Break loading into logical stages** for better progress feedback
2. **Weight stages appropriately** for accurate progress calculation
3. **Make optional stages skippable** to handle loading failures gracefully
4. **Group related assets** into single stages for efficiency
5. **Provide meaningful stage descriptions** for user feedback

### Performance Optimization
1. **Use background loading** whenever possible to maintain frame rate
2. **Limit concurrent operations** to prevent resource contention
3. **Monitor memory usage** during large asset loads
4. **Implement progressive loading** for very large worlds
5. **Cache frequently used assets** to reduce loading times

### User Experience
1. **Show meaningful progress information** rather than generic loading screens
2. **Provide loading time estimates** when possible
3. **Allow cancellation** of non-critical loading operations
4. **Implement smooth progress animations** to maintain perceived responsiveness
5. **Handle loading failures gracefully** with retry options

### Technical Implementation
1. **Use soft references** for assets that should be loaded on demand
2. **Implement proper cleanup** for loaded assets when no longer needed
3. **Handle edge cases** like network disconnections during loading
4. **Test with slow storage** to ensure good performance on all devices
5. **Monitor loading metrics** to optimize future loading sequences

## Technical Notes

- **Thread Safety**: Loading operations use background threads when possible
- **Memory Management**: Automatic cleanup of temporarily loaded assets
- **Platform Support**: Cross-platform loading with platform-specific optimizations
- **Performance**: Optimized asset streaming and memory usage
- **Networking**: Local loading only, but integrates with networked save systems

---

*For more information about hub integration, see [DAI_Hub documentation](DAI_Hub.md).*  
*For save system integration, see [DAI_Save documentation](DAI_Save.md).*  
*For performance management, see [DAI_PerfMngr documentation](DAI_PerfMngr.md).*

---

Last updated: October 6, 2025