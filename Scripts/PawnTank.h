// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBaseClass.h"
#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API APawnTank : public APawnBaseClass
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	APawnTank();
	void MoveInput(float Value);
	void RotationInput(float Value);
	void PawnMovement();
	void PawnRotation();
	void HandleDestruction() override;
	bool GetAliveCondition();
	void SetMoveSpeed(float bonusSpeed);
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"));
	UCameraComponent* cameraComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"));
	USpringArmComponent* springArmComponent = nullptr;
	FVector moveDirection;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Speed Variables", meta = (AllowPrivateAccess = "true"));
	float moveSpeed = 150.0f;
	FQuat rotationDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Variables", meta = (AllowPrivateAccess = "true"));
	float rotateSpeed = 170.0f;
	APlayerController* playerController = nullptr;

	bool isAlive = true;
};
