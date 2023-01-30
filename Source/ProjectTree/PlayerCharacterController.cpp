// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "PlayerCharacter.h"
#include "InGameUI.h"
#include "HealthComponent.h"

void APlayerCharacterController::OnPossess(APawn* newPawn)
{
	Super::OnPossess(newPawn);
	playerCharacter = Cast<APlayerCharacter>(newPawn);
	if (playerCharacter)
	{
		playerCharacter->GetHealthComponent()->onHealthChanged.AddDynamic(this, &APlayerCharacterController::UpdateUIHealth);
	}
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();
	inGameUI = CreateWidget<UInGameUI>(this, inGameUIClass);
	inGameUI->AddToViewport();
}

void APlayerCharacterController::UpdateUIHealth(float newH, float maxH)
{
	
	inGameUI->UpdateHealth(newH, maxH);
}
