// Fill out your copyright notice in the Description page of Project Settings.


#include "SplatoonGameState.h"
#include "Splatoon/Players/SplatoonPlayerController.h"

void ASplatoonGameState::BeginPlay()
{
	Super::BeginPlay();

	StartLevel();
}

void ASplatoonGameState::StartLevel()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		ASplatoonPlayerController* SplatoonPlayerController = Cast<ASplatoonPlayerController>(PlayerController);
		if (SplatoonPlayerController)
		{
			FString CurrentLevelName = GetWorld()->GetMapName();
			if (CurrentLevelName.Contains( MainLevel.ToString()))
			{
				SplatoonPlayerController->ShowMainMenu();
			}
			else
			{
				SplatoonPlayerController->ShowHUD();
			}
		}
	}
}
