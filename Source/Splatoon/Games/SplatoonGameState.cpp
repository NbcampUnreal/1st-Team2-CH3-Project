#include "SplatoonGameState.h"
#include "Splatoon/Players/SplatoonPlayerController.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

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
			if (CurrentLevelName.Contains(MainLevel.ToString()))
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
