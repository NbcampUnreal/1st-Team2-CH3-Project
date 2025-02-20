// Fill out your copyright notice in the Description page of Project Settings.


#include "SplatoonPlayerController.h"
#include "EnhancedInputSubsystems.h"

ASplatoonPlayerController::ASplatoonPlayerController() :
	InputMappingContext(nullptr),
	MoveAction(nullptr),
	JumpAction(nullptr),
	LookAction(nullptr),
	FireAction(nullptr),
	TransforAction(nullptr)
{

}

void ASplatoonPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(ULocalPlayer * LocalPayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = LocalPayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				SubSystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}