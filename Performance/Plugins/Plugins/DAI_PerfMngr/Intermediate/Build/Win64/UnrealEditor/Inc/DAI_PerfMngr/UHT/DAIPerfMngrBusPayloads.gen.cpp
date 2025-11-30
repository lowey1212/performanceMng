// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DAI_PerfMngr/Public/DAIPerfMngrBusPayloads.h"
#include "Runtime/GameplayTags/Classes/GameplayTagContainer.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDAIPerfMngrBusPayloads() {}

// Begin Cross Module References
DAI_PERFMNGR_API UScriptStruct* Z_Construct_UScriptStruct_FDAIMessage_PerfProxySwap();
DAI_PERFMNGR_API UScriptStruct* Z_Construct_UScriptStruct_FDAIMessage_PerfSignificanceTier();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UActorComponent_NoRegister();
GAMEPLAYTAGS_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayTag();
UPackage* Z_Construct_UPackage__Script_DAI_PerfMngr();
// End Cross Module References

// Begin ScriptStruct FDAIMessage_PerfProxySwap
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_DAIMessage_PerfProxySwap;
class UScriptStruct* FDAIMessage_PerfProxySwap::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_DAIMessage_PerfProxySwap.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_DAIMessage_PerfProxySwap.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDAIMessage_PerfProxySwap, (UObject*)Z_Construct_UPackage__Script_DAI_PerfMngr(), TEXT("DAIMessage_PerfProxySwap"));
	}
	return Z_Registration_Info_UScriptStruct_DAIMessage_PerfProxySwap.OuterSingleton;
}
template<> DAI_PERFMNGR_API UScriptStruct* StaticStruct<FDAIMessage_PerfProxySwap>()
{
	return FDAIMessage_PerfProxySwap::StaticStruct();
}
struct Z_Construct_UScriptStruct_FDAIMessage_PerfProxySwap_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/DAIPerfMngrBusPayloads.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Component_MetaData[] = {
		{ "Category", "Performance" },
		{ "ModuleRelativePath", "Public/DAIPerfMngrBusPayloads.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_State_MetaData[] = {
		{ "Category", "Performance" },
		{ "ModuleRelativePath", "Public/DAIPerfMngrBusPayloads.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FWeakObjectPropertyParams NewProp_Component;
	static const UECodeGen_Private::FStructPropertyParams NewProp_State;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDAIMessage_PerfProxySwap>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FWeakObjectPropertyParams Z_Construct_UScriptStruct_FDAIMessage_PerfProxySwap_Statics::NewProp_Component = { "Component", nullptr, (EPropertyFlags)0x001400000008001c, UECodeGen_Private::EPropertyGenFlags::WeakObject, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FDAIMessage_PerfProxySwap, Component), Z_Construct_UClass_UActorComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Component_MetaData), NewProp_Component_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FDAIMessage_PerfProxySwap_Statics::NewProp_State = { "State", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FDAIMessage_PerfProxySwap, State), Z_Construct_UScriptStruct_FGameplayTag, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_State_MetaData), NewProp_State_MetaData) }; // 1298103297
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FDAIMessage_PerfProxySwap_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDAIMessage_PerfProxySwap_Statics::NewProp_Component,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDAIMessage_PerfProxySwap_Statics::NewProp_State,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDAIMessage_PerfProxySwap_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FDAIMessage_PerfProxySwap_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_DAI_PerfMngr,
	nullptr,
	&NewStructOps,
	"DAIMessage_PerfProxySwap",
	Z_Construct_UScriptStruct_FDAIMessage_PerfProxySwap_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDAIMessage_PerfProxySwap_Statics::PropPointers),
	sizeof(FDAIMessage_PerfProxySwap),
	alignof(FDAIMessage_PerfProxySwap),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000005),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDAIMessage_PerfProxySwap_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FDAIMessage_PerfProxySwap_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FDAIMessage_PerfProxySwap()
{
	if (!Z_Registration_Info_UScriptStruct_DAIMessage_PerfProxySwap.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_DAIMessage_PerfProxySwap.InnerSingleton, Z_Construct_UScriptStruct_FDAIMessage_PerfProxySwap_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_DAIMessage_PerfProxySwap.InnerSingleton;
}
// End ScriptStruct FDAIMessage_PerfProxySwap

// Begin ScriptStruct FDAIMessage_PerfSignificanceTier
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_DAIMessage_PerfSignificanceTier;
class UScriptStruct* FDAIMessage_PerfSignificanceTier::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_DAIMessage_PerfSignificanceTier.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_DAIMessage_PerfSignificanceTier.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDAIMessage_PerfSignificanceTier, (UObject*)Z_Construct_UPackage__Script_DAI_PerfMngr(), TEXT("DAIMessage_PerfSignificanceTier"));
	}
	return Z_Registration_Info_UScriptStruct_DAIMessage_PerfSignificanceTier.OuterSingleton;
}
template<> DAI_PERFMNGR_API UScriptStruct* StaticStruct<FDAIMessage_PerfSignificanceTier>()
{
	return FDAIMessage_PerfSignificanceTier::StaticStruct();
}
struct Z_Construct_UScriptStruct_FDAIMessage_PerfSignificanceTier_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/DAIPerfMngrBusPayloads.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Actor_MetaData[] = {
		{ "Category", "Performance" },
		{ "ModuleRelativePath", "Public/DAIPerfMngrBusPayloads.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Tier_MetaData[] = {
		{ "Category", "Performance" },
		{ "ModuleRelativePath", "Public/DAIPerfMngrBusPayloads.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FWeakObjectPropertyParams NewProp_Actor;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Tier;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDAIMessage_PerfSignificanceTier>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FWeakObjectPropertyParams Z_Construct_UScriptStruct_FDAIMessage_PerfSignificanceTier_Statics::NewProp_Actor = { "Actor", nullptr, (EPropertyFlags)0x0014000000000014, UECodeGen_Private::EPropertyGenFlags::WeakObject, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FDAIMessage_PerfSignificanceTier, Actor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Actor_MetaData), NewProp_Actor_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FDAIMessage_PerfSignificanceTier_Statics::NewProp_Tier = { "Tier", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FDAIMessage_PerfSignificanceTier, Tier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Tier_MetaData), NewProp_Tier_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FDAIMessage_PerfSignificanceTier_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDAIMessage_PerfSignificanceTier_Statics::NewProp_Actor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDAIMessage_PerfSignificanceTier_Statics::NewProp_Tier,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDAIMessage_PerfSignificanceTier_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FDAIMessage_PerfSignificanceTier_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_DAI_PerfMngr,
	nullptr,
	&NewStructOps,
	"DAIMessage_PerfSignificanceTier",
	Z_Construct_UScriptStruct_FDAIMessage_PerfSignificanceTier_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDAIMessage_PerfSignificanceTier_Statics::PropPointers),
	sizeof(FDAIMessage_PerfSignificanceTier),
	alignof(FDAIMessage_PerfSignificanceTier),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDAIMessage_PerfSignificanceTier_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FDAIMessage_PerfSignificanceTier_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FDAIMessage_PerfSignificanceTier()
{
	if (!Z_Registration_Info_UScriptStruct_DAIMessage_PerfSignificanceTier.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_DAIMessage_PerfSignificanceTier.InnerSingleton, Z_Construct_UScriptStruct_FDAIMessage_PerfSignificanceTier_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_DAIMessage_PerfSignificanceTier.InnerSingleton;
}
// End ScriptStruct FDAIMessage_PerfSignificanceTier

// Begin Registration
struct Z_CompiledInDeferFile_FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAIPerfMngrBusPayloads_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FDAIMessage_PerfProxySwap::StaticStruct, Z_Construct_UScriptStruct_FDAIMessage_PerfProxySwap_Statics::NewStructOps, TEXT("DAIMessage_PerfProxySwap"), &Z_Registration_Info_UScriptStruct_DAIMessage_PerfProxySwap, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDAIMessage_PerfProxySwap), 2295687478U) },
		{ FDAIMessage_PerfSignificanceTier::StaticStruct, Z_Construct_UScriptStruct_FDAIMessage_PerfSignificanceTier_Statics::NewStructOps, TEXT("DAIMessage_PerfSignificanceTier"), &Z_Registration_Info_UScriptStruct_DAIMessage_PerfSignificanceTier, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDAIMessage_PerfSignificanceTier), 2269798140U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAIPerfMngrBusPayloads_h_671711817(TEXT("/Script/DAI_PerfMngr"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAIPerfMngrBusPayloads_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAIPerfMngrBusPayloads_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
