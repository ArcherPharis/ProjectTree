// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WormSpawner.generated.h"

UCLASS()
class PROJECTTREE_API AWormSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWormSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "WormSpawner")
	USceneComponent* rootComp;

	UPROPERTY(EditDefaultsOnly, Category = "WormSpawner")
	class USphereComponent* detectionSphere;

	UPROPERTY(EditDefaultsOnly, Category = "WormSpawner")
	class USceneComponent* spawnLocation;

	UPROPERTY(EditDefaultsOnly, Category = "WormSpawner")
	TSubclassOf<class AEnemy> enemyClass;

	AEnemy* enemy;

	UPROPERTY(EditDefaultsOnly, Category = "WormSpawner")
	bool isSpawned = false;

	UFUNCTION()
	void OnPlayerTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

};
