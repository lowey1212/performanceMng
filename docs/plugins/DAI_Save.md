# DAI_Save Plugin Documentation

## Overview

**DAI_Save** is a comprehensive save system for Unreal Engine 5.5 that provides game state persistence, profile management, autosave functionality, and optional online integration. The system supports multiple save slots, encrypted save data, replay functionality, and seamless integration with Gameplay Ability System (GAS) for persistent character data.

### Key Features
- 💾 **Complete Save System**: Full game state persistence and restoration
- 👤 **Profile Management**: Multiple user profiles with individual save slots
- ⚡ **Auto-Save**: Intelligent automatic saving with configurable triggers
- 🔒 **Encryption Support**: Secure save data with encryption capabilities
- 🎬 **Replay System**: Record and playback gameplay sessions
- 🌐 **Online Integration**: Cloud save support through online subsystems
- 🎯 **GAS Integration**: Persistent Gameplay Ability System data
- 📊 **Player Statistics**: Comprehensive stat tracking and persistence
- 🔧 **Fragment System**: Modular save data for plugin extensibility
- 🏷️ **Tagged Saves**: Organize saves with metadata and tags

## Architecture

The DAI_Save system consists of:
- **Save Subsystem**: Central save/load coordination
- **Fragment Providers**: Modular save data components
- **Replay System**: Session recording and playback
- **Online Integration**: Cloud save and synchronization
- **GAS Components**: Persistent ability system data

## Core Components

### SaveSubsystem
*GameInstance subsystem managing all save operations*

**Type**: `GameInstance Subsystem`  
**Interfaces**: `IDAISaveService`  
**File**: `SaveSubsystem.h`

Central service for save/load operations, profile management, and online integration.

### GASSaveComponent
*Component for Gameplay Ability System persistence*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `Save|GAS`  
**File**: `GASSaveComponent.h`

Handles saving and loading of GAS attributes, abilities, and effects.

### SaveReplaySubsystem
*GameInstance subsystem for replay recording and management*

**Type**: `GameInstance Subsystem`  
**File**: `SaveReplaySubsystem.h`

Manages gameplay session recording, storage, and playback functionality.

## Blueprint Functions

### Core Save Operations
**Type**: `BlueprintCallable`  
**Category**: `Save`  
**Returns**: `bool`  
**Purpose**: Save game state to a named slot
### Security Settings
Encryption is supported via AES when you call `SetEncryptionKey` with a 32-byte key. Other methods and checksums are not enabled by default.

### Replay System
**Usage**: Primary function for saving game state to persistent storage.

#### SaveGameEx
**Type**: `BlueprintCallable`  
**Category**: `Save`  
### FPlayerStatsMap (Player Statistics Map)
- `bCaptureThumbnail` (bool): Whether to capture a screenshot thumbnail
- `UserIndex` (int32): User profile index (default: 0)
- `PlayerStats` (FPlayerStatsMap): Optional player statistics to include

```cpp
bool SaveGameEx(UObject* WorldContextObject, USaveGame* SaveGameObject, const FString& SlotName, const FString& Tag, bool bCaptureThumbnail = false, int32 UserIndex = 0, const FPlayerStatsMap& PlayerStats = FPlayerStatsMap());
```

**Usage**: Enhanced saving with metadata, thumbnails, and organizational features.

#### LoadGame
**Category**: `Save`  
**Returns**: `USaveGame*`  
**Purpose**: Load game state from a named slot
**Parameters**:
- `SaveGameClass` (TSubclassOf<USaveGame>): Class of save game object to create
- `SlotName` (FString): Name of the save slot to load
### Online Integration
### Performance Settings
- Cloud save support is provided as a stub storage provider that defers to the local provider by default. Hook it up to your backend to enable real cloud sync.
**Usage**: Create unique slot names for auto-saves or timestamped saves.

#### ListSaveSlots
**Type**: `BlueprintCallable`  
**Category**: `Save`  
**Returns**: `TArray<FString>`  
**Purpose**: Get list of all available save slots for a user

**Parameters**:
- `UserIndex` (int32): User profile index (default: 0)

```cpp
TArray<FString> ListSaveSlots(UObject* WorldContextObject, int32 UserIndex = 0);
```

**Usage**: Display available saves in UI or manage save slot organization.

#### GetSaveCount
**Type**: `BlueprintCallable`  
**Category**: `Save`  
**Returns**: `int32`  
**Purpose**: Get total number of save slots for a user

**Parameters**:
- `UserIndex` (int32): User profile index (default: 0)

int32 GetSaveCount(UObject* WorldContextObject, int32 UserIndex = 0);
```

**Usage**: Check save slot limits or display save statistics.

### Auto-Save System

**Purpose**: Perform automatic save with slot rotation

**Parameters**:
- `SaveGameObject` (USaveGame): Save game object containing data to save
- `Prefix` (FString): Prefix for auto-save slot names
- `MaxSlots` (int32): Maximum number of auto-save slots to maintain (default: 3)
- `UserIndex` (int32): User profile index (default: 0)
- `PlayerStats` (FPlayerStatsMap): Optional player statistics to include

```cpp
bool AutoSave(UObject* WorldContextObject, USaveGame* SaveGameObject, const FString& Prefix, int32 MaxSlots = 3, int32 UserIndex = 0, const FPlayerStatsMap& PlayerStats = FPlayerStatsMap());
```

**Usage**: Implement automatic saving with intelligent slot management and rotation.

#### Autosave Event (PIE)
Bind to `USaveSubsystem::OnAutoSaveRequested` from your GameInstance/GameMode and call `AutoSave` or `QuickSave` with your SaveGame object. The interval is configured in Project Settings → Game → DAI Save.

Note on config storage: the save plugin’s developer settings class uses `Config=Editor`, so autosave options are read from the editor config, not DefaultGame.ini. To enable autosave via .ini, add this to `Config/DefaultEditor.ini`:

```
[/Script/DAI_Save.SaveDeveloperSettings]
bAutoSave=True
AutoSaveInterval=15.0
```

When PIE starts, you should see `LogDAISave: Autosave timer started (interval=XX.Xs)` in the Output Log if it’s working. If it doesn’t start, you’ll see a verbose message explaining why.

- Example: See `Source/DAIExampleProject/` for `UDAIExample_AutoSaveBinder` which auto-rotates 5 slots with prefix `Auto`.

Example Save class: `UDAISimpleSaveGame` (in `Source/DAIExampleProject/Public/DAISimpleSaveGame.h`) is used by the binder to persist simple example state (level, health, checkpoint). Replace with your project class as needed.

#### Integrity and Compression (optional)
- Checksums: Enable “Compute Checksums” to store MD5 checksums for .sav and .fragments.json. On load, mismatches are logged as warnings.
- Compression: Enable “Compress Saves” to zlib-compress the save payload before encryption. Decompressed automatically on load.

#### Export / Import
- Blueprint: `ExportSaveSlot(SlotName, UserIndex, DestinationZipPath)` and `ImportSaveSlot(DestinationSlotName, UserIndex, SourceZipPath)` on `USaveSubsystem`.
- Console helpers: `Save.Export <SlotName> <UserIndex> <DestZip>` and `Save.Import <SlotName> <UserIndex> <SourceZip>`.
- Now in-engine: uses a minimal embedded ZIP writer/reader (store-only; no compression) — no external PowerShell dependency. If something goes wrong with ZIP creation/extraction, it falls back to the `*.zip.folder` convention.

Editor UI (optional): Open Window → "Save Tools" to access a simple Export/Import panel with file pickers. This works in PIE/Editor and invokes the same subsystem functions.

#### Cloud mock provider
- Settings: Enable “Cloud Mock”, set “Cloud Endpoint Dir”. Save writes mirror the `.sav` plus sidecar files (`.meta`, `.png`, `.fragments.json`) to that folder; loads prefer the cloud copies when present and also pull sidecars back into the local cache.
- This is a file-based mock to exercise cloud flows without a real backend. Replace with a real provider later.

#### SetSaveCooldown
**Type**: `BlueprintCallable`  
**Category**: `Save`  
**Purpose**: Set minimum time between save operations

**Parameters**:
- `Cooldown` (float): Minimum seconds between saves

```cpp
void SetSaveCooldown(UObject* WorldContextObject, float Cooldown);
```

**Usage**: Prevent save spam and maintain performance during frequent save triggers.

### Combat Integration

#### BeginCombat
**Type**: `BlueprintCallable`  
**Category**: `Save`  
**Purpose**: Notify save system that combat has started

```cpp
void BeginCombat(UObject* WorldContextObject);
```

**Usage**: Disable auto-saving during combat to prevent save-scumming.

#### EndCombat
**Type**: `BlueprintCallable`  
**Category**: `Save`  
**Purpose**: Notify save system that combat has ended

```cpp
void EndCombat(UObject* WorldContextObject);
```

**Usage**: Re-enable auto-saving and potentially trigger post-combat save.

### Security and Encryption

#### SetEncryptionKey
**Type**: `BlueprintCallable`  
**Category**: `Save`  
**Purpose**: Set encryption key for secure save data

**Parameters**:
- `Key` (TArray<uint8>): Encryption key bytes

```cpp
void SetEncryptionKey(UObject* WorldContextObject, const TArray<uint8>& Key);
```

**Usage**: Enable save file encryption for anti-tampering protection.

### Replay System

#### PlayReplay
See the Replay System section below for the currently supported Blueprint functions.

## Blueprint Data Types

### FPlayerStatsMap (Player Statistics Map)
**Type**: `BlueprintType Struct`  
**Purpose**: Lightweight container for analytics stats

**Properties**:
- `Stats` (TMap<FString, float>): Map of statistic names to numeric values

### FSaveSlotInfo (Save Slot Information)
**Type**: `BlueprintType Struct`  
**Purpose**: Metadata about a save slot

**Properties**:
- `SlotName` (FString): Name of the save slot
- `DisplayName` (FString): Human-readable display name
- `SaveTime` (FDateTime): When the save was created
- `PlayTime` (float): Total playtime when save was created
- `LevelName` (FString): Level/map name where save was created
- `PlayerLevel` (int32): Character level at time of save
- `Tag` (FString): Optional metadata tag
- `bHasThumbnail` (bool): Whether a screenshot thumbnail exists
- `FileSize` (int64): Size of save file in bytes

### FReplayInfo (Replay Information)
**Type**: `BlueprintType Struct`  
**Purpose**: Metadata about a recorded gameplay session

**Properties**:
- `SessionName` (FString): Name of the replay session
- `RecordTime` (FDateTime): When recording started
- `Duration` (float): Length of recorded session in seconds
- `PlayerCount` (int32): Number of players in the session
- `LevelName` (FString): Map where session was recorded
- `GameMode` (FString): Game mode during recording
- `Version` (FString): Game version when recorded

## Component Properties

### GASSaveComponent Properties

#### Save Configuration
**Property**: `bAutoSaveAttributes`  
**Type**: `bool`  
**Category**: `GAS Save`  
**Blueprint Access**: `Read/Write`  
**Default**: `true`  
**Purpose**: Whether to automatically save GAS attributes

**Property**: `bAutoSaveAbilities`  
**Type**: `bool`  
**Category**: `GAS Save`  
**Blueprint Access**: `Read/Write`  
**Default**: `true`  
**Purpose**: Whether to automatically save granted abilities

**Property**: `bAutoSaveEffects`  
**Type**: `bool`  
**Category**: `GAS Save`  
**Blueprint Access**: `Read/Write`  
**Default**: `false`  
**Purpose**: Whether to automatically save active gameplay effects

#### Exclusion Filters
**Property**: `ExcludedAttributes`  
**Type**: `TArray<FGameplayAttribute>`  
**Category**: `GAS Save`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Attributes to exclude from save data

**Property**: `ExcludedAbilityTags`  
**Type**: `FGameplayTagContainer`  
**Category**: `GAS Save`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Ability tags to exclude from save data

## Developer Settings

### SaveSubsystem
*GameInstance subsystem managing all save operations*

**Type**: `GameInstance Subsystem`  
**Interfaces**: `IDAISaveService`  
**File**: `SaveSubsystem.h`

Central service for save/load operations, profile management, fragment persistence, and optional analytics hooks.
Access via **Project Settings → Game → DAI Save**

### General Settings

#### Auto-Save Configuration
**Property**: `bEnableAutoSave`  
**Type**: `bool`  
### SaveReplaySubsystem
*GameInstance subsystem for replay recording and management*

**Type**: `GameInstance Subsystem`  
**File**: `SaveReplaySubsystem.h`

Manages instant-replay style snapshot buffering, storage, and debug playback.
**Default**: `true`  
**Purpose**: Whether automatic saving is enabled globally

**Property**: `AutoSaveInterval`  
**Type**: `float`  
**Default**: `300.0`  
**Range**: `60.0-3600.0`  
**Purpose**: Seconds between automatic saves

**Default**: `5`  
**Range**: `1-20`  
**Purpose**: Maximum number of auto-save slots to maintain

#### Save File Settings
**Property**: `SaveFileExtension`  
**Type**: `FString`  
**Default**: `.sav`  
**Purpose**: File extension for save files

**Property**: `bCompressSaveData`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to compress save file data

**Property**: `CompressionLevel`  
**Type**: `int32`  
**Default**: `6`  
**Range**: `1-9`  
**Purpose**: Compression level (higher = smaller files, slower saves)

### Security Settings

Encryption is supported via AES when you call `SetEncryptionKey` with a 32-byte key.
### Replay System

The current replay helpers provide an instant-replay style buffer you fill manually:

- Add input snapshots during play:
    ```cpp
    void AddInputSnapshot(UObject* WorldContextObject, const FInputSnapshot& Snapshot);
    ```
- Save that rolling buffer to a slot:
    ```cpp
    bool SaveInstantReplay(UObject* WorldContextObject, const FString& SlotName);
    ```
- Load and play back a saved replay:
    ```cpp
    UReplaySaveGame* LoadReplay(UObject* WorldContextObject, const FString& SlotName);
    void PlayReplay(UObject* WorldContextObject, UReplaySaveGame* Replay);
    void DrawReplayDebug(UObject* WorldContextObject, UReplaySaveGame* Replay, FLinearColor Color = FLinearColor::Green, float Duration = 5.f);
    ```

#### Anti-Tampering
Checksums are not included by default; you can extend the subsystem to add integrity validation if needed.
### FPlayerStatsMap (Player Statistics Map)
**Type**: `BlueprintType Struct`  
**Purpose**: Lightweight container for analytics stats

**Properties**:
- `Stats` (TMap<FString, float>): Map of statistic names to numeric values
**Property**: `bValidateOnLoad`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to validate checksums when loading

### Online Integration

#### Cloud Save Settings
Use the provided cloud storage provider stub as a starting point; wire it up to your online backend for real synchronization.
## Developer Settings

Access via **Project Settings → Game → DAI Save**

### Available Settings (current build)

- `bAutoSave` (bool): Enable periodic autosaves while playing in editor.
- `AutoSaveInterval` (float): Seconds between automatic saves (PIE).
- `bEnableCustomNaming` (bool): Allow manual naming of save slots by player.
- `DifficultySlots` (array): Map difficulty to preferred slot names.

Note: The subsystem doesn’t auto-save by itself because it doesn’t own a concrete USaveGame class. Use these settings to drive your own autosave logic in game mode or a manager and call `AutoSave`/`QuickSave` with your SaveGame object.

### Performance Settings
### Online Integration
- Cloud save support is provided as a stub storage provider that defers to the local provider by default. Hook it up to your backend to enable real cloud sync.
#### Memory Management
**Property**: `MaxConcurrentSaves`  
**Type**: `int32`  
**Default**: `3`  
**Range**: `1-10`  
**Purpose**: Maximum number of simultaneous save operations

**Property**: `SaveTimeoutSeconds`  
**Type**: `float`  
**Default**: `30.0`  
**Range**: `5.0-120.0`  
**Purpose**: Maximum time to wait for save operations

#### Threading
**Property**: `bUseAsyncSaving`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to perform save operations on background threads

### Replay Settings

#### Recording Configuration
**Property**: `bEnableReplaySystem`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether replay recording is available

**Property**: `MaxReplayDuration`  
**Type**: `float`  
**Default**: `3600.0`  
**Range**: `60.0-7200.0`  
**Purpose**: Maximum duration for replay recordings in seconds

Replay data compression settings are not exposed in this build.

#### Storage Management
**Property**: `MaxReplayFiles`  
**Type**: `int32`  
**Default**: `10`  
**Range**: `1-100`  
**Purpose**: Maximum number of replay files to keep

**Property**: `bAutoDeleteOldReplays`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to automatically delete old replay files

## Usage Examples

### Basic Save/Load
```blueprint
// Save current game state
void SaveCurrentGame()
{
    UMyGameSaveData* SaveData = NewObject<UMyGameSaveData>();
    
    // Populate save data
    SaveData->PlayerLevel = GetPlayerLevel();
    SaveData->CurrentLocation = GetActorLocation();
    SaveData->Inventory = GetPlayerInventory();
    SaveData->QuestProgress = GetQuestManager()->GetSaveData();
    
    // Save to slot
    FString SlotName = "QuickSave_" + FDateTime::Now().ToString();
    bool bSuccess = USaveBlueprintLibrary::SaveGame(this, SaveData, SlotName);
    
    if (bSuccess)
    {
        ShowSaveNotification("Game Saved Successfully");
    }
}

// Load game state
void LoadGame(const FString& SlotName)
{
    UMyGameSaveData* SaveData = Cast<UMyGameSaveData>(
        USaveBlueprintLibrary::LoadGame(this, UMyGameSaveData::StaticClass(), SlotName)
    );
    
    if (SaveData)
    {
        // Restore game state
        SetPlayerLevel(SaveData->PlayerLevel);
        SetActorLocation(SaveData->CurrentLocation);
        GetPlayerInventory()->RestoreFrom(SaveData->Inventory);
        GetQuestManager()->LoadSaveData(SaveData->QuestProgress);
        
        ShowLoadNotification("Game Loaded Successfully");
    }
}
```

### Auto-Save Implementation
```blueprint
// Set up auto-save system
void BeginPlay()
{
    Super::BeginPlay();
    
    // Configure auto-save
    USaveBlueprintLibrary::SetSaveCooldown(this, 60.0f); // 1 minute cooldown
    
    // Bind to checkpoints
    GetQuestManager()->OnQuestCompleted.AddDynamic(this, &AMyGameMode::OnQuestCompleted);
    GetLevelSystem()->OnLevelUp.AddDynamic(this, &AMyGameMode::OnLevelUp);
}

void OnQuestCompleted(const FQuestInfo& Quest)
{
    // Auto-save after quest completion
    PerformAutoSave("Checkpoint");
}

void OnLevelUp(int32 NewLevel)
{
    // Auto-save after level up
    PerformAutoSave("LevelUp");
}

void PerformAutoSave(const FString& Reason)
{
    UMyGameSaveData* SaveData = CreateSaveData();
    
    FPlayerStatsMap Stats;
    Stats.Stats.Add("PlayTimeSeconds", GetTotalPlayTime());
    
    bool bSuccess = USaveBlueprintLibrary::AutoSave(
        this, 
        SaveData, 
        "AutoSave", 
        5, // Keep 5 auto-save slots
        0, // User 0
        Stats
    );
}
```

### GAS Integration
```blueprint
// Set up GAS save component
void BeginPlay()
{
    Super::BeginPlay();
    
    UGASSaveComponent* GASSave = FindComponentByClass<UGASSaveComponent>();
    if (GASSave)
    {
        // Configure what to save
        GASSave->bAutoSaveAttributes = true;
        GASSave->bAutoSaveAbilities = true;
        GASSave->bAutoSaveEffects = false; // Don't save temporary effects
        
        // Exclude sensitive attributes
        GASSave->ExcludedAttributes.Add(UMyAttributeSet::GetHealthAttribute());
        GASSave->ExcludedAttributes.Add(UMyAttributeSet::GetManaAttribute());
        
        // Exclude temporary abilities
        GASSave->ExcludedAbilityTags.AddTag(FGameplayTag::RequestGameplayTag("Ability.Temporary"));
    }
}

// Save/restore GAS state manually
void SaveCharacterProgression()
{
    UGASSaveComponent* GASSave = FindComponentByClass<UGASSaveComponent>();
    if (GASSave)
    {
        FGASSSaveData GASData = GASSave->CreateSaveData();
        
        // Include in main save data
        UMyGameSaveData* SaveData = CreateSaveData();
        SaveData->CharacterProgression = GASData;
        
        USaveBlueprintLibrary::SaveGame(this, SaveData, "ProgressionSave");
    }
}
```

### Replay System Usage
```blueprint
// Add snapshots during play (tick or on input events)
void Tick(float DeltaSeconds)
{
    FInputSnapshot Snap;
    Snap.ActionName = "MoveForward";
    Snap.Value = GetInputValue();
    Snap.Location = GetActorLocation();
    UReplayBlueprintLibrary::AddInputSnapshot(this, Snap);
}

// Save the last N seconds of snapshots to a slot
void SaveInstant()
{
    UReplayBlueprintLibrary::SaveInstantReplay(this, "InstantReplay_01");
}

// Load and draw debug of a saved replay
void DebugReplay()
{
    UReplaySaveGame* Replay = UReplayBlueprintLibrary::LoadReplay(this, "InstantReplay_01");
    UReplayBlueprintLibrary::DrawReplayDebug(this, Replay, FLinearColor::Yellow, 5.0f);
}
```

## Integration with Other Plugins

### DAI_Hub Integration
- **Service Registration**: Save subsystem registers with hub for discovery
- **Event Publishing**: Save/load events published through hub system
- **Fragment Collection**: Automatic collection of save fragments from other plugins

### DAI_Faction Integration
- **Reputation Persistence**: Faction reputation automatically saved
- **Relationship State**: Faction relationships preserved across sessions

### DAI_QuestManager Integration
- **Quest Progress**: Quest states and progress automatically saved
- **Objective Tracking**: Individual objective completion states preserved

### Gameplay Ability System
- **Attribute Persistence**: Character attributes saved and restored
- **Ability State**: Granted abilities and their states preserved
- **Effect Integration**: Optional persistence of gameplay effects

## Best Practices

### Save Data Design
1. **Use versioning** for save data structures to handle updates
2. **Implement data validation** to handle corrupted saves gracefully
3. **Keep save data lightweight** to minimize save times
4. **Use compression** for large save files
5. **Design for forward compatibility** with future game versions

### Performance Optimization
1. **Use async saving** to prevent frame drops during save operations
2. **Implement save cooldowns** to prevent excessive save frequency
3. **Cache save data** rather than recreating it repeatedly
4. **Monitor save file sizes** and optimize large data structures
5. **Use fragment system** for modular save data management

### User Experience
1. **Provide clear save feedback** to users through UI notifications
2. **Implement save slot management** with meaningful names and metadata
3. **Handle save failures gracefully** with retry mechanisms
4. **Support multiple save profiles** for different players
5. **Include save thumbnails** for easy save identification

### Security and Integrity
1. **Enable encryption** for sensitive save data
2. **Use checksums** to detect data corruption
3. **Implement backup saves** to prevent data loss
4. **Validate save data** on load to prevent crashes
5. **Handle version mismatches** appropriately

## Technical Notes

- **Thread Safety**: Save operations can be performed on background threads
- **Memory Management**: Automatic cleanup of temporary save data
- **Networking**: Save system is local-only but supports cloud sync
- **Performance**: Optimized serialization and compression
- **Platform Support**: Cross-platform save file compatibility

---

*For more information about GAS integration, see [DAI documentation](DAI.md).*  
*For hub integration details, see [DAI_Hub documentation](DAI_Hub.md).*  
*For fragment provider implementation, see the DAI Plugin Architecture Guide.*

---

Last updated: October 6, 2025