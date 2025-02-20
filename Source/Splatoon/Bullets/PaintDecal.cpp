#include "PaintDecal.h"
#include "PaintDecalManager.h"
#include "Components/DecalComponent.h"
#include "Materials/MaterialInterface.h"

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
}

void APaintDecal::BeginPlay()
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

void APaintDecal::SpawnPaintDecal(UWorld* World, const FVector& Location, const FRotator& Rotator)
{
	if (!World) return;

	FActorSpawnParameters SpawnParms;
	APaintDecal* NewDecal = World->SpawnActor<APaintDecal>(APaintDecal::StaticClass(), Location, Rotator, SpawnParms);
}


