// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon.h"

APlayerCharacter::APlayerCharacter()
{
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArm->SetupAttachment(RootComponent);
	springArm->bUsePawnControlRotation = true;

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	camera->SetupAttachment(springArm);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapon();
}

bool APlayerCharacter::CanDash() const
{
	return !GetWorldTimerManager().IsTimerActive(DashTimer);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJumping);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::MeleeAttack);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &APlayerCharacter::Dash);

}

void APlayerCharacter::MoveForward(float amt)
{
	AddMovementInput(FVector(camera->GetForwardVector().X, camera->GetForwardVector().Y, 0).GetSafeNormal(), amt);
}

void APlayerCharacter::MoveRight(float amt)
{
	AddMovementInput(camera->GetRightVector(), amt);
}

void APlayerCharacter::LookUp(float amt)
{
	AddControllerPitchInput(amt);
}

void APlayerCharacter::Turn(float amt)
{
	AddControllerYawInput(amt);

}

void APlayerCharacter::MeleeAttack()
{
	if (weapon)
	{
		weapon->Attack(GetMesh());
		
	}
}

void APlayerCharacter::Dash()
{
	if (CanDash())
	{
		float currentSpeed = GetVelocity().Length();
		if (currentSpeed == 0 || !GetCharacterMovement()->IsFalling())
		{
			StillDash();
			GetWorldTimerManager().SetTimer(DashTimer, 1 / dashRate, false);
		}
		else
		{

			VectorDash();
			GetWorldTimerManager().SetTimer(DashTimer, 1 / dashRate, false);
		}
	}
}

void APlayerCharacter::SpawnWeapon()
{
	if (weaponClass == nullptr) return;
	weapon = GetWorld()->SpawnActor<AWeapon>(weaponClass);
	weapon->SetOwner(this);
	weapon->AttachWeapon(GetMesh());
}
