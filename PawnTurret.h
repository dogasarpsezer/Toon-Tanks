// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBaseClass.h"
#include "PawnTurret.generated.h"

class APawnTank;
class APowerUpParent;
UCLASS()
class TOONTANKS_API APawnTurret : public APawnBaseClass
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction() override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat AI", meta = (AllowPrivateAccess = "true"))
	float fireRate = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat AI", meta = (AllowPrivateAccess = "true"))
	float fireRange = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drop", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APowerUpParent> powerUpDrop;
	FTimerHandle fireTimeHandler;
	void FireConditionChecker();
	APawnTank* player;
	float FireRangeCalculator() const;
};
