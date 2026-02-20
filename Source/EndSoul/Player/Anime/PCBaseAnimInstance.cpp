// Fill out your copyright notice in the Description page of Project Settings.


#include "PCBaseAnimInstance.h"
#include "../PlayerCharacterBase.h"
#include "Gameframework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

void UPCBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APlayerCharacterBase* Character = Cast<APlayerCharacterBase>(TryGetPawnOwner());
	if (Character)
	{
		GroundSpeed = Character->GetCharacterMovement()->Velocity.Size2D();
		Direction = UKismetAnimationLibrary::CalculateDirection(Character->GetCharacterMovement()->Velocity, Character->GetActorRotation());
		bIsGuard = Character->GetbIsGuard();
	}
}

