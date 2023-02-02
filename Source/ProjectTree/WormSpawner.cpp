// Fill out your copyright notice in the Description page of Project Settings.


#include "WormSpawner.h"
#include "Components/SphereComponent.h"
#include "Worm.h"

// Sets default values
AWormSpawner::AWormSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);
	detectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
	detectionSphere->SetupAttachment(rootComp);
	spawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("WormSpawnLocation"));
	spawnLocation->SetupAttachment(rootComp);

}

// Called when the game starts or when spawned
void AWormSpawner::BeginPlay()
{
	Super::BeginPlay();
	detectionSphere->OnComponentBeginOverlap.AddDynamic(this, &AWormSpawner::OnPlayerTrigger);
}

// Called every frame
void AWormSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWormSpawner::OnPlayerTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag(TEXT("Player")) && !isSpawned)
	{
		isSpawned = true;
		enemy = GetWorld()->SpawnActor<AEnemy>(enemyClass, spawnLocation->GetComponentLocation(), GetActorRotation());
		
	}
}

