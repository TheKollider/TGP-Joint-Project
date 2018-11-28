// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BatteryPickup.generated.h"

class USphereComponent;

UCLASS()
class ZOMBIEGAME_API ABatteryPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABatteryPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* Mesh_Component;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* Sphere_Component;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* PickupFX;

	void play_effect();


public:	
	// Called every frame
	

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
};
