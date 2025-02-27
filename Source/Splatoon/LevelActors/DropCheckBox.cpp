// Fill out your copyright notice in the Description page of Project Settings.


#include "Splatoon/LevelActors/DropCheckBox.h"
#include "Components/BoxComponent.h"
#include "Splatoon/Character/SplatoonCharacter.h"

// Sets default values
ADropCheckBox::ADropCheckBox()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	BoxComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADropCheckBox::OnOverlapBegin);
}

void ADropCheckBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADropCheckBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASplatoonCharacter* Player = Cast<ASplatoonCharacter>(OtherActor);
	if (Player)
	{
		Player->OnDropDeath();
	}
}

