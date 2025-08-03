// Layman summary:
// This file defines the Unreal Engine module for the performance manager plugin.
// StartupModule/ShutdownModule are called when the plugin is loaded/unloaded.
// There's no special startup logic here—it's just the required boilerplate.
#include "Modules/ModuleManager.h"

class FDAI_PerfMngrModule : public IModuleInterface
{
public:
    virtual void StartupModule() override {}
    virtual void ShutdownModule() override {}
};

IMPLEMENT_MODULE(FDAI_PerfMngrModule, DAI_PerfMngr)