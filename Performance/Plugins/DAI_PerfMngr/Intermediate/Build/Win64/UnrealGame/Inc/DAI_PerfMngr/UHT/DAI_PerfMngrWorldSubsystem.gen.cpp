// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DAI_PerfMngr/Public/DAI_PerfMngrWorldSubsystem.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDAI_PerfMngrWorldSubsystem() {}

// Begin Cross Module References
DAI_PERFMNGR_API UClass* Z_Construct_UClass_UDAI_PerfMngrWorldSubsystem();
DAI_PERFMNGR_API UClass* Z_Construct_UClass_UDAI_PerfMngrWorldSubsystem_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem();
UPackage* Z_Construct_UPackage__Script_DAI_PerfMngr();
// End Cross Module References

// Begin Class UDAI_PerfMngrWorldSubsystem
void UDAI_PerfMngrWorldSubsystem::StaticRegisterNativesUDAI_PerfMngrWorldSubsystem()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UDAI_PerfMngrWorldSubsystem);
UClass* Z_Construct_UClass_UDAI_PerfMngrWorldSubsystem_NoRegister()
{
	return UDAI_PerfMngrWorldSubsystem::StaticClass();
}
struct Z_Construct_UClass_UDAI_PerfMngrWorldSubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * World subsystem for managing global performance manager logic.\n * Handles regular ticking and global cleanup for performance manager systems.\n */" },
#endif
		{ "IncludePath", "DAI_PerfMngrWorldSubsystem.h" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrWorldSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "World subsystem for managing global performance manager logic.\nHandles regular ticking and global cleanup for performance manager systems." },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDAI_PerfMngrWorldSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UDAI_PerfMngrWorldSubsystem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UWorldSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_DAI_PerfMngr,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDAI_PerfMngrWorldSubsystem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UDAI_PerfMngrWorldSubsystem_Statics::ClassParams = {
	&UDAI_PerfMngrWorldSubsystem::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UDAI_PerfMngrWorldSubsystem_Statics::Class_MetaDataParams), Z_Construct_UClass_UDAI_PerfMngrWorldSubsystem_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UDAI_PerfMngrWorldSubsystem()
{
	if (!Z_Registration_Info_UClass_UDAI_PerfMngrWorldSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDAI_PerfMngrWorldSubsystem.OuterSingleton, Z_Construct_UClass_UDAI_PerfMngrWorldSubsystem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UDAI_PerfMngrWorldSubsystem.OuterSingleton;
}
template<> DAI_PERFMNGR_API UClass* StaticClass<UDAI_PerfMngrWorldSubsystem>()
{
	return UDAI_PerfMngrWorldSubsystem::StaticClass();
}
UDAI_PerfMngrWorldSubsystem::UDAI_PerfMngrWorldSubsystem() {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UDAI_PerfMngrWorldSubsystem);
UDAI_PerfMngrWorldSubsystem::~UDAI_PerfMngrWorldSubsystem() {}
// End Class UDAI_PerfMngrWorldSubsystem

// Begin Registration
struct Z_CompiledInDeferFile_FID_DAIExampleProject_5_5_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrWorldSubsystem_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDAI_PerfMngrWorldSubsystem, UDAI_PerfMngrWorldSubsystem::StaticClass, TEXT("UDAI_PerfMngrWorldSubsystem"), &Z_Registration_Info_UClass_UDAI_PerfMngrWorldSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDAI_PerfMngrWorldSubsystem), 545146201U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_DAIExampleProject_5_5_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrWorldSubsystem_h_2504723100(TEXT("/Script/DAI_PerfMngr"),
	Z_CompiledInDeferFile_FID_DAIExampleProject_5_5_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrWorldSubsystem_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_DAIExampleProject_5_5_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrWorldSubsystem_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
