// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "BaseCharacter.generated.h"

UCLASS()
class PROJECTTREE_API ABaseCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	class UHealthComponent* GetHealthComponent() const { return healthComp; }

	virtual void HandleDeath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Assigns Team Agent to given TeamID */
	FORCEINLINE virtual void SetGenericTeamId(const FGenericTeamId& ID) { TeamID = ID; }

	/** Retrieve team identifier in form of FGenericTeamId */
	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const { return TeamID; }

	UAnimMontage* GetFlinchMontage() const { return FlinchMontage; }

	virtual void OnTakeDamage();

	bool IsDead();

	USoundBase* GetDeathSound() const { return DeathSound; }
	USoundBase* GetAttackSound() const { return AttackSound; }
private:
	UPROPERTY(EditAnywhere, Category = "AI")
	FGenericTeamId TeamID;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* FlinchMontage;

	UPROPERTY(EditDefaultsOnly, Category = "HealthComponent")
	UHealthComponent* healthComp;

	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* AttackSound;

	UPROPERTY()
	class UAIPerceptionStimuliSourceComponent* PerceptionStimuliComp;

};
