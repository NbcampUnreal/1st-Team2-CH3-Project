// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SplatoonGameState.generated.h"

/**
 * 
 */
UCLASS()
class SPLATOON_API ASplatoonGameState : public AGameState
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	void StartLevel();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	FName MainLevel;
};
