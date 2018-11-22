// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Zombie.h"
#include "Engine.h"

AZombieController::AZombieController()
{
	behaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(FName("BehaviorTreeComp"));
	blackboardComp = CreateDefaultSubobject<UBlackboardComponent>(FName("BlackBoardComp"));
}

void AZombieController::Possess(APawn * pawn)
{
	Super::Possess(pawn);

	zombieParent = Cast<AZombie>(pawn);
	if (zombieParent)
	{
		if (zombieParent->behaviorTree->BlackboardAsset)
		{
			blackboardComp->InitializeBlackboard(*(zombieParent->behaviorTree->BlackboardAsset));
			behaviorComp->StartTree(*zombieParent->behaviorTree);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Blackboard Asset doesn't exist"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed Cast to Zombie"));
	}
}

void AZombieController::Tick(float DeltaTime)
{
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	blackboardComp->SetValueAsVector(FName("PlayerPosition"), player->GetActorLocation());
}
