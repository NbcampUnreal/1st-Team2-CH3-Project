// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyPaintDecal.generated.h"

class UDecalComponent;
class UMaterialInterface;
class UPaintDecalManager;

UCLASS()
class SPLATOON_API AEnemyPaintDecal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyPaintDecal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

};
