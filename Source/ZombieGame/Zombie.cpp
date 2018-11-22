// Fill out your copyright notice in the Description page of Project Settings.

#include "Zombie.h"
#include "ZombieController.h"
#include "ZombieGameCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"



// Sets default values
AZombie::AZombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	zombieRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ZombieRoot"));
	RootComponent = zombieRoot;
}

// Called when the game starts or when spawned
void AZombie::BeginPlay()
{
	Super::BeginPlay();
	
	AZombieController* AIController = Cast<AZombieController>(GetController());
	AZombieGameCharacter* player = Cast<AZombieGameCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

// Called every frame
void AZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
