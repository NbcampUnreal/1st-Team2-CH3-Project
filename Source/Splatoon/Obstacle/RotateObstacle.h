// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObstacleBase.h"
#include "RotateObstacle.generated.h"

/**
 * 
 */
UCLASS()
class SPLATOON_API ARotateObstacle : public AObstacleBase
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Obstacle|Movement")
	float PitchValue;
	UPROPERTY(EditAnywhere, Category = "Obstacle|Movement")
	float YawValue;
	UPROPERTY(EditAnywhere, Category = "Obstacle|Movement")
	float RollValue;
};
