using UnrealBuildTool;
using System.IO;

public class DAI_PerfMngr : ModuleRules
{
    public DAI_PerfMngr(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "NetCore",
            "GameplayAbilities",
            "GameplayTags",
            "GameplayTasks",
            "SignificanceManager",
            "UMG",
            "AIModule",
            "Niagara",
            "HairStrandsCore",
            "AudioMixer"
        });

        // CoreContracts used only if present (soft include pattern in source)

        PublicIncludePaths.AddRange(new string[] {
            Path.Combine(EngineDirectory, "Plugins/Runtime/SignificanceManager/Source/SignificanceManager/Public"),
            Path.Combine(EngineDirectory, "Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public")
        });

        if (Target.bUseIris)
        {
            PublicDependencyModuleNames.Add("IrisCore");
        }
    }
}
