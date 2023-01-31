// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	SetRootComponent(rootComp);
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	mesh->SetupAttachment(RootComponent);
	hitBox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitBox"));
	hitBox->SetupAttachment(mesh);

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	hitBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnHit);
	
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

void AWeapon::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("We hit: %s"), *OtherActor->GetName());
	ACharacter* hitCharacter = Cast<ACharacter>(OtherActor);
	if (hitCharacter)
	{
		hitCharacter->GetCharacterMovement()->AddImpulse(GetOwner()->GetActorForwardVector() * hitPushSpeed, true);
		UGameplayStatics::ApplyDamage(hitCharacter, -damage, GetOwner()->GetInstigatorController(), GetOwner(), UDamageType::StaticClass());
	}
}

