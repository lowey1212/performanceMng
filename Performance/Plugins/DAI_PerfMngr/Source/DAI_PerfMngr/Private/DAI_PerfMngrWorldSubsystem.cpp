#include "DAI_PerfMngrWorldSubsystem.h"
#include "SignificanceManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "HAL/PlatformTime.h"
#include "Tickable.h"
#include "DAI_ProxyHISMManager.h" // ✅ Required to access Proxy Manager

// Initialize: register a ticker so this subsystem runs every frame (or regularly).
void UDAI_PerfMngrWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    // Register a ticker so Tick() is called regularly by Unreal's core ticker system
    TickerHandle = FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateUObject(this, &UDAI_PerfMngrWorldSubsystem::Tick));
}

// Deinitialize: remove the ticker when the world shuts down.
void UDAI_PerfMngrWorldSubsystem::Deinitialize()
{
    FTSTicker::GetCoreTicker().RemoveTicker(TickerHandle);
    Super::Deinitialize();
}

// Tick: update the significance system using the player's location and drive HISM batching.
bool UDAI_PerfMngrWorldSubsystem::Tick(float DeltaTime)
{
    UWorld* World = GetWorld();
    if (!World) return true;

    // Update the significance manager with the player's current transform for distance-based logic
    if (USignificanceManager* Manager = USignificanceManager::Get(World))
    {
        if (APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(World, 0))
        {
            const FTransform PlayerTransform = PlayerPawn->GetTransform();
            // Only a single view (the player's camera) is provided for significance checks here
            Manager->Update(TArrayView<const FTransform>(&PlayerTransform, 1));
        }
    }

    // ✅ Drive proxy batching (very important!)
    if (UDAI_ProxyHISMManager* ProxyMgr = World->GetSubsystem<UDAI_ProxyHISMManager>())
    {
        ProxyMgr->Tick(DeltaTime);
    }

    // Return true to keep the ticker alive (keep ticking)
    return true;
}
