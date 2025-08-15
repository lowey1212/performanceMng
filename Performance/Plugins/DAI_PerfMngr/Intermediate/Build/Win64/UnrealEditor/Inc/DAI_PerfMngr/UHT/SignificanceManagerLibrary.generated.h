// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SignificanceManagerLibrary.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
#ifdef DAI_PERFMNGR_SignificanceManagerLibrary_generated_h
#error "SignificanceManagerLibrary.generated.h already included, missing '#pragma once' in SignificanceManagerLibrary.h"
#endif
#define DAI_PERFMNGR_SignificanceManagerLibrary_generated_h

#define FID_githubdesktop_performanceMng_Performance_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_SignificanceManagerLibrary_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execRegisterActorWithSignificance);


#define FID_githubdesktop_performanceMng_Performance_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_SignificanceManagerLibrary_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSignificanceManagerLibrary(); \
	friend struct Z_Construct_UClass_USignificanceManagerLibrary_Statics; \
public: \
	DECLARE_CLASS(USignificanceManagerLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/DAI_PerfMngr"), NO_API) \
	DECLARE_SERIALIZER(USignificanceManagerLibrary)


#define FID_githubdesktop_performanceMng_Performance_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_SignificanceManagerLibrary_h_13_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USignificanceManagerLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	USignificanceManagerLibrary(USignificanceManagerLibrary&&); \
	USignificanceManagerLibrary(const USignificanceManagerLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USignificanceManagerLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USignificanceManagerLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USignificanceManagerLibrary) \
	NO_API virtual ~USignificanceManagerLibrary();


#define FID_githubdesktop_performanceMng_Performance_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_SignificanceManagerLibrary_h_10_PROLOG
#define FID_githubdesktop_performanceMng_Performance_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_SignificanceManagerLibrary_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_githubdesktop_performanceMng_Performance_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_SignificanceManagerLibrary_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_githubdesktop_performanceMng_Performance_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_SignificanceManagerLibrary_h_13_INCLASS_NO_PURE_DECLS \
	FID_githubdesktop_performanceMng_Performance_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_SignificanceManagerLibrary_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> DAI_PERFMNGR_API UClass* StaticClass<class USignificanceManagerLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_githubdesktop_performanceMng_Performance_Plugins_DAI_PerfMngr_Source_DAI_PerfMngr_Public_SignificanceManagerLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
