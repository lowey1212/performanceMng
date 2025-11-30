# DAI_QuestManager Plugin Documentation

## Overview

**DAI_QuestManager** is a comprehensive quest system for Unreal Engine 5.5 that provides quest creation, tracking, completion, and reward management with integrated conversation system, performance profiling, and map integration. The system supports complex branching questlines, kill credit tracking, loot tables, and seamless integration with other DAI plugins.

### Key Features
- 📜 **Quest Management**: Complete quest lifecycle from creation to completion
- 🗣️ **Conversation System**: Integrated dialogue and conversation trees
- 🏆 **Reward System**: Flexible reward bundles and loot table management
- 🎯 **Kill Credit Tracking**: Automatic kill credit distribution and policies
- 📊 **Performance Profiling**: Quest performance monitoring and optimization
- 🗺️ **Map Integration**: Quest marker and objective tracking on maps
- 🔄 **Quest Sharing**: Multiplayer quest sharing and synchronization
- 🎭 **Dynamic Content**: Runtime quest generation and modification

## Architecture

The DAI_QuestManager system consists of:
- **Quest Runtime**: Core quest logic and management
- **Quest Editor**: Development tools and quest creation
- **Map Runtime**: Integration with mapping systems
- **Quest Demo**: Example implementation and templates
- **Conversation System**: Dialogue and interaction management

## Core Components

### Quest Service Subsystem
*Main subsystem managing all quest operations*

**Type**: `World Subsystem`  
**Interfaces**: `IDAIQuestService`, `IDAIQuestSaveFragmentProvider`  
**Class**: `UQuestServiceSubsystem`  
**File**: `QuestServiceSubsystem.h/.cpp`

Central service for quest management, tracking, save fragment persistence, and coordination with Map and Save systems. The former actor `ADAI_QuestManager` has been removed; the subsystem is the sole implementation.

### DAI_QuestLogComponent
*Component for quest tracking and management*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `Quest`  
**File**: `DAI_QuestLogComponent.h`

Manages quest state and progress for individual players or parties.

### DAI_QuestPerformanceDirectorComponent
*Component for quest performance monitoring*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `Quest|Performance`  
**File**: `DAI_QuestPerformanceDirectorComponent.h`

Monitors and optimizes quest system performance during gameplay.

### QuestNode
*Individual quest step or objective*

**Type**: `UObject`  
**Blueprint Type**: `Yes`  
**File**: `QuestNode.h`

Represents a single quest objective or step within a larger quest graph.

### QuestGraph
*Container for complete quest structure*

**Type**: `UObject`  
**Blueprint Type**: `Yes`  
**File**: `QuestGraph.h`

Defines the complete structure and flow of a quest with nodes and connections.

## Blueprint Functions

Use `UQuestRuntimeBlueprintLibrary::GetQuestServiceSubsystem(WorldContext)` to get the subsystem, then call its BlueprintCallable methods: `StartQuest`, `CompleteQuest`, `AbandonQuest`, `FailQuest`. Query lists with `GetActiveQuests`, `GetCompletedQuests`, `GetFailedQuests`, `GetAbandonedQuests`.

### Quick start in Blueprint

1. In any Blueprint with a world context (e.g., Level Blueprint or Actor):
    - Call `Get Quest Service Subsystem` (from QuestRuntimeBlueprintLibrary)
2. Promote to a variable if you’ll reuse it.
3. Call subsystem functions:
    - `Start Quest` (QuestId: Name)
    - `Complete Quest` / `Abandon Quest` / `Fail Quest`
    - `Get Active Quests` / `Get Completed Quests` / `Get Failed Quests` / `Get Abandoned Quests`

No actor manager placement is required—the subsystem exists automatically per world.

### Quest Management

#### StartQuest
**Type**: `BlueprintCallable`  
**Category**: `Quest`  
**Returns**: `bool`  
**Purpose**: Begin a new quest for a player

**Parameters**:
- `QuestId` (FString): Unique identifier for the quest
- `Player` (APlayerController): Player who will receive the quest
- `bForceStart` (bool): Whether to force start even if prerequisites not met

```cpp
bool StartQuest(UObject* WorldContextObject, const FString& QuestId, APlayerController* Player, bool bForceStart = false);
```

**Usage**: Initiate new quests for players through triggers, NPCs, or events.

#### CompleteQuest
**Type**: `BlueprintCallable`  
**Category**: `Quest`  
**Returns**: `bool`  
**Purpose**: Mark a quest as completed and distribute rewards

**Parameters**:
- `QuestId` (FString): Identifier of the quest to complete
- `Player` (APlayerController): Player completing the quest
- `bGiveRewards` (bool): Whether to automatically give quest rewards

```cpp
bool CompleteQuest(UObject* WorldContextObject, const FString& QuestId, APlayerController* Player, bool bGiveRewards = true);
```

**Usage**: Complete quests when all objectives are fulfilled.

#### AbandonQuest
**Type**: `BlueprintCallable`  
**Category**: `Quest`  
**Returns**: `bool`  
**Purpose**: Abandon an active quest

**Parameters**:
- `QuestId` (FString): Identifier of the quest to abandon
- `Player` (APlayerController): Player abandoning the quest

```cpp
bool AbandonQuest(UObject* WorldContextObject, const FString& QuestId, APlayerController* Player);
```

**Usage**: Allow players to abandon unwanted or impossible quests.

#### GetQuestStatus
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `Quest`  
**Returns**: `EQuestStatus`  
**Purpose**: Get current status of a quest for a player

**Parameters**:
- `QuestId` (FString): Identifier of the quest to check
- `Player` (APlayerController): Player to check quest status for

```cpp
EQuestStatus GetQuestStatus(UObject* WorldContextObject, const FString& QuestId, APlayerController* Player);
```

**Usage**: Check quest progress for UI display or conditional logic.

### Objective Management

#### UpdateObjective
**Type**: `BlueprintCallable`  
**Category**: `Quest|Objectives`  
**Returns**: `bool`  
**Purpose**: Update progress on a specific quest objective

**Parameters**:
- `QuestId` (FString): Quest containing the objective
- `ObjectiveId` (FString): Identifier of the objective to update
- `Player` (APlayerController): Player whose progress to update
- `Progress` (int32): New progress value
- `bRelative` (bool): Whether progress is relative to current value

```cpp
bool UpdateObjective(UObject* WorldContextObject, const FString& QuestId, const FString& ObjectiveId, APlayerController* Player, int32 Progress, bool bRelative = true);
```

**Usage**: Track objective progress from various gameplay systems.

#### CompleteObjective
**Type**: `BlueprintCallable`  
**Category**: `Quest|Objectives`  
**Returns**: `bool`  
**Purpose**: Mark a specific objective as completed

**Parameters**:
- `QuestId` (FString): Quest containing the objective
- `ObjectiveId` (FString): Identifier of the objective to complete
- `Player` (APlayerController): Player completing the objective

```cpp
bool CompleteObjective(UObject* WorldContextObject, const FString& QuestId, const FString& ObjectiveId, APlayerController* Player);
```

**Usage**: Complete individual objectives within larger quests.

#### GetObjectiveProgress
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `Quest|Objectives`  
**Returns**: `int32`  
**Purpose**: Get current progress on a specific objective

**Parameters**:
- `QuestId` (FString): Quest containing the objective
- `ObjectiveId` (FString): Identifier of the objective to check
- `Player` (APlayerController): Player to check progress for

```cpp
int32 GetObjectiveProgress(UObject* WorldContextObject, const FString& QuestId, const FString& ObjectiveId, APlayerController* Player);
```

**Usage**: Display objective progress in UI or check completion conditions.

### Kill Credit System

#### GrantKillCredit
**Type**: `BlueprintCallable`  
**Category**: `Quest|KillCredit`  
**Purpose**: Grant kill credit for quest objectives

**Parameters**:
- `KillType` (FGameplayTag): Type of kill for quest tracking
- `KilledActor` (AActor): Actor that was killed
- `Killer` (APlayerController): Player who made the kill
- `AssistPlayers` (TArray<APlayerController*>): Players who assisted

```cpp
void GrantKillCredit(UObject* WorldContextObject, FGameplayTag KillType, AActor* KilledActor, APlayerController* Killer, const TArray<APlayerController*>& AssistPlayers);
```

**Usage**: Automatically track kills for quest objectives.

#### SetKillCreditPolicy
**Type**: `BlueprintCallable`  
**Category**: `Quest|KillCredit`  
**Purpose**: Configure how kill credit is distributed

**Parameters**:
- `Policy` (EKillCreditPolicy): Policy for credit distribution
- `GroupRange` (float): Range for group kill credit sharing

```cpp
void SetKillCreditPolicy(UObject* WorldContextObject, EKillCreditPolicy Policy, float GroupRange = 1000.0f);
```

**Usage**: Customize kill credit behavior for different game modes.

### Conversation System

#### StartConversation
**Type**: `BlueprintCallable`  
**Category**: `Quest|Conversation`  
**Returns**: `bool`  
**Purpose**: Begin a conversation with an NPC

**Parameters**:
- `ConversationId` (FString): Identifier of the conversation to start
- `Player` (APlayerController): Player participating in conversation
- `NPC` (AActor): NPC actor for the conversation

```cpp
bool StartConversation(UObject* WorldContextObject, const FString& ConversationId, APlayerController* Player, AActor* NPC);
```

**Usage**: Initiate dialogue interactions for quest progression.

#### AdvanceConversation
**Type**: `BlueprintCallable`  
**Category**: `Quest|Conversation`  
**Returns**: `bool`  
**Purpose**: Advance conversation to next node

**Parameters**:
- `ConversationId` (FString): Active conversation to advance
- `ChoiceIndex` (int32): Player's dialogue choice selection

```cpp
bool AdvanceConversation(UObject* WorldContextObject, const FString& ConversationId, int32 ChoiceIndex);
```

**Usage**: Progress through dialogue trees based on player choices.

#### EndConversation
**Type**: `BlueprintCallable`  
**Category**: `Quest|Conversation`  
**Purpose**: End an active conversation

**Parameters**:
- `ConversationId` (FString): Conversation to end
- `bCompleted` (bool): Whether conversation completed successfully

```cpp
void EndConversation(UObject* WorldContextObject, const FString& ConversationId, bool bCompleted = true);
```

**Usage**: Cleanly terminate dialogue interactions.

### Reward Management

#### GiveQuestReward
**Type**: `BlueprintCallable`  
**Category**: `Quest|Rewards`  
**Returns**: `bool`  
**Purpose**: Give rewards from a quest to a player

**Parameters**:
- `RewardBundle` (FRewardBundle): Bundle of rewards to give
- `Player` (APlayerController): Player to receive rewards
- `bNotifyPlayer` (bool): Whether to show reward notification

```cpp
bool GiveQuestReward(UObject* WorldContextObject, const FRewardBundle& RewardBundle, APlayerController* Player, bool bNotifyPlayer = true);
```

**Usage**: Distribute quest completion rewards to players.

#### GenerateLootReward
**Type**: `BlueprintCallable`  
**Category**: `Quest|Rewards`  
**Returns**: `FRewardBundle`  
**Purpose**: Generate random rewards from a loot table

**Parameters**:
- `LootTable` (ULootTable): Loot table to generate from
- `LootLevel` (int32): Level for loot generation
- `LootModifiers` (FGameplayTagContainer): Modifiers affecting loot generation

```cpp
FRewardBundle GenerateLootReward(UObject* WorldContextObject, ULootTable* LootTable, int32 LootLevel, const FGameplayTagContainer& LootModifiers);
```

**Usage**: Create dynamic rewards based on player level and circumstances.

### Quest Sharing

#### ShareQuest
**Type**: `BlueprintCallable`  
**Category**: `Quest|Sharing`  
**Returns**: `bool`  
**Purpose**: Share a quest with other players

**Parameters**:
- `QuestId` (FString): Quest to share
- `FromPlayer` (APlayerController): Player sharing the quest
- `ToPlayers` (TArray<APlayerController*>): Players to share with

```cpp
bool ShareQuest(UObject* WorldContextObject, const FString& QuestId, APlayerController* FromPlayer, const TArray<APlayerController*>& ToPlayers);
```

**Usage**: Enable cooperative quest gameplay in multiplayer.

#### AcceptSharedQuest
**Type**: `BlueprintCallable`  
**Category**: `Quest|Sharing`  
**Returns**: `bool`  
**Purpose**: Accept a quest shared by another player

**Parameters**:
- `QuestId` (FString): Shared quest to accept
- `Player` (APlayerController): Player accepting the quest

```cpp
bool AcceptSharedQuest(UObject* WorldContextObject, const FString& QuestId, APlayerController* Player);
```

**Usage**: Allow players to join shared quests.

## Blueprint Data Types

### EQuestStatus (Quest Status)
**Type**: `BlueprintType Enum`  
**Purpose**: Current state of a quest

**Values**:
- `NotStarted`: Quest has not been started
- `Available`: Quest is available to start
- `Active`: Quest is currently in progress
- `Completed`: Quest has been completed successfully
- `Failed`: Quest has failed and cannot be completed
- `Abandoned`: Quest was abandoned by the player

### EQuestObjectiveType (Quest Objective Type)
**Type**: `BlueprintType Enum`  
**Purpose**: Type of quest objective

**Values**:
- `Kill`: Eliminate specific targets
- `Collect`: Gather specific items
- `Interact`: Interact with objects or NPCs
- `Escort`: Protect or guide NPCs
- `Reach`: Travel to specific locations
- `Survive`: Survive for a specific duration
- `Custom`: User-defined objective type

### EKillCreditPolicy (Kill Credit Policy)
**Type**: `BlueprintType Enum`  
**Purpose**: How kill credit is distributed

**Values**:
- `Individual`: Only killer gets credit
- `Group`: All group members get credit
- `Proximity`: Players within range get credit
- `Damage`: Credit based on damage contribution
- `Tagged`: Player who first tagged target gets credit

### FQuestInfo (Quest Information)
**Type**: `BlueprintType Struct`  
**Purpose**: Complete information about a quest

**Properties**:
- `QuestId` (FString): Unique identifier for the quest
- `Title` (FText): Display title of the quest
- `Description` (FText): Detailed quest description
- `Category` (FGameplayTag): Quest category for organization
- `Level` (int32): Recommended level for the quest
- `Prerequisites` (TArray<FString>): Required completed quests
- `Rewards` (FRewardBundle): Rewards given on completion
- `TimeLimit` (float): Time limit in seconds (0 = no limit)
- `bRepeatable` (bool): Whether quest can be repeated
- `QuestGraph` (UQuestGraph): Graph defining quest structure

### FQuestObjective (Quest Objective)
**Type**: `BlueprintType Struct`  
**Purpose**: Individual objective within a quest

**Properties**:
- `ObjectiveId` (FString): Unique identifier for this objective
- `Description` (FText): Display description of the objective
- `ObjectiveType` (EQuestObjectiveType): Type of objective
- `TargetTag` (FGameplayTag): Tag identifying target for objective
- `RequiredCount` (int32): Number required to complete objective
- `CurrentCount` (int32): Current progress toward objective
- `bOptional` (bool): Whether objective is optional
- `bHidden` (bool): Whether objective is hidden from player
- `Location` (FVector): Relevant location for objective (if applicable)

### FRewardBundle (Reward Bundle)
**Type**: `BlueprintType Struct`  
**Purpose**: Collection of rewards for quest completion

**Properties**:
- `Experience` (int32): Experience points reward
- `Currency` (int32): Currency/gold reward
- `Items` (TArray<FItemReward>): Item rewards
- `Abilities` (TArray<TSubclassOf<UGameplayAbility>>): Ability rewards
- `Reputation` (TMap<FGameplayTag, int32>): Reputation changes
- `UnlockTags` (FGameplayTagContainer): Gameplay tags to unlock

### FItemReward (Item Reward)
**Type**: `BlueprintType Struct`  
**Purpose**: Individual item reward information

**Properties**:
- `ItemClass` (TSubclassOf<UObject>): Class of item to give
- `Quantity` (int32): Number of items to give
- `Quality` (EItemQuality): Quality level of the item
- `bBindOnPickup` (bool): Whether item binds to player
- `CustomProperties` (TMap<FString, FString>): Additional item properties

### FConversationNode (Conversation Node)
**Type**: `BlueprintType Struct`  
**Purpose**: Individual node in a conversation tree

**Properties**:
- `NodeId` (FString): Unique identifier for this node
- `SpeakerName` (FText): Name of the speaking character
- `DialogueText` (FText): Text to display for this node
- `PlayerChoices` (TArray<FConversationChoice>): Available player responses
- `Conditions` (FGameplayTagContainer): Conditions for showing this node
- `Actions` (TArray<FConversationAction>): Actions to execute when node is reached
- `QuestUpdates` (TArray<FQuestUpdate>): Quest updates triggered by this node

### FConversationChoice (Conversation Choice)
**Type**: `BlueprintType Struct`  
**Purpose**: Player dialogue choice option

**Properties**:
- `ChoiceText` (FText): Text to display for this choice
- `NextNodeId` (FString): Node to go to if this choice is selected
- `Requirements` (FGameplayTagContainer): Requirements to show this choice
- `QuestRequirements` (TArray<FString>): Quests required for this choice
- `bEndsConversation` (bool): Whether this choice ends the conversation

## Component Properties

### DAI_QuestLogComponent Properties

#### Quest Tracking
**Property**: `ActiveQuests`  
**Type**: `TArray<FString>`  
**Category**: `Quest Log`  
**Blueprint Access**: `Read Only`  
**Replication**: `Yes`  
**Purpose**: List of currently active quest IDs

**Property**: `CompletedQuests`  
**Type**: `TArray<FString>`  
**Category**: `Quest Log`  
**Blueprint Access**: `Read Only`  
**Purpose**: List of completed quest IDs

**Property**: `MaxActiveQuests`  
**Type**: `int32`  
**Category**: `Quest Log`  
**Blueprint Access**: `Read/Write`  
**Default**: `10`  
**Purpose**: Maximum number of simultaneously active quests

#### Progress Tracking
**Property**: `QuestProgress`  
**Type**: `TMap<FString, FQuestProgress>`  
**Category**: `Quest Log`  
**Blueprint Access**: `Read Only`  
**Replication**: `Yes`  
**Purpose**: Current progress for all active quests

**Property**: `bAutoTrackObjectives`  
**Type**: `bool`  
**Category**: `Quest Log`  
**Blueprint Access**: `Read/Write`  
**Default**: `true`  
**Purpose**: Whether to automatically track quest objectives

### DAI_QuestPerformanceDirectorComponent Properties

#### Performance Monitoring
**Property**: `bEnablePerformanceMonitoring`  
**Type**: `bool`  
**Category**: `Performance`  
**Blueprint Access**: `Read/Write`  
**Default**: `true`  
**Purpose**: Whether to monitor quest system performance

**Property**: `MaxConcurrentQuests`  
**Type**: `int32`  
**Category**: `Performance`  
**Blueprint Access**: `Read/Write`  
**Default**: `50`  
**Purpose**: Maximum number of quests to process per frame

**Property**: `UpdateFrequency`  
**Type**: `float`  
**Category**: `Performance`  
**Blueprint Access**: `Read/Write`  
**Default**: `0.1`  
**Purpose**: Seconds between quest system updates

## Events and Delegates

### OnQuestStarted
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Quest`  
**Purpose**: Fired when a quest is started

**Parameters**:
- `QuestId` (FString): ID of the started quest
- `Player` (APlayerController): Player who started the quest

**Usage**: Update UI, trigger cutscenes, or spawn quest-related content.

### OnQuestCompleted
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Quest`  
**Purpose**: Fired when a quest is completed

**Parameters**:
- `QuestId` (FString): ID of the completed quest
- `Player` (APlayerController): Player who completed the quest
- `RewardBundle` (FRewardBundle): Rewards given for completion

**Usage**: Trigger celebratory effects, unlock new content, or update progression.

### OnObjectiveUpdated
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Quest`  
**Purpose**: Fired when quest objective progress changes

**Parameters**:
- `QuestId` (FString): Quest containing the updated objective
- `ObjectiveId` (FString): ID of the updated objective
- `NewProgress` (int32): New progress value
- `bCompleted` (bool): Whether objective was completed

**Usage**: Update quest tracker UI and provide player feedback.

### OnConversationStarted
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Quest|Conversation`  
**Purpose**: Fired when a conversation begins

**Parameters**:
- `ConversationId` (FString): ID of the started conversation
- `Player` (APlayerController): Player in the conversation
- `NPC` (AActor): NPC actor in the conversation

**Usage**: Switch to dialogue UI mode and pause other interactions.

### OnQuestFailed
**Type**: `Dynamic Multicast Delegate`  
**Category**: `Quest`  
**Purpose**: Fired when a quest fails

**Parameters**:
- `QuestId` (FString): ID of the failed quest
- `Player` (APlayerController): Player whose quest failed
- `FailureReason` (FString): Reason for quest failure

**Usage**: Provide failure feedback and potentially offer retry options.

## Developer Settings

Access via **Project Settings → Game → DAI Quest Manager**

### General Settings

#### Quest Management
**Property**: `bAutoSaveProgress`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to automatically save quest progress

**Property**: `QuestSaveInterval`  
**Type**: `float`  
**Default**: `30.0`  
**Range**: `10.0-300.0`  
**Purpose**: Seconds between automatic quest progress saves

**Property**: `DefaultQuestTimeLimit`  
**Type**: `float`  
**Default**: `0.0`  
**Purpose**: Default time limit for quests (0 = no limit)

#### Performance Settings
**Property**: `MaxQuestUpdatesPerFrame`  
**Type**: `int32`  
**Default**: `10`  
**Range**: `1-100`  
**Purpose**: Maximum quest updates processed per frame

**Property**: `QuestUpdateBudgetMs`  
**Type**: `float`  
**Default**: `2.0`  
**Range**: `0.5-10.0`  
**Purpose**: Performance budget for quest updates per frame

### Kill Credit Settings

#### Distribution Policy
**Property**: `DefaultKillCreditPolicy`  
**Type**: `EKillCreditPolicy`  
**Default**: `Group`  
**Purpose**: Default policy for kill credit distribution

**Property**: `GroupCreditRange`  
**Type**: `float`  
**Default**: `1000.0`  
**Range**: `100.0-5000.0`  
**Purpose**: Range for group kill credit sharing

**Property**: `bAllowKillSteal`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether non-group members can steal kill credit

### Conversation Settings

#### Dialogue Configuration
**Property**: `DefaultConversationTimeout`  
**Type**: `float`  
**Default**: `300.0`  
**Range**: `30.0-1800.0`  
**Purpose**: Timeout for conversations in seconds

**Property**: `bAutoAdvanceConversations`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to auto-advance conversations without choices

**Property**: `ConversationChoiceTimeout`  
**Type**: `float`  
**Default**: `30.0`  
**Range**: `5.0-120.0`  
**Purpose**: Timeout for player dialogue choices

### Reward Settings

#### Loot Generation
**Property**: `bUseRandomizedRewards`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to use randomized reward generation

**Property**: `RewardQualityVariance`  
**Type**: `float`  
**Default**: `0.2`  
**Range**: `0.0-1.0`  
**Purpose**: Variance in reward quality from base level

**Property**: `bScaleRewardsWithLevel`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to scale rewards with player level

### Map Integration

#### Quest Markers
**Property**: `bEnableQuestMarkers`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to show quest objectives on maps

**Property**: `QuestMarkerUpdateFrequency`  
**Type**: `float`  
**Default**: `1.0`  
**Range**: `0.1-10.0`  
**Purpose**: Seconds between quest marker updates

**Property**: `MaxQuestMarkersOnMap`  
**Type**: `int32`  
**Default**: `20`  
**Range**: `5-100`  
**Purpose**: Maximum number of quest markers to show on map

### Debug Settings

#### Logging
**Property**: `bEnableQuestLogging`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to enable detailed quest system logging

**Property**: `bLogQuestProgress`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to log quest progress updates

#### Visualization
**Property**: `bShowQuestDebugInfo`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to display quest debug information in viewport

**Property**: `bDrawQuestObjectiveLocations`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to draw quest objective locations in world

## Usage Examples

### Basic Quest Creation and Management
```blueprint
// Start a new quest for a player
void GiveQuestToPlayer(APlayerController* Player, const FString& QuestId)
{
    // Check if player meets prerequisites
    bool bCanStart = UDAIQuestBlueprintLibrary::CanStartQuest(this, QuestId, Player);
    
    if (bCanStart)
    {
        bool bSuccess = UDAIQuestBlueprintLibrary::StartQuest(this, QuestId, Player, false);
        
        if (bSuccess)
        {
            // Show quest received notification
            ShowQuestNotification(Player, "New Quest: " + GetQuestTitle(QuestId));
            
            // Update quest markers on map
            UpdateQuestMarkers(Player);
        }
    }
    else
    {
        // Show prerequisite message
        ShowMessage(Player, "You must complete other quests first.");
    }
}

// Track quest objective progress
void OnEnemyKilled(AActor* KilledEnemy, APlayerController* Killer)
{
    // Grant kill credit for quest tracking
    FGameplayTag EnemyType = GetEnemyType(KilledEnemy);
    
    UDAIQuestBlueprintLibrary::GrantKillCredit(
        this,
        EnemyType,
        KilledEnemy,
        Killer,
        GetNearbyPartyMembers(Killer)
    );
}

// Complete quest when all objectives finished
void CheckQuestCompletion(const FString& QuestId, APlayerController* Player)
{
    bool bAllObjectivesComplete = true;
    
    FQuestInfo QuestInfo = GetQuestInfo(QuestId);
    for (const FQuestObjective& Objective : QuestInfo.Objectives)
    {
        int32 Progress = UDAIQuestBlueprintLibrary::GetObjectiveProgress(
            this, QuestId, Objective.ObjectiveId, Player
        );
        
        if (Progress < Objective.RequiredCount && !Objective.bOptional)
        {
            bAllObjectivesComplete = false;
            break;
        }
    }
    
    if (bAllObjectivesComplete)
    {
        UDAIQuestBlueprintLibrary::CompleteQuest(this, QuestId, Player, true);
    }
}
```

### Conversation System Implementation
```blueprint
// Start conversation with NPC
void InteractWithNPC(AActor* NPC, APlayerController* Player)
{
    FString ConversationId = GetNPCConversationId(NPC);
    
    if (!ConversationId.IsEmpty())
    {
        bool bStarted = UDAIQuestBlueprintLibrary::StartConversation(
            this,
            ConversationId,
            Player,
            NPC
        );
        
        if (bStarted)
        {
            // Switch to dialogue UI
            ShowConversationUI(Player, ConversationId);
            
            // Disable other interactions
            SetPlayerInteractionMode(Player, EInteractionMode::Conversation);
        }
    }
}

// Handle player dialogue choice
void OnDialogueChoiceSelected(int32 ChoiceIndex, const FString& ConversationId)
{
    bool bContinued = UDAIQuestBlueprintLibrary::AdvanceConversation(
        this,
        ConversationId,
        ChoiceIndex
    );
    
    if (!bContinued)
    {
        // Conversation ended
        UDAIQuestBlueprintLibrary::EndConversation(this, ConversationId, true);
        
        // Return to normal gameplay
        HideConversationUI();
        SetPlayerInteractionMode(GetCurrentPlayer(), EInteractionMode::Normal);
    }
}

// Bind to conversation events
void BeginPlay()
{
    Super::BeginPlay();
    
    UDAIQuestManagerSubsystem* QuestManager = GetWorld()->GetSubsystem<UDAIQuestManagerSubsystem>();
    QuestManager->OnConversationStarted.AddDynamic(this, &AMyGameMode::OnConversationBegan);
    QuestManager->OnQuestStarted.AddDynamic(this, &AMyGameMode::OnQuestStarted);
    QuestManager->OnQuestCompleted.AddDynamic(this, &AMyGameMode::OnQuestCompleted);
}
```

### Reward System Usage
```blueprint
// Create custom reward bundle
FRewardBundle CreateQuestReward(int32 PlayerLevel, EQuestDifficulty Difficulty)
{
    FRewardBundle Reward;
    
    // Scale experience with level and difficulty
    Reward.Experience = FMath::RoundToInt(PlayerLevel * 100.0f * GetDifficultyMultiplier(Difficulty));
    
    // Currency reward
    Reward.Currency = FMath::RandRange(50, 100) * PlayerLevel;
    
    // Generate random item reward
    ULootTable* LootTable = GetQuestLootTable(Difficulty);
    if (LootTable)
    {
        FGameplayTagContainer LootModifiers;
        LootModifiers.AddTag(FGameplayTag::RequestGameplayTag("Loot.Quest"));
        
        FRewardBundle LootReward = UDAIQuestBlueprintLibrary::GenerateLootReward(
            this,
            LootTable,
            PlayerLevel,
            LootModifiers
        );
        
        Reward.Items.Append(LootReward.Items);
    }
    
    // Add reputation rewards
    Reward.Reputation.Add(FGameplayTag::RequestGameplayTag("Faction.Townspeople"), 25);
    
    return Reward;
}

// Give rewards to player
void GiveQuestRewards(APlayerController* Player, const FRewardBundle& Rewards)
{
    bool bSuccess = UDAIQuestBlueprintLibrary::GiveQuestReward(
        this,
        Rewards,
        Player,
        true // Show notification
    );
    
    if (bSuccess)
    {
        // Play reward effects
        PlayRewardEffects(Player);
        
        // Update player stats
        UpdatePlayerStats(Player, Rewards);
    }
}
```

### Multiplayer Quest Sharing
```blueprint
// Share quest with party members
void ShareQuestWithParty(const FString& QuestId, APlayerController* SharingPlayer)
{
    TArray<APlayerController*> PartyMembers = GetPartyMembers(SharingPlayer);
    
    if (PartyMembers.Num() > 0)
    {
        bool bShared = UDAIQuestBlueprintLibrary::ShareQuest(
            this,
            QuestId,
            SharingPlayer,
            PartyMembers
        );
        
        if (bShared)
        {
            // Notify all party members
            for (APlayerController* Member : PartyMembers)
            {
                ShowQuestShareNotification(Member, QuestId, SharingPlayer);
            }
        }
    }
}

// Handle quest share acceptance
void OnQuestShareAccepted(const FString& QuestId, APlayerController* AcceptingPlayer)
{
    bool bAccepted = UDAIQuestBlueprintLibrary::AcceptSharedQuest(
        this,
        QuestId,
        AcceptingPlayer
    );
    
    if (bAccepted)
    {
        // Sync quest progress with party
        SyncQuestProgressWithParty(QuestId, AcceptingPlayer);
        
        // Update UI
        RefreshQuestLog(AcceptingPlayer);
    }
}
```

### Performance Monitoring
```blueprint
// Monitor quest system performance
void MonitorQuestPerformance()
{
    UDAIQuestPerformanceDirectorComponent* PerfDirector = 
        FindComponentByClass<UDAIQuestPerformanceDirectorComponent>();
    
    if (PerfDirector)
    {
        FQuestPerformanceProfile Profile = PerfDirector->GetPerformanceProfile();
        
        if (Profile.AverageUpdateTimeMs > 5.0f)
        {
            // Quest system taking too long
            ReduceQuestUpdateFrequency();
        }
        
        if (Profile.ActiveQuestCount > MaxRecommendedQuests)
        {
            // Too many active quests
            SuggestQuestCleanup();
        }
        
        // Log performance metrics
        UE_LOG(LogQuest, Log, TEXT("Quest Performance: %.2fms avg, %d active quests"), 
               Profile.AverageUpdateTimeMs, Profile.ActiveQuestCount);
    }
}
```

## Integration with Other Plugins

### DAI_Map Integration
- **Quest Markers**: Automatic quest objective markers on maps
- **Progress Tracking**: Map-based quest progress visualization
- **Location Discovery**: Quest objectives can trigger map POI registration

### DAI_Save Integration
- **Progress Persistence**: Quest progress automatically saved
- **Conversation State**: Dialogue progress and choices preserved
- **Reward History**: Completed quest rewards tracked

### DAI_Faction Integration
- **Reputation Rewards**: Quest completion affects faction standings
- **Faction Quests**: Quests can be faction-specific
- **Relationship Gating**: Quest availability based on faction relationships

### DAI_AI Integration
- **NPC Interactions**: AI characters can give and react to quests
- **Behavior Triggers**: Quest events can trigger AI behavior changes
- **Dynamic Content**: AI can generate contextual quest content

## Best Practices

### Quest Design
1. **Create clear objectives** with measurable progress indicators
2. **Design meaningful rewards** that feel worthwhile to players
3. **Use branching narratives** to increase replay value
4. **Test quest flows** thoroughly for logical progression
5. **Provide clear failure conditions** and recovery options

### Performance Optimization
1. **Limit concurrent active quests** to maintain performance
2. **Use efficient objective tracking** to minimize update overhead
3. **Cache quest data** rather than recalculating frequently
4. **Implement quest LOD** for distant or inactive objectives
5. **Monitor performance metrics** regularly during development

### User Experience
1. **Provide clear quest guidance** through UI and world markers
2. **Allow quest abandonment** for player agency
3. **Show progress clearly** for all objectives
4. **Handle edge cases gracefully** (disconnection, failures, etc.)
5. **Support different playstyles** with optional objectives

### Multiplayer Considerations
1. **Design for cooperation** with appropriate sharing mechanics
2. **Handle progress synchronization** carefully in networked games
3. **Consider individual vs group objectives** for different social dynamics
4. **Test with various group sizes** and connection scenarios
5. **Implement fair kill credit distribution** for combat objectives

## Technical Notes

- **Thread Safety**: Quest operations designed for game thread usage
- **Memory Management**: Efficient storage and cleanup of quest data
- **Networking**: Full replication support for multiplayer quest sharing
- **Performance**: Optimized update loops and caching systems
- **Save Integration**: Seamless persistence through DAI_Save system

---

*For more information about map integration, see [DAI_Map documentation](DAI_Map.md).*  
*For save system integration, see [DAI_Save documentation](DAI_Save.md).*  
*For faction integration, see [DAI_Faction documentation](DAI_Faction.md).*

---

Last updated: October 6, 2025