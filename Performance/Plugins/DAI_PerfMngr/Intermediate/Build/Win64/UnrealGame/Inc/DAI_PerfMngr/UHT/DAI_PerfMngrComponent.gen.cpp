// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DAI_PerfMngr/Public/DAI_PerfMngrComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDAI_PerfMngrComponent() {}

// Begin Cross Module References
DAI_PERFMNGR_API UClass* Z_Construct_UClass_UDAI_PerfMngrComponent();
DAI_PERFMNGR_API UClass* Z_Construct_UClass_UDAI_PerfMngrComponent_NoRegister();
DAI_PERFMNGR_API UEnum* Z_Construct_UEnum_DAI_PerfMngr_EPerformanceMode();
DAI_PERFMNGR_API UEnum* Z_Construct_UEnum_DAI_PerfMngr_EProxySwapState();
DAI_PERFMNGR_API UEnum* Z_Construct_UEnum_DAI_PerfMngr_ESuppressionComponentType();
DAI_PERFMNGR_API UFunction* Z_Construct_UDelegateFunction_DAI_PerfMngr_OnProxyEnteredSignature__DelegateSignature();
DAI_PERFMNGR_API UFunction* Z_Construct_UDelegateFunction_DAI_PerfMngr_OnProxyExitedSignature__DelegateSignature();
DAI_PERFMNGR_API UScriptStruct* Z_Construct_UScriptStruct_FComponentSuppressionRule();
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
NIAGARA_API UClass* Z_Construct_UClass_UNiagaraComponent_NoRegister();
NIAGARA_API UClass* Z_Construct_UClass_UNiagaraSystem_NoRegister();
UPackage* Z_Construct_UPackage__Script_DAI_PerfMngr();
// End Cross Module References

// Begin Enum EProxySwapState
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EProxySwapState;
static UEnum* EProxySwapState_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EProxySwapState.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EProxySwapState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_DAI_PerfMngr_EProxySwapState, (UObject*)Z_Construct_UPackage__Script_DAI_PerfMngr(), TEXT("EProxySwapState"));
	}
	return Z_Registration_Info_UEnum_EProxySwapState.OuterSingleton;
}
template<> DAI_PERFMNGR_API UEnum* StaticEnum<EProxySwapState>()
{
	return EProxySwapState_StaticEnum();
}
struct Z_Construct_UEnum_DAI_PerfMngr_EProxySwapState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Active.Name", "EProxySwapState::Active" },
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
		{ "PendingSwapToFull.Name", "EProxySwapState::PendingSwapToFull" },
		{ "PendingSwapToProxy.Name", "EProxySwapState::PendingSwapToProxy" },
		{ "ProxyActive.Name", "EProxySwapState::ProxyActive" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EProxySwapState::Active", (int64)EProxySwapState::Active },
		{ "EProxySwapState::PendingSwapToProxy", (int64)EProxySwapState::PendingSwapToProxy },
		{ "EProxySwapState::ProxyActive", (int64)EProxySwapState::ProxyActive },
		{ "EProxySwapState::PendingSwapToFull", (int64)EProxySwapState::PendingSwapToFull },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_DAI_PerfMngr_EProxySwapState_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_DAI_PerfMngr,
	nullptr,
	"EProxySwapState",
	"EProxySwapState",
	Z_Construct_UEnum_DAI_PerfMngr_EProxySwapState_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_DAI_PerfMngr_EProxySwapState_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_DAI_PerfMngr_EProxySwapState_Statics::Enum_MetaDataParams), Z_Construct_UEnum_DAI_PerfMngr_EProxySwapState_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_DAI_PerfMngr_EProxySwapState()
{
	if (!Z_Registration_Info_UEnum_EProxySwapState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EProxySwapState.InnerSingleton, Z_Construct_UEnum_DAI_PerfMngr_EProxySwapState_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EProxySwapState.InnerSingleton;
}
// End Enum EProxySwapState

// Begin Enum EPerformanceMode
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EPerformanceMode;
static UEnum* EPerformanceMode_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EPerformanceMode.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EPerformanceMode.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_DAI_PerfMngr_EPerformanceMode, (UObject*)Z_Construct_UPackage__Script_DAI_PerfMngr(), TEXT("EPerformanceMode"));
	}
	return Z_Registration_Info_UEnum_EPerformanceMode.OuterSingleton;
}
template<> DAI_PERFMNGR_API UEnum* StaticEnum<EPerformanceMode>()
{
	return EPerformanceMode_StaticEnum();
}
struct Z_Construct_UEnum_DAI_PerfMngr_EPerformanceMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Auto.Name", "EPerformanceMode::Auto" },
		{ "BlueprintType", "true" },
		{ "Full.Name", "EPerformanceMode::Full" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
		{ "Proxy.Name", "EPerformanceMode::Proxy" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EPerformanceMode::Auto", (int64)EPerformanceMode::Auto },
		{ "EPerformanceMode::Full", (int64)EPerformanceMode::Full },
		{ "EPerformanceMode::Proxy", (int64)EPerformanceMode::Proxy },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_DAI_PerfMngr_EPerformanceMode_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_DAI_PerfMngr,
	nullptr,
	"EPerformanceMode",
	"EPerformanceMode",
	Z_Construct_UEnum_DAI_PerfMngr_EPerformanceMode_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_DAI_PerfMngr_EPerformanceMode_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_DAI_PerfMngr_EPerformanceMode_Statics::Enum_MetaDataParams), Z_Construct_UEnum_DAI_PerfMngr_EPerformanceMode_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_DAI_PerfMngr_EPerformanceMode()
{
	if (!Z_Registration_Info_UEnum_EPerformanceMode.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EPerformanceMode.InnerSingleton, Z_Construct_UEnum_DAI_PerfMngr_EPerformanceMode_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EPerformanceMode.InnerSingleton;
}
// End Enum EPerformanceMode

// Begin Enum ESuppressionComponentType
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ESuppressionComponentType;
static UEnum* ESuppressionComponentType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ESuppressionComponentType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ESuppressionComponentType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_DAI_PerfMngr_ESuppressionComponentType, (UObject*)Z_Construct_UPackage__Script_DAI_PerfMngr(), TEXT("ESuppressionComponentType"));
	}
	return Z_Registration_Info_UEnum_ESuppressionComponentType.OuterSingleton;
}
template<> DAI_PERFMNGR_API UEnum* StaticEnum<ESuppressionComponentType>()
{
	return ESuppressionComponentType_StaticEnum();
}
struct Z_Construct_UEnum_DAI_PerfMngr_ESuppressionComponentType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "AbilitySystem.Name", "ESuppressionComponentType::AbilitySystem" },
		{ "Audio.Name", "ESuppressionComponentType::Audio" },
		{ "BlueprintType", "true" },
		{ "CustomTag.Name", "ESuppressionComponentType::CustomTag" },
		{ "Hair.Name", "ESuppressionComponentType::Hair" },
		{ "Light.Name", "ESuppressionComponentType::Light" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
		{ "MotionWarping.Name", "ESuppressionComponentType::MotionWarping" },
		{ "Niagara.Name", "ESuppressionComponentType::Niagara" },
		{ "Physics.Name", "ESuppressionComponentType::Physics" },
		{ "Widget.Name", "ESuppressionComponentType::Widget" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ESuppressionComponentType::Audio", (int64)ESuppressionComponentType::Audio },
		{ "ESuppressionComponentType::Niagara", (int64)ESuppressionComponentType::Niagara },
		{ "ESuppressionComponentType::AbilitySystem", (int64)ESuppressionComponentType::AbilitySystem },
		{ "ESuppressionComponentType::Light", (int64)ESuppressionComponentType::Light },
		{ "ESuppressionComponentType::Widget", (int64)ESuppressionComponentType::Widget },
		{ "ESuppressionComponentType::MotionWarping", (int64)ESuppressionComponentType::MotionWarping },
		{ "ESuppressionComponentType::Hair", (int64)ESuppressionComponentType::Hair },
		{ "ESuppressionComponentType::Physics", (int64)ESuppressionComponentType::Physics },
		{ "ESuppressionComponentType::CustomTag", (int64)ESuppressionComponentType::CustomTag },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_DAI_PerfMngr_ESuppressionComponentType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_DAI_PerfMngr,
	nullptr,
	"ESuppressionComponentType",
	"ESuppressionComponentType",
	Z_Construct_UEnum_DAI_PerfMngr_ESuppressionComponentType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_DAI_PerfMngr_ESuppressionComponentType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_DAI_PerfMngr_ESuppressionComponentType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_DAI_PerfMngr_ESuppressionComponentType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_DAI_PerfMngr_ESuppressionComponentType()
{
	if (!Z_Registration_Info_UEnum_ESuppressionComponentType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ESuppressionComponentType.InnerSingleton, Z_Construct_UEnum_DAI_PerfMngr_ESuppressionComponentType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ESuppressionComponentType.InnerSingleton;
}
// End Enum ESuppressionComponentType

// Begin ScriptStruct FComponentSuppressionRule
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_ComponentSuppressionRule;
class UScriptStruct* FComponentSuppressionRule::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_ComponentSuppressionRule.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_ComponentSuppressionRule.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FComponentSuppressionRule, (UObject*)Z_Construct_UPackage__Script_DAI_PerfMngr(), TEXT("ComponentSuppressionRule"));
	}
	return Z_Registration_Info_UScriptStruct_ComponentSuppressionRule.OuterSingleton;
}
template<> DAI_PERFMNGR_API UScriptStruct* StaticStruct<FComponentSuppressionRule>()
{
	return FComponentSuppressionRule::StaticStruct();
}
struct Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComponentType_MetaData[] = {
		{ "Category", "Suppression" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComponentTag_MetaData[] = {
		{ "Category", "Suppression" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NameContains_MetaData[] = {
		{ "Category", "Suppression" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SuppressBelowSignificance_MetaData[] = {
		{ "Category", "Suppression" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_ComponentType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ComponentType;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ComponentTag;
	static const UECodeGen_Private::FStrPropertyParams NewProp_NameContains;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SuppressBelowSignificance;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FComponentSuppressionRule>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics::NewProp_ComponentType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics::NewProp_ComponentType = { "ComponentType", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FComponentSuppressionRule, ComponentType), Z_Construct_UEnum_DAI_PerfMngr_ESuppressionComponentType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComponentType_MetaData), NewProp_ComponentType_MetaData) }; // 2802195998
const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics::NewProp_ComponentTag = { "ComponentTag", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FComponentSuppressionRule, ComponentTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComponentTag_MetaData), NewProp_ComponentTag_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics::NewProp_NameContains = { "NameContains", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FComponentSuppressionRule, NameContains), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NameContains_MetaData), NewProp_NameContains_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics::NewProp_SuppressBelowSignificance = { "SuppressBelowSignificance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FComponentSuppressionRule, SuppressBelowSignificance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SuppressBelowSignificance_MetaData), NewProp_SuppressBelowSignificance_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics::NewProp_ComponentType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics::NewProp_ComponentType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics::NewProp_ComponentTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics::NewProp_NameContains,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics::NewProp_SuppressBelowSignificance,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_DAI_PerfMngr,
	nullptr,
	&NewStructOps,
	"ComponentSuppressionRule",
	Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics::PropPointers),
	sizeof(FComponentSuppressionRule),
	alignof(FComponentSuppressionRule),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FComponentSuppressionRule()
{
	if (!Z_Registration_Info_UScriptStruct_ComponentSuppressionRule.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_ComponentSuppressionRule.InnerSingleton, Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_ComponentSuppressionRule.InnerSingleton;
}
// End ScriptStruct FComponentSuppressionRule

// Begin Delegate FOnProxyEnteredSignature
struct Z_Construct_UDelegateFunction_DAI_PerfMngr_OnProxyEnteredSignature__DelegateSignature_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_DAI_PerfMngr_OnProxyEnteredSignature__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_DAI_PerfMngr, nullptr, "OnProxyEnteredSignature__DelegateSignature", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_DAI_PerfMngr_OnProxyEnteredSignature__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_DAI_PerfMngr_OnProxyEnteredSignature__DelegateSignature_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UDelegateFunction_DAI_PerfMngr_OnProxyEnteredSignature__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_DAI_PerfMngr_OnProxyEnteredSignature__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnProxyEnteredSignature_DelegateWrapper(const FMulticastScriptDelegate& OnProxyEnteredSignature)
{
	OnProxyEnteredSignature.ProcessMulticastDelegate<UObject>(NULL);
}
// End Delegate FOnProxyEnteredSignature

// Begin Delegate FOnProxyExitedSignature
struct Z_Construct_UDelegateFunction_DAI_PerfMngr_OnProxyExitedSignature__DelegateSignature_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_DAI_PerfMngr_OnProxyExitedSignature__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_DAI_PerfMngr, nullptr, "OnProxyExitedSignature__DelegateSignature", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_DAI_PerfMngr_OnProxyExitedSignature__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_DAI_PerfMngr_OnProxyExitedSignature__DelegateSignature_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UDelegateFunction_DAI_PerfMngr_OnProxyExitedSignature__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_DAI_PerfMngr_OnProxyExitedSignature__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnProxyExitedSignature_DelegateWrapper(const FMulticastScriptDelegate& OnProxyExitedSignature)
{
	OnProxyExitedSignature.ProcessMulticastDelegate<UObject>(NULL);
}
// End Delegate FOnProxyExitedSignature

// Begin Class UDAI_PerfMngrComponent Function ForceSwapToFull
struct Z_Construct_UFunction_UDAI_PerfMngrComponent_ForceSwapToFull_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDAI_PerfMngrComponent_ForceSwapToFull_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDAI_PerfMngrComponent, nullptr, "ForceSwapToFull", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDAI_PerfMngrComponent_ForceSwapToFull_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDAI_PerfMngrComponent_ForceSwapToFull_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UDAI_PerfMngrComponent_ForceSwapToFull()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDAI_PerfMngrComponent_ForceSwapToFull_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDAI_PerfMngrComponent::execForceSwapToFull)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ForceSwapToFull();
	P_NATIVE_END;
}
// End Class UDAI_PerfMngrComponent Function ForceSwapToFull

// Begin Class UDAI_PerfMngrComponent Function ForceSwapToProxy
struct Z_Construct_UFunction_UDAI_PerfMngrComponent_ForceSwapToProxy_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDAI_PerfMngrComponent_ForceSwapToProxy_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDAI_PerfMngrComponent, nullptr, "ForceSwapToProxy", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDAI_PerfMngrComponent_ForceSwapToProxy_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDAI_PerfMngrComponent_ForceSwapToProxy_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UDAI_PerfMngrComponent_ForceSwapToProxy()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDAI_PerfMngrComponent_ForceSwapToProxy_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDAI_PerfMngrComponent::execForceSwapToProxy)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ForceSwapToProxy();
	P_NATIVE_END;
}
// End Class UDAI_PerfMngrComponent Function ForceSwapToProxy

// Begin Class UDAI_PerfMngrComponent Function GetCurrentProxyState
struct Z_Construct_UFunction_UDAI_PerfMngrComponent_GetCurrentProxyState_Statics
{
	struct DAI_PerfMngrComponent_eventGetCurrentProxyState_Parms
	{
		EProxySwapState ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UDAI_PerfMngrComponent_GetCurrentProxyState_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UDAI_PerfMngrComponent_GetCurrentProxyState_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(DAI_PerfMngrComponent_eventGetCurrentProxyState_Parms, ReturnValue), Z_Construct_UEnum_DAI_PerfMngr_EProxySwapState, METADATA_PARAMS(0, nullptr) }; // 2098493345
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDAI_PerfMngrComponent_GetCurrentProxyState_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDAI_PerfMngrComponent_GetCurrentProxyState_Statics::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDAI_PerfMngrComponent_GetCurrentProxyState_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UDAI_PerfMngrComponent_GetCurrentProxyState_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDAI_PerfMngrComponent_GetCurrentProxyState_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDAI_PerfMngrComponent, nullptr, "GetCurrentProxyState", nullptr, nullptr, Z_Construct_UFunction_UDAI_PerfMngrComponent_GetCurrentProxyState_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UDAI_PerfMngrComponent_GetCurrentProxyState_Statics::PropPointers), sizeof(Z_Construct_UFunction_UDAI_PerfMngrComponent_GetCurrentProxyState_Statics::DAI_PerfMngrComponent_eventGetCurrentProxyState_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDAI_PerfMngrComponent_GetCurrentProxyState_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDAI_PerfMngrComponent_GetCurrentProxyState_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UDAI_PerfMngrComponent_GetCurrentProxyState_Statics::DAI_PerfMngrComponent_eventGetCurrentProxyState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDAI_PerfMngrComponent_GetCurrentProxyState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDAI_PerfMngrComponent_GetCurrentProxyState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDAI_PerfMngrComponent::execGetCurrentProxyState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(EProxySwapState*)Z_Param__Result=P_THIS->GetCurrentProxyState();
	P_NATIVE_END;
}
// End Class UDAI_PerfMngrComponent Function GetCurrentProxyState

// Begin Class UDAI_PerfMngrComponent Function IsUsingProxy
struct Z_Construct_UFunction_UDAI_PerfMngrComponent_IsUsingProxy_Statics
{
	struct DAI_PerfMngrComponent_eventIsUsingProxy_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UDAI_PerfMngrComponent_IsUsingProxy_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((DAI_PerfMngrComponent_eventIsUsingProxy_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UDAI_PerfMngrComponent_IsUsingProxy_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(DAI_PerfMngrComponent_eventIsUsingProxy_Parms), &Z_Construct_UFunction_UDAI_PerfMngrComponent_IsUsingProxy_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDAI_PerfMngrComponent_IsUsingProxy_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDAI_PerfMngrComponent_IsUsingProxy_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UDAI_PerfMngrComponent_IsUsingProxy_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDAI_PerfMngrComponent_IsUsingProxy_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDAI_PerfMngrComponent, nullptr, "IsUsingProxy", nullptr, nullptr, Z_Construct_UFunction_UDAI_PerfMngrComponent_IsUsingProxy_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UDAI_PerfMngrComponent_IsUsingProxy_Statics::PropPointers), sizeof(Z_Construct_UFunction_UDAI_PerfMngrComponent_IsUsingProxy_Statics::DAI_PerfMngrComponent_eventIsUsingProxy_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDAI_PerfMngrComponent_IsUsingProxy_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDAI_PerfMngrComponent_IsUsingProxy_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UDAI_PerfMngrComponent_IsUsingProxy_Statics::DAI_PerfMngrComponent_eventIsUsingProxy_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDAI_PerfMngrComponent_IsUsingProxy()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDAI_PerfMngrComponent_IsUsingProxy_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDAI_PerfMngrComponent::execIsUsingProxy)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsUsingProxy();
	P_NATIVE_END;
}
// End Class UDAI_PerfMngrComponent Function IsUsingProxy

// Begin Class UDAI_PerfMngrComponent Function SwapToFull
struct Z_Construct_UFunction_UDAI_PerfMngrComponent_SwapToFull_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDAI_PerfMngrComponent_SwapToFull_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDAI_PerfMngrComponent, nullptr, "SwapToFull", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDAI_PerfMngrComponent_SwapToFull_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDAI_PerfMngrComponent_SwapToFull_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UDAI_PerfMngrComponent_SwapToFull()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDAI_PerfMngrComponent_SwapToFull_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDAI_PerfMngrComponent::execSwapToFull)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SwapToFull();
	P_NATIVE_END;
}
// End Class UDAI_PerfMngrComponent Function SwapToFull

// Begin Class UDAI_PerfMngrComponent Function SwapToProxy
struct Z_Construct_UFunction_UDAI_PerfMngrComponent_SwapToProxy_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "PerfMngr|Proxy" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Proxy management\n" },
#endif
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Proxy management" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDAI_PerfMngrComponent_SwapToProxy_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDAI_PerfMngrComponent, nullptr, "SwapToProxy", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UDAI_PerfMngrComponent_SwapToProxy_Statics::Function_MetaDataParams), Z_Construct_UFunction_UDAI_PerfMngrComponent_SwapToProxy_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UDAI_PerfMngrComponent_SwapToProxy()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDAI_PerfMngrComponent_SwapToProxy_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UDAI_PerfMngrComponent::execSwapToProxy)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SwapToProxy();
	P_NATIVE_END;
}
// End Class UDAI_PerfMngrComponent Function SwapToProxy

// Begin Class UDAI_PerfMngrComponent
void UDAI_PerfMngrComponent::StaticRegisterNativesUDAI_PerfMngrComponent()
{
	UClass* Class = UDAI_PerfMngrComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ForceSwapToFull", &UDAI_PerfMngrComponent::execForceSwapToFull },
		{ "ForceSwapToProxy", &UDAI_PerfMngrComponent::execForceSwapToProxy },
		{ "GetCurrentProxyState", &UDAI_PerfMngrComponent::execGetCurrentProxyState },
		{ "IsUsingProxy", &UDAI_PerfMngrComponent::execIsUsingProxy },
		{ "SwapToFull", &UDAI_PerfMngrComponent::execSwapToFull },
		{ "SwapToProxy", &UDAI_PerfMngrComponent::execSwapToProxy },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UDAI_PerfMngrComponent);
UClass* Z_Construct_UClass_UDAI_PerfMngrComponent_NoRegister()
{
	return UDAI_PerfMngrComponent::StaticClass();
}
struct Z_Construct_UClass_UDAI_PerfMngrComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "DAI_PerfMngrComponent.h" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDistance_MetaData[] = {
		{ "Category", "PerfMngr" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Configurables\n" },
#endif
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Configurables" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TickEvaluationRate_MetaData[] = {
		{ "Category", "PerfMngr" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TickIntervalHigh_MetaData[] = {
		{ "Category", "PerfMngr" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TickIntervalLow_MetaData[] = {
		{ "Category", "PerfMngr" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinTickClamp_MetaData[] = {
		{ "Category", "PerfMngr" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxTickClamp_MetaData[] = {
		{ "Category", "PerfMngr" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAffectAbilitySystemTick_MetaData[] = {
		{ "Category", "PerfMngr" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableDebugLog_MetaData[] = {
		{ "Category", "PerfMngr|Debug" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bPrintSignificanceToScreen_MetaData[] = {
		{ "Category", "PerfMngr|Debug" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDrawDebugProxySphere_MetaData[] = {
		{ "Category", "PerfMngr|Debug" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProxyDebugSphereDuration_MetaData[] = {
		{ "Category", "PerfMngr|Debug" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProxyStaticMesh_MetaData[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProxyHairMesh_MetaData[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProxyBillboardMesh_MetaData[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProxyParticleEffect_MetaData[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Category_MetaData[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bColorizeBySignificance_MetaData[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComponentSuppressionRules_MetaData[] = {
		{ "Category", "PerfMngr|Suppression" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProxyEnterThreshold_MetaData[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProxyExitThreshold_MetaData[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProxySwapDelay_MetaData[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseHISMProxyBatching_MetaData[] = {
		{ "Category", "PerfMngr|Proxy" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// HISM batching variables\n" },
#endif
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "HISM batching variables" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProxyMeshComponent_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Proxy components\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Proxy components" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProxyHairMeshComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BillboardMeshComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProxyEffectComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnProxyEntered_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Events\n" },
#endif
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Events" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnProxyExited_MetaData[] = {
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TickEvaluationRate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TickIntervalHigh;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TickIntervalLow;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinTickClamp;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxTickClamp;
	static void NewProp_bAffectAbilitySystemTick_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAffectAbilitySystemTick;
	static void NewProp_bEnableDebugLog_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableDebugLog;
	static void NewProp_bPrintSignificanceToScreen_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bPrintSignificanceToScreen;
	static void NewProp_bDrawDebugProxySphere_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDrawDebugProxySphere;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ProxyDebugSphereDuration;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ProxyStaticMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ProxyHairMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ProxyBillboardMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ProxyParticleEffect;
	static const UECodeGen_Private::FNamePropertyParams NewProp_Category;
	static void NewProp_bColorizeBySignificance_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bColorizeBySignificance;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ComponentSuppressionRules_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ComponentSuppressionRules;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ProxyEnterThreshold;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ProxyExitThreshold;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ProxySwapDelay;
	static void NewProp_bUseHISMProxyBatching_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseHISMProxyBatching;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ProxyMeshComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ProxyHairMeshComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BillboardMeshComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ProxyEffectComponent;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnProxyEntered;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnProxyExited;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDAI_PerfMngrComponent_ForceSwapToFull, "ForceSwapToFull" }, // 574982052
		{ &Z_Construct_UFunction_UDAI_PerfMngrComponent_ForceSwapToProxy, "ForceSwapToProxy" }, // 671625145
		{ &Z_Construct_UFunction_UDAI_PerfMngrComponent_GetCurrentProxyState, "GetCurrentProxyState" }, // 110079093
		{ &Z_Construct_UFunction_UDAI_PerfMngrComponent_IsUsingProxy, "IsUsingProxy" }, // 4048003358
		{ &Z_Construct_UFunction_UDAI_PerfMngrComponent_SwapToFull, "SwapToFull" }, // 589692831
		{ &Z_Construct_UFunction_UDAI_PerfMngrComponent_SwapToProxy, "SwapToProxy" }, // 210260693
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDAI_PerfMngrComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_MaxDistance = { "MaxDistance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, MaxDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDistance_MetaData), NewProp_MaxDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_TickEvaluationRate = { "TickEvaluationRate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, TickEvaluationRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TickEvaluationRate_MetaData), NewProp_TickEvaluationRate_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_TickIntervalHigh = { "TickIntervalHigh", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, TickIntervalHigh), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TickIntervalHigh_MetaData), NewProp_TickIntervalHigh_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_TickIntervalLow = { "TickIntervalLow", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, TickIntervalLow), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TickIntervalLow_MetaData), NewProp_TickIntervalLow_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_MinTickClamp = { "MinTickClamp", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, MinTickClamp), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinTickClamp_MetaData), NewProp_MinTickClamp_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_MaxTickClamp = { "MaxTickClamp", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, MaxTickClamp), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxTickClamp_MetaData), NewProp_MaxTickClamp_MetaData) };
void Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bAffectAbilitySystemTick_SetBit(void* Obj)
{
	((UDAI_PerfMngrComponent*)Obj)->bAffectAbilitySystemTick = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bAffectAbilitySystemTick = { "bAffectAbilitySystemTick", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UDAI_PerfMngrComponent), &Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bAffectAbilitySystemTick_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAffectAbilitySystemTick_MetaData), NewProp_bAffectAbilitySystemTick_MetaData) };
void Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bEnableDebugLog_SetBit(void* Obj)
{
	((UDAI_PerfMngrComponent*)Obj)->bEnableDebugLog = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bEnableDebugLog = { "bEnableDebugLog", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UDAI_PerfMngrComponent), &Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bEnableDebugLog_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableDebugLog_MetaData), NewProp_bEnableDebugLog_MetaData) };
void Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bPrintSignificanceToScreen_SetBit(void* Obj)
{
	((UDAI_PerfMngrComponent*)Obj)->bPrintSignificanceToScreen = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bPrintSignificanceToScreen = { "bPrintSignificanceToScreen", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UDAI_PerfMngrComponent), &Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bPrintSignificanceToScreen_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bPrintSignificanceToScreen_MetaData), NewProp_bPrintSignificanceToScreen_MetaData) };
void Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bDrawDebugProxySphere_SetBit(void* Obj)
{
	((UDAI_PerfMngrComponent*)Obj)->bDrawDebugProxySphere = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bDrawDebugProxySphere = { "bDrawDebugProxySphere", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UDAI_PerfMngrComponent), &Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bDrawDebugProxySphere_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDrawDebugProxySphere_MetaData), NewProp_bDrawDebugProxySphere_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyDebugSphereDuration = { "ProxyDebugSphereDuration", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, ProxyDebugSphereDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProxyDebugSphereDuration_MetaData), NewProp_ProxyDebugSphereDuration_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyStaticMesh = { "ProxyStaticMesh", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, ProxyStaticMesh), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProxyStaticMesh_MetaData), NewProp_ProxyStaticMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyHairMesh = { "ProxyHairMesh", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, ProxyHairMesh), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProxyHairMesh_MetaData), NewProp_ProxyHairMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyBillboardMesh = { "ProxyBillboardMesh", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, ProxyBillboardMesh), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProxyBillboardMesh_MetaData), NewProp_ProxyBillboardMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyParticleEffect = { "ProxyParticleEffect", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, ProxyParticleEffect), Z_Construct_UClass_UNiagaraSystem_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProxyParticleEffect_MetaData), NewProp_ProxyParticleEffect_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, Category), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Category_MetaData), NewProp_Category_MetaData) };
void Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bColorizeBySignificance_SetBit(void* Obj)
{
	((UDAI_PerfMngrComponent*)Obj)->bColorizeBySignificance = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bColorizeBySignificance = { "bColorizeBySignificance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UDAI_PerfMngrComponent), &Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bColorizeBySignificance_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bColorizeBySignificance_MetaData), NewProp_bColorizeBySignificance_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ComponentSuppressionRules_Inner = { "ComponentSuppressionRules", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FComponentSuppressionRule, METADATA_PARAMS(0, nullptr) }; // 568929615
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ComponentSuppressionRules = { "ComponentSuppressionRules", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, ComponentSuppressionRules), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComponentSuppressionRules_MetaData), NewProp_ComponentSuppressionRules_MetaData) }; // 568929615
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyEnterThreshold = { "ProxyEnterThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, ProxyEnterThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProxyEnterThreshold_MetaData), NewProp_ProxyEnterThreshold_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyExitThreshold = { "ProxyExitThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, ProxyExitThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProxyExitThreshold_MetaData), NewProp_ProxyExitThreshold_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxySwapDelay = { "ProxySwapDelay", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, ProxySwapDelay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProxySwapDelay_MetaData), NewProp_ProxySwapDelay_MetaData) };
void Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bUseHISMProxyBatching_SetBit(void* Obj)
{
	((UDAI_PerfMngrComponent*)Obj)->bUseHISMProxyBatching = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bUseHISMProxyBatching = { "bUseHISMProxyBatching", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UDAI_PerfMngrComponent), &Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bUseHISMProxyBatching_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseHISMProxyBatching_MetaData), NewProp_bUseHISMProxyBatching_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyMeshComponent = { "ProxyMeshComponent", nullptr, (EPropertyFlags)0x0010000000082008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, ProxyMeshComponent), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProxyMeshComponent_MetaData), NewProp_ProxyMeshComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyHairMeshComponent = { "ProxyHairMeshComponent", nullptr, (EPropertyFlags)0x0010000000082008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, ProxyHairMeshComponent), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProxyHairMeshComponent_MetaData), NewProp_ProxyHairMeshComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_BillboardMeshComponent = { "BillboardMeshComponent", nullptr, (EPropertyFlags)0x0010000000082008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, BillboardMeshComponent), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BillboardMeshComponent_MetaData), NewProp_BillboardMeshComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyEffectComponent = { "ProxyEffectComponent", nullptr, (EPropertyFlags)0x0010000000082008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, ProxyEffectComponent), Z_Construct_UClass_UNiagaraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProxyEffectComponent_MetaData), NewProp_ProxyEffectComponent_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_OnProxyEntered = { "OnProxyEntered", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, OnProxyEntered), Z_Construct_UDelegateFunction_DAI_PerfMngr_OnProxyEnteredSignature__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnProxyEntered_MetaData), NewProp_OnProxyEntered_MetaData) }; // 3185369196
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_OnProxyExited = { "OnProxyExited", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, OnProxyExited), Z_Construct_UDelegateFunction_DAI_PerfMngr_OnProxyExitedSignature__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnProxyExited_MetaData), NewProp_OnProxyExited_MetaData) }; // 2929129087
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_MaxDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_TickEvaluationRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_TickIntervalHigh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_TickIntervalLow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_MinTickClamp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_MaxTickClamp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bAffectAbilitySystemTick,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bEnableDebugLog,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bPrintSignificanceToScreen,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bDrawDebugProxySphere,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyDebugSphereDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyStaticMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyHairMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyBillboardMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyParticleEffect,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_Category,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bColorizeBySignificance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ComponentSuppressionRules_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ComponentSuppressionRules,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyEnterThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyExitThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxySwapDelay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bUseHISMProxyBatching,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyMeshComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyHairMeshComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_BillboardMeshComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyEffectComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_OnProxyEntered,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_OnProxyExited,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_DAI_PerfMngr,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::ClassParams = {
	&UDAI_PerfMngrComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UDAI_PerfMngrComponent()
{
	if (!Z_Registration_Info_UClass_UDAI_PerfMngrComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDAI_PerfMngrComponent.OuterSingleton, Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UDAI_PerfMngrComponent.OuterSingleton;
}
template<> DAI_PERFMNGR_API UClass* StaticClass<UDAI_PerfMngrComponent>()
{
	return UDAI_PerfMngrComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UDAI_PerfMngrComponent);
UDAI_PerfMngrComponent::~UDAI_PerfMngrComponent() {}
// End Class UDAI_PerfMngrComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_DAIExampleProject_5_5_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EProxySwapState_StaticEnum, TEXT("EProxySwapState"), &Z_Registration_Info_UEnum_EProxySwapState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2098493345U) },
		{ EPerformanceMode_StaticEnum, TEXT("EPerformanceMode"), &Z_Registration_Info_UEnum_EPerformanceMode, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1163164187U) },
		{ ESuppressionComponentType_StaticEnum, TEXT("ESuppressionComponentType"), &Z_Registration_Info_UEnum_ESuppressionComponentType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2802195998U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FComponentSuppressionRule::StaticStruct, Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics::NewStructOps, TEXT("ComponentSuppressionRule"), &Z_Registration_Info_UScriptStruct_ComponentSuppressionRule, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FComponentSuppressionRule), 568929615U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDAI_PerfMngrComponent, UDAI_PerfMngrComponent::StaticClass, TEXT("UDAI_PerfMngrComponent"), &Z_Registration_Info_UClass_UDAI_PerfMngrComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDAI_PerfMngrComponent), 2478445233U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_DAIExampleProject_5_5_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_3245078926(TEXT("/Script/DAI_PerfMngr"),
	Z_CompiledInDeferFile_FID_DAIExampleProject_5_5_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_DAIExampleProject_5_5_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_DAIExampleProject_5_5_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_DAIExampleProject_5_5_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_DAIExampleProject_5_5_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_DAIExampleProject_5_5_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
