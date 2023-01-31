// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "GenericTeamAgentInterface.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTREE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyAIController();

public:
	FORCEINLINE virtual void SetGenericTeamId(const FGenericTeamId& ID) { TeamID = ID; }

	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const { return TeamID; }

	void BeginEnemyLogic();
	void SetKnownPlayer(APawn*& target);

private:
	FGenericTeamId TeamID;
	UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
	class UAIPerceptionComponent* PerceptionComp;
	UPROPERTY()
	class UAISenseConfig_Sight* SightConfig;

	UFUNCTION()
	void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	bool PlayerAlwaysKnown = false;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName TargetBlackboardKeyName {"Target"};

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;



protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	
};
