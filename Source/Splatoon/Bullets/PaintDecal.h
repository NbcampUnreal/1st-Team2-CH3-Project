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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet|Paint")
	UDecalComponent* DecalComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet|Paint")
	UMaterialInterface* DecalMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet|Paint")
	FString DecalPath;
	UPROPERTY(EditDefaultsOnly, Category = "Bullet|Paint")
	FVector DecalSize;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* CollisionBox;

	virtual void BeginPlay() override;
};