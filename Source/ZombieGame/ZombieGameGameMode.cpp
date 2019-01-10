// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieGameGameMode.h"

// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#include "ZombieGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AZombieGameGameMode::AZombieGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	
}

void AZombieGameGameMode::CompleteMission(APawn* InstigatorPawn)
{

	


	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);
		
	}

	OnMissionCompleted(InstigatorPawn);
}





