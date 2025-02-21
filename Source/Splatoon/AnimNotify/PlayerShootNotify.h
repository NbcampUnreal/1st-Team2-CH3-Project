// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Splatoon/Guns/BaseGun.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PlayerShootNotify.generated.h"

/**
 * 
 */
UCLASS()
class SPLATOON_API UPlayerShootNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	ABaseGun* GunActor;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
