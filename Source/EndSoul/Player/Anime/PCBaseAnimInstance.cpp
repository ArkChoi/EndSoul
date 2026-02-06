// Fill out your copyright notice in the Description page of Project Settings.


#include "PCBaseAnimInstance.h"
#include "Gameframework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPCBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* Character = Cast<ACharacter>(TryGetPawnOwner());
	if (Character)
	{
		GroundSpeed = Character->GetCharacterMovement()->Velocity.Size2D();
	}
}

