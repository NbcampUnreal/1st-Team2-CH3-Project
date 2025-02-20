// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBullet.h"
#include "StandardBullet.generated.h"

UCLASS()
class SPLATOON_API AStandardBullet : public ABaseBullet
{
	GENERATED_BODY()

public:
	AStandardBullet();

protected:
	virtual void BeginPlay() override;
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	virtual void OnBulletDestroyed() override;
};
