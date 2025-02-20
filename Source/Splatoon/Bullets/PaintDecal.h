#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaintDecal.generated.h"

class UDecalComponent;
class UMaterialInterface;

UCLASS()
class SPLATOON_API APaintDecal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APaintDecal();

	static void SpawnPaintDecal(UWorld* World, const FVector& Location, const FRotator& Rotator);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Bullet|Paint")
	UDecalComponent* DecalComp;
	UPROPERTY(EditDefaultsOnly, Category = "Bullet|Paint")
	UMaterialInterface* DecalMaterial;
	UPROPERTY(EditDefaultsOnly, Category = "Bullet|Paint")
	FVector DecalSize;
	UPROPERTY(EditDefaultsOnly, Category = "Bullet|Paint")
	int32 MaxDecal;

	virtual void BeginPlay() override;

private:
	static TArray<APaintDecal*> DecalList;

	void ManageDecal(APaintDecal* NewDecal);
};
