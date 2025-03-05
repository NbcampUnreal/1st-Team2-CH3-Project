// Fill out your copyright notice in the Description page of Project Settings.


#include "SplatoonGameInstance.h"

USplatoonGameInstance::USplatoonGameInstance()
{
	GameSocre = 0;
}

void USplatoonGameInstance::AddToScore(int32 Amount)
{
	GameSocre += Amount;
}


