// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ComboAttack.h"
#include "GameFramework/Character.h"
#include "kismet/GameplayStatics.h"
#include "../../Player/DamageType/ComboDamageType.h"

FString UAnimNotify_ComboAttack::GetNotifyName_Implementation() const
{
	return TEXT("ComboAttack");
}

void UAnimNotify_ComboAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (Character)
	{
		APlayerController* PC = Cast<APlayerController>(Character->GetController());
		if (!PC || !PC->HasAuthority())
		{
			return;
		}
		//FString TempString = TEXT("hand_r");

		//FVector RightHand = Character->GetMesh()->GetBoneLinearVelocity(FName(*TempString));


		FVector TempVector = Character->GetActorLocation();
		TArray<TEnumAsByte<EObjectTypeQuery>> TempArray;
		TEnumAsByte<EObjectTypeQuery> Pawn = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
		TempArray.Add(Pawn);
		TArray<AActor*> IgnoreActor;
		IgnoreActor.Add(Character);
		FHitResult ResultHit;

		UKismetSystemLibrary::SphereTraceSingleForObjects(Character->GetWorld(), TempVector, TempVector, 100.f, TempArray, false, IgnoreActor, EDrawDebugTrace::ForDuration, ResultHit, true);

		if (ResultHit.bBlockingHit)
		{
			UGameplayStatics::ApplyDamage(ResultHit.GetActor(), 10.f, Character->GetController(), Character, UComboDamageType::StaticClass());
		}
	}
}
