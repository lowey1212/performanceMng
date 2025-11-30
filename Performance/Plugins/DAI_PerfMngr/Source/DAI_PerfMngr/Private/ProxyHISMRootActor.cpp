// This actor exists only as a parent/holder for Hierarchical Instanced Static Mesh (HISM) components.
// Those components let us render many copies of the same mesh very efficiently.
#include "ProxyHISMRootActor.h"
#include "Components/SceneComponent.h"

// Provide an explicit root scene component so spawned HISMs have a stable parent in the world
// outliner. Without this, the first registered HISM would become the actor's root, making it
// harder to organize additional components.
AProxyHISMRootActor::AProxyHISMRootActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // Create a simple root scene component to attach HISM children to
    USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ProxyHISMRoot"));
    SceneRoot->SetMobility(EComponentMobility::Static);
    RootComponent = SceneRoot;
}

