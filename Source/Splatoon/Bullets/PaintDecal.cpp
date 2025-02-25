#include "PaintDecal.h"
#include "PaintDecalManager.h"
#include "Components/DecalComponent.h"
#include "Components/BoxComponent.h"
#include "Materials/MaterialInterface.h"

APaintDecal::APaintDecal()
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

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> PaintDecalMaterial(TEXT("/Game/Resources/Materials/M_PaintDecal.M_PaintDecal"));
	if (PaintDecalMaterial.Succeeded())
	{
		DecalMaterial = PaintDecalMaterial.Object;
	}
	DecalSize = FVector(1.f);

	Tags.Add(FName("PaintDecal"));
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


