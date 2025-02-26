// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropCheckBox.generated.h"

class UBoxComponent;

UCLASS()
class SPLATOON_API ADropCheckBox : public AActor
{
	GENERATED_BODY()
	
public:	
	ADropCheckBox();

protected:
	virtual void BeginPlay() override;

	UBoxComponent* BoxComponent;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
