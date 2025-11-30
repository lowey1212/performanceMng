#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DAI_ProxyHISMManager.generated.h"

class UStaticMesh;
class UHierarchicalInstancedStaticMeshComponent;
class AProxyHISMRootActor;

/**
 * @brief Manages all proxy HISM (Hierarchical Instanced Static Mesh) components by tag.
 * Plain English: batches lots of the same proxy meshes into one draw call to save GPU time.
 */
UCLASS()
class DAI_PERFMNGR_API UDAI_ProxyHISMManager : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    /** Get or create the HISM for a tag/mesh in this world. */
    UHierarchicalInstancedStaticMeshComponent* GetOrCreateHISMForTag(FName Tag, UStaticMesh* Mesh, UObject* Outer);

    /** Remove a single instance at a given transform from the HISM mapped by Tag. */
    void RemoveInstanceAtTransform(FName Tag, const FTransform& Transform);

    /** Remove a single instance by index from the HISM mapped by Tag. */
    void RemoveInstanceByIndex(FName Tag, int32 Index);

    /** Immediately add an instance and return its index for tracking. */
    int32 AddInstanceImmediate(FName Tag, const FTransform& Transform);

    /** Print a list of all HISM components and their instance counts to the log. */
    UFUNCTION(BlueprintCallable, Category = "Debug", meta = (ToolTip = "Logs all proxy HISM components and their instance counts."))
    void PrintAllHISMDebugInfo();

    /** Destroys all managed HISMs and clears internal maps. */
    void Cleanup();

    /** Queue a transform to be added to a HISM batch (throttled adding to avoid frame hitches). */
    void QueueInstanceForBatch(FName Tag, const FTransform& Transform);

    /** Call this every tick to process queued batch adds. */
    void Tick(float DeltaTime);

    /** Override the per-tag batch size (how many instances to add per tick). */
    void SetBatchSizeForTag(FName Tag, int32 BatchSize);

    /** Default number of proxy instances to add to each HISM per tick. Lower = smoother, Higher = faster. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProxyBatching", meta = (ClampMin = "1", ClampMax = "1000", UIMin = "1", UIMax = "200", ToolTip = "How many instances to add to each HISM per tick by default (prevents hitching when spawning many)."))
    int32 BatchedAddSize = 50;

protected:
    /** True when the world is shutting down; prevents creating new components during teardown. */
    bool bIsShuttingDown = false;

    /** Pending batches of instance transforms, per tag. */
    TMap<FName, TArray<FTransform>> PendingBatchedAdds;

    /** Mapping from tag to the HISM component that holds those instances. */
    UPROPERTY() TMap<FName, UHierarchicalInstancedStaticMeshComponent*> TagToHISM;

    /** Per-tag batch size overrides. */
    TMap<FName, int32> TagToBatchSize;
};
