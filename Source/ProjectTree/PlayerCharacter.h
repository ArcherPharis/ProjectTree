// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUp, UTexture2D*, newIcon);

/**
 * 
 */
UCLASS()
class PROJECTTREE_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	FOnLevelUp onLevelUp;

	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerDash")
	void VectorDash();
	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerDash")
	void StillDash();
	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerDash")
	void TakeHit();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure, Category = "Player")
	class AWeapon* GetWeapon() const { return weapon; }

	UFUNCTION(BlueprintCallable, Category = "Player")
	void SwitchCharacter();

	UFUNCTION(BlueprintImplementableEvent, Category = "Player")
	void AttackButtonClicked();


private:

	virtual void HandleDeath() override;

	bool CanDash() const;
	UPROPERTY(EditAnywhere, Category = "PlayerDash")
	float dashRate = 1.f;

	FTimerHandle DashTimer;

	UPROPERTY(EditDefaultsOnly, Category = "PlayerDash")
	UAnimMontage* DashMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	USoundBase* TransformationSound;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	USoundBase* JumpSound;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	UTexture2D* LevelUpIcon;



	//////////////////// CAMERA ////////////////////

	UPROPERTY(VisibleAnywhere, Category = "Player")
	class USpringArmComponent* springArm;

	UPROPERTY(VisibleAnywhere, Category = "Player")
	class UCameraComponent* camera;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AWeapon> weaponClass;
	AWeapon* weapon;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<APlayerCharacter> teenClass;
	APlayerCharacter* teen;

	//////////////////// INPUT ////////////////////
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float amt);
	void MoveRight(float amt);
	void LookUp(float amt);
	void Turn(float amt);
	void MeleeAttack();
	void Dash();
	void SpawnWeapon();
	void Pause();
	virtual void Jump() override;


	
};
