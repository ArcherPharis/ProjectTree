// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Mushroom.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTREE_API AMushroom : public AEnemy
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	virtual void Attack() override;


	
};
