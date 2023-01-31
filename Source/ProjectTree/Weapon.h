// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class PROJECTTREE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AttachWeapon(USkeletalMeshComponent* ownerMesh);

	UAnimMontage* GetNormalAttackMontage() const { return meleeMontage; }

	void Attack(USkeletalMeshComponent* ownerMesh);

protected:
	virtual bool CanAttack() const;

private:
	UPROPERTY(EditAnywhere, Category = "Weapon")
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	class UCapsuleComponent* hitBox;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* meleeMontage;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	FName weaponSocketName;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float damage = 10.f;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float attackRate = 1.f;

	FTimerHandle AttackTimer;

};
