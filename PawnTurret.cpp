// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "PawnTurret.h"
#include "ToonTanks/PowerUpParent.h"
#include"PawnTank.h"

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(fireTimeHandler,this,&APawnTurret::FireConditionChecker,fireRate,true);
	player = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!player || FireRangeCalculator() > fireRange)
	{
		return;
	}

	TurretRotation(player->GetActorLocation());
}

void APawnTurret::FireConditionChecker() 
{
	if(FireRangeCalculator() <= fireRange && player->GetAliveCondition())
	{
		Fire();
	}
}

float APawnTurret::FireRangeCalculator() const
{
	return FVector::Dist(player->GetActorLocation(),GetActorLocation());
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	if(powerUpDrop)
		APowerUpParent* dummyProjectile = GetWorld()->SpawnActor<APowerUpParent>(powerUpDrop,this->GetActorLocation(),this->GetActorRotation());

	Destroy();
}