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

	void SetLightAttack(bool wasIt);

	virtual void BeginPlay() override;

	virtual void Attack();

	virtual void HandleDeath() override;

	virtual void SpecialAttack();



	UFUNCTION(BlueprintCallable, Category = "Enemy")
	class UBoxComponent* GetMeleeHitBox() const { return meleeHitBox; }

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void SetAttackDamage(float amount);

	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy")
	void LaunchTarget(float force, ACharacter* targetToLaunch);

	APawn* target;

	void StartBehaviorTree();
protected:
	class AEnemyAIController* GetAIController() const { return aiController; }

	UAnimMontage* GetMontageAttackOne() const { return enemyAttackOne; }
	UAnimMontage* GetMontageAttackTwo() const { return enemyAttackTwo; }

	virtual void OnTakeDamage() override;


private:
	UPROPERTY(EditAnywhere, Category = "Enemy")
	float attackDamage = 10.f;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	float lightAttackForce = 400.f;
	UPROPERTY(EditAnywhere, Category = "Enemy")
	float heavyAttackForce = 900.f;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	UAnimMontage* enemyAttackOne;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	UAnimMontage* enemyAttackTwo;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	UBoxComponent* meleeHitBox;

	class AEnemyAIController* aiController;

	UFUNCTION()
	void OnTouched(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	
	void Die();

	FTimerHandle logicDelayHandle;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float AILogicStartupTime = 2.0f;

	void ReadyToAttack();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	bool bWasLightAttack;
	bool bWasHeavyAttack;
	bool logicStarted = false;
};
