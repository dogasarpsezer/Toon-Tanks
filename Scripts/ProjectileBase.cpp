// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include"Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "PawnClass/PawnBaseClass.h"
#include"HealthTank.h"
#include "ProjectileBase.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	staticMesh->OnComponentHit.AddDynamic(this,&AProjectileBase::OnHit);
	RootComponent = staticMesh;
	
	projectileTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectile Trail Component"));
	projectileTrail->SetupAttachment(RootComponent);

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	InitialLifeSpan = 3.0f;

	projectileMovement->InitialSpeed = moveSpeed;
	projectileMovement->MaxSpeed = moveSpeed;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySoundAtLocation(this,createEffect,GetActorLocation());
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* thisComponentOwner = GetOwner();


	if(!thisComponentOwner)
	{
		return;
	}

	if(OtherActor && OtherActor != this && OtherActor != thisComponentOwner && OtherActor->IsA<APawnBaseClass>())
	{
		/*if(OtherActor->IsA<APawnBaseClass>())
		{
			APawnBaseClass* hitPawn = Cast<APawnBaseClass>(OtherActor);

			hitPawn->GetHealthComponent()->SetHealth(-damage);
		}*/
		//UGameplayStatics::ApplyDamage(OtherActor,damage,thisComponentOwner->GetInstigatorController(),this,damageType);
		Cast<APawnBaseClass>(OtherActor)->GetHealthComponent()->HealthManager(Cast<APawnBaseClass>(OtherActor), damage);
		UGameplayStatics::SpawnEmitterAtLocation(this,hitParticleSystem,GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(this, hitEffect, GetActorLocation());
		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(cameraHitShake);
	}
		Destroy();
}

