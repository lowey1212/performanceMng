// Layman summary:
// This file defines the Unreal Engine module for the performance manager plugin.
// StartupModule/ShutdownModule are called when the plugin is loaded/unloaded.
// There's no special startup logic here�it's just the required boilerplate.
#include "Modules/ModuleManager.h"
#include "DAI_PerfMngrLog.h"
#include "HAL/IConsoleManager.h"

class FDAI_PerfMngrModule : public IModuleInterface
{
public:
    virtual void StartupModule() override
    {
        IConsoleManager::Get().RegisterConsoleCommand(
            TEXT("DAI.Perf.Help"),
            TEXT("Show DAI_PerfMngr console help"),
            FConsoleCommandDelegate::CreateLambda([]()
                                                  {
                                                      UE_LOG(LogDAIPerfMngr, Display, TEXT("DAI.Perf.Help"));
                                                      UE_LOG(LogDAIPerfMngr, Display, TEXT("  DAI.Perf.Help - Show this help")); }),
            ECVF_Cheat);
    }
    virtual void ShutdownModule() override
    {
        IConsoleManager::Get().UnregisterConsoleObject(TEXT("DAI.Perf.Help"), false);
    }
};

IMPLEMENT_MODULE(FDAI_PerfMngrModule, DAI_PerfMngr)

// Define the module log category
DEFINE_LOG_CATEGORY(LogDAIPerfMngr);