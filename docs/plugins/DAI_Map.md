# DAI_Map Plugin Documentation

## Overview

**DAI_Map** is a comprehensive mapping and minimap system for Unreal Engine 5.5. It provides Point of Interest (POI) management, fog of war, route planning, and fast travel functionality. The system is designed to be flexible and integrates seamlessly with other DAI plugins for a complete mapping solution.

### Key Features
- 🗺️ **POI Management**: Register, update, and track points of interest
- 🌫️ **Fog of War**: Dynamic fog revelation system
- 🧭 **Route Planning**: Pathfinding and navigation integration
- ⚡ **Fast Travel**: Location-based teleportation system
- 🔗 **Quest Integration**: Automatic quest marker bridging
- 📍 **Map Icons**: Component-based icon system for actors

## Architecture

The DAI_Map system consists of:
- **DAIMapServiceSubsystem**: Core map functionality
- **DAIMapIconComponent**: Automatic icon registration for actors
- **POI System**: Centralized point of interest management
- **Fog System**: Dynamic fog revelation
- **Transform System**: World-to-map coordinate conversion

## Core Components

### DAIMapServiceSubsystem
*Main subsystem providing all map functionality*

**Type**: `World Subsystem`  
**Blueprint Category**: `DAI|Map`

### DAIMapIconComponent
*Component for automatic actor icon registration*

**Type**: `Actor Component`  
**Blueprint Spawnable**: `Yes`  
**File**: `Components/DAIMapIconComponent.h`

## Blueprint Functions

### POI Management

#### RegisterPOI
**Type**: `BlueprintCallable`  
**Category**: `DAI|Map`  
**Returns**: `bool`  
**Purpose**: Register a new Point of Interest on the map

**Parameters**:
- `Desc` (FDAIPOIDesc): POI description and configuration
- `OutHandle` (FDAIPOIHandle): Unique handle for this POI

```cpp
bool RegisterPOI(UObject* WorldContextObject, const FDAIPOIDesc& Desc, FDAIPOIHandle& OutHandle);
```

**Usage**: Creates a new POI that will appear on the map. Returns true if registration succeeded.

#### UpdatePOI
**Type**: `BlueprintCallable`  
**Category**: `DAI|Map`  
**Returns**: `bool`  
**Purpose**: Update an existing POI's properties

**Parameters**:
- `Handle` (FDAIPOIHandle): Handle of POI to update
- `NewDesc` (FDAIPOIDesc): Updated POI description

```cpp
bool UpdatePOI(UObject* WorldContextObject, const FDAIPOIHandle& Handle, const FDAIPOIDesc& NewDesc);
```

**Usage**: Modify a previously registered POI. Useful for dynamic markers or quest updates.

#### UnregisterPOI
**Type**: `BlueprintCallable`  
**Category**: `DAI|Map`  
**Returns**: `bool`  
**Purpose**: Remove a POI from the map

**Parameters**:
- `Handle` (FDAIPOIHandle): Handle of POI to remove

```cpp
bool UnregisterPOI(UObject* WorldContextObject, const FDAIPOIHandle& Handle);
```

**Usage**: Permanently removes a POI from the map system.

### Navigation and Routing

#### GetRoute
**Type**: `BlueprintCallable`  
**Category**: `DAI|Map`  
**Returns**: `bool`  
**Purpose**: Calculate a navigation route between two points

**Parameters**:
- `Request` (FDAIPathRequest): Route calculation request
- `OutPath` (FDAIPathPoly): Calculated route points

```cpp
bool GetRoute(UObject* WorldContextObject, const FDAIPathRequest& Request, FDAIPathPoly& OutPath);
```

**Usage**: Generates a pathfinding route for display on maps or AI navigation.

### Transform System

#### GetMapTransform
**Type**: `BlueprintPure`  
**Category**: `DAI|Map`  
**Returns**: `FDAIMapTransform`  
**Purpose**: Get the world-to-map coordinate transformation

**Parameters**:
- `bValid` (bool): Whether the transform is valid

```cpp
FDAIMapTransform GetMapTransform(UObject* WorldContextObject, bool& bValid);
```

**Usage**: Convert between world coordinates and map coordinates for UI display.

## Blueprint Data Types

### FDAIPOIDesc (POI Description)
**Type**: `BlueprintType Struct`  
**Purpose**: Complete description of a Point of Interest

**Properties**:
- `Id` (FName): Unique identifier for this POI
- `DisplayName` (FText): Human-readable name displayed in UI
- `Tags` (FGameplayTagContainer): Gameplay tags for filtering and categorization
- `WorldLocation` (FVector): 3D world position of the POI
- `Icon` (TSoftObjectPtr<UTexture2D>): Texture to display for this POI
- `Visibility` (EDAIPOIVisibility): When this POI should be visible
- `bIsFastTravelPoint` (bool): Whether this POI can be used for fast travel

### FDAIPOIHandle (POI Handle)
**Type**: `BlueprintType Struct`  
**Purpose**: Unique reference to a registered POI

**Properties**:
- `Id` (FGuid): Unique identifier handle

### EDAIPOIVisibility (POI Visibility)
**Type**: `BlueprintType Enum`  
**Purpose**: Controls when a POI is visible to players

**Values**:
- `Always`: POI is always visible
- `WhenDiscovered`: POI only visible after being discovered
- `WhenNearby`: POI only visible when player is close
- `Hidden`: POI is hidden from players

### FDAIPathRequest (Path Request)
**Type**: `BlueprintType Struct`  
**Purpose**: Request parameters for route calculation

**Properties**:
- `Source` (FVector): Starting point for the route
- `Target` (FVector): Destination point for the route
- `RefreshPolicy` (EDAIPathRefreshPolicy): When to recalculate the path

### FDAIPathPoly (Path Polygon)
**Type**: `BlueprintType Struct`  
**Purpose**: Calculated route as a series of 2D points

**Properties**:
- `Points` (TArray<FVector2D>): Array of 2D map coordinates forming the route

### EDAIPathRefreshPolicy (Path Refresh Policy)
**Type**: `BlueprintType Enum`  
**Purpose**: Controls when paths should be recalculated

**Values**:
- `Never`: Never recalculate the path
- `OnChange`: Recalculate when conditions change
- `Always`: Always recalculate when requested

## DAIMapIconComponent Properties

### Icon Display
**Property**: `Icon`  
**Type**: `UTexture2D*`  
**Category**: `Map`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Texture used for the map icon

### Icon Size
**Property**: `Size`  
**Type**: `FVector2D`  
**Category**: `Map`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Size of the icon in pixels

### Icon Pivot
**Property**: `Pivot`  
**Type**: `FVector2D`  
**Category**: `Map`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Pivot point within the icon texture (0,0 = top-left, 1,1 = bottom-right)

### Draw Order
**Property**: `ZOrder`  
**Type**: `int32`  
**Category**: `Map`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Drawing priority relative to other icons (higher values draw on top)

### Filtering Tags
**Property**: `Tags`  
**Type**: `FGameplayTagContainer`  
**Category**: `Map`  
**Blueprint Access**: `Read/Write`  
**Purpose**: Gameplay tags for filtering and categorization

## Developer Settings

Access via **Project Settings → Game → DAI Map**

### Event Settings

#### Publish POI Events
**Property**: `bPublishPOIEvents`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Whether to publish hub events when POIs are registered/updated/unregistered

Enables other systems to react to POI changes through the DAI_Hub event system.

### Integration Settings

#### Quest Marker Bridge
**Property**: `bEnableQuestMarkerBridge`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Automatically mirror quest markers into map POIs

When enabled, quest markers from the DAI_QuestManager are automatically displayed as map POIs.

#### Quest Marker Tag
**Property**: `QuestMarkerTag`  
**Type**: `FName`  
**Default**: `Quest.Marker`  
**Purpose**: Tag assigned to automatically created quest marker POIs

### Fast Travel Settings

#### Fast Travel Region Tag Prefix
**Property**: `FastTravelRegionTagPrefix`  
**Type**: `FString`  
**Default**: `Region.FastTravel.`  
**Purpose**: Prefix used for fast travel region gameplay tags

Example: `Region.FastTravel.Town` or `Region.FastTravel.Dungeon.Level1`

### Fog of War Settings

#### Enable Radius Reveal
**Property**: `bEnableRadiusRevealTick`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Enable periodic radius reveal around players

When enabled, fog of war is automatically revealed around player characters.

#### Reveal Update Interval
**Property**: `RadiusRevealTickInterval`  
**Type**: `float`  
**Default**: `1.0`  
**Range**: `0.1+`  
**Purpose**: Seconds between fog radius reveal updates

Lower values provide smoother fog revelation but impact performance.

#### Fog Section Size
**Property**: `FogSectionWorldSize`  
**Type**: `float`  
**Default**: `1000.0`  
**Range**: `100+`  
**Purpose**: World size of a single fog cell in units

Larger values mean fewer fog cells but less detailed fog revelation.

#### Coalesced Section Broadcast Interval (Runtime CVar)
**CVar**: `dai.map.CoalesceInterval`  
**Type**: `float` (seconds)  
**Default**: `0.25`  
**Minimum**: `0.05` (values lower than this are clamped)  
**Purpose**: Controls how often buffered fog-of-war section IDs are flushed and broadcast using the `OnSectionsRevealed` delegate.

When sections are revealed rapidly (radius reveal ticking, scripted mass reveal, batch calls) they're accumulated in an internal buffer (`PendingRevealedSections`). A timer triggers `FlushPendingSections()` at this interval to emit a single consolidated delegate broadcast instead of many small ones.

Benefits:
* Reduces delegate spam and UI redraw overhead under heavy exploration
* Produces smoother progress bars / minimap updates
* Lowers log noise unless verbose section logging is explicitly enabled

Recommendations:
* Keep at 0.25 for typical gameplay.
* Increase (0.5 - 1.0) for very large open worlds with constant movement.
* Decrease (0.1) only if highly responsive fog updates are required and performance budget allows.

Hot Retiming: The subsystem now watches this CVar each flush cycle; changes take effect automatically (timer is reset) without needing to reinitialize the world.

#### Coalesced Broadcast Enable (Runtime CVar)
**CVar**: `dai.map.CoalesceEnabled`  
**Type**: `int32` (0/1)  
**Default**: `1`  
**Purpose**: Enables (1) or disables (0) batching of revealed fog sections. When disabled, each section reveal immediately triggers `OnSectionsRevealed` with a single-element array.

Use Cases:
* Disable during profiling to see raw reveal frequency
* Disable for debugging UI update logic that expects per-section updates
* Enable in production for performance and reduced event noise

Blueprint Parity: You can also toggle via `SetCoalescingEnabled(bool)` on the `DAIMapServiceSubsystem` and query with `IsCoalescingEnabled()`.

#### Fog Revelation Console Commands

| Command | Description |
|---------|-------------|
| `Map.FlushFog` | Immediately flush any buffered section IDs and broadcast them (no effect if buffer empty). |
| `Map.RevealRadius <Meters>` | One-shot reveal of all fog sections within the given radius of the first player pawn. Does not enable continuous ticking. |

These commands are intended for QA, debugging minimap refresh, and rapid world exploration during development.

### Transform Settings

#### Map Origin
**Property**: `MapOrigin`  
**Type**: `FVector2D`  
**Default**: `(0, 0)`  
**Purpose**: World-space origin used as map coordinate (0,0)

Set this to the center or corner of your game world for proper map alignment.

#### World Units Per Map Unit
**Property**: `WorldUnitsPerMapUnit`  
**Type**: `float`  
**Default**: `100.0`  
**Range**: `1+`  
**Purpose**: Scale factor for converting map units to world units

Higher values make the map represent a larger world area per pixel.

### Debug Settings

#### Debug POI Logging
**Property**: `bDebugLogPOI`  
**Type**: `bool`  
**Default**: `false`  
**Purpose**: Enable verbose logging for POI operations

When enabled, logs all POI registration, updates, and unregistration events.

### Routing Settings

#### Simple Routing
**Property**: `bEnableSimpleRouting`  
**Type**: `bool`  
**Default**: `true`  
**Purpose**: Use simplified navigation for GetRoute queries

Enables faster but less precise pathfinding for map display purposes.

## Usage Examples

### Basic POI Registration
```blueprint
// Create POI description
FDAIPOIDesc POIDesc;
POIDesc.Id = "TownCenter";
POIDesc.DisplayName = "Town Center";
POIDesc.WorldLocation = GetActorLocation();
POIDesc.Icon = TownCenterIcon; // Set in Blueprint
POIDesc.Visibility = EDAIPOIVisibility::Always;
POIDesc.bIsFastTravelPoint = true;

// Add tags for filtering
POIDesc.Tags.AddTag("Location.Town");
POIDesc.Tags.AddTag("Services.Merchant");

// Register the POI
FDAIPOIHandle Handle;
if (RegisterPOI(this, POIDesc, Handle))
{
    // Store handle for later updates/removal
    StoredPOIHandle = Handle;
}
```

### Dynamic POI Updates
```blueprint
// Update POI when quest status changes
FDAIPOIDesc UpdatedDesc = OriginalDesc;
UpdatedDesc.DisplayName = "Town Center (Quest Complete)";
UpdatedDesc.Tags.AddTag("Quest.Completed");

UpdatePOI(this, StoredPOIHandle, UpdatedDesc);
```

### Route Calculation
```blueprint
// Calculate route from player to target
FDAIPathRequest Request;
Request.Source = GetPlayerLocation();
Request.Target = TargetLocation;
Request.RefreshPolicy = EDAIPathRefreshPolicy::OnChange;

FDAIPathPoly CalculatedPath;
if (GetRoute(this, Request, CalculatedPath))
{
    // Use CalculatedPath.Points for map display
    DisplayRouteOnMap(CalculatedPath.Points);
}
```

### Map Icon Component Setup
```blueprint
// Add to actor in Construction Script
UDAIMapIconComponent* MapIcon = CreateDefaultSubobject<UDAIMapIconComponent>("MapIcon");
MapIcon->Icon = MyIconTexture;
MapIcon->Size = FVector2D(32, 32);
MapIcon->Pivot = FVector2D(0.5, 0.5); // Center pivot
MapIcon->ZOrder = 100;
MapIcon->Tags.AddTag("NPC.Merchant");
```

## Integration with Other Plugins

### DAI_Hub Integration
- **Event Publishing**: POI changes trigger hub events when enabled
- **Service Discovery**: Map service registers with hub for other plugins

### DAI_QuestManager Integration
- **Automatic Bridging**: Quest markers automatically appear as POIs
- **Quest Tags**: Quest-related POIs get appropriate gameplay tags

### DAI_Navigation Integration (formerly DAI__Navigation)
- **Route Calculation**: Uses navigation system for pathfinding
- **Smart Objects**: Can display smart object locations as POIs

## Best Practices

### POI Management
1. **Use meaningful IDs** for POIs to avoid conflicts
2. **Include appropriate tags** for filtering and searching
3. **Set proper visibility** based on game design needs
4. **Store handles** for POIs you need to update or remove

### Performance Optimization
1. **Limit POI count** in visible areas to maintain performance
2. **Use appropriate fog section sizes** for your world scale
3. **Disable radius reveal** if not needed for your game
4. **Batch POI operations** when possible

### Map Coordinate System
1. **Set map origin** to a logical world center point
2. **Choose appropriate scale** for your world size
3. **Test coordinate conversion** with known world positions
4. **Document your coordinate system** for team members

### Icon Design
1. **Use consistent icon sizes** for similar POI types
2. **Design icons** for visibility at small sizes
3. **Use appropriate Z-order** to prevent important icons from being hidden
4. **Test icon visibility** on different map backgrounds

## Technical Notes

- **Thread Safety**: Map operations are designed for game thread usage
- **Memory Management**: POIs are efficiently stored with spatial indexing
- **Networking**: POI state is local to each client by default
- **Performance**: Fog system uses optimized cell-based storage
- **Persistence**: POI discovery state can be saved through DAI_Save integration

---

*For more information about quest integration, see [DAI_QuestManager documentation](DAI_QuestManager.md).*  
*For navigation details, see [DAI_Navigation documentation](DAI_Navigation.md).* 

---

Last updated: October 6, 2025