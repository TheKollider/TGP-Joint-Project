// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseZombieAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEGAME_API UBaseZombieAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int stateNum;
	
};
