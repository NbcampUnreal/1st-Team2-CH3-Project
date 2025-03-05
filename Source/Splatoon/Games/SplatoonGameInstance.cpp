// Fill out your copyright notice in the Description page of Project Settings.


#include "SplatoonGameInstance.h"

USplatoonGameInstance::USplatoonGameInstance()
{
	GameScore = 0;
}

void USplatoonGameInstance::AddToScore(int32 Amount)
{
	GameScore += Amount;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Score: %d"), GameScore));
}


