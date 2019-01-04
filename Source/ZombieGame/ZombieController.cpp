// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Zombie.h"
#include "Engine.h"
#include "ZombieGameCharacter.h"
#include "BaseZombieAnimInstance.h"
#include "AI/NavigationSystemBase.h"

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
	AZombieGameCharacter* player = Cast<AZombieGameCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	blackboardComp->SetValueAsObject(FName("Player"), player);

	//Sets the Zombie's State to Dead if it's health gets to or below 0
	if (!zombieParent->dead && zombieParent->health <= 0.0f)
	{
		zombieParent->dead = true;
		blackboardComp->SetValueAsEnum(FName("Dead"), true);
		zombieParent->GetCharacterMovement()->Deactivate();
	

		SetState(3);
	}
}

void AZombieController::SetState(int state)
{
	behaviorComp->StopTree();

	blackboardComp->SetValueAsEnum(FName("ZombieState"), state);
	UBaseZombieAnimInstance* zombieAnimInstance = Cast<UBaseZombieAnimInstance>(zombieParent->GetMesh()->GetAnimInstance());
	zombieAnimInstance->stateNum = state;

	behaviorComp->StartTree(*zombieParent->behaviorTree);
}

void AZombieController::Enrage()
{
	blackboardComp->SetValueAsEnum(FName("ZombieState"), 2);
	UBaseZombieAnimInstance* zombieAnimInstance = Cast<UBaseZombieAnimInstance>(zombieParent->GetMesh()->GetAnimInstance());
	zombieAnimInstance->stateNum = 2;
}

void AZombieController::GetRandomPosition(FVector randomPosition)
{
	blackboardComp->SetValueAsVector(FName("RandomLocation"), randomPosition);
	behaviorComp->RestartTree();
}
