// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyAIController.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

AEnemy::AEnemy()
{
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	aiController = Cast<AEnemyAIController>(GetOwner());
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnTouched);
}

void AEnemy::Attack()
{
}

void AEnemy::HandleDeath()
{
	Super::HandleDeath();
	aiController->StopEnemyLogic();
	FTimerHandle DeathHandle;
	GetWorldTimerManager().SetTimer(DeathHandle, this, &AEnemy::Die, 2.f, true);
}

void AEnemy::StartBehaviorTree()
{
	if (aiController)
	{
		aiController->BeginEnemyLogic();
		
	}
}

void AEnemy::OnTouched(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		UGameplayStatics::ApplyDamage(OtherActor, -attackDamage, GetOwner()->GetInstigatorController(), this, UDamageType::StaticClass());
	}
}

void AEnemy::Die()
{
	Destroy();
}
