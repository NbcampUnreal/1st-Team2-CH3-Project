// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LiquidTank.generated.h"

class UStaticMeshComponent;

UCLASS()
class SPLATOON_API ULiquidTank : public UObject
{
	GENERATED_BODY()

public:
	void Init(UMaterialInstanceDynamic* Material);
	void SetPercent(float Percent);

private:
	UPROPERTY()
	UMaterialInstanceDynamic* LiquidMaterial;
};
