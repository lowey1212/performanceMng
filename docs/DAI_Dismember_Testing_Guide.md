# Testing DAI_Dismember Mutable Integration

## Menu Location
**Tools > DAI Dismember > Combine Materials Directly (Mutable Service)**

## What Changed

The "Combine Materials Directly" menu option now uses the Mutable-integrated service instead of simple `SetMaterial` calls.

### Before (Old Implementation)
```
LogDAIDismemberEditor: Display: DAI Dismember Direct: Applied single material to 1 skeletal mesh slots for BP_Placeable_Greystone_Chest_C_1
```

### After (New Implementation)
You should now see these logs with the Mutable service integration:

```
LogDAIDismemberEditor: Display: DAI Dismember Direct: Processing actor BP_Placeable_Greystone_Chest_C_1 with Mutable service
LogTemp: Log: DAI_DefaultMutableCombinerService: Attempting to combine materials for BP_Placeable_Greystone_Chest_C_1
LogTemp: Log: DAI_DefaultMutableCombinerService: Combining 1 materials on skeletal mesh
LogTemp: Log: DAI_DefaultMutableCombinerService: Successfully merged 1 materials into single material
LogDAIDismemberEditor: Display: DAI Dismember Direct: Successfully combined materials for BP_Placeable_Greystone_Chest_C_1
```

## Expected Behavior

When you select actors and run "Combine Materials Directly":

1. **Creates Service Instance**: `UDAI_DefaultMutableCombinerService` is instantiated
2. **Checks Mutable Availability**: Verifies if `UCustomizableObjectSystem` is available
3. **Processes Each Actor**:
   - Finds skeletal or static mesh components
   - Creates `UMaterialInstanceDynamic` from first material
   - Merges parameters from all material slots
   - Applies merged material to all slots
4. **Comprehensive Logging**: Shows each step of the process

## Testing Steps

1. Open the level in UE5 editor
2. Select one or more actors with mesh components (e.g., `BP_Placeable_Greystone_Chest_C_1`)
3. Go to **Tools > DAI Dismember > Combine Materials Directly (Mutable Service)**
4. Check the **Output Log** for detailed messages

## Log Messages to Expect

### Success Case (Actor with Mesh)
```
LogDAIDismemberEditor: Display: DAI Dismember Direct: Processing actor [ActorName] with Mutable service
LogTemp: Log: DAI_DefaultMutableCombinerService: Attempting to combine materials for [ActorName]
LogTemp: Log: DAI_DefaultMutableCombinerService: Combining [N] materials on skeletal mesh
LogTemp: Log: DAI_DefaultMutableCombinerService: Successfully merged [N] materials into single material
LogDAIDismemberEditor: Display: DAI Dismember Direct: Successfully combined materials for [ActorName]
LogDAIDismemberEditor: Display: DAI Dismember Direct: Processed=1 Skipped=0
```

### If Mutable System Not Available
```
LogTemp: Warning: DAI_DefaultMutableCombinerService: Mutable system not available, using fallback material merge
```
(Still works, but uses simpler material merging)

### Failure Case (No Mesh Component)
```
LogDAIDismemberEditor: Display: DAI Dismember Direct: Processing actor [ActorName] with Mutable service
LogTemp: Warning: DAI_DefaultMutableCombinerService: No valid mesh component found on [ActorName]
LogDAIDismemberEditor: Warning: DAI Dismember Direct: Failed to combine materials for [ActorName]
LogDAIDismemberEditor: Display: DAI Dismember Direct: Processed=0 Skipped=1
```

## What's Different from Old Implementation

| Old Implementation | New Mutable-Integrated Implementation |
|-------------------|--------------------------------------|
| Simple `SetMaterial(i, Mat)` loop | Creates `UMaterialInstanceDynamic` |
| Uses first material slot directly | Merges parameters from all materials |
| No Mutable integration | Checks `UCustomizableObjectSystem` availability |
| Minimal logging | Comprehensive logging at every step |
| No parameter merging | Attempts to merge material parameters |

## Troubleshooting

### "Failed to create Mutable combiner service"
- **Cause**: Memory allocation failure (very rare)
- **Solution**: Restart editor

### "No valid mesh component found"
- **Cause**: Selected actor has no SkeletalMeshComponent or StaticMeshComponent
- **Solution**: Select actors with mesh components

### "No base material available"
- **Cause**: Mesh component has no materials in slot 0
- **Solution**: Ensure mesh has at least one material

## Related Files

- `DAI_DefaultMutableCombinerService.cpp` - Service implementation
- `DAI_DismemberEditor.cpp` - Editor menu integration
- `docs/DAI_Dismember_Mutable_Integration.md` - Full documentation

## Build Info

**Build Date**: November 1, 2024  
**Build Status**: ✅ PASSED  
**Modules Updated**: DAI_Dismember, DAI_DismemberEditor
