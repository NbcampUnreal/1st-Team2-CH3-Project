#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SplatoonGameMode.generated.h"


UCLASS()
class SPLATOON_API ASplatoonGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	void DecreaseBalloonCount();
	void IncreaseGameScore(int32 Score);

private:
	int32 BalloonCount = 0;
	int32 GameScore = 0;

	void SpawnPortal();
};
