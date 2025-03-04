// Fill out your copyright notice in the Description page of Project Settings.


#include "SplatoonPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ASplatoonPlayerController::ASplatoonPlayerController() :
	InputMappingContext(nullptr),
	MoveAction(nullptr),
	JumpAction(nullptr),
	LookAction(nullptr),
	FireAction(nullptr),
	TransforAction(nullptr)
{

}

void ASplatoonPlayerController::ShowMainMenu()
{
	if (HUDWidgetInstance) {
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	if (MainWidgetInatance) {
		MainWidgetInatance->RemoveFromParent();
		MainWidgetInatance = nullptr;
	}

	if (MainWidgetClass) {
		MainWidgetInatance = CreateWidget<UUserWidget>(this, MainWidgetClass);
		if (MainWidgetInatance) {
			MainWidgetInatance->AddToViewport();

			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
		}
	}
}

void ASplatoonPlayerController::StartGame()
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

	// 만약 레벨이 Main인 경우 MainMenu UI 출력
	FString CurrentMapName = GetWorld()->GetMapName();
}