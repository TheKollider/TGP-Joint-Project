// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ZombieGame/ZombieGameHUD.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeZombieGameHUD() {}
// Cross Module References
	ZOMBIEGAME_API UClass* Z_Construct_UClass_AZombieGameHUD_NoRegister();
	ZOMBIEGAME_API UClass* Z_Construct_UClass_AZombieGameHUD();
	ENGINE_API UClass* Z_Construct_UClass_AHUD();
	UPackage* Z_Construct_UPackage__Script_ZombieGame();
// End Cross Module References
	void AZombieGameHUD::StaticRegisterNativesAZombieGameHUD()
	{
	}
	UClass* Z_Construct_UClass_AZombieGameHUD_NoRegister()
	{
		return AZombieGameHUD::StaticClass();
	}
	struct Z_Construct_UClass_AZombieGameHUD_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AZombieGameHUD_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AHUD,
		(UObject* (*)())Z_Construct_UPackage__Script_ZombieGame,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AZombieGameHUD_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Rendering Actor Input Replication" },
		{ "IncludePath", "ZombieGameHUD.h" },
		{ "ModuleRelativePath", "ZombieGameHUD.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AZombieGameHUD_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AZombieGameHUD>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AZombieGameHUD_Statics::ClassParams = {
		&AZombieGameHUD::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x008002ACu,
		nullptr, 0,
		nullptr, 0,
		"Game",
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_AZombieGameHUD_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AZombieGameHUD_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AZombieGameHUD()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AZombieGameHUD_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AZombieGameHUD, 478104777);
	static FCompiledInDefer Z_CompiledInDefer_UClass_AZombieGameHUD(Z_Construct_UClass_AZombieGameHUD, &AZombieGameHUD::StaticClass, TEXT("/Script/ZombieGame"), TEXT("AZombieGameHUD"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AZombieGameHUD);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
