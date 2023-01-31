// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	health = maxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (HealthDrains && health > 0)
	{
		UGameplayStatics::ApplyDamage(GetOwner(), -drainAmount * DeltaTime, GetOwner()->GetInstigatorController(), GetOwner(), UDamageType::StaticClass());
		onHealthChanged.Broadcast(health, maxHealth);
	}

	// ...
}

void UHealthComponent::BeginWaterIncrease()
{
	GetOwner()->GetWorldTimerManager().SetTimer(waterRefillHandle, this, &UHealthComponent::IncreaseHealthInWater, 0.1f, true);
}

void UHealthComponent::StopWaterIncrease()
{
	GetOwner()->GetWorldTimerManager().ClearTimer(waterRefillHandle);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	//if (Damage <= 0)
	//{
	//	return;
	//}
	health = FMath::Clamp(health + Damage, 0, maxHealth);
	onHealthChanged.Broadcast(health, maxHealth);
	
	if (health == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dead"));
		//TODO, each health component needs to know of its BaseCharacter owner, so it can
		//execute the correct death states.
		onHealthEmpty.Broadcast();
	}
}

void UHealthComponent::IncreaseHealthInWater()
{
	if (health < maxHealth && GetOwner()->GetWorldTimerManager().IsTimerActive(waterRefillHandle))
	{
		health += waterIncreaseAmount;
	}
}

