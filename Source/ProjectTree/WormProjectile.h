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

private:
	UPROPERTY(EditDefaultsOnly, Category = "WormProjectile")
	class UProjectileMovementComponent* projectileComp;

	UPROPERTY(EditDefaultsOnly, Category = "WormProjectile")
	USceneComponent* rootComp;

	UPROPERTY(EditDefaultsOnly, Category = "WormProjectile")
	UStaticMeshComponent* mesh;

	UPROPERTY(EditDefaultsOnly, Category = "WormProjectile")
	class USphereComponent* hitBox;

};
