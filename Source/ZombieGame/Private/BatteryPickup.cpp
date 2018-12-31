// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryPickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ZombieGameCharacter.h"


// Sets default values
ABatteryPickup::ABatteryPickup()
{
 	

	Mesh_Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Component"));
	Mesh_Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = Mesh_Component;

	Sphere_Component = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere_Component"));
	Sphere_Component->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere_Component->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere_Component->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Sphere_Component->SetupAttachment(Mesh_Component);

}

// Called when the game starts or when spawned
void ABatteryPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABatteryPickup::play_effect()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}


void ABatteryPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	play_effect();

	AZombieGameCharacter* myCharacter = Cast<AZombieGameCharacter>(OtherActor);

	if (myCharacter)
	{
		myCharacter->ResetBattery();

		Destroy();
	}

}

