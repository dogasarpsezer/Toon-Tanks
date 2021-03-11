// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include"ToonTanks/HealthTank.h"
#include "PawnTank.h"

APawnTank::APawnTank()
{
	springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	springArmComponent->SetupAttachment(RootComponent);
	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cameraComponent->SetupAttachment(springArmComponent);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
	
	if(!springArmComponent || !cameraComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("NULLPTR AVAILABLE"));
		return;
	}

	playerController = Cast<APlayerController>(GetController());
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PawnMovement();
	PawnRotation();

	if(playerController)
	{
		FHitResult hit;
		playerController->GetHitResultUnderCursor(ECC_Visibility,false,hit);
		FVector hitLocation = hit.ImpactPoint;
		TurretRotation(hitLocation);
	}

	//UE_LOG(LogTemp, Error, TEXT("%f canın var"),this->GetHealthComponent()->GetHealth());
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this,&APawnTank::MoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::RotationInput);
	PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&APawnTank::Fire);
}

void APawnTank::MoveInput(float Value)
{
	moveDirection = FVector(Value * moveSpeed * GetWorld()->DeltaTimeSeconds,0,0);
}

void APawnTank::RotationInput(float Value)
{
	float rotationAmount = Value * rotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator rotation = FRotator(0,rotationAmount,0);
	rotationDirection = FQuat(rotation);
}

void APawnTank::PawnMovement()
{
	AddActorLocalOffset(moveDirection,true);
}

void APawnTank::PawnRotation()
{
	AddActorLocalRotation(rotationDirection);
}
void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();

	isAlive = false;

	SetActorHiddenInGame(!isAlive);
	SetActorTickEnabled(isAlive);
}

bool APawnTank::GetAliveCondition()
{
	return isAlive;
}

void APawnTank::SetMoveSpeed(float bonusSpeed)
{
	moveSpeed += bonusSpeed;
}