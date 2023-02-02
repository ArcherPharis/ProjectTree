// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WormProjectile.generated.h"

UCLASS()
class PROJECTTREE_API AWormProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWormProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Projectile")
	void SpawnEffects(APlayerCharacter* charaHit);

private:
	UPROPERTY(EditDefaultsOnly, Category = "WormProjectile")
	class UProjectileMovementComponent* projectileComp;

	UPROPERTY(EditDefaultsOnly, Category = "WormProjectile")
	USceneComponent* rootComp;

	UPROPERTY(EditDefaultsOnly, Category = "WormProjectile")
	UStaticMeshComponent* mesh;

	UPROPERTY(EditDefaultsOnly, Category = "WormProjectile")
	class USphereComponent* hitBox;

	UPROPERTY(EditDefaultsOnly, Category = "WormProjectile")
	float damage = 25.f;

	UFUNCTION()
	void Explode(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

};
