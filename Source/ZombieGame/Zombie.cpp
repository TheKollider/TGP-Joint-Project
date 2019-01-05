// Fill out your copyright notice in the Description page of Project Settings.

#include "Zombie.h"
#include "ZombieController.h"
#include "ZombieGameCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/PointLightComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AZombie::AZombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	zombieRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ZombieRoot"));
	RootComponent = zombieRoot;

	AttackTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	AttackTriggerBox->BodyInstance.SetCollisionProfileName("Trigger");
	AttackTriggerBox->SetupAttachment(GetCapsuleComponent());
	AttackTriggerBox->InitBoxExtent(FVector(64.0f, 64.0f, 64.0f));
	AttackTriggerBox->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	glowColourTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("GlowColourTimeLine"));
	GlowColourInterpFunction.BindUFunction(this, FName("GlowColourTimelineFloatReturn"));

	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));

	Tags.Add(FName("Zombie"));
}

// Called when the game starts or when spawned
void AZombie::BeginPlay()
{
	Super::BeginPlay();

	AttackTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AZombie::BeginOverlap);
	AttackTriggerBox->OnComponentEndOverlap.AddDynamic(this, &AZombie::EndOverlap);
	
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

void AZombie::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->ActorHasTag(FName("Player")))
	{
		AZombieController* controller = Cast<AZombieController>(GetController());
		controller->SetState(4);
	}
}

void AZombie::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(FName("Player")))
	{
		AZombieController* controller = Cast<AZombieController>(GetController());
		controller->SetState(2);
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

void AZombie::Enrage()
{
	if (dead || enraged)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Enraged"));
	enraged = true;
	AZombieController* controller = Cast<AZombieController>(GetController());
	controller->Enrage();
}

void AZombie::PlayEnrageSound()
{
	if (audioComponent->IsPlaying())
	{
		audioComponent->Stop();
	}

	audioComponent->SetSound(enrageSound);
	audioComponent->Play();
}

void AZombie::PlayDeathSound()
{
	if (audioComponent->IsPlaying())
	{
		audioComponent->Stop();
	}

	audioComponent->SetSound(deathSound);
	audioComponent->Play();
}