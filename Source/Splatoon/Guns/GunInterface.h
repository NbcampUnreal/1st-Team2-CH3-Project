// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GunInterface.generated.h"

UINTERFACE(MinimalAPI)
class UGunInterface : public UInterface
{
	GENERATED_BODY()
};

class SPLATOON_API IGunInterface
{
	GENERATED_BODY()

public:
	virtual void FirePressed() = 0;
	virtual void FireReleased() = 0;
	
	virtual void ReloadStart() = 0;
	virtual void ReloadEnd() = 0;
};
