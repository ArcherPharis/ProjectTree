// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "HealthComponent.h"
#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "BrainComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	healthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	PerceptionStimuliComp = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>("PerceptionStimuliComp");

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::HandleDeath()
{
	
	if(DeathMontage)
	GetMesh()->GetAnimInstance()->Montage_Play(DeathMontage);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ABaseCharacter::IsDead()
{
	return healthComp->GetHealth() == 0;
}

