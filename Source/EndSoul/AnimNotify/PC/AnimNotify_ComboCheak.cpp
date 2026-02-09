// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ComboCheak.h"
#include "../../Player/PlayerCharacterBase.h"
#include "../../Weapon/WeaponBase.h"

FString UAnimNotify_ComboCheak::GetNotifyName_Implementation() const
{
	return TEXT("ComboReset");
}

void UAnimNotify_ComboCheak::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	APlayerCharacterBase* PC = Cast<APlayerCharacterBase>(MeshComp->GetOwner());
	if (PC)
	{
		AWeaponBase* Weapon = Cast<AWeaponBase>(PC->GetWeapon()->GetChildActor());
		if (Weapon)
		{
			if (Weapon->GetbComboCheak())
			{
				Weapon->ComboAttack(PC, true);
			}
			else
			{
				Weapon->SetComboCount(1);
				UE_LOG(LogTemp, Warning, TEXT("ComboReset"));
			}
		}
	}

}
