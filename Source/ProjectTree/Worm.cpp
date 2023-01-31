// Fill out your copyright notice in the Description page of Project Settings.


#include "Worm.h"
#include "EnemyAIController.h"
#include "WormProjectile.h"
#include "Kismet/KismetMathLibrary.h"

AWorm::AWorm()
{
	projectileSpawnLocation = CreateEditorOnlyDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnLocation"));
	projectileSpawnLocation->SetupAttachment(RootComponent);
}

void AWorm::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(logicDelayHandle, this, &AWorm::ReadyToAttack, AILogicStartupTime, false);
}

void AWorm::Attack()
{
	if (target)
	{
		
		FVector spawnLoc = projectileSpawnLocation->GetComponentLocation();
		FVector targetLoc = target->GetActorLocation();
		projectileSpawnLocation->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(spawnLoc, targetLoc));
		AWormProjectile* wormProjectile = GetWorld()->SpawnActor<AWormProjectile>(wormProjectileClass, projectileSpawnLocation->GetComponentLocation(), projectileSpawnLocation->GetComponentRotation());
		wormProjectile->SetOwner(this);
	}
	
}

void AWorm::ReadyToAttack()
{
	StartBehaviorTree();
	GetAIController()->SetKnownPlayer(target);
}
