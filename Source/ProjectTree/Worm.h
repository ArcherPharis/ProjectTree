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

	UFUNCTION(BlueprintCallable, Category = "Worm")
	void SpawnProjectile();

private:
	virtual void Attack() override;
	virtual void SpecialAttack() override;

	UPROPERTY(EditDefaultsOnly, Category = "Worm")
	USceneComponent* projectileSpawnLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Worm")
	TSubclassOf<class AWormProjectile> wormProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Worm")
	USoundBase* wormSpit;
	

	
	
};
