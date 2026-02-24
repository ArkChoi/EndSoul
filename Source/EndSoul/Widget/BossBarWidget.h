// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BossBarWidget.generated.h"

class UProgressBar;
class UTextBlock;

/**
 * 
 */
UCLASS()
class ENDSOUL_API UBossBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Data")
	TObjectPtr <class AActor> SaveBoss;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget, meta = (WidgetBind))
	TObjectPtr<UProgressBar> BossHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget, meta = (WidgetBind))
	TObjectPtr<UTextBlock> BossName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget, meta = (WidgetBind))
	TObjectPtr<UTextBlock> Damege;

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void UpdateHP(float InHP);

};
