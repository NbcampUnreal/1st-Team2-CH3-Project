// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SplatoonGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SPLATOON_API USplatoonGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	USplatoonGameInstance();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 GameScore;

	UFUNCTION(BlueprintCallable)
	void AddToScore(int32 Amount);
};
