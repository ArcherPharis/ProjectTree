// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Worm.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTREE_API AWorm : public AEnemy
{
	GENERATED_BODY()

public:
	AWorm();

	virtual void BeginPlay() override;

private:
	virtual void Attack() override;

	UPROPERTY(EditDefaultsOnly, Category = "Worm")
	USceneComponent* projectileSpawnLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Worm")
	TSubclassOf<class AWormProjectile> wormProjectileClass;

	

	FTimerHandle logicDelayHandle;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float AILogicStartupTime = 2.0f;

	void ReadyToAttack();

	APawn* target;
	
};
