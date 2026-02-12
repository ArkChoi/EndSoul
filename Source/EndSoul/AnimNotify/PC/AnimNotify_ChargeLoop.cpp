// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ChargeLoop.h"
#include "../../Player/PlayerCharacterBase.h"
#include "../../Weapon/WeaponBase.h"

FString UAnimNotify_ChargeLoop::GetNotifyName_Implementation() const
{
	return TEXT("ChargeLoop");
}

void UAnimNotify_ChargeLoop::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	APlayerCharacterBase* PC = Cast<APlayerCharacterBase>(MeshComp->GetOwner());
	if (PC)
	{
		AWeaponBase* Weapon = Cast<AWeaponBase>(PC->GetWeapon()->GetChildActor());
		if (Weapon)
		{
			Weapon->SetbChargeLoop(true);

			Weapon->ChargingChargeAttack(PC);
		}
	}

}

