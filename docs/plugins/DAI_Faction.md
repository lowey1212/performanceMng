# DAI_Faction Plugin Documentation

## Overview

**DAI_Faction** is a comprehensive faction and reputation management system for Unreal Engine 5.5 that provides dynamic relationship tracking, reputation systems, hostility determination, and social interaction mechanics. The system supports complex multi-faction scenarios with persistent reputation tracking and event-driven relationship changes.

### Key Features
- 🏛️ **Multi-Faction System**: Support for complex faction hierarchies and relationships
- 📊 **Dynamic Reputation**: Persistent reputation tracking with configurable thresholds
- ⚔️ **Hostility Management**: Automatic hostility determination based on faction relationships
- 🔄 **Relationship Overrides**: Runtime relationship modifications and customization
- 💾 **Save Integration**: Automatic persistence through DAI_Save system
- 🎯 **Event System**: Hub integration for reputation and relationship events
- 🎭 **Multi-Tag Support**: Actors can belong to multiple factions simultaneously
- 🌍 **Zone-Based Systems**: Location-specific faction behaviors and territories
- ⚡ **GAS/StateTree Ready**: Emits Gameplay Events and optional AttributeSet signals for reactive abilities and AI logic

## Architecture

The DAI_Faction system consists of:
- **Faction Service Subsystem**: Central reputation and relationship management
- **Faction Components**: Actor-based faction membership and behavior
- **Data Assets**: Faction definitions and relationship matrices
- **Zone System**: Territory-based faction interactions
- **Character Integration**: AI and player character faction support

## Core Components

### FactionServiceSubsystem
*World subsystem managing all faction operations*

**Type**: `World Subsystem`  
**Interfaces**: `IDAIFactionService`, `IDAISaveFragmentProvider`  
**File**: `FactionServiceSubsystem.h`

Central service for faction management, reputation tracking, and relationship determination.

### FactionComponentMultiTag
*Component enabling multi-faction membership for actors*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `Faction`  
**File**: `FactionComponentMultiTag.h`

Allows actors to belong to multiple factions with individual reputation tracking.

### FactionCatalog
*Data asset defining available factions*

**Type**: `Data Asset`  
**Blueprint Type**: `Yes`  
**File**: `FactionDataAssets.h`

Centralized definition of all factions in the game world.

## Blueprint Functions

### Faction Library Functions

#### AdjustRep
**Type**: `BlueprintCallable`  
**Category**: `Faction`  
**Purpose**: Adjust reputation of subject with specific faction

**Parameters**:
- `Subject` (AActor): Actor whose reputation to adjust
- `Faction` (FGameplayTag): Target faction for reputation change
- `Delta` (float): Amount to change reputation (positive or negative)
- `Reason` (FName): Optional reason identifier for the change

```cpp
void AdjustRep(UObject* WorldContextObject, AActor* Subject, FGameplayTag Faction, float Delta, FName Reason);
```

**Usage**: Primary function for modifying faction reputation based on player actions or story events.

#### AreHostile
**Type**: `BlueprintCallable`  
**Category**: `Faction`  
**Returns**: `bool`  
**Purpose**: Check if two actors are hostile to each other

**Parameters**:
- `A` (AActor): First actor to check
- `B` (AActor): Second actor to check

```cpp
bool AreHostile(UObject* WorldContextObject, const AActor* A, const AActor* B);
```
#### GetRelationCode
Type: `BlueprintPure`
Category: `Faction`
Returns: `int32` (-1 hostile, 0 neutral, 1 friendly, 2 allied)
Purpose: Simple integer mapping for StateTree condition checks or lightweight UI.

```cpp
int32 GetRelationCode(UObject* WorldContextObject, const AActor* A, const AActor* B);
```

**Usage**: Determine combat eligibility, AI behavior, and interaction permissions.

### Multi-Tag Component Functions

#### GetFactionTags
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `Faction`  
**Returns**: `FGameplayTagContainer`  
**Purpose**: Get all faction tags this actor belongs to

```cpp
const FGameplayTagContainer& GetFactionTags() const;
```

**Usage**: Retrieve all faction memberships for an actor.

#### IsHostileTo
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `Faction`  
**Returns**: `bool`  
**Purpose**: Check if this actor is hostile to another actor

**Parameters**:
- `OtherActor` (AActor): Actor to check hostility against

```cpp
bool IsHostileTo(AActor* OtherActor) const;
```

**Usage**: Component-level hostility check for AI behavior and interaction logic.

#### GetRelationTo
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `Faction`  
**Returns**: `EFactionRelation`  
**Purpose**: Get specific relationship type to another actor

**Parameters**:
- `OtherActor` (AActor): Actor to check relationship with

```cpp
EFactionRelation GetRelationTo(AActor* OtherActor) const;
```

**Usage**: Get detailed relationship information beyond simple hostility.

#### SetFactionTags
**Type**: `BlueprintCallable`  
**Category**: `Faction`  
**Purpose**: Set faction memberships for this actor

**Parameters**:
- `Tags` (FGameplayTagContainer): New faction tags to assign

```cpp
void SetFactionTags(const FGameplayTagContainer& Tags);
```

**Usage**: Runtime faction membership changes (defection, recruitment, etc.).

#### AdjustReputationForFaction
**Type**: `BlueprintCallable`  
**Category**: `Faction`  
**Purpose**: Adjust this actor's reputation with a specific faction

**Parameters**:
- `Faction` (FGameplayTag): Target faction
- `Delta` (float): Reputation change amount
- `Reason` (FName): Optional reason identifier

```cpp
void AdjustReputationForFaction(const FGameplayTag& Faction, float Delta, FName Reason = NAME_None);
```

**Usage**: Component-level reputation adjustment for specific interactions.

#### GetReputationWith
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `Faction`  
**Returns**: `float`  
**Purpose**: Get current reputation with specific faction

**Parameters**:
- `Faction` (FGameplayTag): Faction to check reputation with

```cpp
float GetReputationWith(const FGameplayTag& Faction) const;
```

**Usage**: Query current standing for UI display and decision making.

## Blueprint Data Types

### EFactionRelation (Faction Relation)
**Type**: `BlueprintType Enum`  
**Purpose**: Defines relationship types between factions

**Values**:
- `Hostile`: Active enemies, will attack on sight

---

Last updated: October 6, 2025
- `Ally`: Friendly factions, will assist each other
- `Fear`: One faction fears the other (asymmetric relationship)
- `Neutral`: No special relationship, ignores each other
- `Tense`: Uneasy relationship, potential for conflict

### FFactionInfo (Faction Information)
**Type**: `BlueprintType Struct`  
**Purpose**: Complete definition of a game faction

**Properties**:
- `Id` (FGameplayTag): Unique identifier for the faction
- `DisplayName` (FText): Human-readable faction name
- `Color` (FLinearColor): Associated color for UI representation
- `Icon` (UTexture2D): Visual icon for the faction
- `MinRep` (int32): Minimum possible reputation value
- `MaxRep` (int32): Maximum possible reputation value
- `Thresholds` (FFactionThresholds): Reputation thresholds for relationship changes

### FFactionThresholds (Faction Thresholds)
**Type**: `BlueprintType Struct`  
**Purpose**: Reputation thresholds for relationship determination

**Properties**:
- `Hostile` (int32): Reputation threshold below which relations become hostile
- `Friendly` (int32): Reputation threshold above which relations become friendly

### FFactionRelationRow (Faction Relation Row)
**Type**: `BlueprintType Struct`  
**Purpose**: Row in faction relationship matrix

**Properties**:
- `FromFaction` (FGameplayTag): Source faction in relationship
- `Relations` (TMap<FGameplayTag, EFactionRelation>): Relationships to other factions

## Component Properties

### FactionComponentMultiTag Properties

#### Faction Tags
**Property**: `FactionTags`  
**Type**: `FGameplayTagContainer`  
**Category**: `Faction`  
**Blueprint Access**: `Read Only`  
**Replication**: `Yes`  
**Purpose**: All faction tags this actor belongs to

**Usage**: Defines which factions this actor is a member of. Replicated for multiplayer consistency.

## Data Assets

### FactionCatalog
**Type**: `UDataAsset`  
**Purpose**: Central repository of all factions in the game

**Properties**:
- `Factions` (TArray<FFactionInfo>): Array of all faction definitions

**Usage**: Create one per project to define all available factions with their properties and thresholds.

### FactionRelationshipMatrix
**Type**: `UDataAsset`  
**Purpose**: Defines default relationships between all factions

**Properties**:
- `Relations` (TArray<FFactionRelationRow>): Matrix of faction relationships

**Usage**: Establishes baseline relationships that can be overridden at runtime.

## Zone System Components

### FactionZoneVolume
*Volume defining faction territory*

**Type**: `Actor`  
**Category**: `Zone`  
**File**: `FactionZoneVolume.h`

Defines geographical areas controlled by specific factions.

#### Zone Properties

##### Controlling Faction
**Property**: `ControllingFaction`  
**Type**: `FGameplayTag`  
**Category**: `Zone`  
**Blueprint Access**: `Read Only`  
**Replication**: `Yes`  
**Purpose**: Faction that controls this territory

##### Zone State
**Property**: `ZoneState`  
**Type**: `EZoneState`  
**Category**: `Zone`  
**Blueprint Access**: `Read Only`  
**Purpose**: Current state of the zone (peaceful, contested, hostile)

##### Reputation Modifier
**Property**: `ReputationModifier`  
**Type**: `float`  
**Category**: `Zone`  
**Blueprint Access**: `Read Only`  
**Purpose**: Modifier applied to reputation changes in this zone

## Developer Settings

Access via **Project Settings → Game → DAI Faction**

### Reputation Settings

#### Reputation Minimum
**Property**: `ReputationMin`  
**Type**: `float`  
**Default**: `-100.0`  
**Purpose**: Global minimum reputation value (lower clamp)

All reputation values are clamped to this minimum to prevent infinite negative reputation.

#### Reputation Maximum
**Property**: `ReputationMax`  
**Type**: `float`  
**Default**: `100.0`  
**Purpose**: Global maximum reputation value (upper clamp)

All reputation values are clamped to this maximum to prevent infinite positive reputation.

### Debug Settings

#### Verbose Reputation Log
**Property**: `bVerboseReputationLog`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Enable detailed logging of reputation changes and evaluations

When enabled, logs all reputation mutations, threshold crossings, and relationship evaluations.

## Usage Examples

### Basic Faction Setup
```blueprint
// Create faction catalog data asset
UFactionCatalog* Catalog = NewObject<UFactionCatalog>();

// Define faction information
FFactionInfo PlayerFaction;
PlayerFaction.Id = FGameplayTag::RequestGameplayTag("Faction.Player");
PlayerFaction.DisplayName = FText::FromString("Player Alliance");
PlayerFaction.Color = FLinearColor::Blue;
PlayerFaction.Thresholds.Hostile = -50;
PlayerFaction.Thresholds.Friendly = 50;

Catalog->Factions.Add(PlayerFaction);
```

### Actor Faction Assignment
```blueprint
// Assign faction to character
UFactionComponentMultiTag* FactionComp = CreateDefaultSubobject<UFactionComponentMultiTag>("FactionComponent");

FGameplayTagContainer FactionTags;
FactionTags.AddTag(FGameplayTag::RequestGameplayTag("Faction.Player"));
FactionTags.AddTag(FGameplayTag::RequestGameplayTag("Faction.Mercenary"));
FactionComp->SetFactionTags(FactionTags);
```

## GAS and StateTree Integration

This plugin exposes faction activity through two channels:

- Gameplay Events (recommended): When reputation changes, the subsystem sends a Gameplay Event with tag `DAI.Faction.ReputationChanged` to the actor’s Ability System Component (if present). StateTree tasks and GAS abilities can listen for this event to react (e.g., update UI, trigger barks).
- AttributeSet (optional): If the actor’s ASC includes `UDAI_FactionAttributeSet`, two replicated attributes are updated:
    - `ReputationDelta` — last applied reputation change (float)
    - `RelationCode` — coarse relation indicator (-1..2). You can also compute this via `GetRelationCode` when needed.

Suggested patterns:
- In a StateTree, add a “Wait Gameplay Event” or a custom evaluator to observe `DAI.Faction.ReputationChanged` and fetch `ReputationDelta`.
- In GAS, author passive abilities that activate on the event tag to drive HUD/widgets.

Project Settings → Game → DAI Faction exposes toggles:
- Send Gameplay Events (default ON)
- Update AttributeSet (default ON)

Steps:
1) Ensure your pawn/character implements AbilitySystemInterface and has an ASC.
2) Optionally add `UDAI_FactionAttributeSet` to the ASC init attributes (for replicated `ReputationDelta`/`RelationCode`).
3) In StateTree, use Wait Gameplay Event for tag `DAI.Faction.ReputationChanged` to react to reputation deltas.
4) In GAS, create abilities with event-based triggers bound to the same tag, or evaluate `ReputationDelta` from the attribute set.

Note: AttributeSet is optional; events still fire if an ASC is present.

## Console Commands

- `DAI.Faction.Help` — list commands
- `DAI.Faction.AreHostile <ActorA> <ActorB>`
- `DAI.Faction.AdjustRep <ActorName> <FactionTag> <Delta>`
- `DAI.Faction.ListFactions <ActorName>`

### Reputation Management
```blueprint
// Adjust reputation for completing quest
UFactionBlueprintLibrary::AdjustRep(
    this, 
    Player, 
    FGameplayTag::RequestGameplayTag("Faction.Traders"), 
    25.0f, 
    FName("QuestComplete")
);

// Check current reputation
float CurrentRep = FactionComp->GetReputationWith(
    FGameplayTag::RequestGameplayTag("Faction.Traders")
);

if (CurrentRep >= 50.0f)
{
    // Player is now friendly with traders
    UnlockTradingDiscounts();
}
```

### Hostility Checks
```blueprint
// AI behavior based on faction relationships
bool bAreEnemies = UFactionBlueprintLibrary::AreHostile(this, Player, NPCActor);

if (bAreEnemies)
{
    // Initiate combat
    AIController->SetTarget(Player);
    StartCombat();
}
else
{
    EFactionRelation Relation = FactionComp->GetRelationTo(Player);
    switch (Relation)
    {
        case EFactionRelation::Ally:
            OfferAssistance();
            break;
        case EFactionRelation::Neutral:
            ContinueNormalBehavior();
            break;
        case EFactionRelation::Tense:
            ShowSuspicion();
            break;
    }
}
```

### Dynamic Faction Changes
```blueprint
// Character defection system
void DefectToFaction(FGameplayTag NewFaction)
{
    // Remove old faction memberships
    FGameplayTagContainer EmptyTags;
    FactionComp->SetFactionTags(EmptyTags);
    
    // Add new faction
    FGameplayTagContainer NewTags;
    NewTags.AddTag(NewFaction);
    FactionComp->SetFactionTags(NewTags);
    
    // Adjust reputation with old and new factions
    UFactionBlueprintLibrary::AdjustRep(this, this, OldFaction, -75.0f, FName("Defection"));
    UFactionBlueprintLibrary::AdjustRep(this, this, NewFaction, 50.0f, FName("Recruitment"));
}
```

### Zone-Based Reputation
```blueprint
// In FactionZoneVolume
void OnActorEnterZone(AActor* Actor)
{
    UFactionComponentMultiTag* ActorFaction = Actor->FindComponentByClass<UFactionComponentMultiTag>();
    if (ActorFaction && ActorFaction->IsHostileTo(ZoneOwner))
    {
        // Hostile actor entered faction territory
        SpawnGuards();
        AlertNearbyAllies();
    }
}

// Reputation changes affected by zone
void OnReputationAdjustment(AActor* Subject, FGameplayTag Faction, float Delta)
{
    if (Subject->IsInZone(this))
    {
        // Apply zone modifier
        float ModifiedDelta = Delta * ZoneReputationModifier;
        // Apply additional zone-specific effects
        if (Faction == ControllingFaction && Delta > 0)
        {
            // Bonus reputation for helping faction in their territory
            ModifiedDelta *= 1.5f;
        }
    }
}
```

## Integration with Other Plugins

### DAI_Hub Integration
- **Event Publishing**: Reputation changes publish events through hub
- **Service Registration**: Faction service registers with hub for discovery
- **Performance Coordination**: Respects hub performance budgets

### DAI_AI Integration
- **Hostility Bridge**: AI agents use faction component for hostility determination
- **Behavior Integration**: AI behavior trees can query faction relationships
- **Communication**: AI alerts can include faction context

### DAI_Save Integration
- **Automatic Persistence**: Reputation and membership data saved automatically
- **Fragment Provider**: Implements save fragment interface for data persistence
- **Restore Logic**: Properly restores faction state on game load

### DAI_QuestManager Integration
- **Quest Gating**: Quests can be gated by faction reputation
- **Reputation Rewards**: Quest completion can trigger reputation changes
- **Faction Objectives**: Quests can have faction-specific variants

## Best Practices

### Faction Design
1. **Create clear faction hierarchies** with meaningful relationships
2. **Design reputation thresholds** that create interesting gameplay moments
3. **Use consistent naming conventions** for faction tags
4. **Balance reputation changes** to avoid trivial or impossible progression
5. **Document faction relationships** for team reference

### Performance Optimization
1. **Cache relationship queries** for frequently checked pairs
2. **Use events sparingly** to avoid performance impact
3. **Batch reputation updates** when possible
4. **Monitor zone overlap** to prevent expensive calculations
5. **Profile reputation lookups** in complex scenarios

### Multiplayer Considerations
1. **Replicate faction tags** for consistent client state
2. **Handle authority properly** for reputation changes
3. **Synchronize zone states** across clients
4. **Test network latency** impact on faction checks
5. **Implement prediction** for responsive faction UI

### Data Management
1. **Use data assets** for faction definitions
2. **Version control** faction relationship matrices
3. **Implement validation** for faction data consistency
4. **Create editor tools** for faction relationship visualization
5. **Test save/load** thoroughly with complex faction states

## Event System Integration

### Reputation Events
- **Reputation Changed**: Published when any actor's reputation changes
- **Threshold Crossed**: Published when reputation crosses significant thresholds
- **Membership Changed**: Published when actor faction membership changes
- **Relationship Override**: Published when faction relationships are overridden

### Event Data
Events include relevant context such as:
- Actor involved
- Faction affected
- Old and new values
- Reason for change
- Zone context (if applicable)

## Technical Notes

- **Thread Safety**: All operations designed for game thread usage
- **Memory Management**: Efficient storage with automatic cleanup
- **Networking**: Full replication support for multiplayer games
- **Performance**: Optimized lookups with caching and spatial indexing
- **Save System**: Seamless integration with DAI_Save plugin

## Troubleshooting

### Reputation Not Changing
1. Check that faction service subsystem is properly initialized
2. Verify faction tags exist in the faction catalog
3. Ensure reputation values aren't hitting min/max clamps
4. Check for relationship overrides that might be blocking changes

### Hostility Checks Failing
1. Verify both actors have faction components
2. Check faction relationship matrix for correct relationships
3. Ensure faction tags are properly replicated in multiplayer
4. Test with simple two-faction setup first

### Performance Issues
1. Reduce frequency of hostility checks in AI
2. Cache relationship results for static faction pairs
3. Monitor event publication frequency
4. Optimize zone overlap calculations

### Save/Load Problems
1. Verify faction service implements save fragment interface
2. Check that faction tags serialize properly
3. Test with clean save data first
4. Monitor save fragment size for large faction systems

---

*For more information about AI integration, see [DAI_AI documentation](DAI_AI.md).*  
*For hub integration details, see [DAI_Hub documentation](DAI_Hub.md).*  
*For quest integration, see [DAI_QuestManager documentation](DAI_QuestManager.md).*