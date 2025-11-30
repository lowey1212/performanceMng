// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DAI_PerfMngr/Public/PerformanceComponentManager.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePerformanceComponentManager() {}

// Begin Cross Module References
DAI_PERFMNGR_API UClass* Z_Construct_UClass_UPerformanceComponentManager();
DAI_PERFMNGR_API UClass* Z_Construct_UClass_UPerformanceComponentManager_NoRegister();
DAI_PERFMNGR_API UEnum* Z_Construct_UEnum_DAI_PerfMngr_EManagedComponentType();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
UPackage* Z_Construct_UPackage__Script_DAI_PerfMngr();
// End Cross Module References

// Begin Enum EManagedComponentType
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EManagedComponentType;
static UEnum* EManagedComponentType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EManagedComponentType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EManagedComponentType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_DAI_PerfMngr_EManagedComponentType, (UObject*)Z_Construct_UPackage__Script_DAI_PerfMngr(), TEXT("EManagedComponentType"));
	}
	return Z_Registration_Info_UEnum_EManagedComponentType.OuterSingleton;
}
template<> DAI_PERFMNGR_API UEnum* StaticEnum<EManagedComponentType>()
{
	return EManagedComponentType_StaticEnum();
}
struct Z_Construct_UEnum_DAI_PerfMngr_EManagedComponentType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "AIPerception.Name", "EManagedComponentType::AIPerception" },
		{ "Arrow.Name", "EManagedComponentType::Arrow" },
		{ "Audio.Name", "EManagedComponentType::Audio" },
		{ "Billboard.Name", "EManagedComponentType::Billboard" },
		{ "BlueprintType", "true" },
		{ "BoxCollision.Name", "EManagedComponentType::BoxCollision" },
		{ "Camera.Name", "EManagedComponentType::Camera" },
		{ "CapsuleCollision.Name", "EManagedComponentType::CapsuleCollision" },
		{ "ChildActor.Name", "EManagedComponentType::ChildActor" },
		{ "Decal.Name", "EManagedComponentType::Decal" },
		{ "DirectionalLight.Name", "EManagedComponentType::DirectionalLight" },
		{ "Input.Name", "EManagedComponentType::Input" },
		{ "ModuleRelativePath", "Public/PerformanceComponentManager.h" },
		{ "PhysicsConstraint.Name", "EManagedComponentType::PhysicsConstraint" },
		{ "PointLight.Name", "EManagedComponentType::PointLight" },
		{ "RadialForce.Name", "EManagedComponentType::RadialForce" },
		{ "RectLight.Name", "EManagedComponentType::RectLight" },
		{ "Scene.Name", "EManagedComponentType::Scene" },
		{ "SkeletalMesh.Name", "EManagedComponentType::SkeletalMesh" },
		{ "SkyLight.Name", "EManagedComponentType::SkyLight" },
		{ "SphereCollision.Name", "EManagedComponentType::SphereCollision" },
		{ "SpotLight.Name", "EManagedComponentType::SpotLight" },
		{ "SpringArm.Name", "EManagedComponentType::SpringArm" },
		{ "StaticMesh.Name", "EManagedComponentType::StaticMesh" },
		{ "Synth.Name", "EManagedComponentType::Synth" },
		{ "TextRender.Name", "EManagedComponentType::TextRender" },
		{ "Widget.Name", "EManagedComponentType::Widget" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EManagedComponentType::Scene", (int64)EManagedComponentType::Scene },
		{ "EManagedComponentType::ChildActor", (int64)EManagedComponentType::ChildActor },
		{ "EManagedComponentType::StaticMesh", (int64)EManagedComponentType::StaticMesh },
		{ "EManagedComponentType::SkeletalMesh", (int64)EManagedComponentType::SkeletalMesh },
		{ "EManagedComponentType::Decal", (int64)EManagedComponentType::Decal },
		{ "EManagedComponentType::TextRender", (int64)EManagedComponentType::TextRender },
		{ "EManagedComponentType::PointLight", (int64)EManagedComponentType::PointLight },
		{ "EManagedComponentType::SpotLight", (int64)EManagedComponentType::SpotLight },
		{ "EManagedComponentType::DirectionalLight", (int64)EManagedComponentType::DirectionalLight },
		{ "EManagedComponentType::RectLight", (int64)EManagedComponentType::RectLight },
		{ "EManagedComponentType::SkyLight", (int64)EManagedComponentType::SkyLight },
		{ "EManagedComponentType::Camera", (int64)EManagedComponentType::Camera },
		{ "EManagedComponentType::SpringArm", (int64)EManagedComponentType::SpringArm },
		{ "EManagedComponentType::Input", (int64)EManagedComponentType::Input },
		{ "EManagedComponentType::AIPerception", (int64)EManagedComponentType::AIPerception },
		{ "EManagedComponentType::BoxCollision", (int64)EManagedComponentType::BoxCollision },
		{ "EManagedComponentType::SphereCollision", (int64)EManagedComponentType::SphereCollision },
		{ "EManagedComponentType::CapsuleCollision", (int64)EManagedComponentType::CapsuleCollision },
		{ "EManagedComponentType::PhysicsConstraint", (int64)EManagedComponentType::PhysicsConstraint },
		{ "EManagedComponentType::RadialForce", (int64)EManagedComponentType::RadialForce },
		{ "EManagedComponentType::Audio", (int64)EManagedComponentType::Audio },
		{ "EManagedComponentType::Synth", (int64)EManagedComponentType::Synth },
		{ "EManagedComponentType::Widget", (int64)EManagedComponentType::Widget },
		{ "EManagedComponentType::Billboard", (int64)EManagedComponentType::Billboard },
		{ "EManagedComponentType::Arrow", (int64)EManagedComponentType::Arrow },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_DAI_PerfMngr_EManagedComponentType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_DAI_PerfMngr,
	nullptr,
	"EManagedComponentType",
	"EManagedComponentType",
	Z_Construct_UEnum_DAI_PerfMngr_EManagedComponentType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_DAI_PerfMngr_EManagedComponentType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_DAI_PerfMngr_EManagedComponentType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_DAI_PerfMngr_EManagedComponentType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_DAI_PerfMngr_EManagedComponentType()
{
	if (!Z_Registration_Info_UEnum_EManagedComponentType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EManagedComponentType.InnerSingleton, Z_Construct_UEnum_DAI_PerfMngr_EManagedComponentType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EManagedComponentType.InnerSingleton;
}
// End Enum EManagedComponentType

// Begin Class UPerformanceComponentManager Function MulticastSetComponentActive
struct PerformanceComponentManager_eventMulticastSetComponentActive_Parms
{
	AActor* Target;
	EManagedComponentType Type;
	bool bActive;
};
static const FName NAME_UPerformanceComponentManager_MulticastSetComponentActive = FName(TEXT("MulticastSetComponentActive"));
void UPerformanceComponentManager::MulticastSetComponentActive(AActor* Target, EManagedComponentType Type, bool bActive)
{
	PerformanceComponentManager_eventMulticastSetComponentActive_Parms Parms;
	Parms.Target=Target;
	Parms.Type=Type;
	Parms.bActive=bActive ? true : false;
	UFunction* Func = FindFunctionChecked(NAME_UPerformanceComponentManager_MulticastSetComponentActive);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_UPerformanceComponentManager_MulticastSetComponentActive_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/PerformanceComponentManager.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Target;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Type_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Type;
	static void NewProp_bActive_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bActive;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UPerformanceComponentManager_MulticastSetComponentActive_Statics::NewProp_Target = { "Target", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PerformanceComponentManager_eventMulticastSetComponentActive_Parms, Target), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UPerformanceComponentManager_MulticastSetComponentActive_Statics::NewProp_Type_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UPerformanceComponentManager_MulticastSetComponentActive_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PerformanceComponentManager_eventMulticastSetComponentActive_Parms, Type), Z_Construct_UEnum_DAI_PerfMngr_EManagedComponentType, METADATA_PARAMS(0, nullptr) }; // 1188920576
void Z_Construct_UFunction_UPerformanceComponentManager_MulticastSetComponentActive_Statics::NewProp_bActive_SetBit(void* Obj)
{
	((PerformanceComponentManager_eventMulticastSetComponentActive_Parms*)Obj)->bActive = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UPerformanceComponentManager_MulticastSetComponentActive_Statics::NewProp_bActive = { "bActive", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(PerformanceComponentManager_eventMulticastSetComponentActive_Parms), &Z_Construct_UFunction_UPerformanceComponentManager_MulticastSetComponentActive_Statics::NewProp_bActive_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UPerformanceComponentManager_MulticastSetComponentActive_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPerformanceComponentManager_MulticastSetComponentActive_Statics::NewProp_Target,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPerformanceComponentManager_MulticastSetComponentActive_Statics::NewProp_Type_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPerformanceComponentManager_MulticastSetComponentActive_Statics::NewProp_Type,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPerformanceComponentManager_MulticastSetComponentActive_Statics::NewProp_bActive,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UPerformanceComponentManager_MulticastSetComponentActive_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UPerformanceComponentManager_MulticastSetComponentActive_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UPerformanceComponentManager, nullptr, "MulticastSetComponentActive", nullptr, nullptr, Z_Construct_UFunction_UPerformanceComponentManager_MulticastSetComponentActive_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UPerformanceComponentManager_MulticastSetComponentActive_Statics::PropPointers), sizeof(PerformanceComponentManager_eventMulticastSetComponentActive_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00084CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UPerformanceComponentManager_MulticastSetComponentActive_Statics::Function_MetaDataParams), Z_Construct_UFunction_UPerformanceComponentManager_MulticastSetComponentActive_Statics::Function_MetaDataParams) };
static_assert(sizeof(PerformanceComponentManager_eventMulticastSetComponentActive_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UPerformanceComponentManager_MulticastSetComponentActive()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UPerformanceComponentManager_MulticastSetComponentActive_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UPerformanceComponentManager::execMulticastSetComponentActive)
{
	P_GET_OBJECT(AActor,Z_Param_Target);
	P_GET_ENUM(EManagedComponentType,Z_Param_Type);
	P_GET_UBOOL(Z_Param_bActive);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->MulticastSetComponentActive_Implementation(Z_Param_Target,EManagedComponentType(Z_Param_Type),Z_Param_bActive);
	P_NATIVE_END;
}
// End Class UPerformanceComponentManager Function MulticastSetComponentActive

// Begin Class UPerformanceComponentManager Function ServerSetComponentActive
struct PerformanceComponentManager_eventServerSetComponentActive_Parms
{
	AActor* Target;
	EManagedComponentType Type;
	bool bActive;
};
static const FName NAME_UPerformanceComponentManager_ServerSetComponentActive = FName(TEXT("ServerSetComponentActive"));
void UPerformanceComponentManager::ServerSetComponentActive(AActor* Target, EManagedComponentType Type, bool bActive)
{
	PerformanceComponentManager_eventServerSetComponentActive_Parms Parms;
	Parms.Target=Target;
	Parms.Type=Type;
	Parms.bActive=bActive ? true : false;
	UFunction* Func = FindFunctionChecked(NAME_UPerformanceComponentManager_ServerSetComponentActive);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_UPerformanceComponentManager_ServerSetComponentActive_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/PerformanceComponentManager.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Target;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Type_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Type;
	static void NewProp_bActive_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bActive;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UPerformanceComponentManager_ServerSetComponentActive_Statics::NewProp_Target = { "Target", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PerformanceComponentManager_eventServerSetComponentActive_Parms, Target), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UPerformanceComponentManager_ServerSetComponentActive_Statics::NewProp_Type_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UPerformanceComponentManager_ServerSetComponentActive_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PerformanceComponentManager_eventServerSetComponentActive_Parms, Type), Z_Construct_UEnum_DAI_PerfMngr_EManagedComponentType, METADATA_PARAMS(0, nullptr) }; // 1188920576
void Z_Construct_UFunction_UPerformanceComponentManager_ServerSetComponentActive_Statics::NewProp_bActive_SetBit(void* Obj)
{
	((PerformanceComponentManager_eventServerSetComponentActive_Parms*)Obj)->bActive = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UPerformanceComponentManager_ServerSetComponentActive_Statics::NewProp_bActive = { "bActive", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(PerformanceComponentManager_eventServerSetComponentActive_Parms), &Z_Construct_UFunction_UPerformanceComponentManager_ServerSetComponentActive_Statics::NewProp_bActive_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UPerformanceComponentManager_ServerSetComponentActive_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPerformanceComponentManager_ServerSetComponentActive_Statics::NewProp_Target,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPerformanceComponentManager_ServerSetComponentActive_Statics::NewProp_Type_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPerformanceComponentManager_ServerSetComponentActive_Statics::NewProp_Type,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPerformanceComponentManager_ServerSetComponentActive_Statics::NewProp_bActive,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UPerformanceComponentManager_ServerSetComponentActive_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UPerformanceComponentManager_ServerSetComponentActive_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UPerformanceComponentManager, nullptr, "ServerSetComponentActive", nullptr, nullptr, Z_Construct_UFunction_UPerformanceComponentManager_ServerSetComponentActive_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UPerformanceComponentManager_ServerSetComponentActive_Statics::PropPointers), sizeof(PerformanceComponentManager_eventServerSetComponentActive_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00280CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UPerformanceComponentManager_ServerSetComponentActive_Statics::Function_MetaDataParams), Z_Construct_UFunction_UPerformanceComponentManager_ServerSetComponentActive_Statics::Function_MetaDataParams) };
static_assert(sizeof(PerformanceComponentManager_eventServerSetComponentActive_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UPerformanceComponentManager_ServerSetComponentActive()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UPerformanceComponentManager_ServerSetComponentActive_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UPerformanceComponentManager::execServerSetComponentActive)
{
	P_GET_OBJECT(AActor,Z_Param_Target);
	P_GET_ENUM(EManagedComponentType,Z_Param_Type);
	P_GET_UBOOL(Z_Param_bActive);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ServerSetComponentActive_Implementation(Z_Param_Target,EManagedComponentType(Z_Param_Type),Z_Param_bActive);
	P_NATIVE_END;
}
// End Class UPerformanceComponentManager Function ServerSetComponentActive

// Begin Class UPerformanceComponentManager Function SetComponentActive
struct Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive_Statics
{
	struct PerformanceComponentManager_eventSetComponentActive_Parms
	{
		AActor* Target;
		EManagedComponentType Type;
		bool bActive;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Performance" },
		{ "ModuleRelativePath", "Public/PerformanceComponentManager.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Target;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Type_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Type;
	static void NewProp_bActive_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bActive;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive_Statics::NewProp_Target = { "Target", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PerformanceComponentManager_eventSetComponentActive_Parms, Target), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive_Statics::NewProp_Type_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PerformanceComponentManager_eventSetComponentActive_Parms, Type), Z_Construct_UEnum_DAI_PerfMngr_EManagedComponentType, METADATA_PARAMS(0, nullptr) }; // 1188920576
void Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive_Statics::NewProp_bActive_SetBit(void* Obj)
{
	((PerformanceComponentManager_eventSetComponentActive_Parms*)Obj)->bActive = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive_Statics::NewProp_bActive = { "bActive", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(PerformanceComponentManager_eventSetComponentActive_Parms), &Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive_Statics::NewProp_bActive_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive_Statics::NewProp_Target,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive_Statics::NewProp_Type_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive_Statics::NewProp_Type,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive_Statics::NewProp_bActive,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UPerformanceComponentManager, nullptr, "SetComponentActive", nullptr, nullptr, Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive_Statics::PropPointers), sizeof(Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive_Statics::PerformanceComponentManager_eventSetComponentActive_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive_Statics::Function_MetaDataParams), Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive_Statics::PerformanceComponentManager_eventSetComponentActive_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UPerformanceComponentManager::execSetComponentActive)
{
	P_GET_OBJECT(AActor,Z_Param_Target);
	P_GET_ENUM(EManagedComponentType,Z_Param_Type);
	P_GET_UBOOL(Z_Param_bActive);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetComponentActive(Z_Param_Target,EManagedComponentType(Z_Param_Type),Z_Param_bActive);
	P_NATIVE_END;
}
// End Class UPerformanceComponentManager Function SetComponentActive

// Begin Class UPerformanceComponentManager
void UPerformanceComponentManager::StaticRegisterNativesUPerformanceComponentManager()
{
	UClass* Class = UPerformanceComponentManager::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "MulticastSetComponentActive", &UPerformanceComponentManager::execMulticastSetComponentActive },
		{ "ServerSetComponentActive", &UPerformanceComponentManager::execServerSetComponentActive },
		{ "SetComponentActive", &UPerformanceComponentManager::execSetComponentActive },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UPerformanceComponentManager);
UClass* Z_Construct_UClass_UPerformanceComponentManager_NoRegister()
{
	return UPerformanceComponentManager::StaticClass();
}
struct Z_Construct_UClass_UPerformanceComponentManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "PerformanceComponentManager.h" },
		{ "ModuleRelativePath", "Public/PerformanceComponentManager.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UPerformanceComponentManager_MulticastSetComponentActive, "MulticastSetComponentActive" }, // 4185747240
		{ &Z_Construct_UFunction_UPerformanceComponentManager_ServerSetComponentActive, "ServerSetComponentActive" }, // 2791893524
		{ &Z_Construct_UFunction_UPerformanceComponentManager_SetComponentActive, "SetComponentActive" }, // 3139658371
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UPerformanceComponentManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UPerformanceComponentManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_DAI_PerfMngr,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UPerformanceComponentManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UPerformanceComponentManager_Statics::ClassParams = {
	&UPerformanceComponentManager::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UPerformanceComponentManager_Statics::Class_MetaDataParams), Z_Construct_UClass_UPerformanceComponentManager_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UPerformanceComponentManager()
{
	if (!Z_Registration_Info_UClass_UPerformanceComponentManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UPerformanceComponentManager.OuterSingleton, Z_Construct_UClass_UPerformanceComponentManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UPerformanceComponentManager.OuterSingleton;
}
template<> DAI_PERFMNGR_API UClass* StaticClass<UPerformanceComponentManager>()
{
	return UPerformanceComponentManager::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UPerformanceComponentManager);
UPerformanceComponentManager::~UPerformanceComponentManager() {}
// End Class UPerformanceComponentManager

// Begin Registration
struct Z_CompiledInDeferFile_FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_PerformanceComponentManager_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EManagedComponentType_StaticEnum, TEXT("EManagedComponentType"), &Z_Registration_Info_UEnum_EManagedComponentType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1188920576U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UPerformanceComponentManager, UPerformanceComponentManager::StaticClass, TEXT("UPerformanceComponentManager"), &Z_Registration_Info_UClass_UPerformanceComponentManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UPerformanceComponentManager), 3911039325U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_PerformanceComponentManager_h_2411092089(TEXT("/Script/DAI_PerfMngr"),
	Z_CompiledInDeferFile_FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_PerformanceComponentManager_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_PerformanceComponentManager_h_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_PerformanceComponentManager_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_PerformanceComponentManager_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
