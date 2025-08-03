// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DAI_PerfMngr/Public/ProxyHISMRootActor.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProxyHISMRootActor() {}

// Begin Cross Module References
DAI_PERFMNGR_API UClass* Z_Construct_UClass_AProxyHISMRootActor();
DAI_PERFMNGR_API UClass* Z_Construct_UClass_AProxyHISMRootActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AActor();
UPackage* Z_Construct_UPackage__Script_DAI_PerfMngr();
// End Cross Module References

// Begin Class AProxyHISMRootActor
void AProxyHISMRootActor::StaticRegisterNativesAProxyHISMRootActor()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AProxyHISMRootActor);
UClass* Z_Construct_UClass_AProxyHISMRootActor_NoRegister()
{
	return AProxyHISMRootActor::StaticClass();
}
struct Z_Construct_UClass_AProxyHISMRootActor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Simple root actor used to parent all Proxy HISMs for organization in the world outliner.\n * Does not tick or have gameplay logic.\n */" },
#endif
		{ "IncludePath", "ProxyHISMRootActor.h" },
		{ "ModuleRelativePath", "Public/ProxyHISMRootActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple root actor used to parent all Proxy HISMs for organization in the world outliner.\nDoes not tick or have gameplay logic." },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AProxyHISMRootActor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AProxyHISMRootActor_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_DAI_PerfMngr,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AProxyHISMRootActor_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AProxyHISMRootActor_Statics::ClassParams = {
	&AProxyHISMRootActor::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProxyHISMRootActor_Statics::Class_MetaDataParams), Z_Construct_UClass_AProxyHISMRootActor_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AProxyHISMRootActor()
{
	if (!Z_Registration_Info_UClass_AProxyHISMRootActor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AProxyHISMRootActor.OuterSingleton, Z_Construct_UClass_AProxyHISMRootActor_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AProxyHISMRootActor.OuterSingleton;
}
template<> DAI_PERFMNGR_API UClass* StaticClass<AProxyHISMRootActor>()
{
	return AProxyHISMRootActor::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AProxyHISMRootActor);
AProxyHISMRootActor::~AProxyHISMRootActor() {}
// End Class AProxyHISMRootActor

// Begin Registration
struct Z_CompiledInDeferFile_FID_PluginTest_Performance_Plugins_DAI_PerfMngr_DAI_PerfMngr_Source_DAI_PerfMngr_Public_ProxyHISMRootActor_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AProxyHISMRootActor, AProxyHISMRootActor::StaticClass, TEXT("AProxyHISMRootActor"), &Z_Registration_Info_UClass_AProxyHISMRootActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AProxyHISMRootActor), 2048002795U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginTest_Performance_Plugins_DAI_PerfMngr_DAI_PerfMngr_Source_DAI_PerfMngr_Public_ProxyHISMRootActor_h_3273773758(TEXT("/Script/DAI_PerfMngr"),
	Z_CompiledInDeferFile_FID_PluginTest_Performance_Plugins_DAI_PerfMngr_DAI_PerfMngr_Source_DAI_PerfMngr_Public_ProxyHISMRootActor_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginTest_Performance_Plugins_DAI_PerfMngr_DAI_PerfMngr_Source_DAI_PerfMngr_Public_ProxyHISMRootActor_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
