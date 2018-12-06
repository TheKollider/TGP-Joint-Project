// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "Zombie.generated.h"

UCLASS()
class ZOMBIEGAME_API AZombie : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* zombieRoot;

	class UTimelineComponent* glowColourTimeLine;

public:
	UPROPERTY(EditAnywhere, Category = "Behaviour")
	class UBehaviorTree* behaviorTree; //The Zombie's Behavior Tree

	UPROPERTY(EditAnywhere, Category = "Timeline")
		class UCurveFloat* colourCurve;

	//Delegate to be binded with TimelineFloatReturn()
	FOnTimelineFloat GlowColourInterpFunction{};

	UPROPERTY(EditAnywhere)
		float health; //Zombie's Health

private:
	FLinearColor glowColour;

public:
	// Sets default values for this character's properties
	AZombie();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void DealDamage(float damage); //Used to deal damage to the Zombie's

	UFUNCTION(BlueprintCallable)
		void ChangeGlowColour(FLinearColor colour);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void GlowColourTimelineFloatReturn(float value);
};
