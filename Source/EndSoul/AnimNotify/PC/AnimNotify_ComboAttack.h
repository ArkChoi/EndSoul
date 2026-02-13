// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ComboAttack.generated.h"

/**
 * 
 */
UCLASS()
class ENDSOUL_API UAnimNotify_ComboAttack : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	virtual FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
