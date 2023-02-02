// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_SpecialAttack.h"
#include "AIController.h"
#include "Enemy.h"

UBTT_SpecialAttack::UBTT_SpecialAttack()
{
	NodeName = "Special Attack";
}

EBTNodeResult::Type UBTT_SpecialAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemy* enemy = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (enemy)
	{
		enemy->SpecialAttack();
	}
	return EBTNodeResult::Succeeded;
}
