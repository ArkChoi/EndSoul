// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/ChildActorComponent.h"
#include "../Weapon/WeaponBase.h"
#include "../Player/DamageType/ChargeDamageType.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh());
	Weapon->SetChildActorClass(AWeaponBase::StaticClass());

}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	OnTakeAnyDamage.AddDynamic(this, &AEnemyBase::ProcessOnTakeAnyDamage);

}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBase::OnRep_EHPUpdate(const float InEHP)
{
	OnChangeEHP.Broadcast(CurrentHP / MaxHP);
}

FString AEnemyBase::GetName()
{
	return Name;
}

void AEnemyBase::Attack(UAnimMontage* InMontage)
{
	PlayAnimMontage(InMontage);
}

void AEnemyBase::Grogy(UAnimMontage* InMontage)
{
	PlayAnimMontage(InMontage);
	CurrentGrogy = MaxGrogy;
}

bool AEnemyBase::AnimeCheack(UAnimMontage* InMontage)
{
	if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(InMontage))
	{
		return true;
	}
	return false;
}

void AEnemyBase::ProcessOnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamageType->IsA<UChargeDamageType>())
	{
		CurrentGrogy -= 30.f;
	}
	UE_LOG(LogTemp, Warning, TEXT("%s Groggy : %f"), *DamagedActor->GetName(), CurrentGrogy);

	ACharacter* Enemy = Cast<ACharacter>(DamageCauser);
	if (Enemy)
	{
		FVector EnemyLocation = Enemy->GetMesh()->GetComponentLocation();
		FVector MyLocation = GetCapsuleComponent()->GetComponentLocation();
		FVector ImpulseForce;
		ImpulseForce = (MyLocation - EnemyLocation).GetSafeNormal();
		ImpulseForce.Z = 0;
		ImpulseForce *= 1000.f;
		GetCapsuleComponent()->AddImpulse(ImpulseForce);
	}

	CurrentHP -= Damage;
	OnRep_EHPUpdate(1);

}

void AEnemyBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEnemyBase, bIsGrogy);
}
