# DAI Plugins - Quick Reference Index

## Completed Plugin Documentation

### 1. [DAI_AI](DAI_AI_Guide.md)
AI perception, behavior trees, and smart object integration
- **Files:** 7 headers
- **Key Features:** EQS integration, perception configuration, smart object usage

### 2. [DAI_CoreContracts](DAI_CoreContracts_Guide.md)
Shared interfaces and contracts for plugin interoperability
- **Files:** 11 headers
- **Key Features:** Faction interface, smart object interface, save contracts

### 3. [DAI_Dismember](DAI_Dismember_Guide.md)
Skeletal mesh dismemberment system
- **Files:** 8 headers
- **Key Features:** Body part severing, gore effects, networked dismemberment

### 4. [DAI_Faction](DAI_Faction_Guide.md)
Team/faction management system with reputation
- **Files:** 7 headers
- **Key Features:** Team assignment, reputation tracking, faction relationships

### 5. [DAI_LoadDirector](DAI_LoadDirector_Guide.md)
Seamless level streaming and load management
- **Files:** 4 headers
- **Key Features:** Async loading, climb integration, level streaming

### 6. [DAI_Map](DAI_Map_Guide.md)
World map system with fog-of-war and fast travel
- **Files:** 13 headers
- **Key Features:** Map widgets, POI system, fast travel, fog-of-war

### 7. [DAI_Navigation](DAI_Navigation_Guide.md)
Enhanced navigation with dynamic obstacles and jump points
- **Files:** 5 headers
- **Key Features:** Jump point markers, dynamic navmesh, Blueprint utilities

### 8. [DAI_QuestManager](DAI_QuestManager_Guide.md)
Quest and objective tracking system
- **Files:** 4 headers
- **Key Features:** Quest data assets, objective tracking, save integration

### 9. [DAI_SmartObject](DAI_SmartObject_Guide.md)
Interactive object system with slot-based interactions
- **Files:** 10 headers
- **Key Features:** Slot reservation, networking, assassination chains

### 10. [DAI_Spawner](DAI_Spawner_Guide.md)
Actor spawning system with save/load and HISM support
- **Files:** 10 headers
- **Key Features:** Weighted spawning, cooldowns, async batching, HISM

### 11. [DAI_UltraSky](DAI_UltraSky_Guide.md)
Weather and atmospheric system with GAS integration
- **Files:** 27 headers
- **Key Features:** Time-of-day, weather biomes, GAS attributes, celestial effects

## Plugin Dependencies Matrix

```
Plugin              Requires            Optional
─────────────────────────────────────────────────────────────────
DAI_AI              CoreContracts       SmartObject, Faction
DAI_CoreContracts   -                   -
DAI_Dismember       CoreContracts       -
DAI_Faction         CoreContracts       -
DAI_LoadDirector    CoreContracts       Climb (external)
DAI_Map             CoreContracts       QuestManager, Faction
DAI_Navigation      CoreContracts       -
DAI_QuestManager    CoreContracts       -
DAI_SmartObject     CoreContracts       Faction, AI
DAI_Spawner         -                   LocalSave, Faction, Quest
DAI_UltraSky        GameplayAbilities   StateTree
```

## Architecture Patterns

### Soft Dependency Pattern
Used in: **DAI_Spawner** (LocalSave bridge)

Allows optional plugin integration without compile-time dependency:
```cpp
// Check for optional plugin at runtime
if (USpawnerServiceSubsystem* Subsystem = GetWorld()->GetSubsystem<USpawnerServiceSubsystem>())
{
    if (Subsystem->HasSaveSupport()) // Check via bridge interface
    {
        Subsystem->SaveSpawnState(); // Only call if available
    }
}
```

### Service Interface Pattern
Used in: **DAI_UltraSky**, **DAI_Faction**

Expose plugin functionality via interfaces:
```cpp
// C++ interface
class IDAIUltraSkyService
{
    virtual float GetTimeOfDay() const = 0;
    virtual FName GetCurrentCondition() const = 0;
};

// Blueprint interface (separate)
UINTERFACE(Blueprintable)
class UDAI_WeatherService : public UInterface {};
```

### Subsystem Pattern
Used in: **DAI_Spawner**, **DAI_Faction**, **DAI_Map**

World subsystems for per-level singletons:
```cpp
UCLASS()
class USpawnerServiceSubsystem : public UWorldSubsystem
{
    // Automatically created/destroyed with world
    // Access via: GetWorld()->GetSubsystem<USpawnerServiceSubsystem>()
};
```

### Data Asset Pattern
Used in: **All plugins**

Reusable configuration stored as .uasset files:
```cpp
UCLASS(BlueprintType)
class UDAIQuestData : public UPrimaryDataAsset
{
    UPROPERTY(EditAnywhere)
    FText QuestName;
    
    UPROPERTY(EditAnywhere)
    TArray<FObjectiveData> Objectives;
};
```

## GAS Integration

### Plugins Using GAS
- **DAI_UltraSky** - Weather as attributes (37 attributes)
- **DAI_SmartObject** - Assassination abilities
- **DAI_AI** (future) - AI abilities

### GAS Best Practices Implemented
✅ PreAttributeChange for runtime clamping  
✅ PostGameplayEffectExecute for callbacks  
✅ Proper DOREPLIFETIME replication  
✅ ATTRIBUTE_ACCESSORS macro usage  

## Performance Optimization

### Tick Optimization
- **UltraSky:** Configurable tick intervals (0-0.5s recommended)
- **SmartObject:** Event-driven (no tick)
- **Spawner:** Async batch processing

### Network Optimization
- **Faction:** Attribute-based replication with delta compression
- **SmartObject:** Slot state replication with relevancy
- **UltraSky:** GAS attribute replication with thresholds

### Memory Optimization
- **Spawner:** HISM for high-density spawning (100x reduction)
- **Map:** Lazy-loaded POI data
- **LoadDirector:** Streaming-aware resource management

## Common Integration Patterns

### Quest + Spawner
```cpp
// Spawn quest-specific enemies
void SpawnQuestEnemies(UDAIQuestData* Quest)
{
    TArray<ADAISpawnMarker*> Markers = GetQuestMarkers(Quest->QuestTag);
    for (ADAISpawnMarker* Marker : Markers)
    {
        AActor* Enemy = SpawnManager->SpawnAtMarker(Marker);
        TagEnemyForQuest(Enemy, Quest->QuestTag);
    }
}
```

### Faction + SmartObject
```cpp
// Only allow friendly faction to use smart object
bool CanUseSmartObject(AActor* User, USmartObjectComponent* Object)
{
    IDAIFactionAgentInterface* UserFaction = Cast<IDAIFactionAgentInterface>(User);
    IDAIFactionAgentInterface* ObjectFaction = Cast<IDAIFactionAgentInterface>(Object->GetOwner());
    
    return UserFaction && ObjectFaction && 
           UserFaction->IsFriendlyWith(ObjectFaction->GetGenericTeamId());
}
```

### Map + Quest
```cpp
// Reveal quest POI on map when objective activates
void OnObjectiveActivated(FGameplayTag ObjectiveTag)
{
    if (UDAIMapSubsystem* MapSys = GetWorld()->GetSubsystem<UDAIMapSubsystem>())
    {
        MapSys->RevealPOI(ObjectiveTag); // Show objective location on map
    }
}
```

### UltraSky + AI
```cpp
// AI behavior changes based on weather
void AEnemyAI::UpdateBehavior()
{
    if (IDAIUltraSkyService* Weather = GetWeatherService())
    {
        if (Weather->IsPrecipitating())
        {
            // Seek shelter during rain
            SetBehaviorMode(EAIBehavior::SeekShelter);
        }
        else if (Weather->GetTimeOfDay() > 20.0f) // Night time
        {
            // More aggressive at night
            SetBehaviorMode(EAIBehavior::Aggressive);
        }
    }
}
```

## Debug Commands Reference

### Common Debug Commands
```
// Logging
Log LogDAI[Plugin] Verbose
Log LogDAI[Plugin] Display

// Plugin-Specific
Faction.ShowTeams 1              # Show all faction teams
Spawner.ShowMarkers 1            # Show spawn markers
UltraSky.PrintBindingStatus      # Show sky component bindings
SmartObject.ShowSlots 1          # Show smart object slots
Quest.ShowActive                 # Show active quests
Map.ShowPOIs 1                   # Show map POIs

// Performance
Stat UnitGraph                   # Frame time graph
Stat SceneRendering              # Rendering stats
Stat Game                        # Game thread stats
```

## Blueprint Exposure

### Plugins with Extensive BP Support
1. **DAI_UltraSky** - Full weather control from BP
2. **DAI_Map** - Complete map UI system
3. **DAI_Navigation** - Path utilities
4. **DAI_SmartObject** - Interaction system
5. **DAI_QuestManager** - Quest progression

### Blueprint Function Libraries
- **UDAIUltraSkyFunctionLibrary** - Weather queries
- **UDAIMapUtilities** - Map helper functions
- **UDAINavigationBlueprintLibrary** - Navigation utilities
- **UDAIFactionLibrary** - Faction queries

## Code Quality Standards

### Documentation
✅ Beginner-friendly comments on all major files  
✅ Architecture explanations in class headers  
✅ Usage examples in documentation  

### Epic Best Practices
✅ GAS patterns (AttributeSets, Abilities)  
✅ Replication patterns (DOREPLIFETIME, RepNotify)  
✅ Performance optimization (tick intervals, async)  
✅ Interface design (virtual destructors via GENERATED_BODY)  

### Build Status
✅ All 11 plugins compile cleanly  
✅ No warnings or errors  
✅ UE 5.5 compatible  

## Future Roadmap

### Planned Features
- **DAI_Dialogue** - Conversation system
- **DAI_Inventory** - Item management
- **DAI_Combat** - Combat mechanics
- **DAI_Animation** - Animation utilities

### Planned Improvements
- Multi-level support for UltraSky
- Pool system for Spawner
- Enhanced AI perception
- Quest chain dependencies
- Map layer system

## Getting Started

1. **Choose Your Plugins** - Enable only what you need
2. **Check Dependencies** - Ensure required plugins are enabled
3. **Configure Settings** - Edit Project Settings for each plugin
4. **Read Plugin Guide** - Each plugin has detailed documentation
5. **Run Example Project** - See plugins in action

## Support & Resources

- **Documentation:** `/docs/plugins/` folder
- **Templates:** `/docs/templates/` folder
- **Examples:** `DAIExampleProject 5.5/` folder
- **Tools:** `/tools/` folder (build scripts, utilities)
