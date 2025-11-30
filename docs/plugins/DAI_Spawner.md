# DAI_Spawner Plugin Documentation

## Overview

**DAI_Spawner** is a comprehensive spawning system for Unreal Engine 5.5 that provides Blueprint spawn helpers and Gameplay Ability System (GAS) integration for runtime actor creation. The system offers intelligent spawn management, resource pooling, performance optimization, and seamless integration with other DAI plugins for dynamic content generation.

### Key Features
- 🎭 **Blueprint Spawn Helpers**: Simplified actor spawning with enhanced functionality
- 🎯 **GAS Integration**: Spawn abilities and ability-driven spawning mechanics
- 🔄 **Object Pooling**: Efficient reuse of frequently spawned actors
- 📊 **Performance Management**: Spawn budgeting and optimization systems
- 🌍 **Spatial Management**: Location-based spawning with collision avoidance
- 🎮 **Dynamic Content**: Runtime spawn pattern generation and modification
- 🔧 **Configurable Templates**: Reusable spawn configurations and presets
- 📡 **Hub Integration**: Event-driven spawning coordination

## Architecture

The DAI_Spawner system consists of:
- **Spawner Subsystem**: Central spawn coordination and management
- **Spawn Pools**: Object pooling for performance optimization
- **Spawn Templates**: Reusable spawn configurations
- **Location Services**: Intelligent spawn point selection
- **Integration Layer**: Hooks for GAS, Hub, and other systems

## Core Components

### DAISpawnerSubsystem
*World subsystem managing all spawning operations*

**Type**: `World Subsystem`  
**Interfaces**: `IDAISpawnerService`  
**File**: `DAISpawnerSubsystem.h`

Central service for spawn management, pooling, and performance coordination.

### DAISpawnPoolComponent
*Component for object pooling functionality*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `Spawner|Pool`  
**File**: `DAISpawnPoolComponent.h`

Manages pools of reusable actors for efficient spawning and despawning.

### DAISpawnLocationComponent
*Component for spawn point management*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `Spawner|Location`  
**File**: `DAISpawnLocationComponent.h`

Defines and manages spawn points with validation and selection logic.

### DAISpawnAbilityComponent
*Component for GAS-integrated spawning*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `Spawner|GAS`  
**File**: `DAISpawnAbilityComponent.h`

Provides ability system integration for spawn-related gameplay abilities.

## Blueprint Functions

### Core Spawning Operations

#### SpawnActorAdvanced
**Type**: `BlueprintCallable`  
**Category**: `Spawner`  
**Returns**: `AActor*`  
**Purpose**: Spawn an actor with enhanced options and validation

**Parameters**:
- `ActorClass` (TSubclassOf<AActor>): Class of actor to spawn
- `SpawnTransform` (FTransform): World transform for spawning
- `SpawnParams` (FDAISpawnParameters): Additional spawn configuration
- `bUsePooling` (bool): Whether to use object pooling if available

```cpp
AActor* SpawnActorAdvanced(UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform, const FDAISpawnParameters& SpawnParams, bool bUsePooling = true);
```

**Usage**: Primary function for spawning actors with full feature support.

#### SpawnFromTemplate
**Type**: `BlueprintCallable`  
**Category**: `Spawner`  
**Returns**: `AActor*`  
**Purpose**: Spawn an actor using a predefined template

**Parameters**:
- `SpawnTemplate` (UDAISpawnTemplate): Template defining spawn parameters
- `SpawnLocation` (FVector): Override location for spawning
- `SpawnRotation` (FRotator): Override rotation for spawning

```cpp
AActor* SpawnFromTemplate(UObject* WorldContextObject, UDAISpawnTemplate* SpawnTemplate, const FVector& SpawnLocation = FVector::ZeroVector, const FRotator& SpawnRotation = FRotator::ZeroRotator);
```

**Usage**: Spawn actors using designer-created templates for consistency.

#### DespawnActor
**Type**: `BlueprintCallable`  
**Category**: `Spawner`  
**Returns**: `bool`  
**Purpose**: Despawn an actor with pooling support

**Parameters**:
- `Actor` (AActor): Actor to despawn
- `bForceDestroy` (bool): Whether to force destroy instead of pooling
- `DespawnDelay` (float): Delay before despawning (0 = immediate)

```cpp
bool DespawnActor(UObject* WorldContextObject, AActor* Actor, bool bForceDestroy = false, float DespawnDelay = 0.0f);
```

**Usage**: Efficiently remove actors with automatic pooling when possible.

### Spawn Location Management

#### FindSpawnLocation
**Type**: `BlueprintCallable`  
**Category**: `Spawner|Location`  
**Returns**: `bool`  
**Purpose**: Find a suitable spawn location near a target point

**Parameters**:
- `TargetLocation` (FVector): Desired spawn location
- `SearchRadius` (float): Radius to search for valid spawn points
- `SpawnConstraints` (FDAISpawnConstraints): Constraints for spawn validation
- `OutSpawnTransform` (FTransform): Found valid spawn transform

```cpp
bool FindSpawnLocation(UObject* WorldContextObject, const FVector& TargetLocation, float SearchRadius, const FDAISpawnConstraints& SpawnConstraints, FTransform& OutSpawnTransform);
```

**Usage**: Intelligently place spawned actors to avoid collisions and ensure valid placement.

#### RegisterSpawnPoint
**Type**: `BlueprintCallable`  
**Category**: `Spawner|Location`  
**Returns**: `bool`  
**Purpose**: Register a location as a designated spawn point

**Parameters**:
- `SpawnPoint` (AActor): Actor marking the spawn point
- `SpawnTypes` (FGameplayTagContainer): Types of actors that can spawn here
- `Priority` (int32): Priority level for this spawn point

```cpp
bool RegisterSpawnPoint(UObject* WorldContextObject, AActor* SpawnPoint, const FGameplayTagContainer& SpawnTypes, int32 Priority = 0);
```

**Usage**: Set up designer-placed spawn points for controlled actor placement.

#### GetNearbySpawnPoints
**Type**: `BlueprintCallable`  
**Category**: `Spawner|Location`  
**Returns**: `TArray<AActor*>`  
**Purpose**: Get all spawn points within range of a location

**Parameters**:
- `Location` (FVector): Center point for search
- `SearchRadius` (float): Range to search within
- `SpawnType` (FGameplayTag): Type of spawn point to find

```cpp
TArray<AActor*> GetNearbySpawnPoints(UObject* WorldContextObject, const FVector& Location, float SearchRadius, FGameplayTag SpawnType);
```

**Usage**: Find available spawn points for dynamic content generation.

### Object Pooling

#### CreateSpawnPool
**Type**: `BlueprintCallable`  
**Category**: `Spawner|Pool`  
**Returns**: `bool`  
**Purpose**: Create a new object pool for specific actor types

**Parameters**:
- `PoolName` (FString): Unique name for the pool
- `ActorClass` (TSubclassOf<AActor>): Class of actors to pool
- `InitialSize` (int32): Initial number of actors to pre-spawn
- `MaxSize` (int32): Maximum pool size

```cpp
bool CreateSpawnPool(UObject* WorldContextObject, const FString& PoolName, TSubclassOf<AActor> ActorClass, int32 InitialSize, int32 MaxSize);
```

**Usage**: Set up pooling for frequently spawned actors like projectiles or effects.

#### GetPooledActor
**Type**: `BlueprintCallable`  
**Category**: `Spawner|Pool`  
**Returns**: `AActor*`  
**Purpose**: Get an actor from the object pool

**Parameters**:
- `PoolName` (FString): Name of the pool to get actor from
- `SpawnTransform` (FTransform): Transform to place the pooled actor
- `bActivateActor` (bool): Whether to activate the actor immediately

```cpp
AActor* GetPooledActor(UObject* WorldContextObject, const FString& PoolName, const FTransform& SpawnTransform, bool bActivateActor = true);
```

**Usage**: Efficiently reuse pooled actors for performance optimization.

#### ReturnToPool
**Type**: `BlueprintCallable`  
**Category**: `Spawner|Pool`  
**Returns**: `bool`  
**Purpose**: Return an actor to its object pool

**Parameters**:
- `Actor` (AActor): Actor to return to pool
- `bDeactivateActor` (bool): Whether to deactivate actor before pooling

```cpp
bool ReturnToPool(UObject* WorldContextObject, AActor* Actor, bool bDeactivateActor = true);
```

**Usage**: Return finished actors to pools for later reuse.

### GAS Integration

#### SpawnWithAbility
**Type**: `BlueprintCallable`  
**Category**: `Spawner|GAS`  
**Returns**: `AActor*`  
**Purpose**: Spawn an actor and immediately grant it a gameplay ability

**Parameters**:
- `ActorClass` (TSubclassOf<AActor>): Class of actor to spawn
- `SpawnTransform` (FTransform): Transform for spawning
- `AbilityToGrant` (TSubclassOf<UGameplayAbility>): Ability to grant on spawn
- `AbilityLevel` (int32): Level of the ability to grant

```cpp
AActor* SpawnWithAbility(UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform, TSubclassOf<UGameplayAbility> AbilityToGrant, int32 AbilityLevel = 1);
```

**Usage**: Create actors with immediate ability grants for gameplay mechanics.

#### TriggerSpawnAbility
**Type**: `BlueprintCallable`  
**Category**: `Spawner|GAS`  
**Returns**: `bool`  
**Purpose**: Trigger a spawn-related ability on an actor

**Parameters**:
- `Actor` (AActor): Actor to trigger ability on
- `SpawnAbilityTag` (FGameplayTag): Tag identifying the spawn ability
- `SpawnTargets` (TArray<FVector>): Target locations for spawning

```cpp
bool TriggerSpawnAbility(UObject* WorldContextObject, AActor* Actor, FGameplayTag SpawnAbilityTag, const TArray<FVector>& SpawnTargets);
```

**Usage**: Execute abilities that spawn other actors or objects.

### Spawn Patterns

#### SpawnInPattern
**Type**: `BlueprintCallable`  
**Category**: `Spawner|Pattern`  
**Returns**: `TArray<AActor*>`  
**Purpose**: Spawn multiple actors in a geometric pattern

**Parameters**:
- `ActorClass` (TSubclassOf<AActor>): Class of actors to spawn
- `CenterLocation` (FVector): Center point of the pattern
- `Pattern` (EDAISpawnPattern): Type of geometric pattern
- `PatternSize` (float): Size/radius of the pattern
- `ActorCount` (int32): Number of actors to spawn

```cpp
TArray<AActor*> SpawnInPattern(UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, const FVector& CenterLocation, EDAISpawnPattern Pattern, float PatternSize, int32 ActorCount);
```

**Usage**: Create formations, defensive positions, or decorative arrangements.

#### SpawnWave
**Type**: `BlueprintCallable`  
**Category**: `Spawner|Pattern`  
**Returns**: `bool`  
**Purpose**: Spawn a wave of actors over time

**Parameters**:
- `WaveDefinition` (FDAISpawnWave): Definition of the spawn wave
- `WaveStartLocation` (FVector): Starting location for the wave
- `bStartImmediately` (bool): Whether to start spawning immediately

```cpp
bool SpawnWave(UObject* WorldContextObject, const FDAISpawnWave& WaveDefinition, const FVector& WaveStartLocation, bool bStartImmediately = true);
```

**Usage**: Create timed waves of enemies, reinforcements, or environmental effects.

## Blueprint Data Types

### FDAISpawnParameters (Spawn Parameters)
**Type**: `BlueprintType Struct`  
**Purpose**: Configuration for advanced actor spawning

**Properties**:
- `Owner` (AActor): Actor that owns the spawned actor
- `Instigator` (APawn): Pawn that instigated the spawn
- `SpawnCollisionHandling` (ESpawnActorCollisionHandlingMethod): How to handle spawn collisions
- `bDeferConstruction` (bool): Whether to defer actor construction
- `InitialTags` (FGameplayTagContainer): Tags to assign on spawn
- `LifeSpan` (float): Automatic lifespan for spawned actor (0 = permanent)
- `bAllowPooling` (bool): Whether this actor can be pooled

### FDAISpawnConstraints (Spawn Constraints)
**Type**: `BlueprintType Struct`  
**Purpose**: Constraints for spawn location validation

**Properties**:
- `MinDistanceFromActors` (float): Minimum distance from other actors
- `MaxSlope` (float): Maximum ground slope angle
- `RequiredSpace` (FVector): Required free space dimensions
- `ForbiddenTags` (FGameplayTagContainer): Tags that prevent spawning
- `RequiredTags` (FGameplayTagContainer): Tags required for spawning
- `bRequireGroundContact` (bool): Whether spawn location must be on ground
- `bAvoidWater` (bool): Whether to avoid spawning in water

### EDAISpawnPattern (Spawn Pattern)
**Type**: `BlueprintType Enum`  
**Purpose**: Geometric patterns for multi-actor spawning

**Values**:
- `Circle`: Spawn actors in a circular arrangement
- `Line`: Spawn actors in a straight line
- `Grid`: Spawn actors in a grid pattern
- `Random`: Spawn actors at random locations within area
- `Formation`: Spawn actors in a tactical formation
- `Spiral`: Spawn actors in a spiral pattern

### FDAISpawnWave (Spawn Wave)
**Type**: `BlueprintType Struct`  
**Purpose**: Definition for timed spawn waves

**Properties**:
- `WaveName` (FString): Identifier for this wave
- `ActorClasses` (TArray<TSubclassOf<AActor>>): Classes to spawn in this wave
- `SpawnCounts` (TArray<int32>): Number of each class to spawn
- `SpawnInterval` (float): Time between individual spawns
- `WaveDuration` (float): Total duration of the wave
- `SpawnLocations` (TArray<FVector>): Specific spawn locations
- `bRandomizeOrder` (bool): Whether to randomize spawn order

### FDAIPoolConfiguration (Pool Configuration)
**Type**: `BlueprintType Struct`  
**Purpose**: Configuration for object pools

**Properties**:
- `PoolName` (FString): Unique identifier for the pool
- `ActorClass` (TSubclassOf<AActor>): Class of actors in this pool
- `InitialSize` (int32): Number of actors to pre-spawn
- `MaxSize` (int32): Maximum number of actors in pool
- `GrowthIncrement` (int32): Number of actors to add when expanding
- `bAutoExpand` (bool): Whether to automatically expand when depleted
- `ShrinkThreshold` (float): Usage threshold below which pool shrinks

### FDAISpawnTemplate (Spawn Template)
**Type**: `BlueprintType Struct`  
**Purpose**: Reusable spawn configuration template

**Properties**:
- `TemplateName` (FString): Name of this template
- `ActorClass` (TSubclassOf<AActor>): Class to spawn
- `DefaultTransform` (FTransform): Default spawn transform
- `SpawnParameters` (FDAISpawnParameters): Spawn configuration
- `AbilitiesToGrant` (TArray<TSubclassOf<UGameplayAbility>>): Abilities to grant on spawn
- `InitialGameplayEffects` (TArray<TSubclassOf<UGameplayEffect>>): Effects to apply on spawn

## Component Properties

### DAISpawnPoolComponent Properties

#### Pool Configuration
**Property**: `PoolName`  
**Type**: `FString`  
**Category**: `Spawn Pool`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Unique identifier for this pool

**Property**: `ActorClass`  
**Type**: `TSubclassOf<AActor>`  
**Category**: `Spawn Pool`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Class of actors managed by this pool

**Property**: `InitialPoolSize`  
**Type**: `int32`  
**Category**: `Spawn Pool`  
**Blueprint Access**: `Read/Write`  
**Default**: `10`  
**Purpose**: Number of actors to pre-spawn in the pool

**Property**: `MaxPoolSize`  
**Type**: `int32`  
**Category**: `Spawn Pool`  
**Blueprint Access**: `Read/Write`  
**Default**: `50`  
**Purpose**: Maximum number of actors this pool can contain

#### Performance Settings
**Property**: `bAutoExpand`  
**Type**: `bool`  
**Category**: `Spawn Pool`  
**Blueprint Access**: `Read/Write`  
**Default**: `true`  
**Purpose**: Whether to automatically expand pool when depleted

**Property**: `GrowthIncrement`  
**Type**: `int32`  
**Category**: `Spawn Pool`  
**Blueprint Access**: `Read/Write`  
**Default**: `5`  
**Purpose**: Number of actors to add when expanding pool

### DAISpawnLocationComponent Properties

#### Location Settings
**Property**: `SpawnRadius`  
**Type**: `float`  
**Category**: `Spawn Location`  
**Blueprint Access**: `Read/Write`  
**Default**: `100.0`  
**Purpose**: Radius around this location where spawning can occur

**Property**: `SpawnTypes`  
**Type**: `FGameplayTagContainer`  
**Category**: `Spawn Location`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Types of actors that can spawn at this location

#### Validation Settings
**Property**: `bRequireGroundContact`  
**Type**: `bool`  
**Category**: `Spawn Location`  
**Blueprint Access**: `Read/Write`  
**Default**: `true`  
**Purpose**: Whether spawned actors must be on solid ground

**Property**: `MaxSpawnSlope`  
**Type**: `float`  
**Category**: `Spawn Location`  
**Blueprint Access**: `Read/Write`  
**Default**: `30.0`  
**Purpose**: Maximum ground slope angle for spawning

**Property**: `MinDistanceBetweenSpawns`  
**Type**: `float`  
**Category**: `Spawn Location`  
**Blueprint Access**: `Read/Write`  
**Default**: `200.0`  
**Purpose**: Minimum distance between spawned actors

## Events and Delegates

### OnActorSpawned
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Spawner`  
**Purpose**: Fired when an actor is successfully spawned

**Parameters**:
- `SpawnedActor` (AActor): Actor that was spawned
- `SpawnLocation` (FVector): Location where actor was spawned
- `bFromPool` (bool): Whether actor came from object pool

**Usage**: Track spawned actors, trigger effects, or update spawn statistics.

### OnActorDespawned
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Spawner`  
**Purpose**: Fired when an actor is despawned

**Parameters**:
- `DespawnedActor` (AActor): Actor that was despawned
- `bReturnedToPool` (bool): Whether actor was returned to pool
- `DespawnReason` (EDAIDespawnReason): Reason for despawning

**Usage**: Clean up references, update counters, or trigger despawn effects.

### OnSpawnFailed
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Spawner`  
**Purpose**: Fired when spawn attempt fails

**Parameters**:
- `AttemptedClass` (TSubclassOf<AActor>): Class that failed to spawn
- `AttemptedLocation` (FVector): Location where spawn was attempted
- `FailureReason` (EDAISpawnFailureReason): Reason for spawn failure

**Usage**: Handle spawn failures, find alternative locations, or update AI behavior.

### OnPoolExpanded
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Spawner|Pool`  
**Purpose**: Fired when an object pool expands

**Parameters**:
- `PoolName` (FString): Name of the expanded pool
- `NewSize` (int32): New size of the pool
- `ActorsAdded` (int32): Number of actors added

**Usage**: Monitor pool growth and performance implications.

## Developer Settings

Access via **Project Settings → Game → DAI Spawner**

### General Settings

#### Spawn Management
**Property**: `bEnableSpawnSystem`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to enable enhanced spawning system

**Property**: `MaxConcurrentSpawns`  
**Type**: `int32`  
**Default**: `20`  
**Range**: `1-100`  
**Purpose**: Maximum number of actors that can spawn simultaneously

**Property**: `SpawnBudgetMs`  
**Type**: `float`  
**Default**: `2.0`  
**Range**: `0.5-10.0`  
**Purpose**: Performance budget for spawn operations per frame

#### Default Constraints
**Property**: `DefaultSpawnConstraints`  
**Type**: `FDAISpawnConstraints`  
**Purpose**: Default constraints applied to all spawn operations

**Property**: `GlobalSpawnCooldown`  
**Type**: `float`  
**Default**: `0.1`  
**Range**: `0.0-5.0`  
**Purpose**: Minimum time between any spawn operations

### Object Pooling

#### Pool Management
**Property**: `bEnableObjectPooling`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to enable object pooling system

**Property**: `MaxTotalPooledActors`  
**Type**: `int32`  
**Default**: `1000`  
**Range**: `100-10000`  
**Purpose**: Maximum total number of pooled actors across all pools

**Property**: `PoolCleanupInterval`  
**Type**: `float`  
**Default**: `60.0`  
**Range**: `10.0-300.0`  
**Purpose**: Seconds between pool cleanup operations

#### Pool Optimization
**Property**: `bAutoOptimizePools`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to automatically optimize pool sizes

**Property**: `PoolShrinkThreshold`  
**Type**: `float`  
**Default**: `0.3`  
**Range**: `0.1-0.8`  
**Purpose**: Usage threshold below which pools shrink

### Performance Settings

#### Spawn Rate Limiting
**Property**: `bLimitSpawnRate`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to limit spawn rate for performance

**Property**: `MaxSpawnsPerSecond`  
**Type**: `float`  
**Default**: `50.0`  
**Range**: `1.0-200.0`  
**Purpose**: Maximum spawns allowed per second

#### Memory Management
**Property**: `bPreventMemoryLeaks`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to enable additional memory leak prevention

**Property**: `ActorLifespanLimit`  
**Type**: `float`  
**Default**: `300.0`  
**Range**: `30.0-3600.0`  
**Purpose**: Maximum lifespan for spawned actors (seconds)

### Location Services

#### Spawn Point Management
**Property**: `bUseSpawnPointSystem`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to use registered spawn point system

**Property**: `SpawnPointSearchRadius`  
**Type**: `float`  
**Default**: `1000.0`  
**Range**: `100.0-5000.0`  
**Purpose**: Default radius for spawn point searches

#### Validation Settings
**Property**: `bValidateSpawnLocations`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to validate spawn locations before spawning

**Property**: `SpawnValidationAccuracy`  
**Type**: `EDAISpawnValidation`  
**Default**: `Medium`  
**Purpose**: Accuracy level for spawn location validation

### Debug Settings

#### Visualization
**Property**: `bDrawSpawnDebug`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to draw spawn debug visualization

**Property**: `bDrawPoolStats`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to display pool statistics on screen

#### Logging
**Property**: `bLogSpawnEvents`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to log spawn and despawn events

**Property**: `bLogPoolOperations`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to log object pool operations

## Usage Examples

### Basic Spawning with Pooling
```blueprint
// Set up object pool for projectiles
void InitializeProjectilePool()
{
    bool bPoolCreated = UDAISpawnerBlueprintLibrary::CreateSpawnPool(
        this,
        "ProjectilePool",
        ProjectileClass,
        20, // Initial size
        100 // Max size
    );
    
    if (bPoolCreated)
    {
        UE_LOG(LogSpawner, Log, TEXT("Projectile pool created successfully"));
    }
}

// Spawn projectile using pool
void FireProjectile(const FVector& StartLocation, const FVector& Direction)
{
    // Calculate spawn transform
    FTransform SpawnTransform;
    SpawnTransform.SetLocation(StartLocation);
    SpawnTransform.SetRotation(FQuat::FindBetweenNormals(FVector::ForwardVector, Direction));
    
    // Get pooled projectile
    AActor* Projectile = UDAISpawnerBlueprintLibrary::GetPooledActor(
        this,
        "ProjectilePool",
        SpawnTransform,
        true // Activate immediately
    );
    
    if (Projectile)
    {
        // Configure projectile
        SetProjectileDirection(Projectile, Direction);
        SetProjectileSpeed(Projectile, ProjectileSpeed);
        
        // Set lifespan for automatic return to pool
        Projectile->SetLifeSpan(5.0f);
    }
}

// Return projectile to pool when hit
void OnProjectileHit(AActor* Projectile, const FHitResult& Hit)
{
    // Handle hit effects
    PlayImpactEffects(Hit.Location, Hit.Normal);
    
    // Return to pool instead of destroying
    UDAISpawnerBlueprintLibrary::ReturnToPool(this, Projectile, true);
}
```

### Advanced Spawn Location Management
```blueprint
// Find valid spawn location for enemy
void SpawnEnemyNearPlayer(APlayerController* Player)
{
    FVector PlayerLocation = Player->GetPawn()->GetActorLocation();
    
    // Set up spawn constraints
    FDAISpawnConstraints Constraints;
    Constraints.MinDistanceFromActors = 500.0f; // Don't spawn too close to player
    Constraints.RequiredSpace = FVector(100, 100, 200); // Space needed for enemy
    Constraints.bRequireGroundContact = true;
    Constraints.MaxSlope = 30.0f;
    Constraints.bAvoidWater = true;
    
    // Find spawn location
    FTransform SpawnTransform;
    bool bFoundLocation = UDAISpawnerBlueprintLibrary::FindSpawnLocation(
        this,
        PlayerLocation + FVector(FMath::RandRange(-1000, 1000), FMath::RandRange(-1000, 1000), 0),
        1500.0f, // Search radius
        Constraints,
        SpawnTransform
    );
    
    if (bFoundLocation)
    {
        // Set up spawn parameters
        FDAISpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandling = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
        SpawnParams.InitialTags.AddTag(FGameplayTag::RequestGameplayTag("Enemy.Spawned"));
        SpawnParams.LifeSpan = 0.0f; // Permanent
        SpawnParams.bAllowPooling = false; // Unique enemy, don't pool
        
        // Spawn enemy
        AActor* Enemy = UDAISpawnerBlueprintLibrary::SpawnActorAdvanced(
            this,
            EnemyClass,
            SpawnTransform,
            SpawnParams,
            false // Don't use pooling
        );
        
        if (Enemy)
        {
            // Set up enemy AI target
            SetEnemyTarget(Enemy, Player->GetPawn());
            
            // Trigger spawn effects
            PlaySpawnEffects(SpawnTransform.GetLocation());
        }
    }
    else
    {
        // Retry later if no valid location found
        GetWorld()->GetTimerManager().SetTimer(
            SpawnRetryTimer,
            FTimerDelegate::CreateUObject(this, &AMyGameMode::SpawnEnemyNearPlayer, Player),
            5.0f,
            false
        );
    }
}
```

### Pattern Spawning for Formations
```blueprint
// Spawn defensive formation
void SpawnDefensiveFormation(const FVector& CenterLocation, int32 DefenderCount)
{
    // Spawn defenders in circle formation
    TArray<AActor*> Defenders = UDAISpawnerBlueprintLibrary::SpawnInPattern(
        this,
        DefenderClass,
        CenterLocation,
        EDAISpawnPattern::Circle,
        300.0f, // Formation radius
        DefenderCount
    );
    
    // Configure each defender
    for (int32 i = 0; i < Defenders.Num(); i++)
    {
        AActor* Defender = Defenders[i];
        if (Defender)
        {
            // Set formation position index
            SetFormationIndex(Defender, i);
            
            // Face outward from center
            FVector DirectionFromCenter = (Defender->GetActorLocation() - CenterLocation).GetSafeNormal();
            Defender->SetActorRotation(DirectionFromCenter.Rotation());
            
            // Set defensive behavior
            SetDefensiveBehavior(Defender, CenterLocation);
        }
    }
}

// Spawn attack wave
void SpawnAttackWave(const FVector& WaveOrigin)
{
    // Define spawn wave
    FDAISpawnWave AttackWave;
    AttackWave.WaveName = "AttackWave_" + FString::FromInt(CurrentWaveNumber);
    AttackWave.ActorClasses = {LightEnemyClass, HeavyEnemyClass, RangedEnemyClass};
    AttackWave.SpawnCounts = {5, 2, 3}; // 5 light, 2 heavy, 3 ranged
    AttackWave.SpawnInterval = 2.0f; // 2 seconds between spawns
    AttackWave.WaveDuration = 30.0f; // 30 second wave
    AttackWave.bRandomizeOrder = true;
    
    // Start the wave
    bool bWaveStarted = UDAISpawnerBlueprintLibrary::SpawnWave(
        this,
        AttackWave,
        WaveOrigin,
        true // Start immediately
    );
    
    if (bWaveStarted)
    {
        CurrentWaveNumber++;
        ShowWaveStartNotification(AttackWave.WaveName);
    }
}
```

### GAS Integration for Spawn Abilities
```blueprint
// Create spawning ability
UCLASS()
class MYGAME_API USpawnMinionsAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    TSubclassOf<AActor> MinionClass;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    int32 MinionsToSpawn = 3;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    float SpawnRadius = 500.0f;

protected:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
                                const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override
    {
        Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
        
        if (MinionClass)
        {
            AActor* Caster = ActorInfo->AvatarActor.Get();
            
            // Spawn minions in circle around caster
            TArray<AActor*> SpawnedMinions = UDAISpawnerBlueprintLibrary::SpawnInPattern(
                Caster,
                MinionClass,
                Caster->GetActorLocation(),
                EDAISpawnPattern::Circle,
                SpawnRadius,
                MinionsToSpawn
            );
            
            // Grant loyalty to spawned minions
            for (AActor* Minion : SpawnedMinions)
            {
                SetMinionMaster(Minion, Caster);
                
                // Apply spawn effects
                PlayMinionSpawnEffects(Minion);
            }
        }
        
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
    }
};

// Use spawn ability
void CastSummonMinions(AActor* Caster)
{
    UAbilitySystemComponent* ASC = Caster->FindComponentByClass<UAbilitySystemComponent>();
    if (ASC)
    {
        FGameplayTag SpawnAbilityTag = FGameplayTag::RequestGameplayTag("Ability.Spawn.Minions");
        ASC->TryActivateAbilitiesByTag(FGameplayTagContainer(SpawnAbilityTag));
    }
}
```

### Performance Monitoring and Optimization
```blueprint
// Monitor spawn system performance
void MonitorSpawnPerformance()
{
    UDAISpawnerSubsystem* SpawnerSystem = GetWorld()->GetSubsystem<UDAISpawnerSubsystem>();
    if (SpawnerSystem)
    {
        // Get performance metrics
        FDAISpawnerMetrics Metrics = SpawnerSystem->GetPerformanceMetrics();
        
        // Check if spawn rate is too high
        if (Metrics.SpawnsPerSecond > MaxRecommendedSpawnRate)
        {
            // Reduce spawn frequency
            ReduceSpawnFrequency();
        }
        
        // Check pool efficiency
        for (const auto& PoolStat : Metrics.PoolStatistics)
        {
            if (PoolStat.Value.EfficiencyRating < 0.5f)
            {
                // Pool is inefficient, consider adjusting size
                OptimizePool(PoolStat.Key);
            }
        }
        
        // Monitor memory usage
        if (Metrics.TotalPooledActors > MaxPooledActors)
        {
            // Too many pooled actors, trigger cleanup
            TriggerPoolCleanup();
        }
    }
}

// Optimize spawn system based on performance
void OptimizeSpawnSystem()
{
    // Adjust spawn constraints based on performance
    if (GetCurrentFrameRate() < TargetFrameRate)
    {
        // Reduce spawn validation accuracy for performance
        ReduceSpawnValidationAccuracy();
        
        // Increase spawn cooldowns
        IncreaseSpawnCooldowns();
        
        // Limit concurrent spawns
        ReduceMaxConcurrentSpawns();
    }
    else if (GetCurrentFrameRate() > TargetFrameRate * 1.2f)
    {
        // Performance is good, can increase quality
        IncreaseSpawnValidationAccuracy();
        DecreaseSpawnCooldowns();
    }
}
```

## Integration with Other Plugins

### DAI_Hub Integration
- **Service Registration**: Spawner subsystem registers with hub for discovery
- **Event Publishing**: Spawn events published through hub system
- **Performance Coordination**: Spawn operations respect hub performance budgets

### DAI_PerfMngr Integration
- **Performance Budgeting**: Spawn operations respect performance constraints
- **Adaptive Spawning**: Spawn frequency adjusts based on performance metrics
- **Resource Monitoring**: Pool sizes adapt to memory and CPU usage

### DAI_AI Integration
- **Intelligent Spawning**: AI systems can request spawns for tactical purposes
- **Behavior Coordination**: Spawned AI actors coordinate with existing systems
- **Performance Awareness**: AI spawn requests consider current system load

### Gameplay Ability System
- **Spawn Abilities**: Full integration with GAS for spawn-related abilities
- **Effect Integration**: Spawned actors can have effects applied immediately
- **Attribute Scaling**: Spawn parameters can scale with character attributes

## Best Practices

### Performance Optimization
1. **Use object pooling** for frequently spawned actors
2. **Limit concurrent spawns** to maintain frame rate
3. **Validate spawn locations efficiently** with appropriate accuracy levels
4. **Monitor pool efficiency** and adjust sizes based on usage patterns
5. **Implement spawn rate limiting** to prevent performance spikes

### Spawn Location Management
1. **Use registered spawn points** for controlled placement
2. **Implement proper validation** to prevent invalid spawns
3. **Consider gameplay impact** when placing spawned actors
4. **Test with various terrain types** and environmental conditions
5. **Provide fallback locations** when primary spots are invalid

### Object Pool Design
1. **Size pools appropriately** based on expected usage
2. **Implement pool shrinking** to manage memory usage
3. **Monitor pool hit rates** and adjust sizes accordingly
4. **Use separate pools** for different actor types
5. **Clean up pools regularly** to prevent memory leaks

### GAS Integration
1. **Design spawn abilities** with clear costs and cooldowns
2. **Consider ability interactions** with spawned actors
3. **Implement proper cleanup** when abilities are cancelled
4. **Test ability scaling** with different character levels
5. **Handle network replication** properly in multiplayer

## Technical Notes

- **Thread Safety**: Spawn operations designed for game thread usage
- **Memory Management**: Efficient pooling and cleanup systems
- **Platform Support**: Cross-platform spawning with platform-specific optimizations
- **Performance**: Optimized location validation and actor management
- **Network Support**: Proper replication handling for multiplayer spawning

---

*For more information about hub integration, see [DAI_Hub documentation](DAI_Hub.md).*  
*For performance management integration, see [DAI_PerfMngr documentation](DAI_PerfMngr.md).*  
*For GAS integration, see [DAI documentation](DAI.md).*

---

Last updated: October 6, 2025