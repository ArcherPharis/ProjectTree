// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/CanvasPanel.h"

void UInGameUI::UpdateHealth(float health, float maxHealth)
{
	healthBar->SetPercent(health / maxHealth);
}

void UInGameUI::UpdateGrowth(float currentLevel, float maxLevel)
{
	growthBar->SetPercent(currentLevel / maxLevel);
}

void UInGameUI::SwitchToGameOverMenu()
{
	UISwitcher->SetActiveWidget(gameOverCanvas);
}

void UInGameUI::SwitchToPauseMenu()
{
	UISwitcher->SetActiveWidget(pauseCanvas);
}

void UInGameUI::SwitchToCongratsMenu()
{
}

void UInGameUI::NativeConstruct()
{
	continueButton->OnReleased.AddDynamic(this, &UInGameUI::Resume);
	restartButton->OnReleased.AddDynamic(this, &UInGameUI::Restart);
	quitButton->OnReleased.AddDynamic(this, &UInGameUI::Quit);
	restartButtonGameOver->OnReleased.AddDynamic(this, &UInGameUI::Restart);
	quitButtonGameOver->OnReleased.AddDynamic(this, &UInGameUI::Quit);
}

void UInGameUI::Resume()
{
	OnGameResumed.Broadcast();
	UISwitcher->SetActiveWidget(inGameCanvas);
}

void UInGameUI::Restart()
{
	OnGameRestarted.Broadcast();
}

void UInGameUI::Quit()
{
	OnGameQuit.Broadcast();
}
