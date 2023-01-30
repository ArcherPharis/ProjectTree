// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterPlane.h"

// Sets default values
AWaterPlane::AWaterPlane()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	waterPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WaterPlane"));
	waterPlane->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AWaterPlane::BeginPlay()
{
	Super::BeginPlay();
	waterPlane->OnComponentBeginOverlap.AddDynamic(this, &AWaterPlane::OnTouched);
	
}

// Called every frame
void AWaterPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaterPlane::OnTouched(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is here."));
	}
}



