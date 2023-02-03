// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTREE_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* newPawn) override;

	virtual void BeginPlay() override;

	void IncreaseEnemiesKilled();

	UFUNCTION(BlueprintCallable, Category = "PlayerController")
	void SwitchToEndgameScreen();


	UFUNCTION()
	void ResumeGame();

	UFUNCTION()
	void RestartGame();

	UFUNCTION()
	void QuitGame();

	void PauseGame();

	void GameOver();

private:
	class APlayerCharacter* playerCharacter;
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<class UInGameUI> inGameUIClass;
	UInGameUI* inGameUI;

	void ShowEndScreen();

	UFUNCTION()
	void UpdateUIHealth(float newH, float maxH);

	UFUNCTION()
	void ChangeIcon(UTexture2D* iconToSwap);

	UPROPERTY(EditAnywhere, Category = "KillCount")
	int enemiesKilled = 0;
	UPROPERTY(EditAnywhere, Category = "KillCount")
	int enemiesToTransform = 0;

	bool hasTransformed = false;
	
};
