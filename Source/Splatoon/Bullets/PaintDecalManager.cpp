#include "PaintDecalManager.h"
#include "PaintDecal.h"
#include "Engine/World.h"

UPaintDecalManager* UPaintDecalManager::GetInstance(UWorld* World)
{
	if (!World) return nullptr;

	UGameInstance* GameInstance = World->GetGameInstance();
	if (!GameInstance) return nullptr;

	return GameInstance->GetSubsystem<UPaintDecalManager>();
}

void UPaintDecalManager::AddDecalList(APaintDecal* NewDecal)
{
	if (!NewDecal) return;

	DecalList.Add(NewDecal);

	DecalList.RemoveAll([](const TWeakObjectPtr<APaintDecal>& Decal)
		{
			return !Decal.IsValid();
		});

	// 월드에 배치된 데칼 개수가 최대값을 넘어갈 경우 가장 오래된 데칼 제거
	if (DecalList.Num() > MaxDecal)
	{
		if (DecalList[0].IsValid())
		{
			DecalList[0]->Destroy();
		}
		DecalList.RemoveAt(0);
	}
}
