// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ToonTanksGameModeBase.h"
#include "HealthTank.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthTank : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
	float defaultStartingHealth = 100.0f;
	float health = 0.0f;
	bool isDead = false;
	AToonTanksGameModeBase* gameModeBase = nullptr;
public:	
	// Sets default values for this component's properties
	UHealthTank();
	void SetHealth(float change);
	float GetHealth();
	void HealthManager(APawnBaseClass* damagedActor, float damage);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/*UFUNCTION()
	void TakeDamage(AActor* damagedActor,float damageAmount, const UDamageType* damageType, AController* instigatedBy, AActor* damageCauser  );*/

		
};
