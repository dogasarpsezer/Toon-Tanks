// Fill out your copyright notice in the Description page of Project Settings.

#include"Kismet/GameplayStatics.h"
#include "HealthTank.h"

// Sets default values for this component's properties
UHealthTank::UHealthTank()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	
}


// Called when the game starts
void UHealthTank::BeginPlay()
{
	Super::BeginPlay();

	health = defaultStartingHealth;
	gameModeBase = Cast<AToonTanksGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//GetOwner()->OnTakeAnyDamage.AddDynamic(this,&UHealthTank::TakeDamage);
	
}


/*void UHealthTank::TakeDamage(AActor* damagedActor, float damageAmount, const UDamageType* damageType, AController* instigatedBy, AActor* damageCauser)
{
	if(damageAmount == 0 || health <= 0.0f)
	{
		return;
	}
	UE_LOG(LogTemp, Error, TEXT("%f"), health);
	if(health <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor died"));
		if(gameModeBase)
		{
			gameModeBase->DeadActor(GetOwner());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("gameModeBase had nullptr assigned"));
		}
	}
}*/
void UHealthTank::HealthManager(APawnBaseClass* damagedActor,float damage)
{
	if(damagedActor->IsA<APawnBaseClass>())
	{
		UE_LOG(LogTemp, Warning, TEXT("A Pawn was hit"));
		damagedActor->GetHealthComponent()->SetHealth(-damage);
		if(damagedActor->GetHealthComponent()->GetHealth() <= 0.0f)
		{
			if (gameModeBase)
			{
				gameModeBase->DeadActor(damagedActor);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("gameModeBase had nullptr assigned"));
			}
		}
	}
}
void UHealthTank::SetHealth(float change)
{
	this->health += change;
}

float UHealthTank::GetHealth()
{
	return health;
}

