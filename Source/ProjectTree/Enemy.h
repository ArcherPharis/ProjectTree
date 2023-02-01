// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTREE_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemy();

	virtual void BeginPlay() override;

	virtual void Attack();

	virtual void HandleDeath() override;

	void StartBehaviorTree();
protected:
	class AEnemyAIController* GetAIController() const { return aiController; }

private:
	UPROPERTY(EditAnywhere, Category = "Enemy")
	float attackDamage = 10.f;

	class AEnemyAIController* aiController;

	UFUNCTION()
	void OnTouched(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	

	void Die();
};
