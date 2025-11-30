// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DAI_PerfMngr/Public/DAI_ProxyHISMManager.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDAI_ProxyHISMManager() {}

// Begin Cross Module References
DAI_PERFMNGR_API UClass* Z_Construct_UClass_UDAI_ProxyHISMManager();
DAI_PERFMNGR_API UClass* Z_Construct_UClass_UDAI_ProxyHISMManager_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UHierarchicalInstancedStaticMeshComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem();
UPackage* Z_Construct_UPackage__Script_DAI_PerfMngr();
// End Cross Module References

// Begin Class UDAI_ProxyHISMManager Function PrintAllHISMDebugInfo
struct Z_Construct_UFunction_UDAI_ProxyHISMManager_PrintAllHISMDebugInfo_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Debug" },
		{ "ModuleRelativePath", "Public/DAI_ProxyHISMManager.h" },
		{ "ToolTip", "Logs all proxy HISM components and their instance counts." },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDAI_ProxyHISMManager_PrintAllHISMDebugInfo_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDAI_ProxyHISMManager, nullptr, "PrintAllHISMDebugInfo", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDAI_ProxyHISMManager_PrintAllHISMDebugInfo_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDAI_ProxyHISMManager_PrintAllHISMDebugInfo_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UDAI_ProxyHISMManager_PrintAllHISMDebugInfo()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDAI_ProxyHISMManager_PrintAllHISMDebugInfo_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDAI_ProxyHISMManager::execPrintAllHISMDebugInfo)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->PrintAllHISMDebugInfo();
	P_NATIVE_END;
}
// End Class UDAI_ProxyHISMManager Function PrintAllHISMDebugInfo

// Begin Class UDAI_ProxyHISMManager
void UDAI_ProxyHISMManager::StaticRegisterNativesUDAI_ProxyHISMManager()
{
	UClass* Class = UDAI_ProxyHISMManager::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "PrintAllHISMDebugInfo", &UDAI_ProxyHISMManager::execPrintAllHISMDebugInfo },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UDAI_ProxyHISMManager);
UClass* Z_Construct_UClass_UDAI_ProxyHISMManager_NoRegister()
{
	return UDAI_ProxyHISMManager::StaticClass();
}
struct Z_Construct_UClass_UDAI_ProxyHISMManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "Comment", "/**\n * @brief Manages all proxy HISM (Hierarchical Instanced Static Mesh) components by tag.\n * Plain English: batches lots of the same proxy meshes into one draw call to save GPU time.\n */" },
		{ "IncludePath", "DAI_ProxyHISMManager.h" },
		{ "ModuleRelativePath", "Public/DAI_ProxyHISMManager.h" },
		{ "ToolTip", "@brief Manages all proxy HISM (Hierarchical Instanced Static Mesh) components by tag.\nPlain English: batches lots of the same proxy meshes into one draw call to save GPU time." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BatchedAddSize_MetaData[] = {
		{ "Category", "ProxyBatching" },
		{ "ClampMax", "1000" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/DAI_ProxyHISMManager.h" },
		{ "ToolTip", "How many instances to add to each HISM per tick by default (prevents hitching when spawning many)." },
		{ "UIMax", "200" },
		{ "UIMin", "1" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TagToHISM_MetaData[] = {
		{ "Comment", "/** Mapping from tag to the HISM component that holds those instances. */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DAI_ProxyHISMManager.h" },
		{ "ToolTip", "Mapping from tag to the HISM component that holds those instances." },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_BatchedAddSize;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TagToHISM_ValueProp;
	static const UECodeGen_Private::FNamePropertyParams NewProp_TagToHISM_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_TagToHISM;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDAI_ProxyHISMManager_PrintAllHISMDebugInfo, "PrintAllHISMDebugInfo" }, // 3299683259
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDAI_ProxyHISMManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UDAI_ProxyHISMManager_Statics::NewProp_BatchedAddSize = { "BatchedAddSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_ProxyHISMManager, BatchedAddSize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BatchedAddSize_MetaData), NewProp_BatchedAddSize_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDAI_ProxyHISMManager_Statics::NewProp_TagToHISM_ValueProp = { "TagToHISM", nullptr, (EPropertyFlags)0x0000000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, Z_Construct_UClass_UHierarchicalInstancedStaticMeshComponent_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UDAI_ProxyHISMManager_Statics::NewProp_TagToHISM_Key_KeyProp = { "TagToHISM_Key", nullptr, (EPropertyFlags)0x0000000000080008, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_UDAI_ProxyHISMManager_Statics::NewProp_TagToHISM = { "TagToHISM", nullptr, (EPropertyFlags)0x0020088000000008, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_ProxyHISMManager, TagToHISM), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TagToHISM_MetaData), NewProp_TagToHISM_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UDAI_ProxyHISMManager_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_ProxyHISMManager_Statics::NewProp_BatchedAddSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_ProxyHISMManager_Statics::NewProp_TagToHISM_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_ProxyHISMManager_Statics::NewProp_TagToHISM_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_ProxyHISMManager_Statics::NewProp_TagToHISM,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDAI_ProxyHISMManager_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UDAI_ProxyHISMManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UWorldSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_DAI_PerfMngr,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDAI_ProxyHISMManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UDAI_ProxyHISMManager_Statics::ClassParams = {
	&UDAI_ProxyHISMManager::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UDAI_ProxyHISMManager_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UDAI_ProxyHISMManager_Statics::PropPointers),
	0,
	0x009000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UDAI_ProxyHISMManager_Statics::Class_MetaDataParams), Z_Construct_UClass_UDAI_ProxyHISMManager_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UDAI_ProxyHISMManager()
{
	if (!Z_Registration_Info_UClass_UDAI_ProxyHISMManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDAI_ProxyHISMManager.OuterSingleton, Z_Construct_UClass_UDAI_ProxyHISMManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UDAI_ProxyHISMManager.OuterSingleton;
}
template<> DAI_PERFMNGR_API UClass* StaticClass<UDAI_ProxyHISMManager>()
{
	return UDAI_ProxyHISMManager::StaticClass();
}
UDAI_ProxyHISMManager::UDAI_ProxyHISMManager() {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UDAI_ProxyHISMManager);
UDAI_ProxyHISMManager::~UDAI_ProxyHISMManager() {}
// End Class UDAI_ProxyHISMManager

// Begin Registration
struct Z_CompiledInDeferFile_FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_ProxyHISMManager_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDAI_ProxyHISMManager, UDAI_ProxyHISMManager::StaticClass, TEXT("UDAI_ProxyHISMManager"), &Z_Registration_Info_UClass_UDAI_ProxyHISMManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDAI_ProxyHISMManager), 1163589703U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_ProxyHISMManager_h_2853999966(TEXT("/Script/DAI_PerfMngr"),
	Z_CompiledInDeferFile_FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_ProxyHISMManager_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_ProxyHISMManager_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
