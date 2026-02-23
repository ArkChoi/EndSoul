// Fill out your copyright notice in the Description page of Project Settings.


#include "PCUIWidget.h"
#include "Components/ProgressBar.h"
#include "../Player/PlayerCharacterBase.h"

void UPCUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerCharacterBase* Player = Cast<APlayerCharacterBase>(GetOwningPlayer()->GetPawn());
	if (Player)
	{
		Player->OnChangeHP.AddDynamic(this, &UPCUIWidget::UpdateHP);
		Player->OnRep_HPUpdate(1);
		Player->OnChangeStamina.AddDynamic(this, &UPCUIWidget::UpdateStamina);
		Player->OnRep_StaminaUpdate(1);
	}
}

void UPCUIWidget::UpdateHP(float InHP)
{
	if (HPBar)
	{
		HPBar->SetPercent(InHP);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NotFoundHPBar"));
	}
}

void UPCUIWidget::UpdateStamina(float InStamina)
{
	if (StaminaBar)
	{
		StaminaBar->SetPercent(InStamina);
	}
}
