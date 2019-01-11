// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieGameMode.h"

// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#include "ZombieGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AZombieGameMode::AZombieGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	
}

void AZombieGameMode::CompletedMission(APawn* InstigatorPawn)
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);
	}

	OnMissionCompleted(InstigatorPawn);
}




