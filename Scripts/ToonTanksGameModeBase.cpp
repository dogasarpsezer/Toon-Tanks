// Fill out your copyright notice in the Description page of Project Settings.

#include"Kismet/GameplayStatics.h"
#include "ToonTanksGameModeBase.h"


void AToonTanksGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}
void AToonTanksGameModeBase::DeadActor(AActor* actorDied)
{
	if(actorDied == playerTank)
	{
		playerTank->HandleDestruction();
		HandleGameEnd(false);

		if(playerController)
		{
			playerController->SetPlayerController(false);
		}
	}
	else if( APawnTurret* turretObject = Cast<APawnTurret>(actorDied))
	{
		turretObject->HandleDestruction();
		numberOfTurrets--;
		if(numberOfTurrets == 0)
		{
			HandleGameEnd(true);
		}
	}
}
void AToonTanksGameModeBase::HandleGameStart()
{
	TArray<AActor*> turretArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), turretArray);
	numberOfTurrets = turretArray.Num();
	playerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	playerController = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this,0));
	GameStart();

	if (playerController)
	{
		playerController->SetPlayerController(false);

		FTimerHandle timerHandle;
		FTimerDelegate timerDelegate = FTimerDelegate::CreateUObject(playerController,&APlayerControllerBase::SetPlayerController,true);
		GetWorld()->GetTimerManager().SetTimer(timerHandle,timerDelegate,delayAmount,false);
	}
}
void AToonTanksGameModeBase::HandleGameEnd(bool winState)
{
	GameEnd(winState);
}
