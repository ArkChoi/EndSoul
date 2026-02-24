// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PCUIHUD.generated.h"

/**
 * 
 */
class UUserWidget;

UCLASS()
class ENDSOUL_API APCUIHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TObjectPtr <UUserWidget> WidgetBossBar;

public:
	void AddBossBar();

};
