// Fill out your copyright notice in the Description page of Project Settings.

#include"Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PawnClass/PawnTank.h"
#include"HealthTank.h"
#include "PowerUpParent.h"

// Sets default values
APowerUpParent::APowerUpParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	/*sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	RootComponent = sphereComponent;*/

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	baseMesh->OnComponentHit.AddDynamic(this, &APowerUpParent::OnHit);
	RootComponent = baseMesh;

}

// Called when the game starts or when spawned
void APowerUpParent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APowerUpParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APowerUpParent::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* componentOwner = this;
	if(!componentOwner)
	{
		UE_LOG(LogTemp, Error, TEXT("The owner is null"));
		return;
	}

	if(OtherActor && OtherActor->IsA<APawnTank>() && OtherActor != this)
	{
		APawnBaseClass* playerPawn = Cast<APawnBaseClass>(OtherActor);
		HandleDestroy(playerPawn);
	}
}

void APowerUpParent::HandleDestroy(APawnBaseClass* playerPawn)
{
	int32 randomNumber = FMath::RandRange(0,1);
	UHealthTank* healthComponent = playerPawn->GetHealthComponent();
	APawnTank* playerTank = Cast<APawnTank>(playerPawn);


	switch (randomNumber)
	{
		case 0:
			UE_LOG(LogTemp, Warning, TEXT("0"));
			healthComponent->SetHealth(100.0f);
			break;
		case 1:
			UE_LOG(LogTemp, Warning, TEXT("1"));
			playerTank->SetMoveSpeed(100.0f);
			break;
		default:
			break;
	}
	//UE_LOG(LogTemp, Warning, TEXT("%f"), healthComponent->GetHealth());
	Destroy();
}

