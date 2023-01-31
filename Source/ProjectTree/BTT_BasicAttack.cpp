// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_BasicAttack.h"
#include "AIController.h"
#include "Enemy.h"

UBTT_BasicAttack::UBTT_BasicAttack()
{
	NodeName = "Basic Attack";
}

EBTNodeResult::Type UBTT_BasicAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemy* enemy = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (enemy)
	{
		enemy->Attack();
	}
	return EBTNodeResult::Succeeded;
}
