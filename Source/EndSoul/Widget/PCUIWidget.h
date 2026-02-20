// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PCUIWidget.generated.h"

class UProgressBar;
//class;

/**
 * 
 */
UCLASS()
class ENDSOUL_API UPCUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget, meta = (WidgetBind))
	TObjectPtr<UProgressBar> HPBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget, meta = (WidgetBind))
	TObjectPtr<UProgressBar> StaminaBar;

public:
	virtual void NativeConstruct() override;

	void UpdateHP(float InHP);

	void UpdateStamina(float InStamina);

};
