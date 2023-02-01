// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, newHealth, float, maxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthEmpty);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTTREE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	FOnHealthChanged onHealthChanged;
	FOnHealthEmpty onHealthEmpty;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void BeginWaterIncrease();
	void StopWaterIncrease();
	float GetMaxHealth() const { return maxHealth; }
	float GetHealth() const { return health; }


private:

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float maxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float health;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float drainAmount = 0.01f;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float waterIncreaseAmount = 0.1f;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	bool HealthDrains = false;

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser);

	FTimerHandle waterRefillHandle;

	void IncreaseHealthInWater();

	class ABaseCharacter* ownerChara;
		
};
