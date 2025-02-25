#include "SplatoonGameMode.h"
#include "Splatoon/LevelActors/Balloon.h"
#include "Kismet/GameplayStatics.h"

void ASplatoonGameMode::BeginPlay()
{
    Super::BeginPlay();

    // 레벨 내 풍선 액터 확인
    TArray<AActor*> BalloonActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABalloon::StaticClass(), BalloonActors);

    BalloonCount = BalloonActors.Num();
}

void ASplatoonGameMode::DecreaseBalloonCount()
{
    if (BalloonCount > 0)
    {
        BalloonCount--;
    }
    else if (BalloonCount == 0)
    {
        SpawnPortal();
    }
}

void ASplatoonGameMode::IncreaseGameScore(int32 Score)
{
    GameScore += Score;
}

void ASplatoonGameMode::SpawnPortal()
{
    // 포탈 생성
}
