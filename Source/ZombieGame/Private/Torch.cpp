// Fill out your copyright notice in the Description page of Project Settings.

#include "Torch.h"
#include "Engine.h"





// Sets default values
ATorch::ATorch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Light = CreateDefaultSubobject<USpotLightComponent>(TEXT("Light"));
	Light->SetupAttachment(Mesh);

	MaxBatteryLife = 1.0f;
	CurrentBatteryLife = MaxBatteryLife;
	DrainBatteryLifeTickTime = 3.5f;
	BatteryDrainPerTick = 0.05f;
	
	
	
}

// Called when the game starts or when spawned
void ATorch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATorch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	CurrentBatteryLife -= (DeltaTime * CurrentBatteryLife);

	if (CurrentBatteryLife <= 0)
	{
		TurnOff();
		CurrentBatteryLife = 0;
		CanTurnOn();
	}

	

	
}

void ATorch::TurnOn()
{
	
	check(Light);
	if (CanTurnOn())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Torch is on"));
		bLightIsOn = true;
		Light->SetIntensity(3000.0f);
		LightToggled.Broadcast(bLightIsOn);
	}
}

void ATorch::TurnOff()
{
	check(Light);
	if (!CanTurnOn())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Torch is off"));
		bLightIsOn = false;
		Light->SetIntensity(0.0f);
		LightToggled.Broadcast(bLightIsOn);
		
	}
}

void ATorch::Toggle()
{
	if (CanTurnOn())
	{
		TurnOn();
		
	}
	else
	{
		TurnOff();
		
	}
}

void ATorch::BatteryDrain()
{
	if (bLightIsOn)
	{
		if (CurrentBatteryLife > 0.0f)
		{
			CurrentBatteryLife -= BatteryDrainPerTick;
		}
		else
		{
			CurrentBatteryLife = 0.0f;
			TurnOff();
		}
	}
}

bool ATorch::CanTurnOn()
{
	return (CurrentBatteryLife > 0.0f && !bLightIsOn);
}