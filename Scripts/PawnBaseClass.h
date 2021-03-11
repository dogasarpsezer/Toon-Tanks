// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "PawnBaseClass.generated.h"

class UCapsuleComponent;
class AProjectileBase;
class UHealthTank;
UCLASS()
class TOONTANKS_API APawnBaseClass : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnBaseClass();
	virtual void HandleDestruction();
	UHealthTank* GetHealthComponent();
protected:
	void TurretRotation(FVector target);
	void Fire();
	UStaticMeshComponent* getTurret();
private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* capsuleComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* baseMesh = nullptr;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* turretMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USceneComponent* bulletSpawnPoint = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> projectileBase;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health Component", meta = (AllowPrivateAccess = "true"))
	UHealthTank* healthComponent;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* deathParticle;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* deathEffect;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UCameraShake> cameraExplodeShake;
};
