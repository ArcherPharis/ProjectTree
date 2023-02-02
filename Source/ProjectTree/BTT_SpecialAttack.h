// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_SpecialAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTREE_API UBTT_SpecialAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_SpecialAttack();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
