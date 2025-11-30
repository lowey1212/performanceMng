// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "PerformanceComponentManager.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
enum class EManagedComponentType : uint8;
#ifdef DAI_PERFMNGR_PerformanceComponentManager_generated_h
#error "PerformanceComponentManager.generated.h already included, missing '#pragma once' in PerformanceComponentManager.h"
#endif
#define DAI_PERFMNGR_PerformanceComponentManager_generated_h

#define FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_PerformanceComponentManager_h_67_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void MulticastSetComponentActive_Implementation(AActor* Target, EManagedComponentType Type, bool bActive); \
	virtual void ServerSetComponentActive_Implementation(AActor* Target, EManagedComponentType Type, bool bActive); \
	DECLARE_FUNCTION(execMulticastSetComponentActive); \
	DECLARE_FUNCTION(execServerSetComponentActive); \
	DECLARE_FUNCTION(execSetComponentActive);


#define FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_PerformanceComponentManager_h_67_CALLBACK_WRAPPERS
#define FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_PerformanceComponentManager_h_67_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUPerformanceComponentManager(); \
	friend struct Z_Construct_UClass_UPerformanceComponentManager_Statics; \
public: \
	DECLARE_CLASS(UPerformanceComponentManager, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DAI_PerfMngr"), NO_API) \
	DECLARE_SERIALIZER(UPerformanceComponentManager)


#define FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_PerformanceComponentManager_h_67_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UPerformanceComponentManager(UPerformanceComponentManager&&); \
	UPerformanceComponentManager(const UPerformanceComponentManager&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UPerformanceComponentManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPerformanceComponentManager); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UPerformanceComponentManager) \
	NO_API virtual ~UPerformanceComponentManager();


#define FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_PerformanceComponentManager_h_64_PROLOG
#define FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_PerformanceComponentManager_h_67_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_PerformanceComponentManager_h_67_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_PerformanceComponentManager_h_67_CALLBACK_WRAPPERS \
	FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_PerformanceComponentManager_h_67_INCLASS_NO_PURE_DECLS \
	FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_PerformanceComponentManager_h_67_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> DAI_PERFMNGR_API UClass* StaticClass<class UPerformanceComponentManager>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_PerformanceComponentManager_h


#define FOREACH_ENUM_EMANAGEDCOMPONENTTYPE(op) \
	op(EManagedComponentType::Scene) \
	op(EManagedComponentType::ChildActor) \
	op(EManagedComponentType::StaticMesh) \
	op(EManagedComponentType::SkeletalMesh) \
	op(EManagedComponentType::Decal) \
	op(EManagedComponentType::TextRender) \
	op(EManagedComponentType::PointLight) \
	op(EManagedComponentType::SpotLight) \
	op(EManagedComponentType::DirectionalLight) \
	op(EManagedComponentType::RectLight) \
	op(EManagedComponentType::SkyLight) \
	op(EManagedComponentType::Camera) \
	op(EManagedComponentType::SpringArm) \
	op(EManagedComponentType::Input) \
	op(EManagedComponentType::AIPerception) \
	op(EManagedComponentType::BoxCollision) \
	op(EManagedComponentType::SphereCollision) \
	op(EManagedComponentType::CapsuleCollision) \
	op(EManagedComponentType::PhysicsConstraint) \
	op(EManagedComponentType::RadialForce) \
	op(EManagedComponentType::Audio) \
	op(EManagedComponentType::Synth) \
	op(EManagedComponentType::Widget) \
	op(EManagedComponentType::Billboard) \
	op(EManagedComponentType::Arrow) 

enum class EManagedComponentType : uint8;
template<> struct TIsUEnumClass<EManagedComponentType> { enum { Value = true }; };
template<> DAI_PERFMNGR_API UEnum* StaticEnum<EManagedComponentType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
