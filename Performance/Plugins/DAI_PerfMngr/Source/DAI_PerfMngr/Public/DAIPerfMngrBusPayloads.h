#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DAIPerfMngrBusPayloads.generated.h"

USTRUCT(BlueprintType)
struct FDAIMessage_PerfProxySwap
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly, Category = "Performance")
    TWeakObjectPtr<UActorComponent> Component;
    UPROPERTY(BlueprintReadOnly, Category = "Performance")
    FGameplayTag State; // Entered / Exited
};

USTRUCT(BlueprintType)
struct FDAIMessage_PerfSignificanceTier
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly, Category = "Performance")
    TWeakObjectPtr<AActor> Actor;
    UPROPERTY(BlueprintReadOnly, Category = "Performance")
    int32 Tier = 0; // Discrete tier bucket
};
