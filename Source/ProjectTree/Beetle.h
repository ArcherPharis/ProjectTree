// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Beetle.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTREE_API ABeetle : public AEnemy
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
};
