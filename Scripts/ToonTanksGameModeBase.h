// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PawnClass/PawnTank.h"
#include "PawnClass/PawnTurret.h"
#include "PlayerControllerBase.h"
#include "ToonTanksGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:

	APawnTank* playerTank;
	int32 numberOfTurrets = 0;
	void HandleGameStart();
	void HandleGameEnd(bool winState);
	APlayerControllerBase* playerController;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop");
	int32 delayAmount = 3;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void GameEnd(bool winState);
public:
	void DeadActor(AActor* actorDied);
};
