// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameResumed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameRestarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameQuit);

/**
 * 
 */
UCLASS()
class PROJECTTREE_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void UpdateHealth(float health, float maxHealth);

	UFUNCTION()
	void UpdateGrowth(float currentLevel, float maxLevel);

	FOnGameResumed OnGameResumed;
	FOnGameRestarted OnGameRestarted;
	FOnGameQuit OnGameQuit;

	void SwitchToGameOverMenu();
	void SwitchToPauseMenu();
	void SwitchToCongratsMenu();
	void ChangePlayerIcon(UTexture2D* newIcon);

protected:
	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* inGameCanvas;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* pauseCanvas;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* gameOverCanvas;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* endGameCreditsCanvas;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* UISwitcher;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* healthBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* growthBar;

	UPROPERTY(meta = (bindWidget))
	class UButton* continueButton;

	UPROPERTY(meta = (bindWidget))
	class UButton* restartButton;

	UPROPERTY(meta = (bindWidget))
	class UButton* quitButton;

	UPROPERTY(meta = (bindWidget))
	class UButton* restartButtonGameOver;

	UPROPERTY(meta = (bindWidget))
	class UButton* quitButtonGameOver;

	UPROPERTY(meta = (bindWidget))
	class UImage* playerImage;

	UFUNCTION()
	void Resume();
	UFUNCTION()
	void Restart();
	UFUNCTION()
	void Quit();

	
};
