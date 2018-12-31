// Fill out your copyright notice in the Description page of Project Settings.

#include "Zombie.h"
#include "ZombieController.h"
#include "ZombieGameCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/PointLightComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AZombie::AZombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	zombieRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ZombieRoot"));
	RootComponent = zombieRoot;

	glowColourTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("GlowColourTimeLine"));
	GlowColourInterpFunction.BindUFunction(this, FName("GlowColourTimelineFloatReturn"));
}

// Called when the game starts or when spawned
void AZombie::BeginPlay()
{
	Super::BeginPlay();
	
	AZombieController* AIController = Cast<AZombieController>(GetController());
	AZombieGameCharacter* player = Cast<AZombieGameCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (colourCurve)
	{
		glowColourTimeLine->AddInterpFloat(colourCurve, GlowColourInterpFunction, FName("Alpha"));

		glowColour = FindComponentByClass<UPointLightComponent>()->GetLightColor();

		//Setting Timeline settings
		glowColourTimeLine->SetLooping(false);
		glowColourTimeLine->SetIgnoreTimeDilation(true);
	}
}

void AZombie::GlowColourTimelineFloatReturn(float value)
{
	FLinearColor pointLightColour = FindComponentByClass<UPointLightComponent>()->GetLightColor();
	FLinearColor lerpColour = UKismetMathLibrary::LinearColorLerp(pointLightColour, glowColour, value);

	TArray<UPointLightComponent*> pointLights;
	GetComponents<UPointLightComponent>(pointLights);
	for (int i = 0; i < pointLights.Num(); i++) {
		UPointLightComponent* Light = pointLights[i];
		Light->SetLightColor(lerpColour);
	}
}

// Called every frame
void AZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZombie::DealDamage(float damage)
{
	health -= damage;
}

void AZombie::ChangeGlowColour(FLinearColor colour)
{
	glowColour = colour;
	glowColourTimeLine->PlayFromStart();
}
