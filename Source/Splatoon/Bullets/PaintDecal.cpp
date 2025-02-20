// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintDecal.h"

// Sets default values
APaintDecal::APaintDecal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APaintDecal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APaintDecal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

