// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Zombie.generated.h"

UCLASS()
class ZOMBIEGAME_API AZombie : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* zombieRoot;

public:
	UPROPERTY(EditAnywhere, Category = "Behaviour")
	class UBehaviorTree* behaviorTree; //The Zombie's Behavior Tree

	UPROPERTY(EditAnywhere)
		float health; //Zombie's Health

public:
	// Sets default values for this character's properties
	AZombie();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void DealDamage(float damage); //Used to deal damage to the Zombie's

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
