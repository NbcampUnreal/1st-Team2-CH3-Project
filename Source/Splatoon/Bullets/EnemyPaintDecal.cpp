// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPaintDecal.h"
#include "PaintDecalManager.h"
#include "Components/DecalComponent.h"
#include "Components/BoxComponent.h"
#include "Materials/MaterialInterface.h"

// Sets default values
AEnemyPaintDecal::AEnemyPaintDecal()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	//RootComponent = CollisionBox;
	CollisionBox->SetBoxExtent(FVector(170.0f, 170.0f, 170.0f));

	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));
	SetRootComponent(DecalComp);
	//DecalComp->SetupAttachment(CollisionBox);
	CollisionBox->SetupAttachment(DecalComp);

	// DecalMaterial = CreateDefaultSubobject<UMaterial>(TEXT("DecalMaterial"));
	// UMaterialInterface* DMaterial = Cast<UMaterialInterface>(StaticLoadObject(UObject::StaticClass(), nullptr, *DecalPath));

	// /Game/Resources/Materials/M_PaintDecal.M_PaintDecal

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> PaintDecalMaterial(TEXT("/Game/Resources/Materials/M_EnemyPaintDecal.M_EnemyPaintDecal"));
	if (PaintDecalMaterial.Succeeded())
	{
		DecalMaterial = PaintDecalMaterial.Object;
	}
	DecalSize = FVector(1.f);
}

// Called when the game starts or when spawned
void AEnemyPaintDecal::BeginPlay()
{
	Super::BeginPlay();
	
	if (DecalComp && DecalMaterial)
	{
		DecalComp->SetDecalMaterial(DecalMaterial);
		DecalComp->SetWorldScale3D(DecalSize);
	}

	UPaintDecalManager* Manager = UPaintDecalManager::GetInstance(GetWorld());
	if (Manager)
	{
		Manager->AddDecalList(this);
	}
}

void AEnemyPaintDecal::SpawnPaintDecal(UWorld* World, const FVector& Location, const FRotator& Rotator)
{
	if (!World) return;

	FActorSpawnParameters SpawnParms;
	AEnemyPaintDecal* NewDecal = World->SpawnActor<AEnemyPaintDecal>(AEnemyPaintDecal::StaticClass(), Location, Rotator, SpawnParms);
}


