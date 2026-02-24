// Fill out your copyright notice in the Description page of Project Settings.


#include "BossBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "../Enemy/EnemyBossBase.h"
#include "Kismet/GameplayStatics.h"

void UBossBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<AActor*> AllActors;
	float SaveNearest = 999999.f;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBossBase::StaticClass(), AllActors);

	for (AActor* Actor : AllActors)
	{
		float TempNear = FVector::Dist(Actor->GetActorLocation(), GetOwningPlayer()->GetPawn()->GetActorLocation());

		if (SaveNearest > TempNear)
		{
			SaveNearest = TempNear;
			SaveBoss = Actor;
		}
	}

	AEnemyBossBase* Boss = Cast<AEnemyBossBase>(SaveBoss);
	if (Boss)
	{
		BossName->SetText(FText::FromString(Boss->GetName()));

		Boss->OnChangeEHP.AddDynamic(this, &UBossBarWidget::UpdateHP);
		Boss->OnRep_EHPUpdate(1);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Boss_Not_Found"));
	}

}

void UBossBarWidget::UpdateHP(float InHP)
{
	if (BossHP)
	{
		BossHP->SetPercent(InHP);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NotFoundBossHP"));
	}
}
