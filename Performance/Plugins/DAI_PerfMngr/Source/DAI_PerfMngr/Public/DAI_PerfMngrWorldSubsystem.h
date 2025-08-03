#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Tickable.h"
#include "HAL/PlatformTime.h"
#include "DAI_PerfMngrWorldSubsystem.generated.h"

/**
 * @brief World subsystem that hosts global performance-manager logic.
 * In simple terms: a singleton per world that ticks and cleans up perf-related systems.
 */
UCLASS()
class DAI_PERFMNGR_API UDAI_PerfMngrWorldSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    /** Called when the subsystem starts up for a world. */
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    /** Called when the subsystem shuts down for a world. */
    virtual void Deinitialize() override;

private:
    /** Ticker delegate – runs every frame or at a fixed interval to process global perf logic. */
    bool Tick(float DeltaTime);

    /** Handle to unregister the ticker on shutdown. */
    FTSTicker::FDelegateHandle TickerHandle;
};
