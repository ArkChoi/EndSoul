// Fill out your copyright notice in the Description page of Project Settings.


#include "CommanderPCBase.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"

ACommanderPCBase::ACommanderPCBase()
{
}

void ACommanderPCBase::OnUnPossess()
{
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSystem->RemoveMappingContext(InputMapping);
		}
	}

	Super::OnUnPossess();
}

void ACommanderPCBase::BeginPlay()
{
	if (IsLocalController())
	{
		if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSystem->AddMappingContext(InputMapping, 0);
			}
		}
	}
}
