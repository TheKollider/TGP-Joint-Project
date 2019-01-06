
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ZombieGameGameMode.generated.h"

/**
 *
 */
UCLASS()
class AZombieGameGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:

	AZombieGameGameMode();

	void CompleteMission(APawn* InstigatorPawn);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void OnMissionCompleted(APawn* InstigatorPawn);
};