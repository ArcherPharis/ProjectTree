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

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	class UCapsuleComponent* GetHitBox() const { return hitBox; }


	void AttachWeapon(USkeletalMeshComponent* ownerMesh);

	UAnimMontage* GetNormalAttackMontage() const { return meleeMontage; }

	void Attack(USkeletalMeshComponent* ownerMesh);

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void LaunchTarget(ACharacter* characterToLaunch);

protected:
	virtual bool CanAttack() const;

private:

	UPROPERTY(EditAnywhere, Category = "Weapon")
	USceneComponent* rootComp;
	UPROPERTY(EditAnywhere, Category = "Weapon")
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	UCapsuleComponent* hitBox;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* meleeMontage;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	FName weaponSocketName;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float damage = 25.f;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float attackRate = 1.f;

	FTimerHandle AttackTimer;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float hitPushSpeed = 500.f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
};
