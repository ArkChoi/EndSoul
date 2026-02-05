// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CommanderPCBase.generated.h"

/**
 * 
 */
UCLASS()
class ENDSOUL_API ACommanderPCBase : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACommanderPCBase();

	//virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;
	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<class UInputMappingContext> InputMapping;

};
