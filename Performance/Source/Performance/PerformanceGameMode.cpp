#include "PerformanceGameMode.h"
#include "PerformanceCharacter.h"
#include "UObject/ConstructorHelpers.h"

APerformanceGameMode::APerformanceGameMode()
{
        static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
        if (PlayerPawnBPClass.Class != nullptr)
        {
                DefaultPawnClass = PlayerPawnBPClass.Class; // use blueprint character as player
        }
}
