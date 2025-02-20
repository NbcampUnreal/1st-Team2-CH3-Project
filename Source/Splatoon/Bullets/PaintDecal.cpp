#include "PaintDecal.h"
#include "Components/DecalComponent.h"
#include "Materials/MaterialInterface.h"

TArray<APaintDecal*> APaintDecal::DecalList;

APaintDecal::APaintDecal()
{
	PrimaryActorTick.bCanEverTick = false;

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));
	SetRootComponent(DecalComp);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> PaintDecalMaterial(TEXT("/Game/Resources/Materials/M_PaintDecal.M_PaintDecal"));
	if (PaintDecalMaterial.Succeeded())
	{
		DecalMaterial = PaintDecalMaterial.Object;
	}

	DecalSize = FVector(1.f);
	MaxDecal = 50;
}

void APaintDecal::BeginPlay()
{
	Super::BeginPlay();

	if (DecalComp && DecalMaterial)
	{
		DecalComp->SetDecalMaterial(DecalMaterial);
		DecalComp->SetWorldScale3D(DecalSize);
	}

	ManageDecal(this);
}

void APaintDecal::SpawnPaintDecal(UWorld* World, const FVector& Location, const FRotator& Rotator)
{
	if (!World) return;

	FActorSpawnParameters SpawnParms;
	World->SpawnActor<APaintDecal>(APaintDecal::StaticClass(), Location, Rotator, SpawnParms);
}

void APaintDecal::ManageDecal(APaintDecal* NewDecal)
{
	if (!NewDecal) return;

	DecalList.Add(NewDecal);

	// 레벨에 스폰된 데칼 개수가 최대치를 넘어가면 가장 오래된 데칼 삭제
	if (DecalList.Num() > MaxDecal)
	{
		if (DecalList[0])
		{
			DecalList[0]->Destroy();
		}
		DecalList.RemoveAt(0);
	}
}


