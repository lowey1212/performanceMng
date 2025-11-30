#pragma once

#include "CoreMinimal.h"
#include "SignificanceManager.h"

/**
 * @brief Internal C++ helper for registering actors with the significance system.
 * Plain English: use in code to mark actors as important/unimportant by distance.
 */
class DAI_PERFMNGR_API FSignificanceUtility
{
public:
    /**
     * Registers the given actor with the significance manager for distance-based relevance checks.
     * @param Actor      The actor to register.
     * @param Category   Optional category for grouping/filtering significance.
     * @param MaxDistance Maximum distance at which the actor is considered significant.
     */
    static void RegisterActor(AActor* Actor, FName Category, float MaxDistance);
};
