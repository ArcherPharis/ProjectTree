// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(mesh);
	hitBox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitBox"));
	hitBox->SetupAttachment(mesh);

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::AttachWeapon(USkeletalMeshComponent* ownerMesh)
{
	if(GetOwner())
	AttachToComponent(ownerMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, weaponSocketName);
}

void AWeapon::Attack(USkeletalMeshComponent* ownerMesh)
{
	if (CanAttack())
	{
		//ownerMesh->GetAnimInstance()->Montage_Play(meleeMontage);
		GetWorldTimerManager().SetTimer(AttackTimer, 1 / attackRate, false);
		UE_LOG(LogTemp, Warning, TEXT("CanAttack"));
	}
}

bool AWeapon::CanAttack() const
{
	return !GetWorldTimerManager().IsTimerActive(AttackTimer);
}

