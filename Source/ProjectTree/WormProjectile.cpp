// Fill out your copyright notice in the Description page of Project Settings.


#include "WormProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

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
	hitBox->OnComponentBeginOverlap.AddDynamic(this, &AWormProjectile::Explode);
	
}

// Called every frame
void AWormProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWormProjectile::Explode(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	UGameplayStatics::ApplyDamage(OtherActor, -damage, GetOwner()->GetInstigatorController(), GetOwner(), UDamageType::StaticClass());
	if (OtherActor->ActorHasTag("Player"))
	{
		APlayerCharacter* character = Cast<APlayerCharacter>(OtherActor);
		if (!character->IsDead())
		{
			character->TakeHit();
		}
	}
	Destroy();
}

