# DAI_Navigation Plugin Documentation (Renamed)

> NOTE: The plugin name has been standardized from `DAI__Navigation` (double underscore) to `DAI_Navigation`. File paths, folder names, and references in code/docs should migrate to the single underscore form. This file remains to preserve existing links; prefer updating links to `plugins/DAI_Navigation.md`.

Quick links:
- Blueprint API: see `docs/DAI_Navigation_Blueprint_API.md` (DAI_ wrappers only)
- Console help: use `DAI.Nav.Help` at runtime for available nav commands

## Overview

**DAI_Navigation** (formerly **DAI__Navigation**) is a **standalone** navigation system for Unreal Engine 5.5 that provides unified curved path following, spider surface traversal, flying distance-field planning, and optional integration with Gameplay Ability System (GAS) and Smart Objects. The system extends Unreal's built-in navigation with sophisticated movement capabilities for complex 3D environments.

**Plugin Independence**: This plugin functions completely independently and does not require any other DAI plugins to operate. SmartObject integration is optional and only enabled when the DAI_SmartObject plugin is present and loaded.

Blueprint surface policy: Only DAI_ prefixed wrapper nodes are exposed to designers; legacy non-prefixed nodes were removed to keep the surface clean and consistent.

### Key Features
- 🕷️ **Spider Traversal**: Surface-following navigation on walls and ceilings
- ✈️ **3D Flying Navigation**: Distance-field based pathfinding for flying entities
- 🌊 **Curved Path Following**: Smooth, natural movement along curved trajectories
- 🎯 **GAS Integration**: Navigation abilities and movement effects
- 🧠 **Smart Object Hooks**: Integration with contextual interaction system
- 🎮 **Niagara Effects**: Visual feedback for navigation paths and abilities
- 📊 **Performance Optimized**: Efficient pathfinding with LOD and culling systems
- 🔧 **Modular Design**: Component-based system for flexible implementation

## Architecture

The DAI_Navigation system consists of:
- **Navigation Subsystem**: Central pathfinding and coordination
- **Movement Components**: Specialized movement implementations
- **Path Following**: Curved and surface-aware path execution
- **3D Pathfinding**: Distance-field based navigation for 3D spaces
- **Integration Layer**: Hooks for GAS, Smart Objects, and Niagara

## Core Components

### DAINavigationSubsystem
*World subsystem managing navigation operations*

**Type**: `World Subsystem`  
**Interfaces**: `IDAINavigationService`  
**File**: `DAINavigationSubsystem.h`

Central service for pathfinding, movement coordination, and navigation state management.

### DAICurvedPathFollowingComponent
*Component for smooth curved path following*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `Navigation|Movement`  
**File**: `DAICurvedPathFollowingComponent.h`

Provides smooth, curved movement along generated navigation paths.

### DAISpiderMovementComponent
*Component for surface-traversal movement*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `Navigation|Spider`  
**File**: `DAISpiderMovementComponent.h`

Enables movement on arbitrary surfaces including walls and ceilings.

### DAIFlyingNavigationComponent
*Component for 3D flying navigation*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `Navigation|Flying`  
**File**: `DAIFlyingNavigationComponent.h`

Provides distance-field based pathfinding for flying entities.

### DAINavigationAbilityComponent
*GAS integration component for navigation abilities*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `Navigation|GAS`  
**File**: `DAINavigationAbilityComponent.h`

Bridges navigation system with Gameplay Ability System for movement abilities.

## Blueprint Functions

### Core Navigation

#### FindPath3D
**Type**: `BlueprintCallable`  
**Category**: `Navigation|3D`  
**Returns**: `bool`  
**Purpose**: Calculate 3D navigation path using distance fields

**Parameters**:
- `Start` (FVector): Starting location for pathfinding
- `Goal` (FVector): Target destination
- `NavigationType` (EDAINavigationType): Type of navigation (Flying, Spider, Ground)
- `OutPath` (TArray<FVector>): Generated path points
- `SearchRadius` (float): Maximum search radius for pathfinding

```cpp
bool FindPath3D(UObject* WorldContextObject, const FVector& Start, const FVector& Goal, EDAINavigationType NavigationType, TArray<FVector>& OutPath, float SearchRadius = 2000.0f);
```

**Usage**: Generate navigation paths for entities that can move in 3D space.

#### FollowCurvedPath
**Type**: `BlueprintCallable`  
**Category**: `Navigation|Movement`  
**Returns**: `bool`  
**Purpose**: Begin following a curved path with smooth movement

**Parameters**:
- `PathPoints` (TArray<FVector>): Points defining the path to follow
- `MovementSpeed` (float): Speed of movement along the path
- `CurveSmoothing` (float): Amount of smoothing to apply to curves
- `bLoopPath` (bool): Whether to loop the path continuously

```cpp
bool FollowCurvedPath(AActor* Actor, const TArray<FVector>& PathPoints, float MovementSpeed, float CurveSmoothing = 0.5f, bool bLoopPath = false);
```

**Usage**: Execute smooth movement along pre-calculated or designer-defined paths.

#### AttachToSurface
**Type**: `BlueprintCallable`  
**Category**: `Navigation|Spider`  
**Returns**: `bool`  
**Purpose**: Attach actor to surface for spider-like traversal

**Parameters**:
- `Actor` (AActor): Actor to attach to surface
- `SurfaceLocation` (FVector): World location on surface
- `SurfaceNormal` (FVector): Normal vector of the surface
- `AttachmentStrength` (float): Strength of surface attachment

```cpp
bool AttachToSurface(AActor* Actor, const FVector& SurfaceLocation, const FVector& SurfaceNormal, float AttachmentStrength = 1.0f);
```

**Usage**: Enable spider-like movement on walls, ceilings, and irregular surfaces.

#### DetachFromSurface
**Type**: `BlueprintCallable`  
**Category**: `Navigation|Spider`  
**Purpose**: Detach actor from surface and return to normal movement

**Parameters**:
- `Actor` (AActor): Actor to detach from surface

```cpp
void DetachFromSurface(AActor* Actor);
```

**Usage**: Return to normal movement mode from surface traversal.

### Path Analysis

#### GetPathLength
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `Navigation|Analysis`  
**Returns**: `float`  
**Purpose**: Calculate total length of a navigation path

**Parameters**:
- `PathPoints` (TArray<FVector>): Path points to measure

```cpp
float GetPathLength(const TArray<FVector>& PathPoints);
```

**Usage**: Estimate travel time or determine path efficiency.

#### GetPathCurvature
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `Navigation|Analysis`  
**Returns**: `float`  
**Purpose**: Calculate average curvature of a path

**Parameters**:
- `PathPoints` (TArray<FVector>): Path points to analyze

```cpp
float GetPathCurvature(const TArray<FVector>& PathPoints);
```

**Usage**: Assess path complexity for movement planning.

#### IsPathClear
**Type**: `BlueprintCallable`  
**Category**: `Navigation|Validation`  
**Returns**: `bool`  
**Purpose**: Check if path is clear of obstacles

**Parameters**:
- `PathPoints` (TArray<FVector>): Path to validate
- `ActorRadius` (float): Radius of actor that will use the path

---

Last updated: October 6, 2025
- `bIgnoreMovingActors` (bool): Whether to ignore dynamic obstacles

```cpp
bool IsPathClear(UObject* WorldContextObject, const TArray<FVector>& PathPoints, float ActorRadius, bool bIgnoreMovingActors = false);
```

**Usage**: Validate paths before committing to movement.

### Flying Navigation

#### SetFlyingNavigationParams
**Type**: `BlueprintCallable`  
**Category**: `Navigation|Flying`  
**Purpose**: Configure parameters for flying navigation

**Parameters**:
- `Actor` (AActor): Actor to configure
- `Params` (FDAIFlyingNavParams): Flying navigation parameters

```cpp
void SetFlyingNavigationParams(AActor* Actor, const FDAIFlyingNavParams& Params);
```

**Usage**: Customize flying behavior for different entity types.

#### GetNearestFlyableSpace
**Type**: `BlueprintCallable`  
**Category**: `Navigation|Flying`  
**Returns**: `bool`  
**Purpose**: Find nearest location suitable for flying entities

**Parameters**:
- `SearchLocation` (FVector): Location to search from
- `SearchRadius` (float): Radius to search within
- `MinClearance` (float): Minimum clearance required
- `OutLocation` (FVector): Found suitable location

```cpp
bool GetNearestFlyableSpace(UObject* WorldContextObject, const FVector& SearchLocation, float SearchRadius, float MinClearance, FVector& OutLocation);
```

**Usage**: Find safe locations for flying entities to navigate to.

### Surface Navigation

#### GetSurfaceNavigationPath
**Type**: `BlueprintCallable`  
**Category**: `Navigation|Spider`  
**Returns**: `bool`  
**Purpose**: Generate path following surface contours

**Parameters**:
- `Start` (FVector): Starting location on surface
- `Goal` (FVector): Target location on surface
- `OutPath` (TArray<FVector>): Generated surface path
- `OutNormals` (TArray<FVector>): Surface normals at each path point

```cpp
bool GetSurfaceNavigationPath(UObject* WorldContextObject, const FVector& Start, const FVector& Goal, TArray<FVector>& OutPath, TArray<FVector>& OutNormals);
```

**Usage**: Create paths that follow surface geometry for spider movement.

#### FindNearestWalkableSurface
**Type**: `BlueprintCallable`  
**Category**: `Navigation|Spider`  
**Returns**: `bool`  
**Purpose**: Find closest surface suitable for traversal

**Parameters**:
- `SearchLocation` (FVector): Location to search from
- `SearchRadius` (float): Maximum search distance
- `MaxSlopeAngle` (float): Maximum acceptable slope angle
- `OutLocation` (FVector): Found surface location
- `OutNormal` (FVector): Surface normal at found location

```cpp
bool FindNearestWalkableSurface(UObject* WorldContextObject, const FVector& SearchLocation, float SearchRadius, float MaxSlopeAngle, FVector& OutLocation, FVector& OutNormal);
```

**Usage**: Locate suitable surfaces for spider movement transitions.

### SmartObject Integration (Optional)

*Note: These functions require the DAI_SmartObject plugin to be loaded and enabled. They will fail gracefully if the plugin is not available.*

#### IsSmartObjectPluginAvailable
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `Navigation|SmartObject`  
**Returns**: `bool`  
**Purpose**: Check if DAI_SmartObject plugin is loaded and available

```cpp
bool IsSmartObjectPluginAvailable();
```

**Usage**: Use this to conditionally enable SmartObject-related features in your blueprints.

#### MoveActorToNearestSmartObjectSlot
**Type**: `BlueprintCallable`  
**Category**: `Navigation|SmartObject`  
**Returns**: `bool`  
**Purpose**: Find and move to the nearest SmartObject slot matching criteria

**Parameters**:
- `Actor` (AActor): Actor to move
- `SearchRadius` (float): Maximum search distance for SmartObjects
- `DesiredSlotTags` (FGameplayTagContainer): Tags to match for slot selection
- `OutSlotName` (FName): Name of the selected slot (output)
- `OutSmartObjectOwner` (AActor): Actor owning the SmartObject (output)

```cpp
bool MoveActorToNearestSmartObjectSlot(AActor* Actor, float SearchRadius, const FGameplayTagContainer& DesiredSlotTags, FName& OutSlotName, AActor*& OutSmartObjectOwner);
```

**Usage**: Navigate to interactive objects like chairs, workbenches, or cover points.

#### MoveAndReserveNearestSmartObjectSlot
**Type**: `BlueprintCallable`  
**Category**: `Navigation|SmartObject`  
**Returns**: `bool`  
**Purpose**: Move to nearest SmartObject slot and reserve it upon arrival

**Parameters**:
- `Actor` (AActor): Actor to move
- `SearchRadius` (float): Maximum search distance for SmartObjects
- `DesiredSlotTags` (FGameplayTagContainer): Tags to match for slot selection
- `OutSlotName` (FName): Name of the selected slot (output)
- `OutSmartObjectOwner` (AActor): Actor owning the SmartObject (output)

```cpp
bool MoveAndReserveNearestSmartObjectSlot(AActor* Actor, float SearchRadius, const FGameplayTagContainer& DesiredSlotTags, FName& OutSlotName, AActor*& OutSmartObjectOwner);
```

**Usage**: Ensure exclusive access to interactive objects during navigation.

## Blueprint Data Types

### EDAINavigationType (Navigation Type)
**Type**: `BlueprintType Enum`  
**Purpose**: Type of navigation system to use

**Values**:
- `Ground`: Standard ground-based navigation
- `Flying`: 3D flying navigation using distance fields
- `Spider`: Surface-following traversal navigation
- `Swimming`: Water-based navigation
- `Hybrid`: Combination of multiple navigation types

### FDAIFlyingNavParams (Flying Navigation Parameters)
**Type**: `BlueprintType Struct`  
**Purpose**: Configuration for flying navigation behavior

**Properties**:
- `PreferredAltitude` (float): Preferred flying height above ground
- `MinObstacleDistance` (float): Minimum distance to maintain from obstacles
- `TurnRadius` (float): Minimum turning radius for path generation
- `MaxClimbAngle` (float): Maximum angle for climbing movements
- `MaxDiveAngle` (float): Maximum angle for diving movements
- `bAvoidCrowdedAreas` (bool): Whether to avoid areas with many other actors

### FDAISpiderNavParams (Spider Navigation Parameters)
**Type**: `BlueprintType Struct`  
**Purpose**: Configuration for surface traversal navigation

**Properties**:
- `AttachmentStrength` (float): Strength of surface attachment
- `MaxSlopeAngle` (float): Maximum slope angle for traversal
- `SurfaceSearchDistance` (float): Distance to search for surfaces
- `TransitionSpeed` (float): Speed of surface-to-surface transitions
- `bCanTraverseOverhangs` (bool): Whether to allow upside-down movement
- `bAutoAttachToSurfaces` (bool): Automatically attach when near surfaces

### FDAICurvedPathParams (Curved Path Parameters)
**Type**: `BlueprintType Struct`  
**Purpose**: Configuration for curved path following

**Properties**:
- `CurveSmoothing` (float): Amount of smoothing to apply to path curves
- `LookAheadDistance` (float): Distance to look ahead for path planning
- `SpeedVariation` (float): Amount to vary speed based on path curvature
- `BankingAngle` (float): Maximum banking angle for turns
- `bMaintainAltitude` (bool): Whether to maintain consistent altitude
- `PathTolerance` (float): Acceptable deviation from exact path

### FDAINavigationRequest (Navigation Request)
**Type**: `BlueprintType Struct`  
**Purpose**: Complete request for navigation pathfinding

**Properties**:
- `StartLocation` (FVector): Starting point for navigation
- `GoalLocation` (FVector): Destination point
- `NavigationType` (EDAINavigationType): Type of navigation to use
- `RequestingActor` (AActor): Actor making the navigation request
- `Priority` (EDAINavPriority): Priority level for this request
- `SearchConstraints` (FDAINavSearchConstraints): Constraints for pathfinding
- `CallbackDelegate` (FDAINavCompletedDelegate): Callback for completion

### FDAINavSearchConstraints (Navigation Search Constraints)
**Type**: `BlueprintType Struct`  
**Purpose**: Constraints and limits for pathfinding operations

**Properties**:
- `MaxSearchDistance` (float): Maximum distance to search for paths
- `MaxSearchTime` (float): Maximum time to spend on pathfinding
- `ActorRadius` (float): Radius of actor for collision checking
- `ActorHeight` (float): Height of actor for clearance checking
- `bAllowPartialPaths` (bool): Whether to return incomplete paths
- `ExcludedAreas` (TArray<FBox>): Areas to avoid during pathfinding

## Component Properties

### DAICurvedPathFollowingComponent Properties

#### Movement Configuration
**Property**: `MovementSpeed`  
**Type**: `float`  
**Category**: `Curved Path`  
**Blueprint Access**: `Read/Write`  
**Default**: `400.0`  
**Purpose**: Base speed for path following movement

**Property**: `AccelerationRate`  
**Type**: `float`  
**Category**: `Curved Path`  
**Blueprint Access**: `Read/Write`  
**Default**: `800.0`  
**Purpose**: Rate of acceleration when starting movement

**Property**: `DecelerationRate`  
**Type**: `float`  
**Category**: `Curved Path`  
**Blueprint Access**: `Read/Write`  
**Default**: `1200.0`  
**Purpose**: Rate of deceleration when stopping

#### Path Smoothing
**Property**: `CurveSmoothing`  
**Type**: `float`  
**Category**: `Curved Path`  
**Blueprint Access**: `Read/Write`  
**Default**: `0.5`  
**Range**: `0.0-1.0`  
**Purpose**: Amount of smoothing to apply to path curves

**Property**: `LookAheadDistance`  
**Type**: `float`  
**Category**: `Curved Path`  
**Blueprint Access**: `Read/Write`  
**Default**: `200.0`  
**Purpose**: Distance to look ahead for path planning

### DAISpiderMovementComponent Properties

#### Surface Attachment
**Property**: `AttachmentStrength`  
**Type**: `float`  
**Category**: `Spider Movement`  
**Blueprint Access**: `Read/Write`  
**Default**: `1.0`  
**Purpose**: Strength of attachment to surfaces

**Property**: `SurfaceSearchDistance`  
**Type**: `float`  
**Category**: `Spider Movement`  
**Blueprint Access**: `Read/Write`  
**Default**: `100.0`  
**Purpose**: Distance to search for attachable surfaces

#### Movement Constraints
**Property**: `MaxSlopeAngle`  
**Type**: `float`  
**Category**: `Spider Movement`  
**Blueprint Access**: `Read/Write`  
**Default**: `90.0`  
**Range**: `0.0-180.0`  
**Purpose**: Maximum slope angle for surface traversal

**Property**: `bCanTraverseOverhangs`  
**Type**: `bool`  
**Category**: `Spider Movement`  
**Blueprint Access**: `Read/Write`  
**Default**: `true`  
**Purpose**: Whether entity can move on upside-down surfaces

### DAIFlyingNavigationComponent Properties

#### Flight Parameters
**Property**: `PreferredAltitude`  
**Type**: `float`  
**Category**: `Flying Navigation`  
**Blueprint Access**: `Read/Write`  
**Default**: `500.0`  
**Purpose**: Preferred height above ground for flying

**Property**: `MinObstacleDistance`  
**Type**: `float`  
**Category**: `Flying Navigation`  
**Blueprint Access**: `Read/Write`  
**Default**: `100.0`  
**Purpose**: Minimum distance to maintain from obstacles

#### Maneuverability
**Property**: `TurnRadius`  
**Type**: `float`  
**Category**: `Flying Navigation`  
**Blueprint Access**: `Read/Write`  
**Default**: `300.0`  
**Purpose**: Minimum turning radius for smooth flight

**Property**: `MaxClimbAngle`  
**Type**: `float`  
**Category**: `Flying Navigation`  
**Blueprint Access**: `Read/Write`  
**Default**: `45.0`  
**Purpose**: Maximum angle for climbing maneuvers

## Events and Delegates

### OnPathFollowingCompleted
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Navigation`  
**Purpose**: Fired when path following reaches destination

**Parameters**:
- `Actor` (AActor): Actor that completed path following
- `FinalLocation` (FVector): Final reached location
- `bReachedGoal` (bool): Whether the exact goal was reached

**Usage**: Trigger next actions when navigation completes.

### OnSurfaceAttached
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Navigation|Spider`  
**Purpose**: Fired when actor attaches to a surface

**Parameters**:
- `Actor` (AActor): Actor that attached to surface
- `SurfaceLocation` (FVector): Location on surface
- `SurfaceNormal` (FVector): Normal of attached surface

**Usage**: Update movement mode and visual effects for surface traversal.

### OnNavigationFailed
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Navigation`  
**Purpose**: Fired when pathfinding fails to find a valid route

**Parameters**:
- `Actor` (AActor): Actor whose navigation failed
- `RequestedGoal` (FVector): Goal that couldn't be reached
- `FailureReason` (EDAINavFailureReason): Reason for navigation failure

**Usage**: Implement fallback behaviors when navigation is impossible.

### OnObstacleEncountered
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Navigation`  
**Purpose**: Fired when moving actor encounters an unexpected obstacle

**Parameters**:
- `Actor` (AActor): Actor that encountered obstacle
- `ObstacleLocation` (FVector): Location of the obstacle
- `ObstacleActor` (AActor): The obstacle actor (if available)

**Usage**: Trigger avoidance behaviors or path recalculation.

## Developer Settings

Access via **Project Settings → Game → DAI Navigation**

### General Settings

#### Pathfinding Configuration
**Property**: `bEnable3DNavigation`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to enable 3D navigation features

**Property**: `DefaultNavigationType`  
**Type**: `EDAINavigationType`  
**Default**: `Ground`  
**Purpose**: Default navigation type for new navigation requests

**Property**: `PathfindingBudgetMs`  
**Type**: `float`  
**Default**: `5.0`  
**Range**: `1.0-16.0`  
**Purpose**: Maximum milliseconds per frame for pathfinding operations

#### Distance Field Settings
**Property**: `DistanceFieldResolution`  
**Type**: `int32`  
**Default**: `64`  
**Range**: `32-256`  
**Purpose**: Resolution of distance field for 3D navigation

**Property**: `DistanceFieldMaxDistance`  
**Type**: `float`  
**Default**: `2000.0`  
**Range**: `500.0-10000.0`  
**Purpose**: Maximum distance for distance field calculations

### Performance Settings

#### LOD Configuration
**Property**: `bEnableNavigationLOD`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to use LOD for navigation calculations

**Property**: `NavigationLODDistances`  
**Type**: `TArray<float>`  
**Default**: `[500, 1000, 2000]`  
**Purpose**: Distance thresholds for navigation LOD levels

#### Culling Settings
**Property**: `MaxConcurrentPathfinds`  
**Type**: `int32`  
**Default**: `10`  
**Range**: `1-50`  
**Purpose**: Maximum number of simultaneous pathfinding operations

**Property**: `PathfindingCullDistance`  
**Type**: `float`  
**Default**: `5000.0`  
**Range**: `1000.0-20000.0`  
**Purpose**: Distance at which to cull pathfinding operations

### Spider Navigation Settings

#### Surface Detection
**Property**: `SurfaceDetectionMethod`  
**Type**: `EDAISurfaceDetection`  
**Default**: `Raycast`  
**Purpose**: Method for detecting traversable surfaces

**Property**: `SurfaceSearchAngle`  
**Type**: `float`  
**Default**: `45.0`  
**Range**: `10.0-90.0`  
**Purpose**: Angle range for surface search operations

#### Transition Smoothing
**Property**: `bSmoothSurfaceTransitions`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to smooth transitions between surfaces

**Property**: `TransitionSmoothingTime`  
**Type**: `float`  
**Default**: `0.3`  
**Range**: `0.1-2.0`  
**Purpose**: Time to spend smoothing surface transitions

### Flying Navigation Settings

#### Obstacle Avoidance
**Property**: `ObstacleAvoidanceMethod`  
**Type**: `EDAIObstacleAvoidance`  
**Default**: `DistanceField`  
**Purpose**: Method for avoiding obstacles during flight

**Property**: `AvoidanceStrength`  
**Type**: `float`  
**Default**: `1.0`  
**Range**: `0.1-3.0`  
**Purpose**: Strength of obstacle avoidance forces

#### Flight Patterns
**Property**: `bUseFlockingBehavior`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to enable flocking behavior for flying entities

**Property**: `FlockingRadius`  
**Type**: `float`  
**Default**: `200.0`  
**Range**: `50.0-1000.0`  
**Purpose**: Radius for flocking behavior influence

### Debug Settings

#### Visualization
**Property**: `bDrawNavigationPaths`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to draw navigation paths in viewport

**Property**: `bDrawSurfaceNormals`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to draw surface normals for spider navigation

**Property**: `bDrawDistanceFields`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to visualize distance fields

#### Logging
**Property**: `bEnableNavigationLogging`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to enable detailed navigation logging

## Usage Examples

### Basic 3D Pathfinding
```blueprint
// Find flying path to target location
void NavigateToTarget(FVector TargetLocation)
{
    TArray<FVector> PathPoints;
    bool bFoundPath = UDAINavigationBlueprintLibrary::FindPath3D(
        this,
        GetActorLocation(),
        TargetLocation,
        EDAINavigationType::Flying,
        PathPoints,
        2000.0f
    );
    
    if (bFoundPath && PathPoints.Num() > 0)
    {
        // Begin following the generated path
        UDAINavigationBlueprintLibrary::FollowCurvedPath(
            this,
            PathPoints,
            500.0f, // Movement speed
            0.7f,   // Curve smoothing
            false   // Don't loop
        );
    }
}
```

### Spider Surface Traversal
```blueprint
// Enable spider movement and navigate on surfaces
void BeginSpiderMode()
{
    UDAISpiderMovementComponent* SpiderMovement = FindComponentByClass<UDAISpiderMovementComponent>();
    if (SpiderMovement)
    {
        // Configure spider parameters
        FDAISpiderNavParams SpiderParams;
        SpiderParams.AttachmentStrength = 1.5f;
        SpiderParams.MaxSlopeAngle = 120.0f;
        SpiderParams.bCanTraverseOverhangs = true;
        SpiderParams.bAutoAttachToSurfaces = true;
        
        SpiderMovement->SetSpiderParams(SpiderParams);
        
        // Attach to nearest surface
        FVector SurfaceLocation, SurfaceNormal;
        if (UDAINavigationBlueprintLibrary::FindNearestWalkableSurface(
            this,
            GetActorLocation(),
            100.0f,
            120.0f,
            SurfaceLocation,
            SurfaceNormal))
        {
            UDAINavigationBlueprintLibrary::AttachToSurface(
                this,
                SurfaceLocation,
                SurfaceNormal,
                SpiderParams.AttachmentStrength
            );
        }
    }
}

// Navigate to target while staying on surfaces
void SpiderNavigateToTarget(FVector TargetLocation)
{
    TArray<FVector> PathPoints;
    TArray<FVector> SurfaceNormals;
    
    bool bFoundPath = UDAINavigationBlueprintLibrary::GetSurfaceNavigationPath(
        this,
        GetActorLocation(),
        TargetLocation,
        PathPoints,
        SurfaceNormals
    );
    
    if (bFoundPath)
    {
        // Follow path while maintaining surface attachment
        UDAINavigationBlueprintLibrary::FollowCurvedPath(
            this,
            PathPoints,
            300.0f, // Slower speed for surface traversal
            0.8f,   // High smoothing for surface following
            false
        );
    }
}
```

### Flying Navigation with Obstacles
```blueprint
// Set up flying entity with obstacle avoidance
void InitializeFlyingNavigation()
{
    UDAIFlyingNavigationComponent* FlyingNav = FindComponentByClass<UDAIFlyingNavigationComponent>();
    if (FlyingNav)
    {
        FDAIFlyingNavParams FlyingParams;
        FlyingParams.PreferredAltitude = 800.0f;
        FlyingParams.MinObstacleDistance = 150.0f;
        FlyingParams.TurnRadius = 400.0f;
        FlyingParams.MaxClimbAngle = 30.0f;
        FlyingParams.MaxDiveAngle = 45.0f;
        FlyingParams.bAvoidCrowdedAreas = true;
        
        UDAINavigationBlueprintLibrary::SetFlyingNavigationParams(this, FlyingParams);
    }
}

// Navigate while maintaining safe altitude
void FlyToLocation(FVector Destination)
{
    // Find safe flying space near destination
    FVector SafeDestination;
    if (UDAINavigationBlueprintLibrary::GetNearestFlyableSpace(
        this,
        Destination,
        500.0f,
        200.0f, // Min clearance
        SafeDestination))
    {
        // Use the safe location as actual destination
        NavigateToTarget(SafeDestination);
    }
}
```

### GAS Integration for Movement Abilities
```blueprint
// Create navigation ability for dash movement
void ActivateDashAbility(FVector DashTarget)
{
    UDAINavigationAbilityComponent* NavAbility = FindComponentByClass<UDAINavigationAbilityComponent>();
    if (NavAbility)
    {
        // Create curved path for dash
        TArray<FVector> DashPath;
        DashPath.Add(GetActorLocation());
        
        // Add arc point for dramatic movement
        FVector MidPoint = (GetActorLocation() + DashTarget) * 0.5f;
        MidPoint.Z += 200.0f; // Arc height
        DashPath.Add(MidPoint);
        DashPath.Add(DashTarget);
        
        // Execute dash with high speed and low smoothing
        UDAINavigationBlueprintLibrary::FollowCurvedPath(
            this,
            DashPath,
            1200.0f, // High speed for dash
            0.2f,    // Low smoothing for snappy movement
            false
        );
        
        // Trigger visual effects
        PlayDashEffects();
    }
}

// Bind navigation events for ability feedback
void BeginPlay()
{
    Super::BeginPlay();
    
    UDAINavigationSubsystem* NavSubsystem = GetWorld()->GetSubsystem<UDAINavigationSubsystem>();
    NavSubsystem->OnPathFollowingCompleted.AddDynamic(this, &AMyCharacter::OnNavigationComplete);
}

UFUNCTION()
void OnNavigationComplete(AActor* Actor, FVector FinalLocation, bool bReachedGoal)
{
    if (Actor == this && bReachedGoal)
    {
        // End dash ability
        GetAbilitySystemComponent()->TryActivateAbilityByClass(UDashCompleteAbility::StaticClass());
    }
}
```

## Integration with Other Plugins

**DAI_Navigation is a standalone plugin** that functions independently while providing optional integration with other DAI plugins when available.

### DAI_SmartObject Integration (Optional)
- **Status**: Optional integration - requires DAI_SmartObject plugin to be enabled
- **Standalone Mode**: Navigation functions fully without SmartObject plugin
- **Integration Features**: When DAI_SmartObject is available:
  - **Contextual Navigation**: Smart objects can define custom navigation paths
  - **Interaction Points**: Navigation system can path to smart object interaction points
  - **Complex Behaviors**: Combine navigation with contextual interactions
- **Runtime Check**: Use `IsSmartObjectPluginAvailable()` to check availability
- **Blueprint Usage**: SmartObject navigation functions gracefully fail when plugin unavailable

### Gameplay Ability System
- **Movement Abilities**: Navigation abilities integrated with GAS framework
- **Attribute Effects**: Movement speed and navigation parameters affected by attributes
- **Ability Gating**: Navigation abilities can be restricted by gameplay conditions

### Niagara Integration
- **Path Visualization**: Niagara effects for displaying navigation paths
- **Movement Trails**: Visual feedback for complex movement abilities
- **Environmental Effects**: Particle effects for surface attachment and flight

### DAI_Hub Integration (Optional)
- **Service Registration**: Navigation subsystem can register with hub for discovery when available
- **Performance Coordination**: Can respect hub performance budgets for pathfinding when hub is present
- **Event Publishing**: Navigation events can be published through hub system when available

## Best Practices

### Performance Optimization
1. **Use appropriate navigation types** for different entity classes
2. **Implement LOD systems** for distance-based navigation complexity
3. **Cache frequent pathfinding results** to reduce computational overhead
4. **Use navigation culling** to limit active pathfinding operations
5. **Profile pathfinding performance** in complex scenarios

### Movement Design
1. **Design smooth transitions** between different navigation modes
2. **Provide visual feedback** for navigation state changes
3. **Implement fallback behaviors** when navigation fails
4. **Test navigation** with various entity sizes and movement speeds
5. **Consider player expectations** for movement responsiveness

### 3D Navigation
1. **Use distance fields** efficiently for flying navigation
2. **Implement proper obstacle avoidance** for safe flight paths
3. **Design clear aerial corridors** in level geometry
4. **Test navigation** at different altitudes and angles
5. **Provide visual indicators** for 3D navigation boundaries

### Surface Traversal
1. **Design surfaces** with appropriate traversal properties
2. **Test spider movement** on various surface types and angles
3. **Implement smooth surface transitions** for seamless movement
4. **Provide attachment feedback** through visual and audio cues
5. **Consider gameplay implications** of wall and ceiling movement

## Technical Notes

- **Thread Safety**: Pathfinding operations can use background threads
- **Memory Management**: Efficient path caching and cleanup systems
- **Platform Support**: Cross-platform navigation with platform-specific optimizations
- **Performance**: Optimized distance field calculations and path storage
- **Integration**: Seamless compatibility with Unreal's built-in navigation system
- **Plugin Independence**: Fully standalone - no hard dependencies on other DAI plugins
- **Optional Integration**: Uses runtime module loading and reflection for optional plugin integration
- **Graceful Degradation**: SmartObject functions fail safely when the plugin is not available

### Implementation Details

#### Standalone Architecture
- **No Compile-Time Dependencies**: Plugin builds and runs without any other DAI plugins
- **Runtime Plugin Detection**: Uses `FModuleManager` to check for optional plugin availability
- **Reflection-Based Integration**: Uses UE reflection system to access SmartObject functionality when available
- **Safe Function Calls**: All optional integration functions include availability checks

#### SmartObject Integration Pattern
```cpp
// Check plugin availability at runtime
if (!IsDAISmartObjectPluginLoaded()) {
    UE_LOG(LogTemp, Warning, TEXT("SmartObject plugin not available"));
    return false;
}

// Use reflection to access functionality without hard linking
UClass* SmartObjectClass = FindObject<UClass>(nullptr, TEXT("/Script/DAI_SmartObject.DAISmartObjectComponent"));
```

This pattern ensures the Navigation plugin remains functional even when SmartObject plugin is disabled or removed.

---

*For more information about Smart Object integration, see [DAI_SmartObject documentation](DAI_SmartObject.md).*  
*For hub integration details, see [DAI_Hub documentation](DAI_Hub.md).*  
*For GAS integration, see [DAI documentation](DAI.md).*