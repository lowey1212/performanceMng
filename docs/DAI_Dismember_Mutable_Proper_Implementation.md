# DAI_Dismember Proper Mutable Integration Plan

## Current State Analysis

### ❌ What's Missing

The current DAI_Dismember implementation does **NOT** use Mutable for actual dismemberment. It only uses Mutable for **material combining**, which is NOT the same as limb severing.

**Current Issues**:
1. `CombineAllMeshesToSingleMaterialUsingMutable()` - Only combines materials, NOT meshes
2. No use of Mutable CustomizableObject for mesh generation
3. No ClipMorphPlane/ClipMeshWithPlane usage for cutting limbs
4. No duplicate instance generation (main body + severed limb)
5. Severed limbs are not spawned using Mutable-generated meshes

### ✅ What Should Happen

According to Mutable best practices and the user's requirements:

1. **Combine Character Meshes**: Multiple skeletal components (body, armor, clothing) → ONE Mutable CustomizableObject
2. **Runtime Clipping**: Use ClipMorph or ClipPlane to hide/remove limb from main character
3. **Duplicate Generation**: Create second instance showing ONLY the severed limb
4. **Spawn Physics Actor**: Severed limb becomes pooled physics actor
5. **Performance**: Single draw call for main character, optimized severed parts

## Mutable Workflow for Dismemberment

### Phase 1: Editor Setup (CustomizableObject)

**Location**: Content browser (requires Mutable plugin)

1. **Create CustomizableObject Asset**
   - Combine all character mesh components
   - Set up material merging/atlasing
   - Define morph targets or clipping planes per limb

2. **Configure Limb Clipping Nodes**
   ```
   [Body Mesh] → [ClipMeshWithPlane: RightArm] → [Output]
                 └─ Plane Position Parameter (runtime)
                 └─ Enable/Disable Parameter (runtime)
   ```

3. **Set Up States**
   - State: "Intact" - All limbs visible
   - State: "RightArmSevered" - Right arm hidden via ClipMorph
   - State: "LeftLegSevered" - Left leg hidden
   - etc.

### Phase 2: Runtime C++ Implementation

**File**: `DAI_DefaultMutableCombinerService.cpp`

#### A. Character Mesh Combination

```cpp
bool CombineActorMeshesToSingleMutable(AActor* Actor)
{
    // 1. Find all skeletal mesh components on actor
    TArray<USkeletalMeshComponent*> MeshComponents;
    Actor->GetComponents<USkeletalMeshComponent>(MeshComponents);
    
    // 2. Load CustomizableObject asset (configured in settings)
    UCustomizableObject* CO = LoadObject<UCustomizableObject>(
        nullptr, 
        TEXT("/Game/Characters/CharacterCustomizable.CharacterCustomizable")
    );
    
    // 3. Create CustomizableObjectInstance
    UCustomizableObjectInstance* Instance = NewObject<UCustomizableObjectInstance>();
    Instance->SetObject(CO);
    
    // 4. Set instance state to "Intact"
    Instance->SetCurrentState("Intact");
    
    // 5. Configure parameters (textures, colors from original meshes)
    for (USkeletalMeshComponent* MeshComp : MeshComponents)
    {
        // Copy material parameters to CustomizableObject
        TransferMaterialParameters(MeshComp, Instance);
    }
    
    // 6. Generate merged mesh asynchronously
    Instance->UpdateSkeletalMeshAsync(true, true);
    
    // 7. Replace actor's components with new merged mesh
    // ...
    
    return true;
}
```

#### B. Limb Severing with ClipMorph

```cpp
bool SeverLimbUsingMutable(AActor* Actor, FName LimbID)
{
    // 1. Get the CustomizableObjectInstance from actor
    UCustomizableObjectInstance* MainInstance = GetCustomizableInstance(Actor);
    
    // 2. Switch to "Severed" state for this limb
    FString StateName = FString::Printf(TEXT("%sSevered"), *LimbID.ToString());
    MainInstance->SetCurrentState(StateName);
    
    // 3. Set ClipMorph parameters
    // This HIDES the limb on the main character
    MainInstance->SetFloatParameterSelectedOption(
        FString::Printf(TEXT("%s_ClipEnable"), *LimbID.ToString()), 
        1.0f  // Enable clipping
    );
    
    // 4. Update main character mesh (async)
    MainInstance->UpdateSkeletalMeshAsync(true, true);
    
    // 5. Create SECOND instance for the SEVERED LIMB ONLY
    SpawnSeveredLimbActor(Actor, LimbID, MainInstance);
    
    return true;
}
```

#### C. Spawning Severed Limb

```cpp
AActor* SpawnSeveredLimbActor(AActor* OwnerActor, FName LimbID, UCustomizableObjectInstance* SourceInstance)
{
    // 1. Get pool or create new actor
    AActor* SeveredActor = GetFromPool(LimbID);
    
    // 2. Create SECOND CustomizableObjectInstance
    UCustomizableObjectInstance* LimbInstance = DuplicateObject<UCustomizableObjectInstance>(
        SourceInstance, 
        SeveredActor
    );
    
    // 3. Switch to INVERSE state - show ONLY this limb
    FString StateName = FString::Printf(TEXT("%sOnly"), *LimbID.ToString());
    LimbInstance->SetCurrentState(StateName);
    
    // 4. Set position at sever point
    FVector SeverLocation = GetLimbSocket(OwnerActor, LimbID)->GetComponentLocation();
    SeveredActor->SetActorLocation(SeverLocation);
    
    // 5. Update mesh (async)
    LimbInstance->UpdateSkeletalMeshAsync(true, true);
    
    // 6. Enable physics
    USkeletalMeshComponent* LimbMesh = SeveredActor->FindComponentByClass<USkeletalMeshComponent>();
    LimbMesh->SetSimulatePhysics(true);
    LimbMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    
    // 7. Apply impulse (flying limb effect)
    FVector ImpulseDirection = (SeverLocation - OwnerActor->GetActorLocation()).GetSafeNormal();
    LimbMesh->AddImpulse(ImpulseDirection * 1000.0f, NAME_None, true);
    
    return SeveredActor;
}
```

### Phase 3: CustomizableObject Setup Requirements

**In Mutable Editor**:

1. **Import All Meshes**
   - Base body
   - Armor pieces
   - Clothing
   - Each should have proper bone hierarchy

2. **Set Up Material Nodes**
   - Texture atlas generation
   - Material parameter merging
   - UV remapping

3. **Create ClipMorph Nodes Per Limb**
   ```
   Right Arm Clip:
   - Morph Target: "Hide_RightArm"
   - Enable Parameter: "RightArm_Severed" (bool)
   
   Left Leg Clip:
   - Morph Target: "Hide_LeftLeg"
   - Enable Parameter: "LeftLeg_Severed" (bool)
   ```

4. **Define States**
   - **Intact**: All limbs visible, all ClipMorph disabled
   - **RightArmSevered**: RightArm_Severed = true
   - **RightArmOnly**: All OTHER limbs clipped, only right arm visible

### Phase 4: Service Interface Update

**File**: `DAI_MutableCombinerService.h`

```cpp
UINTERFACE(BlueprintType)
class DAI_DISMEMBER_API UDAI_MutableCombinerService : public UInterface
{
    GENERATED_BODY()
};

class DAI_DISMEMBER_API IDAI_MutableCombinerService
{
    GENERATED_BODY()

public:
    // Updated interface for proper dismemberment
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DAI|Dismember|Mutable")
    bool InitializeActorWithMutable(AActor* Actor);
    
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DAI|Dismember|Mutable")
    bool SeverLimbWithMutable(AActor* Actor, FName LimbID, FVector SeverLocation);
    
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DAI|Dismember|Mutable")
    AActor* SpawnSeveredLimbFromMutable(AActor* SourceActor, FName LimbID, FVector SpawnLocation);
    
    // Keep old method for backwards compatibility
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DAI|Dismember|Mutable")
    bool CombineActorToSingleMesh(AActor* Actor, UMaterialInterface* SingleMaterialOverride, float Priority);
};
```

## Implementation Steps

### Step 1: Create Mutable Asset Structure
- [ ] Set up CustomizableObject in Content browser
- [ ] Import all character meshes
- [ ] Configure ClipMorph nodes for each limb
- [ ] Define States (Intact, per-limb severed, per-limb only)
- [ ] Test in Mutable Preview

### Step 2: Update Service Interface
- [ ] Add `InitializeActorWithMutable()`
- [ ] Add `SeverLimbWithMutable()`
- [ ] Add `SpawnSeveredLimbFromMutable()`
- [ ] Keep backwards compatibility

### Step 3: Implement DefaultMutableCombinerService
- [ ] Character initialization with CustomizableObject
- [ ] Limb hiding via State switching
- [ ] Severed limb spawning with inverse State
- [ ] Physics and impulse application
- [ ] Pool management for severed limbs

### Step 4: Integrate with Subsystem
- [ ] Update `UDAI_DismemberSubsystem::SeverLimb()`
- [ ] Call Mutable service for actual mesh generation
- [ ] Handle async mesh generation callbacks
- [ ] Spawn severed limb actors

### Step 5: Testing
- [ ] Test single limb sever
- [ ] Test multiple limb severs
- [ ] Test severed limb physics
- [ ] Test pool reuse
- [ ] Performance profiling

## Example CustomizableObject Graph

```
[Character Base Mesh]
    ↓
[Material Combiner]
    ↓
[ClipMeshWithMorph: RightArm]  ← Boolean Param: "Hide_RightArm"
    ↓
[ClipMeshWithMorph: LeftArm]   ← Boolean Param: "Hide_LeftArm"
    ↓
[ClipMeshWithMorph: RightLeg]  ← Boolean Param: "Hide_RightLeg"
    ↓
[ClipMeshWithMorph: LeftLeg]   ← Boolean Param: "Hide_LeftLeg"
    ↓
[ClipMeshWithMorph: Head]      ← Boolean Param: "Hide_Head"
    ↓
[Output Mesh]
```

**States**:
- **Intact**: All Hide_* = false
- **RightArmSevered**: Hide_RightArm = true
- **RightArmOnly**: Hide_LeftArm, Hide_RightLeg, Hide_LeftLeg, Hide_Head = true

## Configuration Settings

**File**: `DAI_DismemberDeveloperSettings.h`

Add these settings:

```cpp
UPROPERTY(EditDefaultsOnly, Config, Category = "Mutable")
TSoftObjectPtr<UCustomizableObject> CharacterCustomizableObject;

UPROPERTY(EditDefaultsOnly, Config, Category = "Mutable")
TMap<FName, FString> LimbToMorphTargetMap;  // "RightArm" → "Hide_RightArm"

UPROPERTY(EditDefaultsOnly, Config, Category = "Mutable")
TMap<FName, FString> LimbToStateMap;  // "RightArm" → "RightArmSevered"

UPROPERTY(EditDefaultsOnly, Config, Category = "Mutable")
bool bUseProperMutableDismemberment = true;
```

## Resources

### Mutable Documentation
- **Tutorial**: "Mutable: Remove Unseen Mesh Parts"
- **File**: `mutable docs/community-learning-tutorials-DPO8-unreal-engine-h-1759330916305.html`
- **Key Nodes**: ClipMeshWithPlane, ClipMeshWithMorph, ClipDeform, ClipWithMesh

### Epic Python API
- `CustomizableObjectNodeMeshClipMorph`
- `CustomizableObjectNodeMeshClipDeform`
- `CustomizableObjectNodeMeshClipWithMesh`
- `CustomizableObjectNodeModifierClipMorph`

### Sample Content
- Mutable Sample: `Content/Tutorials/RemoveUnseen`
- Available on FAB: [Mutable Sample Package](https://www.fab.com/listings/209e82f6-ad40-4253-b565-d2f65b12efe7)

## Notes

- Current implementation ONLY does material combining
- Proper dismemberment requires CustomizableObject asset creation
- ClipMorph is the key to hiding/showing limbs
- Two instances needed: main character + severed limb
- Severed limb instance uses INVERSE clipping (show only that limb)
- Object pooling critical for performance with many severed limbs

## Revision History

- **2024-11-01**: Initial analysis and implementation plan
- User requested proper Mutable integration for mesh combining and limb spawning
- Current implementation identified as incomplete (material-only combining)
