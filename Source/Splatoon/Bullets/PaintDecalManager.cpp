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

	// ���忡 ��ġ�� ��Į ������ �ִ밪�� �Ѿ ��� ���� ������ ��Į ����
	if (DecalList.Num() > MaxDecal)
	{
		if (DecalList[0].IsValid())
		{
			DecalList[0]->Destroy();
		}
		DecalList.RemoveAt(0);
	}
}
