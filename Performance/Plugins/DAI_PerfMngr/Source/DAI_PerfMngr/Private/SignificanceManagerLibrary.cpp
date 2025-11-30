// Blueprint helper to register actors with the significance system
// so far-away things can update less often for better performance.
#include "SignificanceManagerLibrary.h"
#include "SignificanceUtility.h"

// What this does (in plain English):
// Expose a simple Blueprint function that opts an Actor into
// the "significance" system (distance-based importance). The closer it is,
// the more updates it gets. Farther away = fewer updates.
void USignificanceManagerLibrary::RegisterActorWithSignificance(AActor* Actor, FName Category, float MaxDistance)
{
    // Just call the internal C++ helper to do the actual registration.
    FSignificanceUtility::RegisterActor(Actor, Category, MaxDistance);
}
