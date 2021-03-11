// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CapsuleComponent.h"
#include "PawnBaseClass.h"
#include "ToonTanks/HealthTank.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/ProjectileBase.h"

// Sets default values
APawnBaseClass::APawnBaseClass()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = capsuleComponent;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh->SetupAttachment(RootComponent);

	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	turretMesh->SetupAttachment(baseMesh);

	bulletSpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Spawn Point"));
	bulletSpawnPoint->SetupAttachment(turretMesh);

	healthComponent = CreateDefaultSubobject<UHealthTank>(TEXT("Health Component"));
}

void APawnBaseClass::TurretRotation(FVector target)
{
	FVector targetVector = FVector(target.X,target.Y,turretMesh->GetComponentLocation().Z);
	FVector startLocation = turretMesh->GetComponentLocation();

	FRotator targetRotation = FVector(targetVector - startLocation).Rotation();
	turretMesh->SetWorldRotation(targetRotation);
}

void APawnBaseClass::Fire()
{
	if(projectileBase)
	{
		AProjectileBase* dummyProjectile = GetWorld()->SpawnActor<AProjectileBase>(projectileBase, bulletSpawnPoint->GetComponentLocation(), bulletSpawnPoint->GetComponentRotation());
		dummyProjectile->SetOwner(this);
	}
}

void APawnBaseClass::HandleDestruction()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, deathParticle, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this,deathEffect,GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(cameraExplodeShake);
}

UHealthTank* APawnBaseClass::GetHealthComponent()
{
	return healthComponent;
}

UStaticMeshComponent* APawnBaseClass::getTurret()
{
	return turretMesh;
}

