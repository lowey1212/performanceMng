// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDAI_PerfMngr_init() {}
	DAI_PERFMNGR_API UFunction* Z_Construct_UDelegateFunction_DAI_PerfMngr_OnProxyEnteredSignature__DelegateSignature();
	DAI_PERFMNGR_API UFunction* Z_Construct_UDelegateFunction_DAI_PerfMngr_OnProxyExitedSignature__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_DAI_PerfMngr;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_DAI_PerfMngr()
	{
		if (!Z_Registration_Info_UPackage__Script_DAI_PerfMngr.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_DAI_PerfMngr_OnProxyEnteredSignature__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_DAI_PerfMngr_OnProxyExitedSignature__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/DAI_PerfMngr",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x3ADC53C8,
				0xA2D7E65C,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_DAI_PerfMngr.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_DAI_PerfMngr.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_DAI_PerfMngr(Z_Construct_UPackage__Script_DAI_PerfMngr, TEXT("/Script/DAI_PerfMngr"), Z_Registration_Info_UPackage__Script_DAI_PerfMngr, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x3ADC53C8, 0xA2D7E65C));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
