#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProxyHISMRootActor.generated.h"

/**
 * Simple root actor used to parent all Proxy HISMs for organization in the world outliner.
 * Does not tick or have gameplay logic.
 */
UCLASS()
class DAI_PERFMNGR_API AProxyHISMRootActor : public AActor
{
    GENERATED_BODY()
public:
    AProxyHISMRootActor();
};

/**
 * Finds or spawns the proxy HISM root actor for the given world.
 * Used to ensure a single parent for all managed HISMs.
 */
AProxyHISMRootActor* FindOrSpawnProxyHISMRootActor(UWorld* World);
