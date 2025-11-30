// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "DAI_PerfMngrComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EPerformanceQuality : uint8;
enum class EProxySwapState : uint8;
#ifdef DAI_PERFMNGR_DAI_PerfMngrComponent_generated_h
#error "DAI_PerfMngrComponent.generated.h already included, missing '#pragma once' in DAI_PerfMngrComponent.h"
#endif
#define DAI_PERFMNGR_DAI_PerfMngrComponent_generated_h

#define FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_73_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FComponentSuppressionRule_Statics; \
	DAI_PERFMNGR_API static class UScriptStruct* StaticStruct();


template<> DAI_PERFMNGR_API UScriptStruct* StaticStruct<struct FComponentSuppressionRule>();

#define FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_126_DELEGATE \
DAI_PERFMNGR_API void FOnProxyEnteredSignature_DelegateWrapper(const FMulticastScriptDelegate& OnProxyEnteredSignature);


#define FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_127_DELEGATE \
DAI_PERFMNGR_API void FOnProxyExitedSignature_DelegateWrapper(const FMulticastScriptDelegate& OnProxyExitedSignature);


#define FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_136_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execSetPerformanceQuality); \
	DECLARE_FUNCTION(execForceSwapToFull); \
	DECLARE_FUNCTION(execForceSwapToProxy); \
	DECLARE_FUNCTION(execGetCurrentSignificance); \
	DECLARE_FUNCTION(execGetCurrentProxyState); \
	DECLARE_FUNCTION(execIsUsingProxy); \
	DECLARE_FUNCTION(execSwapToFull); \
	DECLARE_FUNCTION(execSwapToProxy);


#define FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_136_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUDAI_PerfMngrComponent(); \
	friend struct Z_Construct_UClass_UDAI_PerfMngrComponent_Statics; \
public: \
	DECLARE_CLASS(UDAI_PerfMngrComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DAI_PerfMngr"), NO_API) \
	DECLARE_SERIALIZER(UDAI_PerfMngrComponent)


#define FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_136_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UDAI_PerfMngrComponent(UDAI_PerfMngrComponent&&); \
	UDAI_PerfMngrComponent(const UDAI_PerfMngrComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UDAI_PerfMngrComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDAI_PerfMngrComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UDAI_PerfMngrComponent) \
	NO_API virtual ~UDAI_PerfMngrComponent();


#define FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_133_PROLOG
#define FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_136_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_136_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_136_INCLASS_NO_PURE_DECLS \
	FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h_136_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> DAI_PERFMNGR_API UClass* StaticClass<class UDAI_PerfMngrComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_githubdesktop_Wolfsige_plugins_Marketplace_UE5_5_DAI_PerfMngr_HostProject_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_DAI_PerfMngrComponent_h


#define FOREACH_ENUM_EPROXYSWAPSTATE(op) \
	op(EProxySwapState::Active) \
	op(EProxySwapState::PendingSwapToProxy) \
	op(EProxySwapState::ProxyActive) \
	op(EProxySwapState::PendingSwapToFull) 

enum class EProxySwapState : uint8;
template<> struct TIsUEnumClass<EProxySwapState> { enum { Value = true }; };
template<> DAI_PERFMNGR_API UEnum* StaticEnum<EProxySwapState>();

#define FOREACH_ENUM_EPERFORMANCEMODE(op) \
	op(EPerformanceMode::Auto) \
	op(EPerformanceMode::Full) \
	op(EPerformanceMode::Proxy) 

enum class EPerformanceMode : uint8;
template<> struct TIsUEnumClass<EPerformanceMode> { enum { Value = true }; };
template<> DAI_PERFMNGR_API UEnum* StaticEnum<EPerformanceMode>();

#define FOREACH_ENUM_ESUPPRESSIONCOMPONENTTYPE(op) \
	op(ESuppressionComponentType::Audio) \
	op(ESuppressionComponentType::Niagara) \
	op(ESuppressionComponentType::AbilitySystem) \
	op(ESuppressionComponentType::Light) \
	op(ESuppressionComponentType::Widget) \
	op(ESuppressionComponentType::MotionWarping) \
	op(ESuppressionComponentType::Hair) \
	op(ESuppressionComponentType::Physics) \
	op(ESuppressionComponentType::Camera) \
	op(ESuppressionComponentType::CustomTag) 

enum class ESuppressionComponentType : uint8;
template<> struct TIsUEnumClass<ESuppressionComponentType> { enum { Value = true }; };
template<> DAI_PERFMNGR_API UEnum* StaticEnum<ESuppressionComponentType>();

#define FOREACH_ENUM_EPERFORMANCEQUALITY(op) \
	op(EPerformanceQuality::High) \
	op(EPerformanceQuality::Medium) \
	op(EPerformanceQuality::Low) 

enum class EPerformanceQuality : uint8;
template<> struct TIsUEnumClass<EPerformanceQuality> { enum { Value = true }; };
template<> DAI_PERFMNGR_API UEnum* StaticEnum<EPerformanceQuality>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
