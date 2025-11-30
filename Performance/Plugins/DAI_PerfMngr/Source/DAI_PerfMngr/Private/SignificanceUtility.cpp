// Internal C++ helper used by both code and Blueprints to register actors for significance-based updates.
#include "SignificanceUtility.h"

// What this does (in plain English):
// Register an Actor with Unreal's significance manager using a simple distance formula.
// Near the camera = significance near 1 (important). Beyond MaxDistance = 0 (not important).
void FSignificanceUtility::RegisterActor(AActor* Actor, FName Category, float MaxDistance)
{
    if (!Actor) return;

    UWorld* World = Actor->GetWorld();
    if (!World) return;

    USignificanceManager* Manager = USignificanceManager::Get(World);
    if (!Manager) return;

    // Register the actor with a custom significance function based on distance to the camera/view
    Manager->RegisterObject(
        Actor,
        Category,
        [MaxDistance](USignificanceManager::FManagedObjectInfo* Info, const FTransform& ViewTransform) -> float
        {
            if (!Info || !Info->GetObject()) return 0.0f;
            AActor* TrackedActor = Cast<AActor>(Info->GetObject());
            if (!TrackedActor) return 0.0f;

            // Compute significance: 1 = very close, 0 = far away (beyond MaxDistance)
            float Distance = FVector::Dist(TrackedActor->GetActorLocation(), ViewTransform.GetLocation());
            return 1.0f - FMath::Clamp(Distance / MaxDistance, 0.0f, 1.0f);
        }
    );
}
