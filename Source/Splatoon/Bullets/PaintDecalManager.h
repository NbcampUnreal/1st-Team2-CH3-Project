
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PaintDecalManager.generated.h"


class APaintDecal;

UCLASS()
class SPLATOON_API UPaintDecalManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UPaintDecalManager* GetInstance(UWorld* World);
	void AddDecalList(AActor* NewDecal);

private:
	UPROPERTY()
	TArray<TWeakObjectPtr<AActor>> DecalList;
	UPROPERTY(EditDefaultsOnly)
	int32 MaxDecal = 100;
};
