# DAI Plugin Documentation

## Overview

**DAI (Data Asset Inventory)** is a comprehensive gameplay framework for Unreal Engine 5.5 that provides a flexible inventory system fully integrated with the Gameplay Ability System (GAS) to handle all combat elements, character progression, and item management. The plugin serves as the foundation for complex RPG and action game mechanics with robust multiplayer support and extensible architecture.

### Key Features
- 🎒 **Advanced Inventory System**: Flexible item management with containers, stacking, and organization
- ⚔️ **Combat Integration**: Complete combat system with damage, healing, and status effects
- 🎯 **Gameplay Ability System**: Full GAS integration for abilities, attributes, and effects
- 👤 **Character Progression**: Leveling, skill trees, and attribute advancement
- 🔄 **Item Enhancement**: Crafting, upgrading, and modification systems  
- 🌐 **Multiplayer Ready**: Full replication support with optimized network performance
- 💾 **Save Integration**: Seamless persistence through DAI_Save system
- 🎭 **Equipment System**: Complex equipment slots with stat modifications
- 🏪 **Trading System**: Player-to-player and NPC trading functionality
- 🎮 **Blueprint Friendly**: Extensive Blueprint integration for designers

## Architecture

The DAI system consists of:
- **Inventory Management**: Core item storage and organization
- **Gameplay Ability Integration**: GAS-based ability and effect systems
- **Combat System**: Damage calculation and effect application
- **Character Progression**: Experience, levels, and attribute systems
- **Equipment Management**: Wearable items and stat modifications
- **Trading and Economy**: Item exchange and value systems

## Core Components

### DAICharacter
*Enhanced character class with inventory and GAS integration*

**Type**: `Character`  
**Parent**: `ACharacter`  
**Interfaces**: `IAbilitySystemInterface`, `IDAIInventoryInterface`  
**File**: `DAICharacter.h`

Primary character class providing inventory, abilities, and combat functionality.

### DAIInventoryComponent
*Component managing item storage and organization*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `DAI|Inventory`  
**File**: `DAIInventoryComponent.h`

Core component handling all inventory operations, item management, and container functionality.

### DAIAbilitySystemComponent
*Enhanced ability system component with DAI integration*

**Type**: `Actor Component`  
**Parent**: `UAbilitySystemComponent`  
**File**: `DAIAbilitySystemComponent.h`

Extended GAS component with DAI-specific functionality and optimizations.

### DAIAttributeSet
*Base attribute set for character stats*

**Type**: `Attribute Set`  
**Parent**: `UAttributeSet`  
**File**: `DAIAttributeSet.h`

Foundational attribute set containing core character statistics and modifiers.

### DAIItem
*Base class for all items in the system*

**Type**: `UObject`  
**Interfaces**: `IDAIItemInterface`  
**File**: `DAIItem.h`

Base item class providing core functionality for all item types.

### DAIEquipmentComponent
*Component managing equipped items and their effects*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**Category**: `DAI|Equipment`  
**File**: `DAIEquipmentComponent.h`

Handles equipment slots, stat modifications, and visual representation of equipped items.

## Blueprint Functions

### Inventory Management

#### AddItemToInventory
**Type**: `BlueprintCallable`  
**Category**: `DAI|Inventory`  
**Returns**: `bool`  
**Purpose**: Add an item to the character's inventory

**Parameters**:
- `Item` (UDAIItem): Item to add to inventory
- `Quantity` (int32): Number of items to add
- `bAllowPartialAdd` (bool): Whether to allow partial addition if inventory space is limited

```cpp
bool AddItemToInventory(UDAIItem* Item, int32 Quantity = 1, bool bAllowPartialAdd = true);
```

**Usage**: Primary function for giving items to characters from various sources.

#### RemoveItemFromInventory
**Type**: `BlueprintCallable`  
**Category**: `DAI|Inventory`  
**Returns**: `int32`  
**Purpose**: Remove items from inventory

**Parameters**:
- `Item` (UDAIItem): Item to remove
- `Quantity` (int32): Number of items to remove
- `bExactMatch` (bool): Whether to require exact item match or allow similar items

```cpp
int32 RemoveItemFromInventory(UDAIItem* Item, int32 Quantity = 1, bool bExactMatch = true);
```

**Usage**: Remove items for consumption, trading, or quest requirements.

#### GetInventoryContents
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `DAI|Inventory`  
**Returns**: `TArray<FDAIItemStack>`  
**Purpose**: Get all items currently in inventory

```cpp
TArray<FDAIItemStack> GetInventoryContents() const;
```

**Usage**: Display inventory contents in UI or check for specific items.

#### HasItem
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `DAI|Inventory`  
**Returns**: `bool`  
**Purpose**: Check if inventory contains a specific item

**Parameters**:
- `Item` (UDAIItem): Item to check for
- `RequiredQuantity` (int32): Minimum quantity required

```cpp
bool HasItem(UDAIItem* Item, int32 RequiredQuantity = 1) const;
```

**Usage**: Validate quest requirements, recipe prerequisites, or ability costs.

### Equipment System

#### EquipItem
**Type**: `BlueprintCallable`  
**Category**: `DAI|Equipment`  
**Returns**: `bool`  
**Purpose**: Equip an item to an equipment slot

**Parameters**:
- `Item` (UDAIItem): Item to equip
- `SlotName` (FName): Equipment slot to use (optional, auto-detects if empty)
- `bForceEquip` (bool): Whether to force equip even if slot is occupied

```cpp
bool EquipItem(UDAIItem* Item, FName SlotName = NAME_None, bool bForceEquip = false);
```

**Usage**: Equip weapons, armor, and accessories with automatic stat application.

#### UnequipItem
**Type**: `BlueprintCallable`  
**Category**: `DAI|Equipment`  
**Returns**: `UDAIItem*`  
**Purpose**: Remove an item from equipment slot

**Parameters**:
- `SlotName` (FName): Equipment slot to clear

```cpp
UDAIItem* UnequipItem(FName SlotName);
```

**Usage**: Remove equipped items and return them to inventory.

#### GetEquippedItem
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `DAI|Equipment`  
**Returns**: `UDAIItem*`  
**Purpose**: Get item currently equipped in a slot

**Parameters**:
- `SlotName` (FName): Equipment slot to check

```cpp
UDAIItem* GetEquippedItem(FName SlotName) const;
```

**Usage**: Check what's currently equipped for UI display or logic decisions.

### Ability System Integration

#### GrantAbility
**Type**: `BlueprintCallable`  
**Category**: `DAI|Abilities`  
**Returns**: `FGameplayAbilitySpecHandle`  
**Purpose**: Grant a gameplay ability to the character

**Parameters**:
- `AbilityClass` (TSubclassOf<UGameplayAbility>): Ability class to grant
- `Level` (int32): Level of the ability
- `InputID` (int32): Input binding for the ability

```cpp
FGameplayAbilitySpecHandle GrantAbility(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level = 1, int32 InputID = -1);
```

**Usage**: Give new abilities to characters through leveling, items, or story progression.

#### TryActivateAbility
**Type**: `BlueprintCallable`  
**Category**: `DAI|Abilities`  
**Returns**: `bool`  
**Purpose**: Attempt to activate an ability by class

**Parameters**:
- `AbilityClass` (TSubclassOf<UGameplayAbility>): Ability class to activate
- `bAllowRemoteActivation` (bool): Whether to allow network activation

```cpp
bool TryActivateAbility(TSubclassOf<UGameplayAbility> AbilityClass, bool bAllowRemoteActivation = true);
```

**Usage**: Trigger abilities from input, AI logic, or scripted events.

#### ApplyGameplayEffect
**Type**: `BlueprintCallable`  
**Category**: `DAI|Abilities`  
**Returns**: `FActiveGameplayEffectHandle`  
**Purpose**: Apply a gameplay effect to the character

**Parameters**:
- `EffectClass` (TSubclassOf<UGameplayEffect>): Effect class to apply
- `Level` (float): Level of the effect
- `Source` (AActor): Source actor for the effect

```cpp
FActiveGameplayEffectHandle ApplyGameplayEffect(TSubclassOf<UGameplayEffect> EffectClass, float Level = 1.0f, AActor* Source = nullptr);
```

**Usage**: Apply buffs, debuffs, damage, or healing effects.

### Character Progression

#### GainExperience
**Type**: `BlueprintCallable`  
**Category**: `DAI|Progression`  
**Purpose**: Add experience points to the character

**Parameters**:
- `ExperienceAmount` (float): Amount of experience to gain
- `ExperienceSource` (FGameplayTag): Source of the experience (optional)

```cpp
void GainExperience(float ExperienceAmount, FGameplayTag ExperienceSource = FGameplayTag());
```

**Usage**: Award experience for kills, quest completion, or discovery.

#### GetCharacterLevel
**Type**: `BlueprintCallable`, `BlueprintPure`  
**Category**: `DAI|Progression`  
**Returns**: `int32`  
**Purpose**: Get current character level

```cpp
int32 GetCharacterLevel() const;
```

**Usage**: Display level in UI or check level requirements for content.

#### SpendAttributePoints
**Type**: `BlueprintCallable`  
**Category**: `DAI|Progression`  
**Returns**: `bool`  
**Purpose**: Spend attribute points to increase a stat

**Parameters**:
- `Attribute` (FGameplayAttribute): Attribute to increase
- `PointsToSpend` (int32): Number of points to spend

```cpp
bool SpendAttributePoints(FGameplayAttribute Attribute, int32 PointsToSpend);
```

**Usage**: Character customization and stat allocation systems.

### Trading System

#### InitiateTrade
**Type**: `BlueprintCallable`  
**Category**: `DAI|Trading`  
**Returns**: `bool`  
**Purpose**: Start a trade session with another character

**Parameters**:
- `TradePartner` (ADAICharacter): Character to trade with
- `TradeType` (EDAITradeType): Type of trade (player, merchant, etc.)

```cpp
bool InitiateTrade(ADAICharacter* TradePartner, EDAITradeType TradeType = EDAITradeType::Player);
```

**Usage**: Begin trading interactions between players or with NPCs.

#### AddItemToTrade
**Type**: `BlueprintCallable`  
**Category**: `DAI|Trading`  
**Returns**: `bool`  
**Purpose**: Add an item to the current trade offer

**Parameters**:
- `Item` (UDAIItem): Item to add to trade
- `Quantity` (int32): Quantity to trade

```cpp
bool AddItemToTrade(UDAIItem* Item, int32 Quantity = 1);
```

**Usage**: Build trade offers during trading sessions.

#### AcceptTrade
**Type**: `BlueprintCallable`  
**Category**: `DAI|Trading`  
**Returns**: `bool`  
**Purpose**: Accept the current trade offer

```cpp
bool AcceptTrade();
```

**Usage**: Finalize trade agreements and execute item exchanges.

## Blueprint Data Types

### FDAIItemStack (Item Stack)
**Type**: `BlueprintType Struct`  
**Purpose**: Represents a stack of items in inventory

**Properties**:
- `Item` (UDAIItem): The item object
- `Quantity` (int32): Number of items in this stack
- `SlotIndex` (int32): Inventory slot index
- `bIsEquipped` (bool): Whether this item is currently equipped
- `ItemGUID` (FGuid): Unique identifier for this item instance

### EDAIItemType (Item Type)
**Type**: `BlueprintType Enum`  
**Purpose**: Classification of different item types

**Values**:
- `Weapon`: Weapons and combat implements
- `Armor`: Protective gear and clothing
- `Consumable`: Items that are consumed on use
- `Material`: Crafting materials and components
- `Quest`: Quest-specific items
- `Miscellaneous`: General items and collectibles
- `Currency`: Money and valuable items

### EDAIRarity (Item Rarity)
**Type**: `BlueprintType Enum`  
**Purpose**: Rarity classification for items

**Values**:
- `Common`: Basic items with standard properties
- `Uncommon`: Slightly enhanced items
- `Rare`: Valuable items with good bonuses
- `Epic`: Powerful items with significant bonuses
- `Legendary`: Extremely rare and powerful items
- `Artifact`: Unique items with special properties

### FDAIItemStats (Item Statistics)
**Type**: `BlueprintType Struct`  
**Purpose**: Statistical modifiers provided by items

**Properties**:
- `AttributeModifiers` (TMap<FGameplayAttribute, float>): Attribute bonuses/penalties
- `DamageBonus` (float): Additional damage when equipped
- `DefenseBonus` (float): Additional defense when equipped
- `HealthBonus` (float): Additional health when equipped
- `ManaBonus` (float): Additional mana when equipped
- `SpecialEffects` (TArray<TSubclassOf<UGameplayEffect>>): Special effects granted by item

### FDAICharacterProgression (Character Progression)
**Type**: `BlueprintType Struct`  
**Purpose**: Character advancement and progression data

**Properties**:
- `CurrentLevel` (int32): Current character level
- `CurrentExperience` (float): Current experience points
- `ExperienceToNextLevel` (float): Experience needed for next level
- `AvailableAttributePoints` (int32): Unspent attribute points
- `AvailableSkillPoints` (int32): Unspent skill points
- `TotalExperienceEarned` (float): Lifetime experience earned
- `LevelUpRewards` (TArray<FDAILevelUpReward>): Pending level-up rewards

### FDAITradeOffer (Trade Offer)
**Type**: `BlueprintType Struct`  
**Purpose**: Items and currency offered in a trade

**Properties**:
- `OfferedItems` (TArray<FDAIItemStack>): Items being offered
- `OfferedCurrency` (int32): Currency amount offered
- `TradeValue` (float): Total estimated value of the offer
- `bIsAccepted` (bool): Whether this offer has been accepted
- `OfferingPlayer` (ADAICharacter): Player making this offer

### FDAIEquipmentSlot (Equipment Slot)
**Type**: `BlueprintType Struct`  
**Purpose**: Configuration for an equipment slot

**Properties**:
- `SlotName` (FName): Unique name for this slot
- `SlotType` (EDAIEquipmentSlotType): Type of equipment this slot accepts
- `bIsVisible` (bool): Whether this slot is visible in UI
- `bIsRequired` (bool): Whether this slot must be filled
- `DefaultItem` (UDAIItem): Default item for this slot
- `AcceptedItemTypes` (TArray<EDAIItemType>): Item types that can be equipped here

## Component Properties

### DAIInventoryComponent Properties

#### Storage Configuration
**Property**: `MaxInventorySlots`  
**Type**: `int32`  
**Category**: `Inventory`  
**Blueprint Access**: `Read/Write`  
**Default**: `30`  
**Purpose**: Maximum number of inventory slots available

**Property**: `bAllowItemStacking`  
**Type**: `bool`  
**Category**: `Inventory`  
**Blueprint Access**: `Read/Write`  
**Default**: `true`  
**Purpose**: Whether items can stack in inventory slots

**Property**: `MaxStackSize`  
**Type**: `int32`  
**Category**: `Inventory`  
**Blueprint Access**: `Read/Write`  
**Default**: `99`  
**Purpose**: Maximum number of items per stack

#### Organization Settings
**Property**: `bAutoSortInventory`  
**Type**: `bool`  
**Category**: `Inventory`  
**Blueprint Access**: `Read/Write`  
**Default**: `false`  
**Purpose**: Whether to automatically sort inventory contents

**Property**: `SortCriteria` (EDAISortCriteria)**: `EDAISortCriteria`  
**Type**: **Category**: `Inventory`  
**Blueprint Access**: `Read/Write`  
**Default**: `ByType`  
**Purpose**: Criteria for automatic inventory sorting

### DAIEquipmentComponent Properties

#### Equipment Slots
**Property**: `EquipmentSlots`  
**Type**: `TArray<FDAIEquipmentSlot>`  
**Category**: `Equipment`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Configuration for all equipment slots

**Property**: `bAutoCalculateStats`  
**Type**: `bool`  
**Category**: `Equipment`  
**Blueprint Access**: `Read/Write`  
**Default**: `true`  
**Purpose**: Whether to automatically calculate stat bonuses from equipment

#### Visual Settings
**Property**: `bUpdateVisualMesh`  
**Type**: `bool`  
**Category**: `Equipment`  
**Blueprint Access**: `Read/Write`  
**Default**: `true`  
**Purpose**: Whether to update character mesh based on equipped items

**Property**: `EquipmentMeshes`  
**Type**: `TMap<FName, USkeletalMeshComponent*>`  
**Category**: `Equipment`  
**Blueprint Access**: `Read Only`  
**Purpose**: Mesh components for each equipment slot

### DAIAttributeSet Properties

#### Core Attributes
**Property**: `Health`  
**Type**: `FGameplayAttributeData`  
**Category**: `Vital Attributes`  
**Replication**: `OnRep_Health`  
**Purpose**: Current health points

**Property**: `MaxHealth`  
**Type**: `FGameplayAttributeData`  
**Category**: `Vital Attributes`  
**Replication**: `OnRep_MaxHealth`  
**Purpose**: Maximum health capacity

**Property**: `Mana`  
**Type**: `FGameplayAttributeData`  
**Category**: `Vital Attributes`  
**Replication**: `OnRep_Mana`  
**Purpose**: Current mana/magic points

**Property**: `MaxMana`  
**Type**: `FGameplayAttributeData`  
**Category**: `Vital Attributes`  
**Replication**: `OnRep_MaxMana`  
**Purpose**: Maximum mana capacity

#### Combat Attributes
**Property**: `AttackPower`  
**Type**: `FGameplayAttributeData`  
**Category**: `Combat Attributes`  
**Replication**: `OnRep_AttackPower`  
**Purpose**: Base damage modifier for attacks

**Property**: `Defense`  
**Type**: `FGameplayAttributeData`  
**Category**: `Combat Attributes`  
**Replication**: `OnRep_Defense`  
**Purpose**: Damage reduction from attacks

**Property**: `CriticalChance`  
**Type**: `FGameplayAttributeData`  
**Category**: `Combat Attributes`  
**Replication**: `OnRep_CriticalChance`  
**Purpose**: Chance to deal critical damage (0-1)

**Property**: `CriticalMultiplier`  
**Type**: `FGameplayAttributeData`  
**Category**: `Combat Attributes`  
**Replication**: `OnRep_CriticalMultiplier`  
**Purpose**: Multiplier for critical damage

## Events and Delegates

### OnInventoryChanged
**Type**: `Dynamic Multicast Delegate`  
**Category**: `DAI|Inventory`  
**Purpose**: Fired when inventory contents change

**Parameters**:
- `ChangedItem` (UDAIItem): Item that was added/removed
- `ChangeType` (EDAIInventoryChangeType): Type of change (added, removed, moved)
- `NewQuantity` (int32): New quantity of the item

**Usage**: Update inventory UI and handle inventory-related logic.

### OnItemEquipped
**Type**: `Dynamic Multicast Delegate`  
**Category**: `DAI|Equipment`  
**Purpose**: Fired when an item is equipped

**Parameters**:
- `EquippedItem` (UDAIItem): Item that was equipped
- `SlotName` (FName): Equipment slot used
- `PreviousItem` (UDAIItem): Previously equipped item (if any)

**Usage**: Update character appearance, apply stat bonuses, and trigger equipment effects.

### OnLevelUp
**Type**: `Dynamic Multicast Delegate`  
**Category**: `DAI|Progression`  
**Purpose**: Fired when character gains a level

**Parameters**:
- `NewLevel` (int32): New character level
- `AttributePointsGained` (int32): Attribute points awarded
- `SkillPointsGained` (int32): Skill points awarded

**Usage**: Trigger level-up effects, unlock new content, and update progression UI.

### OnTradeCompleted
**Type**: `Dynamic Multicast Delegate`  
**Category**: `DAI|Trading`  
**Purpose**: Fired when a trade is successfully completed

**Parameters**:
- `TradePartner` (ADAICharacter): Other participant in the trade
- `ItemsReceived` (TArray<FDAIItemStack>): Items received from the trade
- `ItemsGiven` (TArray<FDAIItemStack>): Items given in the trade

**Usage**: Update trade statistics, trigger achievement progress, and handle post-trade logic.

## Developer Settings

Access via **Project Settings → Game → DAI**

### General Settings

#### Core System
**Property**: `bEnableDAISystem`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to enable the DAI framework globally

**Property**: `DefaultCharacterClass`  
**Type**: `TSubclassOf<ADAICharacter>`  
**Purpose**: Default character class to use for DAI integration

#### Inventory Settings
**Property**: `GlobalInventorySize`  
**Type**: `int32`  
**Default**: `30`  
**Range**: `10-200`  
**Purpose**: Default inventory size for new characters

**Property**: `bPersistInventory`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to automatically save inventory contents

### Progression Settings

#### Experience Configuration
**Property**: `BaseExperiencePerLevel`  
**Type**: `float`  
**Default**: `1000.0`  
**Range**: `100.0-10000.0`  
**Purpose**: Base experience required for first level

**Property**: `ExperienceScalingFactor`  
**Type**: `float`  
**Default**: `1.5`  
**Range**: `1.0-3.0`  
**Purpose**: Multiplier for experience requirements per level

**Property**: `MaxCharacterLevel`  
**Type**: `int32`  
**Default**: `100`  
**Range**: `10-1000`  
**Purpose**: Maximum achievable character level

#### Attribute Points
**Property**: `AttributePointsPerLevel`  
**Type**: `int32`  
**Default**: `2`  
**Range**: `0-10`  
**Purpose**: Attribute points awarded per level gained

**Property**: `StartingAttributePoints`  
**Type**: `int32`  
**Default**: `10`  
**Range**: `0-50`  
**Purpose**: Attribute points available at character creation

### Equipment Settings

#### Slot Configuration
**Property**: `DefaultEquipmentSlots`  
**Type**: `TArray<FDAIEquipmentSlot>`  
**Purpose**: Default equipment slots for all characters

**Property**: `bAllowDuplicateSlotTypes`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether multiple slots can accept the same item type

#### Visual Updates
**Property**: `bAutoUpdateEquipmentVisuals`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to automatically update character appearance with equipment

**Property**: `EquipmentUpdateDelay`  
**Type**: `float`  
**Default**: `0.1`  
**Range**: `0.0-2.0`  
**Purpose**: Delay before applying equipment visual updates

### Trading Settings

#### Trade Configuration
**Property**: `bEnablePlayerTrading`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether players can trade with each other

**Property**: `MaxTradeDistance`  
**Type**: `float`  
**Default**: `500.0`  
**Range**: `100.0-2000.0`  
**Purpose**: Maximum distance for initiating trades

**Property**: `TradeTimeoutSeconds`  
**Type**: `float`  
**Default**: `300.0`  
**Range**: `30.0-1800.0`  
**Purpose**: Time before trade sessions automatically expire

#### Economic Settings
**Property**: `bUseItemValues`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether items have economic values for trading

**Property**: `CurrencyItemClass`  
**Type**: `TSubclassOf<UDAIItem>`  
**Purpose**: Item class to use as primary currency

### Multiplayer Settings

#### Replication
**Property**: `bReplicateInventory`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to replicate inventory contents in multiplayer

**Property**: `InventoryReplicationRate`  
**Type**: `float`  
**Default**: `10.0`  
**Range**: `1.0-60.0`  
**Purpose**: Frequency of inventory replication updates

#### Authority
**Property**: `bServerAuthoritativeInventory`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether server has authority over inventory operations

### Debug Settings

#### Logging
**Property**: `bEnableDAILogging`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to enable detailed DAI system logging

**Property**: `LogLevel`  
**Type**: `EDAILogLevel`  
**Default**: `Warning`  
**Purpose**: Minimum log level for DAI messages

#### Visualization
**Property**: `bShowInventoryDebug`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to display inventory debug information

**Property**: `bShowAttributeDebug`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Whether to display attribute values on screen

## Usage Examples

### Character Setup and Initialization
```cpp
// Initialize DAI character with inventory and abilities
void ADAICharacter::BeginPlay()
{
    Super::BeginPlay();
    
    // Initialize inventory component
    if (InventoryComponent)
    {
        InventoryComponent->InitializeInventory(30); // 30 slots
        
        // Give starting items
        GiveStartingItems();
    }
    
    // Initialize ability system
    if (AbilitySystemComponent && IsLocallyControlled())
    {
        // Grant starting abilities
        for (TSubclassOf<UGameplayAbility> AbilityClass : StartingAbilities)
        {
            GrantAbility(AbilityClass, 1, GetNextAvailableInputID());
        }
        
        // Apply starting effects
        for (TSubclassOf<UGameplayEffect> EffectClass : StartingEffects)
        {
            ApplyGameplayEffect(EffectClass, 1.0f, this);
        }
    }
    
    // Set up attribute change delegates
    if (AttributeSet)
    {
        AttributeSet->OnHealthChanged.AddDynamic(this, &ADAICharacter::OnHealthChanged);
        AttributeSet->OnLevelChanged.AddDynamic(this, &ADAICharacter::OnCharacterLevelChanged);
    }
}

void ADAICharacter::GiveStartingItems()
{
    // Give basic weapon
    if (StartingWeaponClass)
    {
        UDAIItem* StartingWeapon = NewObject<UDAIItem>(this, StartingWeaponClass);
        AddItemToInventory(StartingWeapon, 1);
        EquipItem(StartingWeapon);
    }
    
    // Give healing potions
    if (HealthPotionClass)
    {
        UDAIItem* HealthPotion = NewObject<UDAIItem>(this, HealthPotionClass);
        AddItemToInventory(HealthPotion, 5);
    }
    
    // Give starting currency
    if (CurrencyClass)
    {
        UDAIItem* Currency = NewObject<UDAIItem>(this, CurrencyClass);
        AddItemToInventory(Currency, 100);
    }
}
```

### Combat System Implementation
```cpp
// Handle damage calculation with equipment bonuses
void ADAICharacter::TakeDamage(float DamageAmount, AActor* DamageDealer, TSubclassOf<UDamageType> DamageType)
{
    if (!IsAlive())
        return;
    
    // Calculate defense from equipment
    float DefenseValue = GetAttributeValue(UDAIAttributeSet::GetDefenseAttribute());
    
    // Apply equipment bonuses
    if (EquipmentComponent)
    {
        DefenseValue += EquipmentComponent->GetTotalDefenseBonus();
    }
    
    // Calculate damage reduction
    float DamageReduction = DefenseValue / (DefenseValue + 100.0f);
    float FinalDamage = DamageAmount * (1.0f - DamageReduction);
    
    // Apply damage through GAS
    if (AbilitySystemComponent)
    {
        FGameplayEffectSpecHandle DamageSpec = CreateDamageEffect(FinalDamage, DamageType);
        AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*DamageSpec.Data.Get());
    }
    
    // Trigger combat events
    OnDamageTaken.Broadcast(FinalDamage, DamageDealer);
    
    // Check for death
    if (GetAttributeValue(UDAIAttributeSet::GetHealthAttribute()) <= 0.0f)
    {
        HandleDeath(DamageDealer);
    }
}

// Experience gain and leveling
void ADAICharacter::HandleKill(AActor* KilledActor)
{
    if (ADAICharacter* KilledCharacter = Cast<ADAICharacter>(KilledActor))
    {
        // Calculate experience based on level difference
        int32 KilledLevel = KilledCharacter->GetCharacterLevel();
        int32 MyLevel = GetCharacterLevel();
        
        float BaseExperience = KilledLevel * 100.0f;
        float LevelDifference = KilledLevel - MyLevel;
        float ExperienceMultiplier = FMath::Clamp(1.0f + (LevelDifference * 0.1f), 0.1f, 2.0f);
        
        float ExperienceGained = BaseExperience * ExperienceMultiplier;
        GainExperience(ExperienceGained, FGameplayTag::RequestGameplayTag("Experience.Combat"));
    }
}

UFUNCTION()
void ADAICharacter::OnCharacterLevelChanged(int32 NewLevel, int32 PreviousLevel)
{
    // Award attribute points
    int32 AttributePointsGained = (NewLevel - PreviousLevel) * AttributePointsPerLevel;
    AvailableAttributePoints += AttributePointsGained;
    
    // Award skill points
    int32 SkillPointsGained = (NewLevel - PreviousLevel) * SkillPointsPerLevel;
    AvailableSkillPoints += SkillPointsGained;
    
    // Trigger level up event
    OnLevelUp.Broadcast(NewLevel, AttributePointsGained, SkillPointsGained);
    
    // Play level up effects
    PlayLevelUpEffects();
}
```

### Trading System Implementation
```cpp
// Player-to-player trading
void ADAICharacter::StartTradeWithPlayer(ADAICharacter* TradePartner)
{
    if (!TradePartner || IsTrading())
        return;
    
    // Check distance
    float Distance = FVector::Dist(GetActorLocation(), TradePartner->GetActorLocation());
    if (Distance > MaxTradeDistance)
    {
        NotifyPlayer("Trade partner is too far away");
        return;
    }
    
    // Initialize trade session
    CurrentTradeSession = NewObject<UDAITradeSession>(this);
    CurrentTradeSession->InitializeTrade(this, TradePartner);
    
    // Set up trade UI
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        ShowTradeInterface(PC, TradePartner);
    }
    
    // Notify trade partner
    TradePartner->ReceiveTradeRequest(this);
}

void ADAICharacter::AddItemToTradeOffer(UDAIItem* Item, int32 Quantity)
{
    if (!CurrentTradeSession || !Item)
        return;
    
    // Verify player owns the item
    if (!HasItem(Item, Quantity))
    {
        NotifyPlayer("You don't have enough of this item");
        return;
    }
    
    // Add to trade offer
    CurrentTradeSession->AddItemToOffer(this, Item, Quantity);
    
    // Update trade UI
    UpdateTradeInterface();
}

void ADAICharacter::AcceptCurrentTrade()
{
    if (!CurrentTradeSession)
        return;
    
    if (CurrentTradeSession->AcceptTrade(this))
    {
        // Trade was successful, execute item exchange
        ExecuteTradeExchange();
        CleanupTradeSession();
    }
}

void ADAICharacter::ExecuteTradeExchange()
{
    if (!CurrentTradeSession)
        return;
    
    // Get trade offers
    FDAITradeOffer MyOffer = CurrentTradeSession->GetPlayerOffer(this);
    FDAITradeOffer PartnerOffer = CurrentTradeSession->GetPartnerOffer(this);
    
    // Remove items being given away
    for (const FDAIItemStack& ItemStack : MyOffer.OfferedItems)
    {
        RemoveItemFromInventory(ItemStack.Item, ItemStack.Quantity);
    }
    
    // Add items being received
    for (const FDAIItemStack& ItemStack : PartnerOffer.OfferedItems)
    {
        AddItemToInventory(ItemStack.Item, ItemStack.Quantity);
    }
    
    // Handle currency exchange
    if (MyOffer.OfferedCurrency > 0)
    {
        ModifyCurrency(-MyOffer.OfferedCurrency);
    }
    if (PartnerOffer.OfferedCurrency > 0)
    {
        ModifyCurrency(PartnerOffer.OfferedCurrency);
    }
    
    // Trigger trade completion event
    OnTradeCompleted.Broadcast(
        CurrentTradeSession->GetTradePartner(this),
        PartnerOffer.OfferedItems,
        MyOffer.OfferedItems
    );
}
```

### Equipment and Stat Management
```cpp
// Handle equipment changes and stat recalculation
UFUNCTION()
void ADAICharacter::OnItemEquipped(UDAIItem* EquippedItem, FName SlotName, UDAIItem* PreviousItem)
{
    // Update visual mesh
    if (EquipmentComponent)
    {
        EquipmentComponent->UpdateEquipmentMesh(SlotName, EquippedItem);
    }
    
    // Recalculate stats
    RecalculateEquipmentStats();
    
    // Apply equipment abilities
    if (EquippedItem)
    {
        GrantEquipmentAbilities(EquippedItem);
    }
    
    // Remove previous equipment abilities
    if (PreviousItem)
    {
        RemoveEquipmentAbilities(PreviousItem);
    }
    
    // Update UI
    UpdateCharacterStatsUI();
}

void ADAICharacter::RecalculateEquipmentStats()
{
    if (!EquipmentComponent || !AbilitySystemComponent)
        return;
    
    // Remove previous equipment bonuses
    AbilitySystemComponent->RemoveActiveGameplayEffectBySourceEffect(
        EquipmentStatsBonusEffect,
        AbilitySystemComponent
    );
    
    // Calculate new bonuses from all equipped items
    FDAIItemStats TotalStats = EquipmentComponent->CalculateTotalStats();
    
    // Apply new equipment bonuses
    FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
    EffectContext.AddSourceObject(this);
    
    FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
        EquipmentStatsBonusEffect,
        1.0f,
        EffectContext
    );
    
    if (SpecHandle.IsValid())
    {
        // Set magnitude for each stat bonus
        for (const auto& StatPair : TotalStats.AttributeModifiers)
        {
            SpecHandle.Data->SetSetByCallerMagnitude(
                FGameplayTag::RequestGameplayTag("SetByCaller." + StatPair.Key.AttributeName),
                StatPair.Value
            );
        }
        
        AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
    }
}

// Item usage and consumption
void ADAICharacter::UseItem(UDAIItem* Item)
{
    if (!Item || !HasItem(Item))
        return;
    
    // Check if item can be used
    if (!Item->CanBeUsed(this))
    {
        NotifyPlayer("Cannot use this item right now");
        return;
    }
    
    // Apply item effects
    Item->UseItem(this);
    
    // Consume item if it's consumable
    if (Item->IsConsumable())
    {
        RemoveItemFromInventory(Item, 1);
    }
    
    // Trigger item usage events
    OnItemUsed.Broadcast(Item);
}
```

## Integration with Other DAI Plugins

### DAI_Save Integration
- **Character Persistence**: Complete character data including inventory, equipment, and progression
- **Save Fragments**: Modular save system for different character components
- **Load Restoration**: Proper restoration of character state on game load

### DAI_Hub Integration
- **Service Registration**: DAI system registers with hub for discovery by other plugins
- **Event Coordination**: Character events published through hub system
- **Performance Budgeting**: Character operations respect hub performance management

### DAI_AI Integration
- **AI Characters**: AI can use DAI character system for inventory and abilities
- **NPC Trading**: AI merchants use DAI trading system
- **Combat Integration**: AI characters participate in DAI combat system

### DAI_QuestManager Integration
- **Item Rewards**: Quest completion can grant items through DAI system
- **Inventory Requirements**: Quest objectives can check DAI inventory contents
- **Character Progression**: Quest rewards can include experience and levels

## Best Practices

### Inventory Management
1. **Design logical item categories** and organization systems
2. **Implement stack limits** appropriate for item types
3. **Provide sorting and filtering** options for large inventories
4. **Test inventory UI** with various screen resolutions
5. **Handle edge cases** like full inventories gracefully

### Equipment System
1. **Design clear equipment slot hierarchies** and restrictions
2. **Balance stat bonuses** to avoid overpowered combinations
3. **Provide visual feedback** for equipment changes
4. **Test equipment** with various character models and animations
5. **Consider equipment sets** and synergy bonuses

### Character Progression
1. **Balance experience curves** for engaging progression
2. **Provide meaningful choices** in attribute allocation
3. **Design level-appropriate** content and challenges
4. **Test progression** across the full level range
5. **Consider alternative progression** systems beyond levels

### Performance Optimization
1. **Use object pooling** for frequently created items
2. **Optimize replication** of inventory and equipment data
3. **Cache calculated values** like total equipment stats
4. **Profile inventory operations** for performance bottlenecks
5. **Implement efficient UI updates** for inventory changes

### Multiplayer Considerations
1. **Design secure server authority** for critical operations
2. **Handle network prediction** for responsive UI
3. **Synchronize trading** properly across all clients
4. **Test with various network conditions** and latency
5. **Implement proper validation** to prevent cheating

## Technical Notes

- **Thread Safety**: All operations designed for game thread usage
- **Memory Management**: Efficient item creation and cleanup systems
- **Platform Support**: Cross-platform character data with platform-specific optimizations
- **Save Compatibility**: Forward-compatible save data structures
- **Network Architecture**: Optimized replication for multiplayer scalability

---

*This is the foundational plugin for the entire DAI ecosystem. For information about other DAI plugins, see their respective documentation files.*  
*For GAS integration details, consult the Unreal Engine 5.5 Gameplay Ability System documentation.*  
*For multiplayer implementation, see the Unreal Engine networking documentation.*

---

Last updated: October 6, 2025