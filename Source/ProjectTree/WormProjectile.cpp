// Fill out your copyright notice in the Description page of Project Settings.


#include "WormProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AWormProjectile::AWormProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);
	projectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	mesh->SetupAttachment(rootComp);
	hitBox = CreateDefaultSubobject<USphereComponent>(TEXT("SphereBox"));
	hitBox->SetupAttachment(rootComp);

	
}

// Called when the game starts or when spawned
void AWormProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWormProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

