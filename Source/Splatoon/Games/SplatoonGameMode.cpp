#include "SplatoonGameMode.h"
#include "Splatoon/LevelActors/Balloon.h"
#include "Splatoon/LevelActors/Portal.h"
#include "Kismet/GameplayStatics.h"

void ASplatoonGameMode::BeginPlay()
{
    Super::BeginPlay();

    // ���� �� ǳ�� ���� Ȯ��
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

    SpawnPortal();
}

void ASplatoonGameMode::IncreaseGameScore(int32 Score)
{
    GameScore += Score;
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
