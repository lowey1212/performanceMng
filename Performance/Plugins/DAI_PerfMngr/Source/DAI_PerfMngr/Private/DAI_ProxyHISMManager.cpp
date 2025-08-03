// Layman summary:// Manages groups of instanced meshes (HISMs) so we can draw lots of simple proxies cheaply.
// It batches "add instance" operations over time to avoid frame hitches.
#include "DAI_ProxyHISMManager.h"
#include "ProxyHISMRootActor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"

// Queue up a transform to be added to a batched HISM group identified by a tag.
// (We add them in chunks to avoid frame spikes.)
void UDAI_ProxyHISMManager::QueueInstanceForBatch(FName Tag, const FTransform& Transform)
{
    TArray<FTransform>& Queue = PendingBatchedAdds.FindOrAdd(Tag);
    Queue.RemoveAll([
        &Transform
    ](const FTransform& Existing)
    {
        return Existing.GetLocation().Equals(Transform.GetLocation(), 1.0f);
    });
    Queue.Add(Transform);
}

// Set how many instances per tick we add for this specific tag.
void UDAI_ProxyHISMManager::SetBatchSizeForTag(FName Tag, int32 BatchSize)
{
    TagToBatchSize.FindOrAdd(Tag) = BatchSize;
}

int32 UDAI_ProxyHISMManager::AddInstanceImmediate(FName Tag, const FTransform& Transform)
{
    if (bIsShuttingDown)
        return INDEX_NONE;

    if (UHierarchicalInstancedStaticMeshComponent* HISM = TagToHISM.FindRef(Tag))
    {
        return HISM->AddInstance(Transform);
    }
    return INDEX_NONE;
}

// Per-frame manager tick: add a limited number of pending instances to each HISM,
// and clean up any empty queues.
void UDAI_ProxyHISMManager::Tick(float DeltaTime)
{
    for (auto& Pair : PendingBatchedAdds)
    {
        FName Tag = Pair.Key;
        TArray<FTransform>& Queue = Pair.Value;

        UHierarchicalInstancedStaticMeshComponent* HISM = TagToHISM.FindRef(Tag);
        if (!HISM || Queue.Num() == 0)
            continue;

        // Use per-tag batch size if set, else global default
        int32 BatchSize = TagToBatchSize.Contains(Tag) ? TagToBatchSize[Tag] : BatchedAddSize;
        int32 NumToAdd = FMath::Min(BatchSize, Queue.Num());

        TArray<FTransform> ToAdd;
        ToAdd.Append(Queue.GetData(), NumToAdd);

        HISM->AddInstances(ToAdd, false);

        Queue.RemoveAt(0, NumToAdd, EAllowShrinking::No); // Updated: use EAllowShrinking::No
    }

    // Clean up empty queues
    for (auto It = PendingBatchedAdds.CreateIterator(); It; ++It)
    {
        if (It->Value.Num() == 0)
            It.RemoveCurrent();
    }
}

// Find the worlds dedicated root actor for all proxy HISMs; spawn one if missing.
AProxyHISMRootActor* FindOrSpawnProxyHISMRootActor(UWorld* World)
{
    // Look for an existing root actor
    for (TActorIterator<AProxyHISMRootActor> It(World); It; ++It)
    {
        return *It;
    }
    // If not found, spawn a new one with a unique name
    FActorSpawnParameters Params;
    Params.Name = TEXT("ProxyHISMRootActor_Auto");
    AProxyHISMRootActor* NewRoot = World->SpawnActor<AProxyHISMRootActor>(AProxyHISMRootActor::StaticClass(), FTransform::Identity, Params);
    if (GEngine && NewRoot)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Spawned ProxyHISMRootActor at runtime!"));
    }
    return NewRoot;
}

// Get the HISM component for a tag, or create and register one if it doesnt exist yet.
// All such HISMs are attached under the root actor for organization.
UHierarchicalInstancedStaticMeshComponent* UDAI_ProxyHISMManager::GetOrCreateHISMForTag(FName Tag, UStaticMesh* Mesh, UObject* Outer)
{
    if (bIsShuttingDown)
        return nullptr;

    if (!Mesh)
    {
        UE_LOG(LogTemp, Error, TEXT("GetOrCreateHISMForTag: Mesh is null!"));
        return nullptr;
    }
    if (!Outer)
    {
        UE_LOG(LogTemp, Error, TEXT("GetOrCreateHISMForTag: Outer is null!"));
        return nullptr;
    }

    // Check if we already have a HISM for this tag
    if (UHierarchicalInstancedStaticMeshComponent** Found = TagToHISM.Find(Tag))
    {
        if (*Found && ::IsValid(*Found))
            return *Found;
        TagToHISM.Remove(Tag);
    }

    UWorld* World = nullptr;
    if (AActor* OuterActor = Cast<AActor>(Outer))
        World = OuterActor->GetWorld();
    else if (UObject* OuterObj = Cast<UObject>(Outer))
        World = OuterObj->GetWorld();

    if (!World)
    {
        if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No World found for HISM!"));
        return nullptr;
    }

    // Find or spawn the root actor to parent the HISM
    AProxyHISMRootActor* RootActor = FindOrSpawnProxyHISMRootActor(World);
    if (!RootActor)
    {
        if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No ProxyHISMRootActor found/spawned in world!"));
        return nullptr;
    }

    // Create and register a new HISM component, attach to the root
    UHierarchicalInstancedStaticMeshComponent* HISM = NewObject<UHierarchicalInstancedStaticMeshComponent>(RootActor);
    if (!HISM)
        return nullptr;

    // Attach the HISM to the dedicated root component so multiple HISMs share the same parent
    HISM->SetupAttachment(RootActor->GetRootComponent());
    RootActor->AddInstanceComponent(HISM);
    HISM->SetStaticMesh(Mesh);
    HISM->RegisterComponent();
    HISM->ComponentTags.Add(Tag);
    TagToHISM.Add(Tag, HISM);

    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Created HISM [%s] and attached to root actor"), *Tag.ToString()));

    return HISM;
}

// Remove the HISM instance thats at (or very close to) the given transform.
void UDAI_ProxyHISMManager::RemoveInstanceAtTransform(FName Tag, const FTransform& Transform)
{
    if (bIsShuttingDown)
        return;

    if (UHierarchicalInstancedStaticMeshComponent** Found = TagToHISM.Find(Tag))
    {
        if (*Found && ::IsValid(*Found))
        {
            UHierarchicalInstancedStaticMeshComponent* HISM = *Found;
            int32 Num = HISM->GetInstanceCount();
            int32 BestIdx = -1;
            float BestDist = TNumericLimits<float>::Max();

            for (int32 i = 0; i < Num; ++i)
            {
                FTransform InstTransform;
                HISM->GetInstanceTransform(i, InstTransform, true);

                float Dist = FVector::DistSquared(InstTransform.GetLocation(), Transform.GetLocation());
                if (Dist < BestDist)
                {
                    BestDist = Dist;
                    BestIdx = i;
                }
            }
            // Remove if within 1cm (safety)
            if (BestIdx != -1 && BestDist < 1.0f)
            {
                HISM->RemoveInstance(BestIdx);
            }
        }
        else
        {
            TagToHISM.Remove(Tag);
        }
    }
}

void UDAI_ProxyHISMManager::RemoveInstanceByIndex(FName Tag, int32 Index)
{
    if (bIsShuttingDown)
        return;

    if (UHierarchicalInstancedStaticMeshComponent* HISM = TagToHISM.FindRef(Tag))
    {
        if (Index >= 0 && Index < HISM->GetInstanceCount())
        {
            HISM->RemoveInstance(Index);
        }
    }
}

// Print simple on-screen info about all HISM groups and how many instances each has.
void UDAI_ProxyHISMManager::PrintAllHISMDebugInfo()
{
    if (bIsShuttingDown)
        return;

    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("PrintAllHISMDebugInfo CALLED"));

    TArray<FName> TagsToRemove;
    int32 NumHISMs = 0;
    for (const TPair<FName, UHierarchicalInstancedStaticMeshComponent*>& Pair : TagToHISM)
    {
        if (Pair.Value && ::IsValid(Pair.Value))
        {
            NumHISMs++;
            int32 Num = Pair.Value->GetInstanceCount();
            FString Msg = FString::Printf(TEXT("HISM [%s] - %d Instances"), *Pair.Key.ToString(), Num);
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, Msg);
        }
        else
        {
            TagsToRemove.Add(Pair.Key);
        }
    }
    for (const FName& Tag : TagsToRemove)
        TagToHISM.Remove(Tag);

    if (NumHISMs == 0 && GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("No HISM components registered yet!"));
}

// Called on shutdown to clear all internal maps and stop managing HISMs.
void UDAI_ProxyHISMManager::Cleanup()
{
    bIsShuttingDown = true;
    TagToHISM.Empty();
    PendingBatchedAdds.Empty();
    TagToBatchSize.Empty();
}
