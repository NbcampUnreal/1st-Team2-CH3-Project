#include "SplatoonGameMode.h"
#include "Splatoon/LevelActors/Balloon.h"
#include "Splatoon/LevelActors/Portal.h"
#include "Kismet/GameplayStatics.h"
#include "SplatoonGameInstance.h"

void ASplatoonGameMode::BeginPlay()
{
    Super::BeginPlay();

    // 레벨 내 풍선 액터 확인
    TArray<AActor*> BalloonActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABalloon::StaticClass(), BalloonActors);

    BalloonCount = BalloonActors.Num();
    MaxBalloonCount = BalloonCount;
}

void ASplatoonGameMode::DecreaseBalloonCount()
{
    if (BalloonCount > 0)
    {
        BalloonCount--;
    }

    SpawnPortal();
}

void ASplatoonGameMode::IncreaseGameScore(int32 Score)
{
    if (UGameInstance* GameInstance = GetGameInstance()) {
        USplatoonGameInstance* SplatoonGameInstance = Cast<USplatoonGameInstance>(GameInstance);
        if (SplatoonGameInstance) {
            SplatoonGameInstance->AddToScore(Score);
        }
    }
    //GameScore += Score;
}

void ASplatoonGameMode::SpawnPortal()
{
    APortal* Portal = Cast<APortal>(UGameplayStatics::GetActorOfClass(GetWorld(), APortal::StaticClass()));

    if (!Portal) return;

    if (BalloonCount==0)
    {
        Portal->ActivePortal();
    }
}
