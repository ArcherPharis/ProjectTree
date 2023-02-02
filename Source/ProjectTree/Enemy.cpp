// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyAIController.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

AEnemy::AEnemy()
{
	meleeHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Melee Hit Box"));
	meleeHitBox->SetupAttachment(RootComponent);
}

void AEnemy::SetLightAttack(bool wasIt)
{
	bWasLightAttack = wasIt;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	aiController = Cast<AEnemyAIController>(GetOwner());
	meleeHitBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnHit);
	GetWorldTimerManager().SetTimer(logicDelayHandle, this, &AEnemy::ReadyToAttack, AILogicStartupTime, false);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnTouched);
}

void AEnemy::Attack()
{
	int randomNum = FMath::RandRange(0, 100);

	if (randomNum <= 50)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(enemyAttackOne);
		bWasLightAttack = true;
		bWasHeavyAttack = false;
	}
	else
	{
		GetMesh()->GetAnimInstance()->Montage_Play(enemyAttackTwo);
		bWasLightAttack = false;
		bWasHeavyAttack = true;

	}


	
}

void AEnemy::HandleDeath()
{
	Super::HandleDeath();
	aiController->StopEnemyLogic();
	FTimerHandle DeathHandle;
	GetWorldTimerManager().SetTimer(DeathHandle, this, &AEnemy::Die, 2.f, true);
}

void AEnemy::SpecialAttack()
{
}

void AEnemy::SetAttackDamage(float amount)
{
	attackDamage = amount;
}

void AEnemy::StartBehaviorTree()
{
	if (aiController)
	{
		aiController->BeginEnemyLogic();
		GetAIController()->SetKnownPlayer(target);
		
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

void AEnemy::ReadyToAttack()
{
	StartBehaviorTree();
	
}

void AEnemy::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("Player") && OtherActor != this)
	{
		ACharacter* characterToLaunch = Cast<ACharacter>(OtherActor);

		if (bWasLightAttack)
		{
			LaunchTarget(lightAttackForce, characterToLaunch);
		}
		if (bWasHeavyAttack)
		{
			LaunchTarget(heavyAttackForce, characterToLaunch);
		}

		UGameplayStatics::ApplyDamage(OtherActor, -attackDamage, GetController(), this, UDamageType::StaticClass());
	}
}
