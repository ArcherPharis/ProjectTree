// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "InGameUI.h"
#include "HealthComponent.h"

void APlayerCharacterController::OnPossess(APawn* newPawn)
{
	Super::OnPossess(newPawn);
	playerCharacter = Cast<APlayerCharacter>(newPawn);
	if (playerCharacter)
	{
		playerCharacter->GetHealthComponent()->onHealthChanged.AddDynamic(this, &APlayerCharacterController::UpdateUIHealth);
		playerCharacter->onLevelUp.AddDynamic(this, &APlayerCharacterController::ChangeIcon);
		if (inGameUIClass && !inGameUI)
		{
			inGameUI = CreateWidget<UInGameUI>(this, inGameUIClass);
			inGameUI->AddToViewport();
			inGameUI->OnGameResumed.AddDynamic(this, &APlayerCharacterController::ResumeGame);
			inGameUI->OnGameRestarted.AddDynamic(this, &APlayerCharacterController::RestartGame);
			inGameUI->OnGameQuit.AddDynamic(this, &APlayerCharacterController::QuitGame);
		}


	}
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerCharacterController::IncreaseEnemiesKilled()
{
	enemiesKilled++;
	if (enemiesKilled <= enemiesToTransform)
	{
		inGameUI->UpdateGrowth(enemiesKilled, enemiesToTransform);
	}
	if (enemiesKilled >= enemiesToTransform && !hasTransformed)
	{
		APlayerCharacter* charact = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
		charact->SwitchCharacter();
		hasTransformed = true;
	}
}

void APlayerCharacterController::SwitchToEndgameScreen()
{
	inGameUI->SwitchToCongratsMenu();
	inGameUI->PlayCreditsAnimation();
}

void APlayerCharacterController::ResumeGame()
{
	UGameplayStatics::SetGamePaused(this, false);
	SetInputMode(FInputModeGameOnly());
	SetShowMouseCursor(false);
}

void APlayerCharacterController::RestartGame()
{
	RestartLevel();
	SetInputMode(FInputModeGameOnly());
}

void APlayerCharacterController::QuitGame()
{
	UGameplayStatics::GetPlayerController(this, 0)->ConsoleCommand("quit");
}

void APlayerCharacterController::PauseGame()
{
	inGameUI->SwitchToPauseMenu();
	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
	UGameplayStatics::SetGamePaused(this, true);
}

void APlayerCharacterController::GameOver()
{
	SetInputMode(FInputModeUIOnly());
	FTimerHandle GOHandle;
	GetWorldTimerManager().SetTimer(GOHandle, this, &APlayerCharacterController::ShowEndScreen, 2.0f, false);

}

void APlayerCharacterController::ShowEndScreen()
{

	inGameUI->SwitchToGameOverMenu();
	SetShowMouseCursor(true);
	UGameplayStatics::SetGamePaused(this, true);
}

void APlayerCharacterController::UpdateUIHealth(float newH, float maxH)
{
	
	inGameUI->UpdateHealth(newH, maxH);
}

void APlayerCharacterController::ChangeIcon(UTexture2D* iconToSwap)
{
	inGameUI->ChangePlayerIcon(iconToSwap);
}
