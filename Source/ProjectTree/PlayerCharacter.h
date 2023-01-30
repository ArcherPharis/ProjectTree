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


private:

	//////////////////// CAMERA ////////////////////

	UPROPERTY(VisibleAnywhere, Category = "Player")
	class USpringArmComponent* springArm;

	UPROPERTY(VisibleAnywhere, Category = "Player")
	class UCameraComponent* camera;

	//////////////////// INPUT ////////////////////
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float amt);
	void MoveRight(float amt);
	void LookUp(float amt);
	void Turn(float amt);
	
};
