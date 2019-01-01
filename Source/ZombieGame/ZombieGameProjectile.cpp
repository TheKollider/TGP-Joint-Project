// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ZombieGameProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Zombie.h"

AZombieGameProjectile::AZombieGameProjectile() 
{
	// Use a sphere as a simple collision representation
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->BodyInstance.SetCollisionProfileName("Projectile");
	BoxCollision->OnComponentHit.AddDynamic(this, &AZombieGameProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	BoxCollision->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	BoxCollision->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = BoxCollision;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = BoxCollision;
	ProjectileMovement->InitialSpeed = 6000.f;
	ProjectileMovement->MaxSpeed = 6000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AZombieGameProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag(FName("Zombie")))
	{
		AZombie* zombie = Cast<AZombie>(OtherActor);
		zombie->DealDamage(20);
		Destroy();
	}

	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		Destroy();
	}
}