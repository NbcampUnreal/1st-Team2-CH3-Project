#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SplatoonGameMode.generated.h"


UCLASS()
class SPLATOON_API ASplatoonGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Balloon")
	int32 BalloonCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Balloon")
	int32 MaxBalloonCount;

	virtual void BeginPlay() override;
	void DecreaseBalloonCount();
	void IncreaseGameScore(int32 Score);
	
private:
	void SpawnPortal();
};
