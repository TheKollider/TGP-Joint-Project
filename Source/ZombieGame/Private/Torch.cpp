#include "Torch.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "ZombieController.h"
#include "Zombie.h"
#include "Kismet/GameplayStatics.h"
#include "ZombieGameCharacter.h"
#include "Components/SkeletalMeshComponent.h"

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

	//Setting the Light to be off by default
	bLightIsOn = false;
	Light->SetIntensity(0.0f);
	LightToggled.Broadcast(bLightIsOn);
}

// Called every frame
void ATorch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bLightIsOn)
	{
		CurrentBatteryLife = CurrentBatteryLife - (DeltaTime * BatteryDrainPerTick);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::SanitizeFloat(CurrentBatteryLife));
	}

	if (CurrentBatteryLife <= 0 && !batteryDead)
	{
		TurnOff();
		CurrentBatteryLife = 0;
		batteryDead = true;
	}

	if (CanTurnOn())
	{
		batteryDead = false;
	}
}

void ATorch::TurnOn()
{
	check(Light);
	if (CanTurnOn() && torchActive)
	{
		bLightIsOn = true;
		Light->SetIntensity(3000.0f);
		LightToggled.Broadcast(bLightIsOn);

		UGameplayStatics::PlaySoundAtLocation(this, torchOnSound, GetActorLocation());
	}
}

void ATorch::TurnOff()
{
	check(Light);
	if (!CanTurnOn() && torchActive)
	{
		bLightIsOn = false;
		Light->SetIntensity(0.0f);
		LightToggled.Broadcast(bLightIsOn);

		UGameplayStatics::PlaySoundAtLocation(this, torchOffSound, GetActorLocation());
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