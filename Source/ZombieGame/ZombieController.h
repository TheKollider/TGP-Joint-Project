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

	UFUNCTION(BlueprintCallable)
	void SetState(int state);

	UFUNCTION(BlueprintCallable)
	void Enrage(); //Sets the Zombie to chase the Player

protected:
	UBehaviorTreeComponent* behaviorComp;
	UBlackboardComponent* blackboardComp;

private:
	AZombie* zombieParent;
};
