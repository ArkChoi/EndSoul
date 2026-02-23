// Fill out your copyright notice in the Description page of Project Settings.


#include "InBossRoom.h"
#include "../Player/PlayerCharacterBase.h"
#include "../UI/PCUIHUD.h"

// Sets default values
AInBossRoom::AInBossRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInBossRoom::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInBossRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInBossRoom::NotifyActorBeginOverlap(AActor* OtherActor)
{
	APlayerCharacterBase* PC = Cast<APlayerCharacterBase>(OtherActor);
	if (PC)
	{
		APCUIHUD* UI = Cast<APCUIHUD>(PC->GetLocalViewingPlayerController()->GetHUD());
	}
}

