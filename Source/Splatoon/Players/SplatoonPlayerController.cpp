// Fill out your copyright notice in the Description page of Project Settings.


#include "SplatoonPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
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

void ASplatoonPlayerController::ShowHUD()
{
	if (HUDWidgetInstance) {
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	if (MainWidgetInatance) {
		MainWidgetInatance->RemoveFromParent();
		MainWidgetInatance = nullptr;
	}

	if (HUDWidgetClass) {
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance) {
			HUDWidgetInstance->AddToViewport();
		}
	}
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

	if (GameOverWidgetInstance)
	{
		GameOverWidgetInstance->RemoveFromParent();
		GameOverWidgetInstance = nullptr;
	}

	if (MainWidgetClass) {
		MainWidgetInatance = CreateWidget<UUserWidget>(this, MainWidgetClass);
		if (MainWidgetInatance) {
			MainWidgetInatance->AddToViewport(1);

			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
		}
	}
}

void ASplatoonPlayerController::StartGame()
{

}

void ASplatoonPlayerController::ShowGameOver()
{
	if (HUDWidgetInstance) {
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	if (MainWidgetInatance) {
		MainWidgetInatance->RemoveFromParent();
		MainWidgetInatance = nullptr;
	}

	if (GameOverWidgetInstance)
	{
		GameOverWidgetInstance->RemoveFromParent();
		GameOverWidgetInstance = nullptr;
	}

	if (GameOverWidgetClass)
	{
		GameOverWidgetInstance = CreateWidget<UUserWidget>(this, GameOverWidgetClass);
		if (GameOverWidgetInstance)
		{
			GameOverWidgetInstance->AddToViewport();
			SetInputMode(FInputModeUIOnly());
			bShowMouseCursor = true;
		}
	}
}

void ASplatoonPlayerController::ShowClearWidget()
{
	if (HUDWidgetInstance) {
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	if (MainWidgetInatance) {
		MainWidgetInatance->RemoveFromParent();
		MainWidgetInatance = nullptr;
	}

	if (GameOverWidgetInstance){
		GameOverWidgetInstance->RemoveFromParent();
		GameOverWidgetInstance = nullptr;
	}

	if (ClearWidgetClass) {
		ClearWidgetInstance = CreateWidget<UUserWidget>(this, ClearWidgetClass);

		if (ClearWidgetInstance) {
			ClearWidgetInstance->AddToViewport();
			SetInputMode(FInputModeUIOnly());
			bShowMouseCursor = true;
		}
	}
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

	// ���� ������ Main�� ��� MainMenu UI ���
	FString CurrentMapName = GetWorld()->GetMapName();

	ASplatoonCharacter* Chr = Cast<ASplatoonCharacter>(GetPawn());
	if (Chr)
	{
		Agent = Chr;
		TeamId = FGenericTeamId(Agent->ID);
	}
}

ETeamAttitude::Type ASplatoonPlayerController::GetTeamAttitudeTowards(const AActor& Other) const
{
	// Check if Pawn
	const APawn* OtherPawn = Cast<APawn>(&Other);
	if (OtherPawn == nullptr)
	{
		return ETeamAttitude::Neutral;
	}

	auto PlayerTI = Cast<IGenericTeamAgentInterface>(&Other);
	class IGenericTeamAgentInterface* BotTI = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController());
	if (BotTI == nullptr && PlayerTI == nullptr)
	{
		return ETeamAttitude::Neutral;
	}

	FGenericTeamId OtherActorTeamId = NULL;
	if (BotTI != nullptr)
	{
		OtherActorTeamId = BotTI->GetGenericTeamId();
	}
	else if (PlayerTI != nullptr)
	{
		OtherActorTeamId = PlayerTI->GetGenericTeamId();
	}

	FGenericTeamId ThisId = GetGenericTeamId();
	if (OtherActorTeamId == 8)
	{
		return ETeamAttitude::Neutral;
	}
	else if (OtherActorTeamId == ThisId)
	{
		return ETeamAttitude::Friendly;
	}
	else
	{
		return ETeamAttitude::Hostile;
	}
}