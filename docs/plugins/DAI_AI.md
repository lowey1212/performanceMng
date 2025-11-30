# DAI_AI Plugin Documentation

## Overview

**DAI_AI** is a comprehensive AI system plugin that provides intelligent behavior, emotional modeling, communication systems, and perception capabilities for Unreal Engine 5.5. The system integrates with Unreal's StateTree, Gameplay Ability System (GAS), and provides modular components for creating sophisticated AI entities.

### Key Features
- 🤖 **Agent System**: Team-based identification and hostility management
- 💭 **Affect System**: Emotional modeling with Fear, Anger, Curiosity, Happiness, and Alertness
- 📡 **Communication System**: AI alert broadcasting and message queuing
- 👁️ **Perception Helpers**: Line-of-sight and detection utilities
- 🦁 **Predator-Prey System**: Ecosystem-based relationship modeling
- 🎯 **StateTree Integration**: Modern state-based AI behavior
- 🎮 **GAS Integration**: Attribute-based emotional state management
- 🔍 **Line-of-Sight Batching**: Performance-optimized visibility checks

## Architecture

The DAI_AI system consists of:
- **Agent Components**: Core AI identity and team management
- **Affect System**: Emotional state modeling and reactions
- **Communication System**: Inter-AI messaging and alerts
- **Perception Systems**: Optimized sensory input processing
- **Behavior Integration**: StateTree and ability system connectivity

## Core Components

### DAIAgentComponent
*Lightweight AI agent component for team/hostility checks and perception helpers*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `DAI|Agent`  
**File**: `DAIAgentComponent.h`

Provides basic AI identity, team management, and simple perception utilities.

### DAIAICommComponent
*AI communication system for broadcasting and receiving alerts*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `DAI|Comm`  
**File**: `DAIAICommComponent.h`

Enables AI entities to communicate alerts and coordinate behavior.

### DAIAffectAttributeSet
*Gameplay Attribute Set for emotional modeling*

**Type**: `Attribute Set`  
**Category**: `DAI|Affect|Attr`  
**File**: `DAIAffectAttributeSet.h`

Provides GAS-based emotional attributes for AI entities.

### DAIAffectStateComponent
*Component managing emotional state transitions*

**Type**: `Actor Component`  
**Category**: `AI|Affect`  
**File**: `DAIAffectStateComponent.h`

## Blueprint Functions

### Agent System Functions

#### IsHostileTo
**Type**: `BlueprintCallable`  
**Category**: `DAI|Agent`  
**Returns**: `bool`  
**Purpose**: Check if another actor is considered hostile

**Parameters**:
- `Other` (AActor): Actor to check hostility against

```cpp
bool IsHostileTo(const AActor* Other) const;
```

**Usage**: Returns true if the other actor's team tag is in this agent's hostile teams list, or if faction bridge determines hostility.

#### HasLineOfSightTo
**Type**: `BlueprintCallable`  
**Category**: `DAI|Agent`  
**Returns**: `bool`  
**Purpose**: Perform line-of-sight check to target with optional distance limit

**Parameters**:
- `Target` (AActor): Actor to check line-of-sight to
- `MaxDistance` (float): Maximum distance for check (0 = unlimited)
- `ActorsToIgnore` (TArray<AActor*>): Actors to ignore during trace

```cpp
bool HasLineOfSightTo(const AActor* Target, float MaxDistance, const TArray<AActor*>& ActorsToIgnore) const;
```

**Usage**: Performs a trace from agent to target, useful for perception and targeting decisions.

#### HasLineOfSightSimple
**Type**: `BlueprintCallable`  
**Category**: `DAI|Agent`  
**Returns**: `bool`  
**Purpose**: Simplified line-of-sight check without ignore list

**Parameters**:
- `Target` (AActor): Actor to check line-of-sight to
- `MaxDistance` (float): Maximum distance for check (0 = unlimited)

```cpp
bool HasLineOfSightSimple(const AActor* Target, float MaxDistance = 0.f) const;
```

**Usage**: Convenience function for basic line-of-sight checks.

### Communication System Functions

#### BroadcastAlert
**Type**: `BlueprintCallable`  
**Category**: `DAI|Comm`  
**Purpose**: Broadcast an alert to other nearby AI communication components

**Parameters**:
- `Message` (FDAIAlertMessage): Alert message to broadcast

```cpp
void BroadcastAlert(const FDAIAlertMessage& Message);
```

**Usage**: Sends alert to all nearby AI agents within communication range.

#### PopAlert
**Type**: `BlueprintCallable`  
**Category**: `DAI|Comm`  
**Returns**: `bool`  
**Purpose**: Remove and return the oldest queued alert matching allowed tags

**Parameters**:
- `AllowedTags` (FGameplayTagContainer): Tags to filter alerts (empty = any)
- `OutMessage` (FDAIAlertMessage): Retrieved alert message

```cpp
bool PopAlert(const FGameplayTagContainer& AllowedTags, FDAIAlertMessage& OutMessage);
```

**Usage**: Process incoming alerts from other AI agents.

#### GetQueueSnapshot
**Type**: `BlueprintCallable`  
**Category**: `DAI|Comm`  
**Purpose**: Copy current queued alerts into an array for save or inspection

**Parameters**:
- `OutAlerts` (TArray<FDAIAlertMessage>): Array to fill with current alerts

```cpp
void GetQueueSnapshot(TArray<FDAIAlertMessage>& OutAlerts) const;
```

**Usage**: Useful for save/load systems or debugging.

#### RestoreQueueSnapshot
**Type**: `BlueprintCallable`  
**Category**: `DAI|Comm`  
**Purpose**: Restore alerts previously captured via GetQueueSnapshot

**Parameters**:
- `Alerts` (TArray<FDAIAlertMessage>): Alerts to restore to queue

```cpp
void RestoreQueueSnapshot(const TArray<FDAIAlertMessage>& Alerts);
```

**Usage**: Restore alert state during loading.

### Predator-Prey System Functions

#### IsPrey
**Type**: `BlueprintCallable`  
**Category**: `PredatorPrey`  
**Returns**: `bool`  
**Purpose**: Check if target is considered prey by hunter according to matrix

**Parameters**:
- `Hunter` (AActor): Actor doing the hunting
- `Target` (AActor): Potential prey actor
- `Matrix` (UDAIPredatorPreyMatrix): Relationship matrix to consult

```cpp
bool IsPrey(AActor* Hunter, AActor* Target, const UDAIPredatorPreyMatrix* Matrix);
```

**Usage**: Determine natural predator-prey relationships for ecosystem AI.

#### GetActorFactionTags
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `PredatorPrey`  
**Returns**: `FGameplayTagContainer`  
**Purpose**: Get faction tags for an actor

**Parameters**:
- `Actor` (AActor): Actor to get faction tags from

```cpp
FGameplayTagContainer GetActorFactionTags(AActor* Actor);
```

**Usage**: Retrieves faction tags from faction component or agent team tag.

### Affect System Functions

#### SetAffectStimulus
**Type**: `BlueprintCallable`  
**Category**: `AI|Affect`  
**Purpose**: Apply emotional stimulus to affect component

**Parameters**:
- `StimulusType` (FGameplayTag): Type of emotional stimulus
- `Strength` (float): Intensity of the stimulus

```cpp
void SetAffectStimulus(FGameplayTag StimulusType, float Strength);
```

**Usage**: Trigger emotional responses in AI entities.

#### GetCurrentAffectState
**Type**: `BlueprintCallable`  
**Category**: `AI|Affect`  
**Returns**: `FGameplayTag`  
**Purpose**: Get the current dominant emotional state

```cpp
FGameplayTag GetCurrentAffectState() const;
```

**Usage**: Determine what emotional state the AI is currently experiencing.

## Blueprint Data Types

### FDAIAlertMessage (Alert Message)
**Type**: `BlueprintType Struct`  
**Purpose**: Message passed between AI communication components

**Properties**:
- `AlertTag` (FGameplayTag): Category/tag describing the alert purpose (e.g., DAI.Alert.EnemySeen)
- `Sender` (AActor): Actor that originated the alert
- `Instigator` (AActor): Actor that caused the event (may differ from Sender)
- `Target` (AActor): Primary target actor of the alert
- `Location` (FVector): World-space location relevant to the alert
- `TimeSeconds` (float): Game time when the alert was generated

### Affect Attributes (GAS)
**Type**: `Gameplay Attributes`  
**Category**: `DAI|Affect|Attr`  
**Range**: `0.0 - 1.0` (normalized)

#### Fear
- **Purpose**: Fear intensity driving Scared/Flee state transitions
- **Replication**: `OnRep_Fear`
- **Usage**: Higher values cause defensive or flee behaviors

#### Anger
- **Purpose**: Anger intensity driving Angry/Attack state transitions
- **Replication**: `OnRep_Anger`
- **Usage**: Higher values cause aggressive behaviors

#### Curiosity
- **Purpose**: Curiosity intensity driving investigative behaviors
- **Replication**: `OnRep_Curiosity`
- **Usage**: Above threshold enters Curious state

#### Happiness
- **Purpose**: Happiness intensity affecting social behaviors
- **Replication**: `OnRep_Happiness`
- **Usage**: Above threshold enters Happy state

#### Alertness
- **Purpose**: Alertness level affecting perception and state transitions
- **Replication**: `OnRep_Alertness`
- **Usage**: Influences perception gating and reaction speed

## Component Properties

### DAIAgentComponent Properties

#### Team Tag
**Property**: `TeamTag`  
**Type**: `FGameplayTag`  
**Category**: `DAI|Agent`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Primary team/faction identifier (e.g., AI.Team.Player, AI.Team.Enemy)

#### Hostile Teams
**Property**: `HostileTeams`  
**Type**: `FGameplayTagContainer`  
**Category**: `DAI|Agent`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Team tags this agent treats as hostile

### DAIAICommComponent Properties

#### Listen Alert Tags
**Property**: `ListenAlertTags`  
**Type**: `FGameplayTagContainer`  
**Category**: `DAI|Comm`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Filter tags for received alerts (empty = receive all)

#### Communication Range
**Property**: `Range`  
**Type**: `float`  
**Category**: `DAI|Comm`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Maximum distance for broadcasting/receiving alerts

#### Alert Queue
**Property**: `AlertQueue`  
**Type**: `TArray<FDAIAlertMessage>`  
**Category**: `DAI|Comm`  
**Blueprint Access**: `Read Only`  
**Purpose**: Internal queue of received alerts

## Events and Delegates

### OnDAIAlertReceived
**Type**: `Dynamic Multicast Delegate`  
**Category**: `DAI|Comm`  
**Purpose**: Fired when AI communication component receives an alert

**Parameters**:
- `Message` (FDAIAlertMessage): The received alert message

**Usage**: Bind to this delegate to react to incoming AI alerts.

## Usage Examples

### Basic Agent Setup
```blueprint
// Set up agent component
UDAIAgentComponent* Agent = CreateDefaultSubobject<UDAIAgentComponent>("Agent");
Agent->TeamTag = AI.Team.Player;
Agent->HostileTeams.AddTag(AI.Team.Enemy);
Agent->HostileTeams.AddTag(AI.Team.Wildlife.Aggressive);
```

### Hostility Check
```blueprint
// Check if target is hostile before attacking
if (Agent->IsHostileTo(TargetActor))
{
    // Check line of sight before engaging
    if (Agent->HasLineOfSightSimple(TargetActor, 1000.0f))
    {
        BeginCombat(TargetActor);
    }
}
```

### AI Communication
```blueprint
// Send enemy spotted alert
FDAIAlertMessage Alert;
Alert.AlertTag = DAI.Alert.EnemySeen;
Alert.Sender = this;
Alert.Target = SpottedEnemy;
Alert.Location = SpottedEnemy->GetActorLocation();
Alert.TimeSeconds = GetWorld()->GetTimeSeconds();

CommComponent->BroadcastAlert(Alert);

// Process incoming alerts
FDAIAlertMessage IncomingAlert;
FGameplayTagContainer InterestingTags;
InterestingTags.AddTag(DAI.Alert.EnemySeen);
InterestingTags.AddTag(DAI.Alert.Danger);

if (CommComponent->PopAlert(InterestingTags, IncomingAlert))
{
    // React to the alert
    InvestigateLocation(IncomingAlert.Location);
}
```

### Emotional State Management
```blueprint
// Apply fear stimulus when taking damage
AffectComponent->SetAffectStimulus(DAI.Affect.Stimulus.Fear, 0.3f);

// Check current emotional state
FGameplayTag CurrentState = AffectComponent->GetCurrentAffectState();
if (CurrentState.MatchesTag(DAI.Affect.State.Scared))
{
    // Run away behavior
    FleeFromDanger();
}
else if (CurrentState.MatchesTag(DAI.Affect.State.Angry))
{
    // Aggressive behavior
    AttackNearbyEnemies();
}
```

### Predator-Prey Relationships
```blueprint
// Check if this actor should hunt the target
if (UDAIPredatorPreyLibrary::IsPrey(this, PotentialTarget, PredatorPreyMatrix))
{
    // Begin hunting behavior
    StartHuntingTarget(PotentialTarget);
}

// Get faction information
FGameplayTagContainer FactionTags = UDAIPredatorPreyLibrary::GetActorFactionTags(SomeActor);
```

## Integration with Other Plugins

### DAI_Hub Integration
- **Service Registration**: AI services register with hub for discovery
- **Event Communication**: AI alerts can be published through hub events
- **Performance Budgeting**: AI operations respect performance budgets

### DAI_Faction Integration
- **Team Resolution**: Agent components can bridge to faction system
- **Reputation System**: Emotional states can affect faction standings

### StateTree Integration
- **Affect Conditions**: StateTree can query emotional states
- **Communication Tasks**: StateTree tasks can send/receive alerts
- **Perception Tasks**: StateTree can use agent perception helpers

### Gameplay Ability System
- **Affect Attributes**: Emotional states exposed as GAS attributes
- **Ability Gating**: Abilities can be gated by emotional states
- **Stimulus Application**: Abilities can trigger emotional stimuli

## Best Practices

### Agent Configuration
1. **Use hierarchical team tags** (e.g., AI.Team.Player.Squad1)
2. **Configure hostility relationships** based on game design
3. **Set appropriate communication ranges** for performance
4. **Use faction bridging** for complex relationship systems

### Performance Optimization
1. **Limit alert frequency** to avoid message spam
2. **Use filtered listening** to reduce processing overhead
3. **Batch line-of-sight checks** through LOS subsystem
4. **Monitor affect attribute replication** in multiplayer

### Emotional Modeling
1. **Design stimulus curves** for realistic emotional responses
2. **Use thresholds** for state transitions
3. **Implement decay systems** for natural emotional recovery
4. **Balance emotional intensity** for engaging but not overwhelming AI

### Communication Design
1. **Use meaningful alert tags** for proper filtering
2. **Include relevant context** in alert messages
3. **Implement alert prioritization** for important events
4. **Design response behaviors** for different alert types

## Technical Notes

- **Thread Safety**: AI operations are designed for game thread usage
- **Memory Management**: Alert queues are automatically managed
- **Networking**: Affect attributes support replication
- **Performance**: LOS batching optimizes perception checks
- **State Persistence**: Communication state can be saved/loaded

## Common AI Patterns

### Guard Behavior
```blueprint
// Guard that responds to alerts and investigates
void OnAlertReceived(const FDAIAlertMessage& Alert)
{
    if (Alert.AlertTag.MatchesTag(DAI.Alert.Intruder) && 
        FVector::Dist(GetActorLocation(), Alert.Location) < GuardRadius)
    {
        SetPatrolTarget(Alert.Location);
        SetEmotionalState(DAI.Affect.State.Alert);
    }
}
```

### Pack Hunting
```blueprint
// Coordinate pack hunting through communication
void InitiatePackHunt(AActor* Prey)
{
    FDAIAlertMessage HuntAlert;
    HuntAlert.AlertTag = DAI.Alert.PackHunt.Initiate;
    HuntAlert.Target = Prey;
    HuntAlert.Sender = this;
    
    CommComponent->BroadcastAlert(HuntAlert);
}
```

### Emotional Contagion
```blueprint
// Spread emotional states through groups
void PropagateEmotion(FGameplayTag EmotionTag, float Intensity)
{
    FDAIAlertMessage EmotionAlert;
    EmotionAlert.AlertTag = FGameplayTag::RequestGameplayTag("DAI.Alert.Emotion." + EmotionTag.ToString());
    EmotionAlert.Sender = this;
    
    CommComponent->BroadcastAlert(EmotionAlert);
}
```

---

*For more information about faction integration, see [DAI_Faction documentation](DAI_Faction.md).*  
*For hub integration details, see [DAI_Hub documentation](DAI_Hub.md).*  
*For StateTree node reference, see [DAI_AI StateTree Nodes](../StateTree_DAI_AI_Nodes.md).*  
*For StateTree patterns, consult the Unreal Engine 5.5 StateTree documentation.*

---

Last updated: October 6, 2025