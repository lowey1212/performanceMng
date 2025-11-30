# DAI_Spawner Plugin Guide

## Overview
**DAI_Spawner** provides a flexible, performance-optimized actor spawning system with save/load support, weighted random selection, cooldowns, and HISM (Hierarchical Instanced Static Mesh) integration for high-density spawning.

## Architecture

### Core Components
- **USpawnerServiceSubsystem** - World subsystem managing spawn state and save/load
- **UDAISpawnManager** - Main spawn logic orchestrator (499 lines)
- **UDAI_SpawnerComponent** - Lightweight component for spawnable actors
- **ADAISpawnMarker** - Designer-placed marker defining spawn points
- **ASpawnerActor** - Editor preview actor for spawn visualization

### Key Features
1. **Weighted Random Spawning** - Priority-based spawn selection
2. **Save/Load Support** - Persistent spawn state via soft dependency pattern
3. **HISM Integration** - High-performance instanced mesh spawning
4. **Cooldown System** - Per-marker cooldown management
5. **Async Batching** - Deferred spawning to prevent frame hitches
6. **Volume Support** - Spawn within volumes or at markers

## File Structure

### Public Headers (10 files)
```
DAI_Spawner/Source/DAI_Spawner/Public/
├── SpawnerServiceSubsystem.h            # World subsystem
├── DAI_SpawnerComponent.h               # Spawnable actor component
├── DAISpawnMarker.h                     # Designer marker actor
├── SpawnerActor.h                       # Editor preview actor
├── DAISpawnManager.h                    # Main spawn manager
├── Interfaces/
│   ├── DAISpawnerService.h             # Spawner interface
│   └── DAILocalSaveFragmentProviderBridge.h # Save system bridge
├── SpawnerGameplayTags.h                # Spawn event tags
└── DAI_SpawnerLog.h                     # Log categories
```

## Usage Examples

### Basic Spawn Marker Setup
```cpp
// Place ADAISpawnMarker in level
ADAISpawnMarker* Marker = SpawnActor<ADAISpawnMarker>(Location);
Marker->SpawnClasses.Add(AEnemyActor::StaticClass());
Marker->bUseWeightedRandomSelection = true;
Marker->SpawnWeights.Add(10.0f); // Relative spawn weight
```

### Weighted Spawning
```cpp
// Configure multiple spawn options with weights
Marker->SpawnClasses = {
    AWeakEnemy::StaticClass(),   // Weight 50 (common)
    AStrongEnemy::StaticClass(), // Weight 20 (uncommon)
    ABossEnemy::StaticClass()    // Weight 5 (rare)
};
Marker->SpawnWeights = {50.0f, 20.0f, 5.0f};
Marker->bUseWeightedRandomSelection = true;
```

### HISM Spawning (High Performance)
```cpp
// Spawn many static meshes efficiently
Marker->bUseHISM = true;
Marker->HISMStaticMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Meshes/SM_Rock"));
Marker->HISMInstanceCount = 100; // Spawn 100 instances
Marker->HISMScatterRadius = 1000.0f; // Within 10m radius
```

### Cooldown System
```cpp
// Prevent immediate respawning
Marker->bUseCooldown = true;
Marker->CooldownSeconds = 60.0f; // Wait 1 minute before respawn
Marker->bRandomizeCooldown = true;
Marker->CooldownRandomRange = FVector2D(30.0f, 90.0f); // 30-90 seconds
```

### Async Batch Spawning
```cpp
// Spawn many actors without frame hitches
UDAISpawnManager* Manager = GetWorld()->GetSubsystem<USpawnerServiceSubsystem>()->GetSpawnManager();

TArray<FSpawnRequest> Requests;
for (int32 i = 0; i < 100; ++i)
{
    FSpawnRequest Request;
    Request.SpawnClass = AEnemyActor::StaticClass();
    Request.Location = GetRandomLocation();
    Requests.Add(Request);
}

Manager->BatchSpawnAsync(Requests, 10); // Spawn 10 per frame
```

### Volume-Based Spawning
```cpp
// Spawn randomly within volume bounds
AVolume* SpawnVolume = GetSpawnVolume();
Marker->bUseVolumeSpawning = true;
Marker->SpawnVolume = SpawnVolume;
Marker->MaxSpawnsInVolume = 50;
```

## Save/Load Integration

### Soft Dependency Pattern
The spawner uses a bridge interface to avoid hard dependency on LocalSave plugin:

```cpp
// Check if save system is available
if (USpawnerServiceSubsystem* Subsystem = GetWorld()->GetSubsystem<USpawnerServiceSubsystem>())
{
    if (Subsystem->HasSaveSupport())
    {
        // Save spawn state
        Subsystem->SaveSpawnState();
    }
}
```

### Save Fragment Provider Bridge
```cpp
// Plugin implements IDAILocalSaveFragmentProviderBridge if LocalSave plugin exists
// Spawner queries bridge at runtime to enable save/load features
// No compile-time dependency required
```

## Configuration

### Spawn Manager Settings
```cpp
UDAISpawnManager* Manager = Subsystem->GetSpawnManager();

// Async spawning configuration
Manager->MaxSpawnsPerFrame = 10;
Manager->bEnableAsyncSpawning = true;

// Cooldown management
Manager->GlobalCooldownMultiplier = 1.0f; // Adjust all cooldowns globally
Manager->bPersistCooldownsOnSave = true;
```

### Component Settings
```cpp
// On spawned actors
UDAI_SpawnerComponent* SpawnerComp = Actor->FindComponentByClass<UDAI_SpawnerComponent>();
SpawnerComp->SourceMarker = Marker; // Track which marker spawned this
SpawnerComp->bDestroyOnDeath = true;
SpawnerComp->bNotifyMarkerOnDestroy = true; // Tell marker to start cooldown
```

## Gameplay Tags

### Spawn Events
```cpp
// Tags broadcast when spawning occurs
GameplayTag.Spawner.SpawnBegin     // Before spawn
GameplayTag.Spawner.SpawnComplete  // After spawn
GameplayTag.Spawner.SpawnFailed    // On failure
GameplayTag.Spawner.CooldownStart  // Cooldown begins
GameplayTag.Spawner.CooldownEnd    // Cooldown ends
```

## Network Replication

### Authority-Only Spawning
```cpp
// Spawning only occurs on server
if (HasAuthority())
{
    SpawnManager->SpawnAtMarker(Marker);
}
// Clients receive replicated actors via normal replication
```

### Marker Replication
```cpp
// Markers replicate their state
UPROPERTY(Replicated)
bool bIsOnCooldown;

UPROPERTY(Replicated)
float RemainingCooldownTime;
```

## Performance Optimization

### HISM vs Actor Spawning
```cpp
// Use HISM for:
// - Static decorative objects (rocks, plants)
// - No gameplay logic required
// - High density (100+ instances)

// Use Actor spawning for:
// - AI enemies with behavior
// - Interactive objects
// - Objects with components/logic
```

### Batch Processing
```cpp
// Spread expensive operations across frames
Manager->SetMaxSpawnsPerFrame(5); // Only spawn 5 actors per frame
Manager->SetBatchProcessingInterval(0.1f); // Process every 0.1 seconds
```

## Debugging

### Console Commands
```
// Enable verbose logging
Log LogDAISpawner Verbose

// Show all active spawn markers
Spawner.ShowMarkers 1

// Show cooldown timers
Spawner.ShowCooldowns 1

// Force spawn at all markers
Spawner.ForceSpawnAll
```

### Log Categories
```cpp
UE_LOG(LogDAISpawner, Log, TEXT("Spawned actor at marker: %s"), *Marker->GetName());
UE_LOG(LogDAISpawner, Warning, TEXT("Spawn failed: No valid spawn locations"));
UE_LOG(LogDAISpawner, Error, TEXT("Marker missing SpawnClasses array"));
```

## Common Patterns

### Respawn on Death
```cpp
// In Actor's Destroyed() or OnDeath()
void AEnemyActor::OnDeath()
{
    if (UDAI_SpawnerComponent* SpawnerComp = FindComponentByClass<UDAI_SpawnerComponent>())
    {
        if (ADAISpawnMarker* Marker = SpawnerComp->SourceMarker)
        {
            Marker->StartCooldownAndRespawn();
        }
    }
}
```

### Wave Spawning
```cpp
// Spawn multiple waves with delays
void SpawnWave(int32 WaveNumber)
{
    TArray<ADAISpawnMarker*> Markers = GetWaveMarkers(WaveNumber);
    
    for (ADAISpawnMarker* Marker : Markers)
    {
        SpawnManager->SpawnAtMarker(Marker);
    }
    
    // Next wave after cooldown
    GetWorld()->GetTimerManager().SetTimer(
        WaveTimerHandle,
        FTimerDelegate::CreateUObject(this, &AThis::SpawnWave, WaveNumber + 1),
        30.0f, // 30 seconds between waves
        false
    );
}
```

### Procedural Population
```cpp
// Procedurally place spawn markers
void PopulateArea(FBox AreaBounds, int32 Count)
{
    for (int32 i = 0; i < Count; ++i)
    {
        FVector Location = FMath::RandPointInBox(AreaBounds);
        
        ADAISpawnMarker* Marker = SpawnActor<ADAISpawnMarker>(Location);
        Marker->SpawnClasses = GetRandomEnemyTypes();
        Marker->bUseWeightedRandomSelection = true;
        
        // Immediate spawn
        SpawnManager->SpawnAtMarker(Marker);
    }
}
```

## Integration with Other Systems

### Quest System Integration
```cpp
// Spawn specific enemies for quest objectives
void SpawnQuestEnemies(FGameplayTag QuestTag)
{
    TArray<ADAISpawnMarker*> QuestMarkers = GetMarkersByTag(QuestTag);
    
    for (ADAISpawnMarker* Marker : QuestMarkers)
    {
        AActor* Enemy = SpawnManager->SpawnAtMarker(Marker);
        
        // Tag enemy for quest tracking
        if (IGameplayTagAssetInterface* TagInterface = Cast<IGameplayTagAssetInterface>(Enemy))
        {
            TagInterface->GetOwnedGameplayTags().AddTag(QuestTag);
        }
    }
}
```

### Faction Integration
```cpp
// Assign faction to spawned actors
void ADAISpawnMarker::PostSpawnActor(AActor* SpawnedActor)
{
    if (IDAIFactionAgentInterface* FactionAgent = Cast<IDAIFactionAgentInterface>(SpawnedActor))
    {
        FactionAgent->SetGenericTeamId(DesiredTeamID);
    }
}
```

## Known Limitations

1. **No Cross-Level Spawning** - Markers only spawn in their own level
2. **Save System Optional** - Save/load requires separate LocalSave plugin
3. **HISM Limitations** - HISM instances cannot have individual logic/components
4. **Single Manager** - One spawn manager per world (no multi-manager support)

## Migration Notes

### From Previous Versions
- `DAISaveFragmentProvider_REMOVED_DO_NOT_USE.tmp` deleted (deprecated save interface)
- Marker vs SpawnerActor distinction clarified (Marker = runtime, SpawnerActor = editor preview)
- Soft dependency pattern added for LocalSave plugin

## Dependencies

### Required
- None (standalone plugin)

### Optional
- **DAI_LocalSave** - Enables save/load functionality via bridge pattern
- **DAI_Faction** - For faction assignment to spawned actors
- **DAI_QuestManager** - For quest-based spawning

## Best Practices

1. **Use HISM for static objects** - 10-100x better performance than actor spawning
2. **Set appropriate cooldowns** - Prevent spawn spam, balance gameplay
3. **Batch async spawning** - Avoid frame hitches with large spawn counts
4. **Weight distributions carefully** - Common=50+, Uncommon=10-20, Rare=1-5
5. **Save spawn state** - Use save system to persist spawn cooldowns between sessions

## Future Enhancements

- Pool system for frequently spawned actors
- Density-based auto-culling
- LOD system for distant spawned actors
- Event-driven spawning (sound triggers, player proximity)
- Spawn analytics (track what spawns where, when)
