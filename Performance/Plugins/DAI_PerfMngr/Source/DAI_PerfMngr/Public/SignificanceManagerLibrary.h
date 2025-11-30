#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "SignificanceManagerLibrary.generated.h"

/**
 * @brief Blueprint helper library for the significance manager.
 * Plain English: easy BP helpers to register actors for distance-based importance checks.
 */
UCLASS()
class DAI_PERFMNGR_API USignificanceManagerLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /**
     * Registers an actor with the significance system for distance-based performance management.
     * @param Actor The actor to register.
     * @param Category Optional category label for filtering or grouping.
     * @param MaxDistance The maximum distance at which the actor is considered significant.
     */
    UFUNCTION(BlueprintCallable, Category = "Significance", meta = (ToolTip = "Register an actor with the significance system so distance/importance can scale its cost."))
    static void RegisterActorWithSignificance(AActor* Actor, FName Category, float MaxDistance);
};
