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
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
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
		{ "Active.Comment", "/** Full, high\xe2\x80\x91quality representation is active. */" },
		{ "Active.Name", "EProxySwapState::Active" },
		{ "Active.ToolTip", "Full, high\xe2\x80\x91quality representation is active." },
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * @brief Component that automatically swaps an actor between \"full\" and \"proxy\" representations\n * based on how important (significant) the actor is to the player (usually how close it is).\n *\n * In plain English: this speeds things up by showing cheap stand\xe2\x80\x91ins (proxies) for far\xe2\x80\x91""away actors\n * and the full, expensive version when the actor is close enough to matter.\n */" },
#endif
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
		{ "PendingSwapToFull.Comment", "/** Returning from proxy to full representation, swap is pending. */" },
		{ "PendingSwapToFull.Name", "EProxySwapState::PendingSwapToFull" },
		{ "PendingSwapToFull.ToolTip", "Returning from proxy to full representation, swap is pending." },
		{ "PendingSwapToProxy.Comment", "/** A proxy is about to be used, swap is pending. */" },
		{ "PendingSwapToProxy.Name", "EProxySwapState::PendingSwapToProxy" },
		{ "PendingSwapToProxy.ToolTip", "A proxy is about to be used, swap is pending." },
		{ "ProxyActive.Comment", "/** Proxy (cheap stand\xe2\x80\x91in) is currently active. */" },
		{ "ProxyActive.Name", "EProxySwapState::ProxyActive" },
		{ "ProxyActive.ToolTip", "Proxy (cheap stand\xe2\x80\x91in) is currently active." },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "@brief Component that automatically swaps an actor between \"full\" and \"proxy\" representations\nbased on how important (significant) the actor is to the player (usually how close it is).\n\nIn plain English: this speeds things up by showing cheap stand\xe2\x80\x91ins (proxies) for far\xe2\x80\x91""away actors\nand the full, expensive version when the actor is close enough to matter." },
#endif
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
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * @brief How the component should decide what to show.\n * Auto = pick for me. Full = always full quality. Proxy = always proxy.\n */" },
#endif
		{ "Full.Name", "EPerformanceMode::Full" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
		{ "Proxy.Name", "EPerformanceMode::Proxy" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "@brief How the component should decide what to show.\nAuto = pick for me. Full = always full quality. Proxy = always proxy." },
#endif
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
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * @brief Types of components this system can temporarily turn off (suppress) when the actor\n * is unimportant (low significance).\n *\n * In plain English: what parts can we temporarily mute to save performance.\n */" },
#endif
		{ "CustomTag.Name", "ESuppressionComponentType::CustomTag" },
		{ "Hair.Name", "ESuppressionComponentType::Hair" },
		{ "Light.Name", "ESuppressionComponentType::Light" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
		{ "MotionWarping.Name", "ESuppressionComponentType::MotionWarping" },
		{ "Niagara.Name", "ESuppressionComponentType::Niagara" },
		{ "Physics.Name", "ESuppressionComponentType::Physics" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "@brief Types of components this system can temporarily turn off (suppress) when the actor\nis unimportant (low significance).\n\nIn plain English: what parts can we temporarily mute to save performance." },
#endif
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
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * @brief Rule describing which component(s) can be suppressed as significance drops.\n *\n * Layman\xe2\x80\x99s terms: When the actor is far away (not important), these rules tell the system\n * which bits to switch off and when.\n */" },
#endif
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "@brief Rule describing which component(s) can be suppressed as significance drops.\n\nLayman\xe2\x80\x99s terms: When the actor is far away (not important), these rules tell the system\nwhich bits to switch off and when." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComponentType_MetaData[] = {
		{ "Category", "Suppression" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "What type of component this rule affects (e.g., Audio, Niagara, Hair)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComponentTag_MetaData[] = {
		{ "Category", "Suppression" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Optional filter: only components with this tag are affected. Leave empty to match all of the chosen type." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NameContains_MetaData[] = {
		{ "Category", "Suppression" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Optional filter by name: only components with names containing this text are affected." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SuppressBelowSignificance_MetaData[] = {
		{ "Category", "Suppression" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "When the actor\xe2\x80\x99s significance is below this value (0..1), this component gets turned off to save performance." },
#endif
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
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics::NewProp_ComponentType = { "ComponentType", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FComponentSuppressionRule, ComponentType), Z_Construct_UEnum_DAI_PerfMngr_ESuppressionComponentType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComponentType_MetaData), NewProp_ComponentType_MetaData) }; // 2398797330
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
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Forces an immediate switch back to the full version (ignores normal delays/safety checks)." },
#endif
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
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Forces an immediate switch to the proxy version (ignores normal delays/safety checks)." },
#endif
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
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Gets the current proxy swap state (Active, ProxyActive, or pending states)." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UDAI_PerfMngrComponent_GetCurrentProxyState_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UDAI_PerfMngrComponent_GetCurrentProxyState_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(DAI_PerfMngrComponent_eventGetCurrentProxyState_Parms, ReturnValue), Z_Construct_UEnum_DAI_PerfMngr_EProxySwapState, METADATA_PARAMS(0, nullptr) }; // 1431846166
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
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns true if the actor is currently using a proxy representation." },
#endif
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
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Swap back to the full (high\xe2\x80\x91quality) version of this actor when safe to do so." },
#endif
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
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Swap to the proxy (cheap) version of this actor when safe to do so." },
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
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * @brief Main Performance Manager component. Add this to actors you want to auto\xe2\x80\x91optimize.\n *\n * It monitors the actor\xe2\x80\x99s distance/importance and swaps meshes/effects to cheaper versions or\n * reduces tick rates to save frame time.\n */" },
#endif
		{ "IncludePath", "DAI_PerfMngrComponent.h" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "@brief Main Performance Manager component. Add this to actors you want to auto\xe2\x80\x91optimize.\n\nIt monitors the actor\xe2\x80\x99s distance/importance and swaps meshes/effects to cheaper versions or\nreduces tick rates to save frame time." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDistance_MetaData[] = {
		{ "Category", "PerfMngr" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "How far from the player this actor can be before we prefer cheaper representations (proxies/billboards)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TickEvaluationRate_MetaData[] = {
		{ "Category", "PerfMngr" },
		{ "ClampMin", "0.01" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "How often (in seconds) to re-evaluate significance and choose proxy/full state. Higher = less CPU overhead." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TickIntervalHigh_MetaData[] = {
		{ "Category", "PerfMngr" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Tick interval to use when the actor is close or important (smaller = more updates, smoother behavior)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TickIntervalLow_MetaData[] = {
		{ "Category", "PerfMngr" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Tick interval to use when the actor is far or unimportant (larger = fewer updates, better performance)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinTickClamp_MetaData[] = {
		{ "Category", "PerfMngr" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Minimum allowed tick interval after clamping." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxTickClamp_MetaData[] = {
		{ "Category", "PerfMngr" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum allowed tick interval after clamping." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAffectAbilitySystemTick_MetaData[] = {
		{ "Category", "PerfMngr" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Also throttle the owner\xe2\x80\x99s Ability System Component tick when significance is low." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableDebugLog_MetaData[] = {
		{ "Category", "PerfMngr|Debug" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Print detailed debug information to the Output Log." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bPrintSignificanceToScreen_MetaData[] = {
		{ "Category", "PerfMngr|Debug" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Draw the actor\xe2\x80\x99s current significance value on screen each time it\xe2\x80\x99s evaluated." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDrawDebugProxySphere_MetaData[] = {
		{ "Category", "PerfMngr|Debug" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Draw a sphere in the world to visualize the proxy/billboard swap radius." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProxyDebugSphereDuration_MetaData[] = {
		{ "Category", "PerfMngr|Debug" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "How long (seconds) the debug sphere should remain on screen." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProxyStaticMesh_MetaData[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Mesh used as the actor\xe2\x80\x99s cheap proxy representation when in proxy mode." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProxyHairMesh_MetaData[] = {
		{ "Category", "PerfMngr|Proxy|Hair" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Optional mesh to display as a cheap hair stand\xe2\x80\x91in while in proxy mode." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProxyBillboardMesh_MetaData[] = {
		{ "Category", "PerfMngr|Proxy|Billboard" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Billboard mesh used when significance is very low. Can be batched via HISM for large crowds." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProxyParticleEffect_MetaData[] = {
		{ "Category", "PerfMngr|Proxy|Particle" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Niagara effect to show when using a particle-only proxy representation." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BillboardFadeMaterial_MetaData[] = {
		{ "Category", "PerfMngr|Proxy|Billboard" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Material with a 'FadeAlpha' parameter used to cross-fade between proxy and billboard." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BillboardFadeDuration_MetaData[] = {
		{ "Category", "PerfMngr|Proxy|Billboard" },
		{ "ClampMin", "0.000000" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "How long to cross-fade (in seconds) between proxy mesh and billboard. 0 = instant." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BillboardProxyTag_MetaData[] = {
		{ "Category", "PerfMngr|Proxy|Billboard" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Component tag added to billboard proxy meshes (useful for filtering in gameplay logic)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BillboardEnterThreshold_MetaData[] = {
		{ "Category", "PerfMngr|Proxy|Billboard" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "When significance is below this, show the billboard proxy." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BillboardExitThreshold_MetaData[] = {
		{ "Category", "PerfMngr|Proxy|Billboard" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "When significance rises above this, hide the billboard proxy." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParticleProxyTag_MetaData[] = {
		{ "Category", "PerfMngr|Proxy|Particle" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Component tag added to particle proxy components (useful for filtering in gameplay logic)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParticleEnterThreshold_MetaData[] = {
		{ "Category", "PerfMngr|Proxy|Particle" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "When significance is below this, show the particle proxy." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParticleExitThreshold_MetaData[] = {
		{ "Category", "PerfMngr|Proxy|Particle" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "When significance rises above this, hide the particle proxy." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HairProxyTag_MetaData[] = {
		{ "Category", "PerfMngr|Proxy|Hair" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Optional tag assigned to hair proxy meshes so you can find/manipulate them later." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Category_MetaData[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Optional category name used by significance systems to group similar actors." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bColorizeBySignificance_MetaData[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Colorize meshes by their significance value (debug/visualization)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComponentSuppressionRules_MetaData[] = {
		{ "Category", "PerfMngr|Suppression" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "List of suppression rules. Each rule can turn off a type of component when significance is low." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProxyEnterThreshold_MetaData[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "When significance is below this, swap to the proxy representation." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProxyExitThreshold_MetaData[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "When significance rises above this, swap back to full representation." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProxySwapDelay_MetaData[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Grace period before a swap actually happens. Helps avoid flicker when value bounces around." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseHISMProxyBatching_MetaData[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Enable Hierarchical Instanced Static Mesh (HISM) batching for proxies to reduce draw calls." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProxyBatchAddSize_MetaData[] = {
		{ "Category", "PerfMngr|Proxy" },
		{ "ClampMax", "1000" },
		{ "ClampMin", "1" },
		{ "EditCondition", "bUseHISMProxyBatching" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of proxy instances to add to each HISM per tick (throttles mass adds)." },
#endif
		{ "UIMax", "200" },
		{ "UIMin", "1" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAllowAIThrottling_MetaData[] = {
		{ "Category", "PerfMngr|AI" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Allow AI logic (BT/Perception/etc.) to be throttled when this actor is far away and not important." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AIDeepFreezeSignificance_MetaData[] = {
		{ "Category", "PerfMngr|AI" },
		{ "ClampMax", "1.000000" },
		{ "ClampMin", "0.000000" },
		{ "EditCondition", "bAllowAIThrottling" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "When significance is below this, heavily throttle or pause AI." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProxyMeshComponent_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Proxy components created at runtime\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Proxy components created at runtime" },
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
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Event fired when the actor enters proxy mode." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnProxyExited_MetaData[] = {
		{ "ModuleRelativePath", "Public/DAI_PerfMngrComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Event fired when the actor exits proxy mode (back to full)." },
#endif
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
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BillboardFadeMaterial;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BillboardFadeDuration;
	static const UECodeGen_Private::FNamePropertyParams NewProp_BillboardProxyTag;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BillboardEnterThreshold;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BillboardExitThreshold;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ParticleProxyTag;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ParticleEnterThreshold;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ParticleExitThreshold;
	static const UECodeGen_Private::FNamePropertyParams NewProp_HairProxyTag;
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
	static const UECodeGen_Private::FIntPropertyParams NewProp_ProxyBatchAddSize;
	static void NewProp_bAllowAIThrottling_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAllowAIThrottling;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AIDeepFreezeSignificance;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ProxyMeshComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ProxyHairMeshComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BillboardMeshComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ProxyEffectComponent;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnProxyEntered;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnProxyExited;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDAI_PerfMngrComponent_ForceSwapToFull, "ForceSwapToFull" }, // 1254889978
		{ &Z_Construct_UFunction_UDAI_PerfMngrComponent_ForceSwapToProxy, "ForceSwapToProxy" }, // 1561695637
		{ &Z_Construct_UFunction_UDAI_PerfMngrComponent_GetCurrentProxyState, "GetCurrentProxyState" }, // 2087821262
		{ &Z_Construct_UFunction_UDAI_PerfMngrComponent_IsUsingProxy, "IsUsingProxy" }, // 795534363
		{ &Z_Construct_UFunction_UDAI_PerfMngrComponent_SwapToFull, "SwapToFull" }, // 3178803443
		{ &Z_Construct_UFunction_UDAI_PerfMngrComponent_SwapToProxy, "SwapToProxy" }, // 424432638
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
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_BillboardFadeMaterial = { "BillboardFadeMaterial", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, BillboardFadeMaterial), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BillboardFadeMaterial_MetaData), NewProp_BillboardFadeMaterial_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_BillboardFadeDuration = { "BillboardFadeDuration", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, BillboardFadeDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BillboardFadeDuration_MetaData), NewProp_BillboardFadeDuration_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_BillboardProxyTag = { "BillboardProxyTag", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, BillboardProxyTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BillboardProxyTag_MetaData), NewProp_BillboardProxyTag_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_BillboardEnterThreshold = { "BillboardEnterThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, BillboardEnterThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BillboardEnterThreshold_MetaData), NewProp_BillboardEnterThreshold_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_BillboardExitThreshold = { "BillboardExitThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, BillboardExitThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BillboardExitThreshold_MetaData), NewProp_BillboardExitThreshold_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ParticleProxyTag = { "ParticleProxyTag", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, ParticleProxyTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParticleProxyTag_MetaData), NewProp_ParticleProxyTag_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ParticleEnterThreshold = { "ParticleEnterThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, ParticleEnterThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParticleEnterThreshold_MetaData), NewProp_ParticleEnterThreshold_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ParticleExitThreshold = { "ParticleExitThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, ParticleExitThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParticleExitThreshold_MetaData), NewProp_ParticleExitThreshold_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_HairProxyTag = { "HairProxyTag", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, HairProxyTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HairProxyTag_MetaData), NewProp_HairProxyTag_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, Category), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Category_MetaData), NewProp_Category_MetaData) };
void Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bColorizeBySignificance_SetBit(void* Obj)
{
	((UDAI_PerfMngrComponent*)Obj)->bColorizeBySignificance = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bColorizeBySignificance = { "bColorizeBySignificance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UDAI_PerfMngrComponent), &Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bColorizeBySignificance_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bColorizeBySignificance_MetaData), NewProp_bColorizeBySignificance_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ComponentSuppressionRules_Inner = { "ComponentSuppressionRules", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FComponentSuppressionRule, METADATA_PARAMS(0, nullptr) }; // 2590223019
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ComponentSuppressionRules = { "ComponentSuppressionRules", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, ComponentSuppressionRules), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComponentSuppressionRules_MetaData), NewProp_ComponentSuppressionRules_MetaData) }; // 2590223019
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyEnterThreshold = { "ProxyEnterThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, ProxyEnterThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProxyEnterThreshold_MetaData), NewProp_ProxyEnterThreshold_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyExitThreshold = { "ProxyExitThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, ProxyExitThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProxyExitThreshold_MetaData), NewProp_ProxyExitThreshold_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxySwapDelay = { "ProxySwapDelay", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, ProxySwapDelay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProxySwapDelay_MetaData), NewProp_ProxySwapDelay_MetaData) };
void Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bUseHISMProxyBatching_SetBit(void* Obj)
{
	((UDAI_PerfMngrComponent*)Obj)->bUseHISMProxyBatching = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bUseHISMProxyBatching = { "bUseHISMProxyBatching", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UDAI_PerfMngrComponent), &Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bUseHISMProxyBatching_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseHISMProxyBatching_MetaData), NewProp_bUseHISMProxyBatching_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyBatchAddSize = { "ProxyBatchAddSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, ProxyBatchAddSize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProxyBatchAddSize_MetaData), NewProp_ProxyBatchAddSize_MetaData) };
void Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bAllowAIThrottling_SetBit(void* Obj)
{
	((UDAI_PerfMngrComponent*)Obj)->bAllowAIThrottling = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bAllowAIThrottling = { "bAllowAIThrottling", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UDAI_PerfMngrComponent), &Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bAllowAIThrottling_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAllowAIThrottling_MetaData), NewProp_bAllowAIThrottling_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_AIDeepFreezeSignificance = { "AIDeepFreezeSignificance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDAI_PerfMngrComponent, AIDeepFreezeSignificance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AIDeepFreezeSignificance_MetaData), NewProp_AIDeepFreezeSignificance_MetaData) };
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
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_BillboardFadeMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_BillboardFadeDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_BillboardProxyTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_BillboardEnterThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_BillboardExitThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ParticleProxyTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ParticleEnterThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ParticleExitThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_HairProxyTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_Category,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bColorizeBySignificance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ComponentSuppressionRules_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ComponentSuppressionRules,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyEnterThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyExitThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxySwapDelay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bUseHISMProxyBatching,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_ProxyBatchAddSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_bAllowAIThrottling,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDAI_PerfMngrComponent_Statics::NewProp_AIDeepFreezeSignificance,
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
struct Z_CompiledInDeferFile_FID_PluginTest_Performance_Plugins_DAI_PerfMngr_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EProxySwapState_StaticEnum, TEXT("EProxySwapState"), &Z_Registration_Info_UEnum_EProxySwapState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1431846166U) },
		{ EPerformanceMode_StaticEnum, TEXT("EPerformanceMode"), &Z_Registration_Info_UEnum_EPerformanceMode, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 909143192U) },
		{ ESuppressionComponentType_StaticEnum, TEXT("ESuppressionComponentType"), &Z_Registration_Info_UEnum_ESuppressionComponentType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2398797330U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FComponentSuppressionRule::StaticStruct, Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics::NewStructOps, TEXT("ComponentSuppressionRule"), &Z_Registration_Info_UScriptStruct_ComponentSuppressionRule, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FComponentSuppressionRule), 2590223019U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDAI_PerfMngrComponent, UDAI_PerfMngrComponent::StaticClass, TEXT("UDAI_PerfMngrComponent"), &Z_Registration_Info_UClass_UDAI_PerfMngrComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDAI_PerfMngrComponent), 3836386147U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginTest_Performance_Plugins_DAI_PerfMngr_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_1542698364(TEXT("/Script/DAI_PerfMngr"),
	Z_CompiledInDeferFile_FID_PluginTest_Performance_Plugins_DAI_PerfMngr_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginTest_Performance_Plugins_DAI_PerfMngr_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_PluginTest_Performance_Plugins_DAI_PerfMngr_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginTest_Performance_Plugins_DAI_PerfMngr_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_PluginTest_Performance_Plugins_DAI_PerfMngr_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginTest_Performance_Plugins_DAI_PerfMngr_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
