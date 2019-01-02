#include "Torch.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "ZombieController.h"
#include "Zombie.h"



// Sets default values
ATorch::ATorch()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Light = CreateDefaultSubobject<USpotLightComponent>(TEXT("Light"));
	Light->SetupAttachment(Mesh);

	LightDetection = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Light Detection Mesh"));
	LightDetection->SetupAttachment(Light);

	MaxBatteryLife = 1.0f;
	CurrentBatteryLife = MaxBatteryLife;
	DrainBatteryLifeTickTime = 3.5f;
	BatteryDrainPerTick = 0.05f;
}

// Called when the game starts or when spawned
void ATorch::BeginPlay()
{
	Super::BeginPlay();

	TurnOff(); //Setting the Light to be off by default
}

// Called every frame
void ATorch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CanTurnOn())
	{
		CurrentBatteryLife = CurrentBatteryLife - (DeltaTime * BatteryDrainPerTick);
	}

	if (CurrentBatteryLife <= 0)
	{
		TurnOff();
		CurrentBatteryLife = 0;
		CanTurnOn();
	}

	//Checks to see if Zombie's are colliding with the torch light, and if they are, they are enraged
	if (bLightIsOn)
	{
		TArray<AActor*> overlappingZombies;
		LightDetection->GetOverlappingActors(overlappingZombies, TSubclassOf<AZombie>());

		for (int i = 0; i < overlappingZombies.Num(); i++)
		{
			AZombie* zombie = Cast<AZombie>(overlappingZombies[i]);
			AZombieController* zombieController = Cast<AZombieController>(zombie->GetController());
			zombieController->Enrage();
		}
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
	return (CurrentBatteryLife > 0.0f && !bLightIsOn && torchActive);
}