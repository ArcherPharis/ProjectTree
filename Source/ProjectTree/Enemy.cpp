// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyAIController.h"

AEnemy::AEnemy()
{
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	aiController = Cast<AEnemyAIController>(GetOwner());
}

void AEnemy::Attack()
{
}

void AEnemy::StartBehaviorTree()
{
	if (aiController)
	{
		aiController->BeginEnemyLogic();
		
	}
}
