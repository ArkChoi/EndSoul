// Fill out your copyright notice in the Description page of Project Settings.


#include "CommanderGMB.h"
#include "../Player/PlayerCharacterBase.h"
#include "CommanderPCBase.h"

ACommanderGMB::ACommanderGMB()
{
	DefaultPawnClass = APlayerCharacterBase::StaticClass();
	PlayerControllerClass = ACommanderPCBase::StaticClass();
}
