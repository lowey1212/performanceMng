using UnrealBuildTool;
using System.IO;

public class DAI_PerfMngr : ModuleRules
{
    public DAI_PerfMngr(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "GameplayAbilities",
            "GameplayTags",
            "GameplayTasks",
            "SignificanceManager",
            "UMG",
            "AIModule",
            "Niagara",
            "HairStrandsCore"
        });

        PublicIncludePaths.AddRange(new string[] {
            Path.Combine(EngineDirectory, "Plugins/Runtime/SignificanceManager/Source/SignificanceManager/Public"),
            Path.Combine(EngineDirectory, "Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public")
        });
    }
}
