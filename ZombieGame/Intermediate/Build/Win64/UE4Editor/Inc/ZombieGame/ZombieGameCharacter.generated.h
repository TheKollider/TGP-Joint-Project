// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef ZOMBIEGAME_ZombieGameCharacter_generated_h
#error "ZombieGameCharacter.generated.h already included, missing '#pragma once' in ZombieGameCharacter.h"
#endif
#define ZOMBIEGAME_ZombieGameCharacter_generated_h

#define ZombieGame_Source_ZombieGame_ZombieGameCharacter_h_14_RPC_WRAPPERS
#define ZombieGame_Source_ZombieGame_ZombieGameCharacter_h_14_RPC_WRAPPERS_NO_PURE_DECLS
#define ZombieGame_Source_ZombieGame_ZombieGameCharacter_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAZombieGameCharacter(); \
	friend struct Z_Construct_UClass_AZombieGameCharacter_Statics; \
public: \
	DECLARE_CLASS(AZombieGameCharacter, ACharacter, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ZombieGame"), NO_API) \
	DECLARE_SERIALIZER(AZombieGameCharacter)


#define ZombieGame_Source_ZombieGame_ZombieGameCharacter_h_14_INCLASS \
private: \
	static void StaticRegisterNativesAZombieGameCharacter(); \
	friend struct Z_Construct_UClass_AZombieGameCharacter_Statics; \
public: \
	DECLARE_CLASS(AZombieGameCharacter, ACharacter, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ZombieGame"), NO_API) \
	DECLARE_SERIALIZER(AZombieGameCharacter)


#define ZombieGame_Source_ZombieGame_ZombieGameCharacter_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AZombieGameCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AZombieGameCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AZombieGameCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AZombieGameCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AZombieGameCharacter(AZombieGameCharacter&&); \
	NO_API AZombieGameCharacter(const AZombieGameCharacter&); \
public:


#define ZombieGame_Source_ZombieGame_ZombieGameCharacter_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AZombieGameCharacter(AZombieGameCharacter&&); \
	NO_API AZombieGameCharacter(const AZombieGameCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AZombieGameCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AZombieGameCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AZombieGameCharacter)


#define ZombieGame_Source_ZombieGame_ZombieGameCharacter_h_14_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__Mesh1P() { return STRUCT_OFFSET(AZombieGameCharacter, Mesh1P); } \
	FORCEINLINE static uint32 __PPO__FP_Gun() { return STRUCT_OFFSET(AZombieGameCharacter, FP_Gun); } \
	FORCEINLINE static uint32 __PPO__FP_MuzzleLocation() { return STRUCT_OFFSET(AZombieGameCharacter, FP_MuzzleLocation); } \
	FORCEINLINE static uint32 __PPO__VR_Gun() { return STRUCT_OFFSET(AZombieGameCharacter, VR_Gun); } \
	FORCEINLINE static uint32 __PPO__VR_MuzzleLocation() { return STRUCT_OFFSET(AZombieGameCharacter, VR_MuzzleLocation); } \
	FORCEINLINE static uint32 __PPO__FirstPersonCameraComponent() { return STRUCT_OFFSET(AZombieGameCharacter, FirstPersonCameraComponent); } \
	FORCEINLINE static uint32 __PPO__R_MotionController() { return STRUCT_OFFSET(AZombieGameCharacter, R_MotionController); } \
	FORCEINLINE static uint32 __PPO__L_MotionController() { return STRUCT_OFFSET(AZombieGameCharacter, L_MotionController); }


#define ZombieGame_Source_ZombieGame_ZombieGameCharacter_h_11_PROLOG
#define ZombieGame_Source_ZombieGame_ZombieGameCharacter_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ZombieGame_Source_ZombieGame_ZombieGameCharacter_h_14_PRIVATE_PROPERTY_OFFSET \
	ZombieGame_Source_ZombieGame_ZombieGameCharacter_h_14_RPC_WRAPPERS \
	ZombieGame_Source_ZombieGame_ZombieGameCharacter_h_14_INCLASS \
	ZombieGame_Source_ZombieGame_ZombieGameCharacter_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ZombieGame_Source_ZombieGame_ZombieGameCharacter_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ZombieGame_Source_ZombieGame_ZombieGameCharacter_h_14_PRIVATE_PROPERTY_OFFSET \
	ZombieGame_Source_ZombieGame_ZombieGameCharacter_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	ZombieGame_Source_ZombieGame_ZombieGameCharacter_h_14_INCLASS_NO_PURE_DECLS \
	ZombieGame_Source_ZombieGame_ZombieGameCharacter_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ZombieGame_Source_ZombieGame_ZombieGameCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
