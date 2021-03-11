// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectileBase.generated.h"


class UProjectileMovementComponent;
class UParticleSystemComponent;
UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat AI", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* projectileMovement = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat AI", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* staticMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType> damageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float moveSpeed = 1500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* projectileTrail = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	float damage = 50.0f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* hitParticleSystem;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* hitEffect;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* createEffect;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UCameraShake> cameraHitShake;
};
