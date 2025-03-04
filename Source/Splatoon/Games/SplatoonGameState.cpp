// Fill out your copyright notice in the Description page of Project Settings.


#include "SplatoonGameState.h"
#include "Blueprint/UserWidget.h"
#include "Splatoon/Players/SplatoonPlayerController.h"

void ASplatoonGameState::OnGameOver()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ASplatoonPlayerController* SplatoonPlayerController = Cast<ASplatoonPlayerController>(PlayerController))
		{
			SplatoonPlayerController->ShowGameOver();
			SplatoonPlayerController->SetPause(true);
		}
	}
}

