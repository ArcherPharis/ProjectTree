// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BrainComponent.h"
#include "Kismet/GameplayStatics.h"

AEnemyAIController::AEnemyAIController()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComp");
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	if (SightConfig)
	{
		PerceptionComp->ConfigureSense(*SightConfig);
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::PerceptionUpdated);
	}
}

void AEnemyAIController::BeginEnemyLogic()
{
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		
	}
}

void AEnemyAIController::StopEnemyLogic()
{
	BrainComponent->StopLogic("cuz it ded");
}

void AEnemyAIController::SetKnownPlayer(APawn*& target)
{
	if (PlayerAlwaysKnown)
	{
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
		GetBlackboardComponent()->SetValueAsObject(TargetBlackboardKeyName, PlayerPawn);
		target = PlayerPawn;
	}
}

void AEnemyAIController::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (PlayerAlwaysKnown)
	{
		return;
	}

	if (Stimulus.WasSuccessfullySensed())
	{
		GetBlackboardComponent()->SetValueAsObject(TargetBlackboardKeyName, Actor);
	}
	else
	{
		auto PerceptionInfo = PerceptionComp->GetActorInfo(*Actor);
		if (!PerceptionInfo->HasAnyCurrentStimulus())
		{
			UE_LOG(LogTemp, Warning, TEXT("They gone: %s"), *Actor->GetName());
			GetBlackboardComponent()->ClearValue(TargetBlackboardKeyName);
		}
	}
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();



}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	IGenericTeamAgentInterface* TAInterface = Cast<IGenericTeamAgentInterface>(InPawn);
	if (TAInterface)
	{
		TeamID = TAInterface->GetGenericTeamId();
	}
}
