# DAI_Dismember - Component-Based Mutable Integration

## Architecture Overview

This implementation assumes characters have **pre-segmented limb components** (Head, Torso, Arms, Legs as separate SkeletalMeshComponents) controlled by **GAS Attributes**.

### Key Concept

1. **Mutable Instance 1** (Main Character): Dynamic combination of VISIBLE limbs only
2. **Mutable Instance 2** (Severed Limb): Contains ONLY the severed limb mesh
3. **GAS Attributes**: Track which limbs are severed (`bRightArmSevered`, etc.)
4. **On Sever**: Rebuild Instance 1 (exclude limb), spawn Instance 2 (only limb)

## Implementation

### Service Interface

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
    // Initialize actor with Mutable - combines all visible limb meshes
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DAI|Dismember|Mutable")
    bool InitializeActorMutable(AActor* Actor, const TArray<USkeletalMeshComponent*>& LimbComponents);
    
    // Rebuild character mesh excluding severed limbs
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DAI|Dismember|Mutable")
    bool RebuildCharacterMesh(AActor* Actor, const TArray<FName>& ExcludedLimbs);
    
    // Create severed limb mesh instance
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DAI|Dismember|Mutable")
    USkeletalMesh* GenerateSeveredLimbMesh(AActor* SourceActor, FName LimbID, USkeletalMeshComponent* LimbComponent);
    
    // Spawn severed limb actor with physics
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DAI|Dismember|Mutable")
    AActor* SpawnSeveredLimbActor(AActor* SourceActor, FName LimbID, USkeletalMesh* LimbMesh, FVector SpawnLocation, FVector ImpulseDirection);
};
```

### Default Implementation

**File**: `DAI_DefaultMutableCombinerService.h`

```cpp
UCLASS(BlueprintType, Blueprintable)
class DAI_DISMEMBER_API UDAI_DefaultMutableCombinerService : public UObject, public IDAI_MutableCombinerService
{
    GENERATED_BODY()

public:
    // Service interface implementation
    virtual bool InitializeActorMutable_Implementation(AActor* Actor, const TArray<USkeletalMeshComponent*>& LimbComponents) override;
    virtual bool RebuildCharacterMesh_Implementation(AActor* Actor, const TArray<FName>& ExcludedLimbs) override;
    virtual USkeletalMesh* GenerateSeveredLimbMesh_Implementation(AActor* SourceActor, FName LimbID, USkeletalMeshComponent* LimbComponent) override;
    virtual AActor* SpawnSeveredLimbActor_Implementation(AActor* SourceActor, FName LimbID, USkeletalMesh* LimbMesh, FVector SpawnLocation, FVector ImpulseDirection) override;

protected:
    // Helper: Get CustomizableObject from settings
    UCustomizableObject* GetCharacterCustomizableObject() const;
    
    // Helper: Create mesh combination from components
    bool CombineSkeletalMeshComponents(const TArray<USkeletalMeshComponent*>& Components, UCustomizableObjectInstance* TargetInstance);
    
    // Helper: Get limb component by ID
    USkeletalMeshComponent* GetLimbComponent(AActor* Actor, FName LimbID) const;
    
    // Cache: Store CustomizableObjectInstance per actor
    UPROPERTY(Transient)
    TMap<TObjectPtr<AActor>, TObjectPtr<UCustomizableObjectInstance>> ActorInstanceMap;
    
    // Cache: Map limb IDs to component names
    UPROPERTY(Transient)
    TMap<FName, FName> LimbIDToComponentNameMap;
};
```

### Implementation Logic

**File**: `DAI_DefaultMutableCombinerService.cpp`

```cpp
#include "DAI_DefaultMutableCombinerService.h"
#include "DAI_DismemberDeveloperSettings.h"
#include "MuCO/CustomizableObject.h"
#include "MuCO/CustomizableObjectInstance.h"
#include "MuCO/CustomizableObjectSystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"

bool UDAI_DefaultMutableCombinerService::InitializeActorMutable_Implementation(
    AActor* Actor, 
    const TArray<USkeletalMeshComponent*>& LimbComponents)
{
    if (!Actor || LimbComponents.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("MutableService: Cannot initialize - invalid actor or no components"));
        return false;
    }

    UCustomizableObject* CO = GetCharacterCustomizableObject();
    if (!CO)
    {
        UE_LOG(LogTemp, Warning, TEXT("MutableService: CustomizableObject not configured"));
        return false;
    }

    // Create CustomizableObjectInstance for this actor
    UCustomizableObjectInstance* Instance = NewObject<UCustomizableObjectInstance>(Actor);
    Instance->SetObject(CO);
    
    // Combine all limb meshes
    if (!CombineSkeletalMeshComponents(LimbComponents, Instance))
    {
        UE_LOG(LogTemp, Error, TEXT("MutableService: Failed to combine meshes"));
        return false;
    }
    
    // Store instance
    ActorInstanceMap.Add(Actor, Instance);
    
    // Generate combined mesh asynchronously
    Instance->UpdateSkeletalMeshAsync(true, true);
    
    UE_LOG(LogTemp, Log, TEXT("MutableService: Initialized actor %s with %d limb components"), 
           *Actor->GetName(), LimbComponents.Num());
    
    return true;
}

bool UDAI_DefaultMutableCombinerService::RebuildCharacterMesh_Implementation(
    AActor* Actor, 
    const TArray<FName>& ExcludedLimbs)
{
    if (!Actor)
    {
        return false;
    }

    UCustomizableObjectInstance** InstancePtr = ActorInstanceMap.Find(Actor);
    if (!InstancePtr || !*InstancePtr)
    {
        UE_LOG(LogTemp, Warning, TEXT("MutableService: No CustomizableObjectInstance found for actor %s"), *Actor->GetName());
        return false;
    }

    UCustomizableObjectInstance* Instance = *InstancePtr;
    
    // Get all limb components
    TArray<USkeletalMeshComponent*> AllLimbComponents;
    Actor->GetComponents<USkeletalMeshComponent>(AllLimbComponents);
    
    // Filter out excluded limbs
    TArray<USkeletalMeshComponent*> IncludedComponents;
    for (USkeletalMeshComponent* Comp : AllLimbComponents)
    {
        FName ComponentName = Comp->GetFName();
        bool bIsExcluded = false;
        
        // Check if this component corresponds to an excluded limb
        for (const FName& ExcludedLimb : ExcludedLimbs)
        {
            if (LimbIDToComponentNameMap.Contains(ExcludedLimb))
            {
                if (LimbIDToComponentNameMap[ExcludedLimb] == ComponentName)
                {
                    bIsExcluded = true;
                    break;
                }
            }
        }
        
        if (!bIsExcluded)
        {
            IncludedComponents.Add(Comp);
        }
    }
    
    UE_LOG(LogTemp, Log, TEXT("MutableService: Rebuilding mesh for %s - %d included, %d excluded"), 
           *Actor->GetName(), IncludedComponents.Num(), ExcludedLimbs.Num());
    
    // Recombine only included components
    if (!CombineSkeletalMeshComponents(IncludedComponents, Instance))
    {
        UE_LOG(LogTemp, Error, TEXT("MutableService: Failed to rebuild mesh"));
        return false;
    }
    
    // Regenerate mesh
    Instance->UpdateSkeletalMeshAsync(true, true);
    
    return true;
}

USkeletalMesh* UDAI_DefaultMutableCombinerService::GenerateSeveredLimbMesh_Implementation(
    AActor* SourceActor,
    FName LimbID, 
    USkeletalMeshComponent* LimbComponent)
{
    if (!SourceActor || !LimbComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("MutableService: Invalid parameters for severed limb generation"));
        return nullptr;
    }

    UCustomizableObject* CO = GetCharacterCustomizableObject();
    if (!CO)
    {
        UE_LOG(LogTemp, Warning, TEXT("MutableService: CustomizableObject not configured"));
        return nullptr;
    }

    // Create temporary instance for ONLY this limb
    UCustomizableObjectInstance* LimbInstance = NewObject<UCustomizableObjectInstance>(GetTransientPackage());
    LimbInstance->SetObject(CO);
    
    // Combine ONLY the severed limb component
    TArray<USkeletalMeshComponent*> SingleComponent;
    SingleComponent.Add(LimbComponent);
    
    if (!CombineSkeletalMeshComponents(SingleComponent, LimbInstance))
    {
        UE_LOG(LogTemp, Error, TEXT("MutableService: Failed to generate severed limb mesh"));
        return nullptr;
    }
    
    // Generate mesh synchronously (we need it immediately for spawning)
    LimbInstance->UpdateSkeletalMeshAsync(false, true);
    
    USkeletalMesh* GeneratedMesh = LimbInstance->GetSkeletalMesh();
    
    UE_LOG(LogTemp, Log, TEXT("MutableService: Generated severed limb mesh for %s"), *LimbID.ToString());
    
    return GeneratedMesh;
}

AActor* UDAI_DefaultMutableCombinerService::SpawnSeveredLimbActor_Implementation(
    AActor* SourceActor,
    FName LimbID,
    USkeletalMesh* LimbMesh, 
    FVector SpawnLocation,
    FVector ImpulseDirection)
{
    if (!SourceActor || !LimbMesh)
    {
        UE_LOG(LogTemp, Warning, TEXT("MutableService: Cannot spawn severed limb - invalid parameters"));
        return nullptr;
    }

    UWorld* World = SourceActor->GetWorld();
    if (!World)
    {
        return nullptr;
    }

    // Spawn actor for severed limb
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    
    AActor* SeveredActor = World->SpawnActor<AActor>(AActor::StaticClass(), SpawnLocation, FRotator::ZeroRotator, SpawnParams);
    if (!SeveredActor)
    {
        UE_LOG(LogTemp, Error, TEXT("MutableService: Failed to spawn severed limb actor"));
        return nullptr;
    }
    
    // Add skeletal mesh component
    USkeletalMeshComponent* LimbMeshComp = NewObject<USkeletalMeshComponent>(SeveredActor);
    LimbMeshComp->SetSkeletalMesh(LimbMesh);
    LimbMeshComp->RegisterComponent();
    SeveredActor->SetRootComponent(LimbMeshComp);
    
    // Enable physics
    LimbMeshComp->SetSimulatePhysics(true);
    LimbMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    LimbMeshComp->SetCollisionObjectType(ECC_PhysicsBody);
    LimbMeshComp->SetCollisionResponseToAllChannels(ECR_Block);
    
    // Apply impulse for flying limb effect
    FVector NormalizedImpulse = ImpulseDirection.GetSafeNormal();
    LimbMeshComp->AddImpulse(NormalizedImpulse * 500.0f, NAME_None, true);
    
    // Add angular velocity for spinning effect
    FVector AngularVelocity = FVector(
        FMath::RandRange(-10.0f, 10.0f),
        FMath::RandRange(-10.0f, 10.0f),
        FMath::RandRange(-10.0f, 10.0f)
    );
    LimbMeshComp->SetPhysicsAngularVelocityInRadians(AngularVelocity);
    
    UE_LOG(LogTemp, Log, TEXT("MutableService: Spawned severed limb actor for %s at %s"), 
           *LimbID.ToString(), *SpawnLocation.ToString());
    
    return SeveredActor;
}

// Helper Methods

UCustomizableObject* UDAI_DefaultMutableCombinerService::GetCharacterCustomizableObject() const
{
    const UDAI_DismemberDeveloperSettings* Settings = GetDefault<UDAI_DismemberDeveloperSettings>();
    if (!Settings || !Settings->CharacterCustomizableObject.IsValid())
    {
        return nullptr;
    }
    
    return Settings->CharacterCustomizableObject.LoadSynchronous();
}

bool UDAI_DefaultMutableCombinerService::CombineSkeletalMeshComponents(
    const TArray<USkeletalMeshComponent*>& Components,
    UCustomizableObjectInstance* TargetInstance)
{
    if (!TargetInstance || Components.Num() == 0)
    {
        return false;
    }

    // In a real implementation, you would:
    // 1. Set CustomizableObject parameters for each component
    // 2. Configure material parameters
    // 3. Set mesh part visibility/inclusion
    
    // For now, this is a placeholder that assumes your CustomizableObject
    // is set up to accept multiple mesh inputs and has parameters like:
    // - "IncludeHead" (bool)
    // - "IncludeTorso" (bool)
    // - "IncludeRightArm" (bool)
    // etc.
    
    for (USkeletalMeshComponent* Comp : Components)
    {
        FString ComponentName = Comp->GetName();
        FString IncludeParam = FString::Printf(TEXT("Include%s"), *ComponentName);
        
        // Set parameter to include this mesh part
        TargetInstance->SetBoolParameterSelectedOption(IncludeParam, true);
        
        // Copy material parameters if needed
        for (int32 MatIdx = 0; MatIdx < Comp->GetNumMaterials(); ++MatIdx)
        {
            UMaterialInterface* Mat = Comp->GetMaterial(MatIdx);
            if (Mat)
            {
                // Transfer material parameters to CustomizableObject
                // This is project-specific - adjust based on your CO setup
            }
        }
    }
    
    return true;
}

USkeletalMeshComponent* UDAI_DefaultMutableCombinerService::GetLimbComponent(AActor* Actor, FName LimbID) const
{
    if (!Actor)
    {
        return nullptr;
    }

    // Try to find component by mapped name
    if (LimbIDToComponentNameMap.Contains(LimbID))
    {
        FName ComponentName = LimbIDToComponentNameMap[LimbID];
        return Cast<USkeletalMeshComponent>(Actor->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
    }
    
    // Fallback: try to find by matching name
    TArray<USkeletalMeshComponent*> Components;
    Actor->GetComponents<USkeletalMeshComponent>(Components);
    
    for (USkeletalMeshComponent* Comp : Components)
    {
        if (Comp->GetFName() == LimbID)
        {
            return Comp;
        }
    }
    
    return nullptr;
}
```

### Settings Configuration

**File**: `DAI_DismemberDeveloperSettings.h` (additions)

```cpp
UPROPERTY(EditDefaultsOnly, Config, Category = "Mutable", 
          meta = (ToolTip = "CustomizableObject asset for character mesh combination"))
TSoftObjectPtr<UCustomizableObject> CharacterCustomizableObject;

UPROPERTY(EditDefaultsOnly, Config, Category = "Mutable",
          meta = (ToolTip = "Map limb IDs to skeletal mesh component names"))
TMap<FName, FName> LimbIDToComponentMap;
```

### GAS Integration Example

**In your Gameplay Ability:**

```cpp
void UGAS_SeverLimb::ActivateAbility(...)
{
    // 1. Apply GAS damage to limb attribute
    FGameplayEffectSpecHandle DamageSpec = MakeOutgoingGameplayEffectSpec(LimbDamageEffect);
    ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, DamageSpec, TargetDataHandle);
    
    // 2. Check if limb health <= 0
    if (GetLimbHealth(TargetActor, LimbID) <= 0.0f)
    {
        // 3. Get Mutable service
        UDAI_DefaultMutableCombinerService* Service = GetMutableService();
        
        // 4. Get limb component
        USkeletalMeshComponent* LimbComp = GetLimbComponent(TargetActor, LimbID);
        
        // 5. Generate severed limb mesh
        USkeletalMesh* SeveredMesh = Service->GenerateSeveredLimbMesh(TargetActor, LimbID, LimbComp);
        
        // 6. Rebuild main character (exclude this limb)
        TArray<FName> ExcludedLimbs = {LimbID};
        Service->RebuildCharacterMesh(TargetActor, ExcludedLimbs);
        
        // 7. Spawn severed limb
        FVector SpawnLoc = LimbComp->GetSocketLocation("SeverSocket");
        FVector ImpulseDir = (SpawnLoc - TargetActor->GetActorLocation()).GetSafeNormal();
        Service->SpawnSeveredLimbActor(TargetActor, LimbID, SeveredMesh, SpawnLoc, ImpulseDir);
        
        // 8. Mark limb as severed in GAS
        SetLimbSeveredAttribute(TargetActor, LimbID, true);
    }
    
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
```

## Performance Comparison

### Your Approach (Component-Based):
- ✅ **Simpler CustomizableObject**: Just include/exclude mesh parts
- ✅ **Less Runtime Cost**: No morph evaluation
- ✅ **Better for Armor Systems**: Easy to swap gear pieces
- ✅ **GAS Native**: Attributes directly control visibility

### ClipMorph Approach:
- ❌ **Complex Setup**: Need morph targets per limb
- ❌ **Runtime Overhead**: Morph evaluation every frame
- ✅ **Good for Single Mesh**: When character is one piece
- ❌ **Harder Integration**: Need to map GAS → Morph params

## Summary

**Your approach is correct and more efficient** for a character system with:
- Pre-segmented limb components
- GAS attribute-driven state
- Modular armor/equipment system

**No need for ClipMorph** - just rebuild the CustomizableObject with different included components.

