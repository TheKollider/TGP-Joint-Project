// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FVector;
struct FHitResult;
#ifdef ZOMBIEGAME_ZombieGameProjectile_generated_h
#error "ZombieGameProjectile.generated.h already included, missing '#pragma once' in ZombieGameProjectile.h"
#endif
#define ZOMBIEGAME_ZombieGameProjectile_generated_h

#define ZombieGame_Source_ZombieGame_ZombieGameProjectile_h_12_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnHit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_STRUCT(FVector,Z_Param_NormalImpulse); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnHit(Z_Param_HitComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_Hit); \
		P_NATIVE_END; \
	}


#define ZombieGame_Source_ZombieGame_ZombieGameProjectile_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnHit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_STRUCT(FVector,Z_Param_NormalImpulse); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnHit(Z_Param_HitComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_Hit); \
		P_NATIVE_END; \
	}


#define ZombieGame_Source_ZombieGame_ZombieGameProjectile_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAZombieGameProjectile(); \
	friend struct Z_Construct_UClass_AZombieGameProjectile_Statics; \
public: \
	DECLARE_CLASS(AZombieGameProjectile, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ZombieGame"), NO_API) \
	DECLARE_SERIALIZER(AZombieGameProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define ZombieGame_Source_ZombieGame_ZombieGameProjectile_h_12_INCLASS \
private: \
	static void StaticRegisterNativesAZombieGameProjectile(); \
	friend struct Z_Construct_UClass_AZombieGameProjectile_Statics; \
public: \
	DECLARE_CLASS(AZombieGameProjectile, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ZombieGame"), NO_API) \
	DECLARE_SERIALIZER(AZombieGameProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define ZombieGame_Source_ZombieGame_ZombieGameProjectile_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AZombieGameProjectile(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AZombieGameProjectile) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AZombieGameProjectile); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AZombieGameProjectile); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AZombieGameProjectile(AZombieGameProjectile&&); \
	NO_API AZombieGameProjectile(const AZombieGameProjectile&); \
public:


#define ZombieGame_Source_ZombieGame_ZombieGameProjectile_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AZombieGameProjectile(AZombieGameProjectile&&); \
	NO_API AZombieGameProjectile(const AZombieGameProjectile&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AZombieGameProjectile); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AZombieGameProjectile); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AZombieGameProjectile)


#define ZombieGame_Source_ZombieGame_ZombieGameProjectile_h_12_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__CollisionComp() { return STRUCT_OFFSET(AZombieGameProjectile, CollisionComp); } \
	FORCEINLINE static uint32 __PPO__ProjectileMovement() { return STRUCT_OFFSET(AZombieGameProjectile, ProjectileMovement); }


#define ZombieGame_Source_ZombieGame_ZombieGameProjectile_h_9_PROLOG
#define ZombieGame_Source_ZombieGame_ZombieGameProjectile_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ZombieGame_Source_ZombieGame_ZombieGameProjectile_h_12_PRIVATE_PROPERTY_OFFSET \
	ZombieGame_Source_ZombieGame_ZombieGameProjectile_h_12_RPC_WRAPPERS \
	ZombieGame_Source_ZombieGame_ZombieGameProjectile_h_12_INCLASS \
	ZombieGame_Source_ZombieGame_ZombieGameProjectile_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ZombieGame_Source_ZombieGame_ZombieGameProjectile_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ZombieGame_Source_ZombieGame_ZombieGameProjectile_h_12_PRIVATE_PROPERTY_OFFSET \
	ZombieGame_Source_ZombieGame_ZombieGameProjectile_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	ZombieGame_Source_ZombieGame_ZombieGameProjectile_h_12_INCLASS_NO_PURE_DECLS \
	ZombieGame_Source_ZombieGame_ZombieGameProjectile_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ZombieGame_Source_ZombieGame_ZombieGameProjectile_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
