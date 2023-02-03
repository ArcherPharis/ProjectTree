// Fill out your copyright notice in the Description page of Project Settings.


#include "Worm.h"
#include "EnemyAIController.h"
#include "WormProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AWorm::AWorm()
{
	projectileSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnLocation"));
	projectileSpawnLocation->SetupAttachment(RootComponent);
}

void AWorm::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AWorm::SpawnProjectile()
{
	FVector spawnLoc = projectileSpawnLocation->GetComponentLocation();
	FVector targetLoc = target->GetActorLocation();
	projectileSpawnLocation->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(spawnLoc, targetLoc));
	AWormProjectile* wormProjectile = GetWorld()->SpawnActor<AWormProjectile>(wormProjectileClass, projectileSpawnLocation->GetComponentLocation(), projectileSpawnLocation->GetComponentRotation());
	wormProjectile->SetOwner(this);
}

void AWorm::Attack()
{
	if (target)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(GetMontageAttackTwo());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), wormSpit, GetActorLocation());
	}
	
}

void AWorm::SpecialAttack()
{
	if (target)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(GetMontageAttackOne());
		SetLightAttack(true);

	}
}

