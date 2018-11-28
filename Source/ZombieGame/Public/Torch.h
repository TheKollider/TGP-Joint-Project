// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include <Components/SpotLightComponent.h>
#include <Components/StaticMeshComponent.h>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Torch.generated.h"




DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTorchDrained, bool, IsDrained);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTorchToggled, float, CurrentBatteryLife);

UCLASS()
class ZOMBIEGAME_API ATorch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATorch();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Torch")
		UStaticMeshComponent *Mesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Torch")
		USpotLightComponent *Light;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Torch")
		float MaxBatteryLife;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Torch")
		float CurrentBatteryLife;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flashlight")
		float DrainBatteryLifeTickTime;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flashlight")
		float BatteryDrainPerTick;

	UFUNCTION(BlueprintCallable, Category = "Torch")
		void TurnOn();


	UFUNCTION(BlueprintCallable, Category = "Torch")
		void TurnOff();

	UFUNCTION(BlueprintCallable, Category = "Torch")
		void Toggle();

	UPROPERTY(BlueprintReadOnly, Category = "Torch")
		bool bLightIsOn;

	UPROPERTY(BlueprintAssignable, Category = "Torch")
		FTorchToggled LightToggled;

	UPROPERTY(BlueprintAssignable, Category = "Torch")
		FTorchDrained LightDrained;
	
private:

	void BatteryDrain();
	
	bool CanTurnOn();
	
};
