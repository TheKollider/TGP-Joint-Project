// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
class AZombie;

UCLASS()
class ZOMBIEGAME_API AZombieController : public AAIController
{
	GENERATED_BODY()

public:
	AZombieController();

	virtual void Possess(APawn* pawn) override;
	virtual void Tick(float DeltaTime) override;

protected:
	UBehaviorTreeComponent* behaviorComp;
	UBlackboardComponent* blackboardComp;

private:
	AZombie* zombieParent;
};
