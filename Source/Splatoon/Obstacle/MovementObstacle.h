// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObstacleBase.h"
#include "Components/TimelineComponent.h"
#include "MovementObstacle.generated.h"

/**
 * 
 */
UCLASS()
class SPLATOON_API AMovementObstacle : public AObstacleBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void TimelineProgress(float Value);

protected:
	virtual void BeginPlay() override;

	void MoveEvent();

	FTimeline MoveTimeline;
	UPROPERTY(EditAnywhere, Category = "Obstacle|Timeline")
	UCurveFloat* MoveCurve;

	UPROPERTY()
	FVector StartLocation;
	UPROPERTY()
	FVector EndLocation;
	UPROPERTY(EditAnywhere, Category = "Obstacle|Timeline")
	float fOffset_X;
	UPROPERTY(EditAnywhere, Category = "Obstacle|Timeline")
	float fOffset_Y;
	UPROPERTY(EditAnywhere, Category = "Obstacle|Timeline")
	float fOffset_Z;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
