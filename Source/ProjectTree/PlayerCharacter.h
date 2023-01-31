// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTREE_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerDash")
	void VectorDash();
	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerDash")
	void StillDash();

protected:
	virtual void BeginPlay() override;


private:


	bool CanDash() const;
	UPROPERTY(EditAnywhere, Category = "PlayerDash")
	float dashRate = 1.f;

	FTimerHandle DashTimer;


	//////////////////// CAMERA ////////////////////

	UPROPERTY(VisibleAnywhere, Category = "Player")
	class USpringArmComponent* springArm;

	UPROPERTY(VisibleAnywhere, Category = "Player")
	class UCameraComponent* camera;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<class AWeapon> weaponClass;
	AWeapon* weapon;

	//////////////////// INPUT ////////////////////
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float amt);
	void MoveRight(float amt);
	void LookUp(float amt);
	void Turn(float amt);
	void MeleeAttack();
	void Dash();
	void SpawnWeapon();
	
};
