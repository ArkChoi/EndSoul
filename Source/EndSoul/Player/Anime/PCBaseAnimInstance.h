// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PCBaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ENDSOUL_API UPCBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	float GroundSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	float Direction = 0.f;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;
};
