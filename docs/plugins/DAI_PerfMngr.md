# DAI_PerfMngr Plugin Documentation

## Overview

**DAI_PerfMngr** is a comprehensive performance management system for Unreal Engine 5.5 that exposes and extends Unreal's SignificanceManager system through a plugin interface. The system provides intelligent performance budgeting, LOD management, significance-based culling, and integration with hair strands, Mutable, and other DAI plugins for optimal performance scaling.

### Key Features
- 📊 **Performance Budgeting**: Dynamic resource allocation and management
- 🎯 **Significance Management**: Distance and importance-based object culling
- 💇 **Hair Strands Integration**: Performance optimization for complex hair rendering
- 🔄 **Mutable Integration**: Dynamic mesh performance management
- 📈 **Real-time Monitoring**: Performance metrics and profiling tools
- ⚡ **Adaptive LOD**: Dynamic level-of-detail adjustment based on performance
- 🎮 **GAS Integration**: Performance-aware ability system execution
- 🔧 **Configurable Budgets**: Customizable performance thresholds and limits

## Architecture

The DAI_PerfMngr system consists of:
- **Performance Manager Subsystem**: Central performance coordination
- **Significance Components**: Object-based significance tracking
- **Budget Management**: Resource allocation and monitoring
- **LOD Controllers**: Dynamic level-of-detail management
- **Integration Bridges**: Connections to specialized systems

## Core Components

### DAIPerfMngrSubsystem
*World subsystem managing performance operations*

**Type**: `World Subsystem`  
**Interfaces**: `IDAIPerformanceService`  
**File**: `DAIPerfMngrSubsystem.h`

Central service for performance budgeting, significance management, and optimization coordination.

### DAISignificanceComponent
*Component for object significance tracking*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `Performance|Significance`  
**File**: `DAISignificanceComponent.h`

Manages significance calculations and performance-based optimizations for individual actors.

### DAIPerformanceBudgetComponent
*Component for budget-aware systems*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `Performance|Budget`  
**File**: `DAIPerformanceBudgetComponent.h`

Provides budget-aware functionality for systems that need to scale with performance.

### DAILODController
*Controller for dynamic LOD management*

**Type**: `UObject`  
**Blueprint Type**: `Yes`  
**File**: `DAILODController.h`

Manages dynamic level-of-detail adjustments based on performance metrics.

## Blueprint Functions

### Performance Monitoring

#### GetCurrentFrameRate
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `Performance|Monitoring`  
**Returns**: `float`  
**Purpose**: Get current frame rate in frames per second

```cpp
float GetCurrentFrameRate(UObject* WorldContextObject);
```

**Usage**: Monitor real-time performance for dynamic optimization decisions.

#### GetFrameTimeMs
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `Performance|Monitoring`  
**Returns**: `float`  
**Purpose**: Get current frame time in milliseconds

```cpp
float GetFrameTimeMs(UObject* WorldContextObject);
```

**Usage**: Detailed frame timing for performance analysis.

#### GetPerformanceBudgetUsage
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `Performance|Budget`  
**Returns**: `float`  
**Purpose**: Get current budget usage as percentage

**Parameters**:
- `BudgetCategory` (EDAIBudgetCategory): Category of budget to check

```cpp
float GetPerformanceBudgetUsage(UObject* WorldContextObject, EDAIBudgetCategory BudgetCategory);
```

**Usage**: Monitor resource usage for specific performance categories.

#### IsPerformanceBudgetExceeded
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `Performance|Budget`  
**Returns**: `bool`  
**Purpose**: Check if performance budget is being exceeded

**Parameters**:
- `BudgetCategory` (EDAIBudgetCategory): Category of budget to check
- `Threshold` (float): Threshold percentage (default: 90%)

```cpp
bool IsPerformanceBudgetExceeded(UObject* WorldContextObject, EDAIBudgetCategory BudgetCategory, float Threshold = 0.9f);
```

**Usage**: Trigger performance optimizations when budgets are strained.

### Significance Management

#### SetActorSignificance
**Type**: `BlueprintCallable`  
**Category**: `Performance|Significance`  
**Purpose**: Manually set significance value for an actor

**Parameters**:
- `Actor` (AActor): Actor to set significance for
- `Significance` (float): Significance value (0.0 to 1.0)
- `bOverrideCalculation` (bool): Whether to override automatic calculation

```cpp
void SetActorSignificance(AActor* Actor, float Significance, bool bOverrideCalculation = false);
```

**Usage**: Manually control importance of specific actors for optimization.

#### GetActorSignificance
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `Performance|Significance`  
**Returns**: `float`  
**Purpose**: Get current significance value for an actor

**Parameters**:
- `Actor` (AActor): Actor to get significance for

```cpp
float GetActorSignificance(UObject* WorldContextObject, AActor* Actor);
```

**Usage**: Query actor importance for decision making.

#### RegisterSignificanceActor
**Type**: `BlueprintCallable`  
**Category**: `Performance|Significance`  
**Returns**: `bool`  
**Purpose**: Register actor with significance management system

**Parameters**:
- `Actor` (AActor): Actor to register
- `SignificanceFunction` (EDAISignificanceFunction): How to calculate significance
- `BaseSignificance` (float): Base significance value

```cpp
bool RegisterSignificanceActor(UObject* WorldContextObject, AActor* Actor, EDAISignificanceFunction SignificanceFunction, float BaseSignificance = 1.0f);
```

**Usage**: Enable automatic significance tracking for performance optimization.

#### UnregisterSignificanceActor
**Type**: `BlueprintCallable`  
**Category**: `Performance|Significance`  
**Purpose**: Remove actor from significance management

**Parameters**:
- `Actor` (AActor): Actor to unregister

```cpp
void UnregisterSignificanceActor(UObject* WorldContextObject, AActor* Actor);
```

**Usage**: Stop tracking significance for actors that no longer need optimization.

### LOD Management

#### SetActorLODLevel
**Type**: `BlueprintCallable`  
**Category**: `Performance|LOD`  
**Purpose**: Manually set LOD level for an actor

**Parameters**:
- `Actor` (AActor): Actor to set LOD for
- `LODLevel` (int32): Level of detail (0 = highest quality)
- `bForceUpdate` (bool): Whether to force immediate update

```cpp
void SetActorLODLevel(AActor* Actor, int32 LODLevel, bool bForceUpdate = false);
```

**Usage**: Override automatic LOD selection for specific actors.

#### GetRecommendedLODLevel
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `Performance|LOD`  
**Returns**: `int32`  
**Purpose**: Get recommended LOD level based on significance and performance

**Parameters**:
- `Actor` (AActor): Actor to get recommendation for
- `ViewerLocation` (FVector): Location of the viewer/camera

```cpp
int32 GetRecommendedLODLevel(UObject* WorldContextObject, AActor* Actor, const FVector& ViewerLocation);
```

**Usage**: Determine optimal LOD level for performance vs quality balance.

#### EnableAdaptiveLOD
**Type**: `BlueprintCallable`  
**Category**: `Performance|LOD`  
**Purpose**: Enable or disable adaptive LOD for an actor

**Parameters**:
- `Actor` (AActor): Actor to configure
- `bEnable` (bool): Whether to enable adaptive LOD
- `LODSettings` (FDAIAdaptiveLODSettings): Configuration for adaptive LOD

```cpp
void EnableAdaptiveLOD(AActor* Actor, bool bEnable, const FDAIAdaptiveLODSettings& LODSettings);
```

**Usage**: Configure automatic LOD adjustment based on performance conditions.

### Budget Management

#### SetPerformanceBudget
**Type**: `BlueprintCallable`  
**Category**: `Performance|Budget`  
**Purpose**: Set performance budget for a specific category

**Parameters**:
- `BudgetCategory` (EDAIBudgetCategory): Category to set budget for
- `BudgetMs` (float): Budget in milliseconds per frame

```cpp
void SetPerformanceBudget(UObject* WorldContextObject, EDAIBudgetCategory BudgetCategory, float BudgetMs);
```

**Usage**: Configure performance limits for different system categories.

#### RequestBudgetAllocation
**Type**: `BlueprintCallable`  
**Category**: `Performance|Budget`  
**Returns**: `bool`  
**Purpose**: Request allocation from performance budget

**Parameters**:
- `BudgetCategory` (EDAIBudgetCategory): Category to allocate from
- `RequestedMs` (float): Requested time in milliseconds
- `Priority` (EDAIBudgetPriority): Priority of this request

```cpp
bool RequestBudgetAllocation(UObject* WorldContextObject, EDAIBudgetCategory BudgetCategory, float RequestedMs, EDAIBudgetPriority Priority);
```

**Usage**: Reserve performance budget before executing expensive operations.

#### ReleaseBudgetAllocation
**Type**: `BlueprintCallable`  
**Category**: `Performance|Budget`  
**Purpose**: Release previously allocated budget

**Parameters**:
- `BudgetCategory` (EDAIBudgetCategory): Category to release from
- `ReleasedMs` (float): Amount to release in milliseconds

```cpp
void ReleaseBudgetAllocation(UObject* WorldContextObject, EDAIBudgetCategory BudgetCategory, float ReleasedMs);
```

**Usage**: Return unused budget allocation for other systems to use.

### Hair Strands Integration

#### SetHairStrandsLOD
**Type**: `BlueprintCallable`  
**Category**: `Performance|Hair`  
**Purpose**: Set LOD level for hair strands on an actor

**Parameters**:
- `Actor` (AActor): Actor with hair strands to modify
- `LODLevel` (int32): Hair strands LOD level
- `bAffectAllHairComponents` (bool): Whether to affect all hair components

```cpp
void SetHairStrandsLOD(AActor* Actor, int32 LODLevel, bool bAffectAllHairComponents = true);
```

**Usage**: Optimize hair rendering performance based on distance or importance.

#### GetHairStrandsComplexity
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `Performance|Hair`  
**Returns**: `float`  
**Purpose**: Get performance complexity of hair strands for an actor

**Parameters**:
- `Actor` (AActor): Actor to analyze

```cpp
float GetHairStrandsComplexity(AActor* Actor);
```

**Usage**: Assess hair rendering cost for performance planning.

### Mutable Integration

#### SetMutableLOD
**Type**: `BlueprintCallable`  
**Category**: `Performance|Mutable`  
**Purpose**: Set LOD level for Mutable components

**Parameters**:
- `Actor` (AActor): Actor with Mutable components
- `LODLevel` (int32): Mutable system LOD level

```cpp
void SetMutableLOD(AActor* Actor, int32 LODLevel);
```

**Usage**: Optimize dynamic mesh generation performance.

#### RequestMutableUpdate
**Type**: `BlueprintCallable`  
**Category**: `Performance|Mutable`  
**Returns**: `bool`  
**Purpose**: Request Mutable update with performance budgeting

**Parameters**:
- `Actor` (AActor): Actor requesting update
- `Priority` (EDAIBudgetPriority): Priority of this update
- `MaxUpdateTimeMs` (float): Maximum time to spend on update

```cpp
bool RequestMutableUpdate(UObject* WorldContextObject, AActor* Actor, EDAIBudgetPriority Priority, float MaxUpdateTimeMs);
```

**Usage**: Schedule Mutable updates within performance constraints.

## Blueprint Data Types

### EDAIBudgetCategory (Budget Category)
**Type**: `BlueprintType Enum`  
**Purpose**: Categories for performance budget allocation

**Values**:
- `Rendering`: Rendering and graphics operations
- `Animation`: Character and object animation
- `AI`: Artificial intelligence and behavior
- `Physics`: Physics simulation and collision
- `Audio`: Sound processing and effects
- `Networking`: Network communication and replication
- `Scripting`: Blueprint and scripting execution
- `Custom`: User-defined budget categories

### EDAISignificanceFunction (Significance Function)
**Type**: `BlueprintType Enum`  
**Purpose**: Methods for calculating object significance

**Values**:
- `Distance`: Based on distance from viewer
- `ScreenSize`: Based on size on screen
- `Importance`: Based on gameplay importance
- `Combined`: Combination of multiple factors
- `Custom`: User-defined significance calculation

### EDAIBudgetPriority (Budget Priority)
**Type**: `BlueprintType Enum`  
**Purpose**: Priority levels for budget allocation

**Values**:
- `Critical`: Must execute, cannot be deferred
- `High`: High priority, execute if budget available
- `Normal`: Standard priority operations
- `Low`: Execute only if excess budget available
- `Background`: Execute during idle time only

### FDAIPerformanceMetrics (Performance Metrics)
**Type**: `BlueprintType Struct`  
**Purpose**: Comprehensive performance measurement data

**Properties**:
- `FrameRate` (float): Current frames per second
- `FrameTimeMs` (float): Frame time in milliseconds
- `RenderTimeMs` (float): Rendering time per frame
- `GameThreadTimeMs` (float): Game thread execution time
- `GPUTimeMs` (float): GPU processing time
- `MemoryUsageMB` (int32): Current memory usage in megabytes
- `BudgetUsage` (TMap<EDAIBudgetCategory, float>): Budget usage per category

### FDAIAdaptiveLODSettings (Adaptive LOD Settings)
**Type**: `BlueprintType Struct`  
**Purpose**: Configuration for automatic LOD adjustment

**Properties**:
- `bEnableDistanceLOD` (bool): Whether to use distance-based LOD
- `bEnablePerformanceLOD` (bool): Whether to adjust LOD based on performance
- `DistanceThresholds` (TArray<float>): Distance thresholds for LOD levels
- `PerformanceThresholds` (TArray<float>): Performance thresholds for LOD adjustment
- `UpdateFrequency` (float): How often to update LOD (seconds)
- `HysteresisThreshold` (float): Threshold to prevent LOD flickering

### FDAISignificanceSettings (Significance Settings)
**Type**: `BlueprintType Struct`  
**Purpose**: Configuration for significance calculation

**Properties**:
- `SignificanceFunction` (EDAISignificanceFunction): Method for calculating significance
- `BaseSignificance` (float): Base significance value
- `DistanceScale` (float): Scale factor for distance-based significance
- `MinSignificance` (float): Minimum significance value
- `MaxSignificance` (float): Maximum significance value
- `UpdateFrequency` (float): How often to recalculate significance

### FDAIBudgetConfiguration (Budget Configuration)
**Type**: `BlueprintType Struct`  
**Purpose**: Configuration for performance budgets

**Properties**:
- `Category` (EDAIBudgetCategory): Budget category
- `BudgetMs` (float): Allocated time budget in milliseconds
- `PriorityWeights` (TMap<EDAIBudgetPriority, float>): Weight for each priority level
- `bAllowOverage` (bool): Whether to allow temporary budget overages
- `OverageThreshold` (float): Maximum allowable overage percentage

## Component Properties

### DAISignificanceComponent Properties

#### Significance Configuration
**Property**: `SignificanceFunction`  
**Type**: `EDAISignificanceFunction`  
**Category**: `Significance`  
**Blueprint Access**: `Read/Write`  
**Default**: `Distance`  
**Purpose**: Method for calculating this actor's significance

**Property**: `BaseSignificance`  
**Type**: `float`  
**Category**: `Significance`  
**Blueprint Access**: `Read/Write`  
**Default**: `1.0`  
**Purpose**: Base significance value before modifiers

**Property**: `bOverrideSignificance`  
**Type**: `bool`  
**Category**: `Significance`  
**Blueprint Access**: `Read/Write`  
**Default**: `false`  
**Purpose**: Whether to use manual significance instead of calculated

#### Performance Impact
**Property**: `PerformanceWeight`  
**Type**: `float`  
**Category**: `Performance`  
**Blueprint Access**: `Read/Write`  
**Default**: `1.0`  
**Purpose**: Relative performance cost of this actor

**Property**: `bCanBeOptimized`  
**Type**: `bool`  
**Category**: `Performance`  
**Blueprint Access**: `Read/Write`  
**Default**: `true`  
**Purpose**: Whether this actor can be optimized by the performance manager

### DAIPerformanceBudgetComponent Properties

#### Budget Settings
**Property**: `RequiredBudgetCategory`  
**Type**: `EDAIBudgetCategory`  
**Category**: `Budget`  
**Blueprint Access**: `Read/Write`  
**Default**: `Custom`  
**Purpose**: Budget category this component draws from

**Property**: `EstimatedCostMs`  
**Type**: `float`  
**Category**: `Budget`  
**Blueprint Access**: `Read/Write`  
**Default**: `1.0`  
**Purpose**: Estimated performance cost in milliseconds

**Property**: `Priority`  
**Type**: `EDAIBudgetPriority`  
**Category**: `Budget`  
**Blueprint Access**: `Read/Write`  
**Default**: `Normal`  
**Purpose**: Priority level for budget allocation

#### Execution Control
**Property**: `bRequireBudget`  
**Type**: `bool`  
**Category**: `Budget`  
**Blueprint Access**: `Read/Write`  
**Default**: `false`  
**Purpose**: Whether execution requires available budget

**Property**: `bCanBeDeferred`  
**Type**: `bool`  
**Category**: `Budget`  
**Blueprint Access**: `Read/Write`  
**Default**: `true`  
**Purpose**: Whether execution can be deferred if budget unavailable

## Events and Delegates

### OnPerformanceThresholdExceeded
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Performance`  
**Purpose**: Fired when performance exceeds configured thresholds

**Parameters**:
- `Category` (EDAIBudgetCategory): Budget category that was exceeded
- `CurrentUsage` (float): Current usage percentage
- `Threshold` (float): Threshold that was exceeded

**Usage**: Trigger performance optimizations when systems are stressed.

### OnSignificanceChanged
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Performance|Significance`  
**Purpose**: Fired when actor significance changes significantly

**Parameters**:
- `Actor` (AActor): Actor whose significance changed
- `OldSignificance` (float): Previous significance value
- `NewSignificance` (float): New significance value

**Usage**: React to significance changes for optimization adjustments.

### OnLODChanged
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Performance|LOD`  
**Purpose**: Fired when actor LOD level changes

**Parameters**:
- `Actor` (AActor): Actor whose LOD changed
- `OldLOD` (int32): Previous LOD level
- `NewLOD` (int32): New LOD level

**Usage**: Update related systems when LOD changes.

### OnBudgetExhausted
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Performance|Budget`  
**Purpose**: Fired when performance budget is completely exhausted

**Parameters**:
- `Category` (EDAIBudgetCategory): Budget category that was exhausted
- `FailedRequests` (int32): Number of failed allocation requests

**Usage**: Implement emergency performance measures when budget runs out.

## Developer Settings

Access via **Project Settings → Game → DAI Performance Manager**

### General Settings

#### Performance Monitoring
**Property**: `bEnablePerformanceMonitoring`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to enable performance tracking and budgeting

**Property**: `MonitoringUpdateFrequency`  
**Type**: `float`  
**Default**: `0.1`  
**Range**: `0.01-1.0`  
**Purpose**: Seconds between performance metric updates

**Property**: `PerformanceHistoryFrames`  
**Type**: `int32`  
**Default**: `300`  
**Range**: `30-1000`  
**Purpose**: Number of frames to keep in performance history

#### Significance Management
**Property**: `bEnableSignificanceManager`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to use significance-based optimization

**Property**: `SignificanceUpdateFrequency`  
**Type**: `float`  
**Default**: `0.2`  
**Range**: `0.05-2.0`  
**Purpose**: Seconds between significance recalculations

**Property**: `MaxSignificanceActors`  
**Type**: `int32`  
**Default**: `1000`  
**Range**: `100-10000`  
**Purpose**: Maximum number of actors to track for significance

### Budget Configuration

#### Default Budgets
**Property**: `DefaultBudgets`  
**Type**: `TMap<EDAIBudgetCategory, float>`  
**Default**: Various per category  
**Purpose**: Default performance budgets for each category

Example default values:
- Rendering: 10.0ms
- Animation: 3.0ms  
- AI: 2.0ms
- Physics: 2.0ms
- Audio: 1.0ms

#### Budget Enforcement
**Property**: `bEnforceBudgets`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to strictly enforce performance budgets

**Property**: `BudgetOverageThreshold`  
**Type**: `float`  
**Default**: `1.2`  
**Range**: `1.0-2.0`  
**Purpose**: Maximum allowable budget overage multiplier

**Property**: `EmergencyModeThreshold`  
**Type**: `float`  
**Default**: `1.5`  
**Range**: `1.2-3.0`  
**Purpose**: Threshold that triggers emergency performance mode

### LOD Settings

#### Adaptive LOD
**Property**: `bEnableAdaptiveLOD`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to enable automatic LOD adjustment

**Property**: `LODUpdateFrequency`  
**Type**: `float`  
**Default**: `0.5`  
**Range**: `0.1-5.0`  
**Purpose**: Seconds between LOD level evaluations

**Property**: `LODHysteresisThreshold`  
**Type**: `float`  
**Default**: `0.1`  
**Range**: `0.05-0.5`  
**Purpose**: Threshold to prevent LOD level flickering

#### Distance LOD
**Property**: `DefaultDistanceLODThresholds`  
**Type**: `TArray<float>`  
**Default**: `[500, 1000, 2000, 5000]`  
**Purpose**: Default distance thresholds for LOD levels

### Hair Strands Integration

#### Hair Performance
**Property**: `bManageHairStrandsLOD`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to manage hair strands LOD automatically

**Property**: `HairStrandsLODDistances`  
**Type**: `TArray<float>`  
**Default**: `[300, 800, 1500]`  
**Purpose**: Distance thresholds for hair strands LOD

**Property**: `MaxHairStrandsActors`  
**Type**: `int32`  
**Default**: `20`  
**Range**: `5-100`  
**Purpose**: Maximum number of actors with high-quality hair rendering

### Mutable Integration

#### Mutable Performance
**Property**: `bManageMutablePerformance`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to manage Mutable system performance

**Property**: `MutableUpdateBudgetMs`  
**Type**: `float`  
**Default**: `5.0`  
**Range**: `1.0-16.0`  
**Purpose**: Performance budget for Mutable updates per frame

**Property**: `MaxConcurrentMutableUpdates`  
**Type**: `int32`  
**Default**: `2`  
**Range**: `1-10`  
**Purpose**: Maximum simultaneous Mutable update operations

### Debug Settings

#### Visualization
**Property**: `bShowPerformanceHUD`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to display performance debugging HUD

**Property**: `bShowSignificanceVisualization`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to visualize actor significance values

**Property**: `bShowLODVisualization`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to display LOD levels in viewport

#### Logging
**Property**: `bLogPerformanceWarnings`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to log performance budget warnings

**Property**: `bLogSignificanceChanges`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to log significance value changes

## Usage Examples

### Basic Performance Monitoring
```blueprint
// Monitor performance and adjust quality settings
void UpdatePerformanceSettings()
{
    float CurrentFPS = UDAIPerfMngrBlueprintLibrary::GetCurrentFrameRate(this);
    
    if (CurrentFPS < TargetFPS)
    {
        // Performance is below target, reduce quality
        if (UDAIPerfMngrBlueprintLibrary::IsPerformanceBudgetExceeded(this, EDAIBudgetCategory::Rendering, 0.8f))
        {
            // Reduce rendering quality
            ReduceRenderingQuality();
        }
        
        if (UDAIPerfMngrBlueprintLibrary::IsPerformanceBudgetExceeded(this, EDAIBudgetCategory::AI, 0.9f))
        {
            // Reduce AI complexity
            ReduceAIComplexity();
        }
    }
    else if (CurrentFPS > TargetFPS * 1.2f)
    {
        // Performance is above target, can increase quality
        IncreaseQualitySettings();
    }
}
```

### Significance-Based Optimization
```blueprint
// Set up significance tracking for important actors
void RegisterImportantActors()
{
    // Register player character with high base significance
    UDAIPerfMngrBlueprintLibrary::RegisterSignificanceActor(
        this,
        PlayerCharacter,
        EDAISignificanceFunction::Importance,
        10.0f // High base significance
    );
    
    // Register enemy characters with distance-based significance
    for (AActor* Enemy : EnemyActors)
    {
        UDAIPerfMngrBlueprintLibrary::RegisterSignificanceActor(
            this,
            Enemy,
            EDAISignificanceFunction::Distance,
            3.0f
        );
    }
    
    // Register environmental objects with combined significance
    for (AActor* EnvObject : EnvironmentalObjects)
    {
        UDAIPerfMngrBlueprintLibrary::RegisterSignificanceActor(
            this,
            EnvObject,
            EDAISignificanceFunction::Combined,
            1.0f
        );
    }
}

// Adjust LOD based on significance
void UpdateActorLOD(AActor* Actor)
{
    float Significance = UDAIPerfMngrBlueprintLibrary::GetActorSignificance(this, Actor);
    
    int32 RecommendedLOD = UDAIPerfMngrBlueprintLibrary::GetRecommendedLODLevel(
        this,
        Actor,
        GetPlayerCameraLocation()
    );
    
    // Override LOD for very important actors
    if (Significance > 5.0f)
    {
        RecommendedLOD = FMath::Min(RecommendedLOD, 1); // Force higher quality
    }
    
    UDAIPerfMngrBlueprintLibrary::SetActorLODLevel(Actor, RecommendedLOD, false);
}
```

### Budget-Aware Operations
```blueprint
// Execute expensive operation within budget constraints
void PerformExpensiveOperation()
{
    // Request budget allocation
    bool bBudgetAvailable = UDAIPerfMngrBlueprintLibrary::RequestBudgetAllocation(
        this,
        EDAIBudgetCategory::AI,
        3.0f, // Estimated 3ms operation
        EDAIBudgetPriority::Normal
    );
    
    if (bBudgetAvailable)
    {
        // Perform the operation
        float StartTime = FPlatformTime::Seconds();
        
        ExecuteComplexAI();
        
        float ActualTime = (FPlatformTime::Seconds() - StartTime) * 1000.0f;
        
        // Release unused budget
        if (ActualTime < 3.0f)
        {
            UDAIPerfMngrBlueprintLibrary::ReleaseBudgetAllocation(
                this,
                EDAIBudgetCategory::AI,
                3.0f - ActualTime
            );
        }
    }
    else
    {
        // Budget not available, defer operation or use simplified version
        DeferOperation();
    }
}
```

### Hair Strands Performance Management
```blueprint
// Optimize hair rendering based on distance and performance
void OptimizeHairRendering()
{
    for (AActor* Character : CharactersWithHair)
    {
        float Distance = FVector::Dist(GetPlayerLocation(), Character->GetActorLocation());
        float Significance = UDAIPerfMngrBlueprintLibrary::GetActorSignificance(this, Character);
        
        int32 HairLOD = 0;
        
        // Determine hair LOD based on distance and significance
        if (Distance > 1500.0f || Significance < 0.5f)
        {
            HairLOD = 3; // Lowest quality
        }
        else if (Distance > 800.0f || Significance < 1.0f)
        {
            HairLOD = 2;
        }
        else if (Distance > 300.0f || Significance < 2.0f)
        {
            HairLOD = 1;
        }
        // else HairLOD = 0 (highest quality)
        
        // Apply performance pressure adjustments
        if (UDAIPerfMngrBlueprintLibrary::IsPerformanceBudgetExceeded(this, EDAIBudgetCategory::Rendering, 0.85f))
        {
            HairLOD = FMath::Min(HairLOD + 1, 3); // Reduce quality under pressure
        }
        
        UDAIPerfMngrBlueprintLibrary::SetHairStrandsLOD(Character, HairLOD, true);
    }
}
```

### Adaptive LOD Configuration
```blueprint
// Set up adaptive LOD for dynamic objects
void ConfigureAdaptiveLOD(AActor* Actor)
{
    FDAIAdaptiveLODSettings LODSettings;
    LODSettings.bEnableDistanceLOD = true;
    LODSettings.bEnablePerformanceLOD = true;
    LODSettings.DistanceThresholds = {500.0f, 1000.0f, 2000.0f};
    LODSettings.PerformanceThresholds = {0.7f, 0.85f, 0.95f};
    LODSettings.UpdateFrequency = 0.5f;
    LODSettings.HysteresisThreshold = 0.1f;
    
    UDAIPerfMngrBlueprintLibrary::EnableAdaptiveLOD(Actor, true, LODSettings);
}

// Bind to performance events for reactive optimization
void BeginPlay()
{
    Super::BeginPlay();
    
    UDAIPerfMngrSubsystem* PerfMngr = GetWorld()->GetSubsystem<UDAIPerfMngrSubsystem>();
    PerfMngr->OnPerformanceThresholdExceeded.AddDynamic(this, &AMyGameMode::OnPerformancePressure);
    PerfMngr->OnBudgetExhausted.AddDynamic(this, &AMyGameMode::OnBudgetCrisis);
}

UFUNCTION()
void OnPerformancePressure(EDAIBudgetCategory Category, float CurrentUsage, float Threshold)
{
    // React to performance pressure
    switch (Category)
    {
        case EDAIBudgetCategory::Rendering:
            ReduceVisualQuality();
            break;
        case EDAIBudgetCategory::AI:
            ReduceAIFrequency();
            break;
        case EDAIBudgetCategory::Animation:
            SimplifyAnimations();
            break;
    }
}

UFUNCTION()
void OnBudgetCrisis(EDAIBudgetCategory Category, int32 FailedRequests)
{
    // Emergency performance measures
    EnableEmergencyMode();
    PauseNonEssentialSystems();
}
```

## Integration with Other Plugins

### DAI_Hub Integration
- **Service Registration**: Performance manager registers with hub for discovery
- **Performance Coordination**: Central coordination of performance budgets across all plugins
- **Event Publishing**: Performance events published through hub system

### DAI_Dismember Integration
- **Dismemberment Performance**: Budget-aware dismemberment operations
- **Mutable Coordination**: Coordinate Mutable updates with performance budgets
- **LOD Integration**: Dismemberment detail scales with performance constraints

### DAI_AI Integration
- **AI Performance Budgeting**: AI operations respect performance budgets
- **Significance-Based AI**: AI complexity scales with actor significance
- **Behavior Optimization**: AI behaviors adapt to performance constraints

### Hair Strands Integration
- **Automatic LOD**: Hair quality automatically adjusts based on performance
- **Strand Count Management**: Dynamic strand count based on budget availability
- **Distance Culling**: Hair rendering culled based on distance and significance

### Mutable Integration
- **Update Scheduling**: Mutable updates scheduled within performance budgets
- **Priority Management**: Important Mutable updates get priority allocation
- **LOD Coordination**: Mutable LOD levels coordinate with overall performance state

## Best Practices

### Performance Budget Design
1. **Set realistic budgets** based on target platform capabilities
2. **Reserve emergency headroom** for unexpected performance spikes
3. **Prioritize critical systems** with higher budget allocations
4. **Monitor budget usage trends** to identify optimization opportunities
5. **Test under stress conditions** to validate budget effectiveness

### Significance Management
1. **Design clear significance hierarchies** for different object types
2. **Update significance appropriately** based on gameplay state changes
3. **Use combined significance factors** for more nuanced optimization
4. **Avoid significance flickering** with appropriate hysteresis
5. **Profile significance calculations** to ensure they don't impact performance

### LOD Strategy
1. **Design consistent LOD chains** across similar object types
2. **Test LOD transitions** for visual quality maintenance
3. **Use appropriate LOD distances** for your game's scale and perspective
4. **Consider gameplay impact** when reducing LOD for interactive objects
5. **Implement smooth transitions** between LOD levels

### Integration Planning
1. **Coordinate with other performance systems** to avoid conflicts
2. **Design for scalability** across different platform capabilities
3. **Implement graceful degradation** for extreme performance pressure
4. **Monitor system interactions** for unintended performance impacts
5. **Plan for future expansion** with extensible performance categories

## Technical Notes

- **Thread Safety**: Performance monitoring uses thread-safe metrics collection
- **Memory Management**: Efficient storage of performance history and significance data
- **Platform Optimization**: Platform-specific optimizations for performance monitoring
- **Integration Architecture**: Clean interfaces for extending performance management
- **Scalability**: Designed to handle large numbers of tracked objects efficiently

---

*For more information about hub integration, see [DAI_Hub documentation](DAI_Hub.md).*  
*For dismemberment performance integration, see [DAI_Dismember documentation](DAI_Dismember.md).*  
*For AI performance budgeting, see [DAI_AI documentation](DAI_AI.md).*

---

Last updated: October 6, 2025