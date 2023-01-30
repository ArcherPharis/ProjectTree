// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "Components/ProgressBar.h"

void UInGameUI::UpdateHealth(float health, float maxHealth)
{
	healthBar->SetPercent(health / maxHealth);
}

void UInGameUI::NativeConstruct()
{
}
