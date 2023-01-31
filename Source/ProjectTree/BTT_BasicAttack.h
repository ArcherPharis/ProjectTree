// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_BasicAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTREE_API UBTT_BasicAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_BasicAttack();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
