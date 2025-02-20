#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaintDecal.generated.h"

class UDecalComponent;
class UMaterialInterface;
class UPaintDecalManager;

UCLASS()
class SPLATOON_API APaintDecal : public AActor
{
	GENERATED_BODY()
	
public:	
	APaintDecal();

public:
	static void SpawnPaintDecal(UWorld* World, const FVector& Location, const FRotator& Rotator);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Bullet|Paint")
	UDecalComponent* DecalComp;
	UPROPERTY(EditDefaultsOnly, Category = "Bullet|Paint")
	UMaterialInterface* DecalMaterial;
	UPROPERTY(EditDefaultsOnly, Category = "Bullet|Paint")
	FVector DecalSize;

	virtual void BeginPlay() override;
};
