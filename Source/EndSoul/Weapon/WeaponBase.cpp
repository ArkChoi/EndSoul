// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "GameFramework/Character.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AWeaponBase::CheackAnimation(ACharacter* PC)
{
	if (PC->GetMesh()->GetAnimInstance()->Montage_IsPlaying(ComboAttackMontage))
	{
		return true;
	}

	return false;
}

void AWeaponBase::ComboAttack(ACharacter *PC, bool bIsPlay)
{
	if (!bIsPlay && bComboCheak)
	{
		return;
	}
	else if (CheackAnimation(PC) && !bIsPlay)
	{
		ComboAttackCountUp();
		bComboCheak = 1;
		return;
	}

	bComboCheak = 0;
	FString TempString = FString::FromInt(ComboCount);
	PC->PlayAnimMontage(ComboAttackMontage, 1.0f, FName(*TempString));
}

void AWeaponBase::ComboAttackCountUp()
{
	ComboCount = ComboCount % 3;
	ComboCount++;
}

