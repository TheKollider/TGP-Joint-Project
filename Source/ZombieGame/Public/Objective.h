// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objective.generated.h"

class USphereComponent;

UCLASS()
class ZOMBIEGAME_API AObjective : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjective();

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* Mesh_Component;


	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* Sphere_Component;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* PickupFX;

	
	virtual void BeginPlay() override;

	void play_effect();

public:	
	// Called every frame
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	
	
};
