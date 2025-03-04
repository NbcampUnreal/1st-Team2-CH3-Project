#include "Portal.h"
#include "Splatoon/Character/SplatoonCharacter.h"
#include "Splatoon/Games/SplatoonGameMode.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = false;

	// Portal Collision
	PortalCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("PortalCollisionComp"));
	SetRootComponent(PortalCollisionComp);
	PortalCollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PortalCollisionComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	PortalCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlap);

	// Portal Mesh
	PortalNiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PortalNiagaraComp"));
	PortalNiagaraComp->SetupAttachment(RootComponent);
	PortalNiagaraComp->SetVisibility(false);

	CurrentLevelIndex = 0;
	MaxLevels = 3;
}

void APortal::ActivePortal()
{
	if (!PortalNiagaraComp) return;

	PortalNiagaraComp->SetVisibility(true);

	if (PortalCollisionComp)
	{
		PortalCollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		PortalCollisionComp->SetGenerateOverlapEvents(true);
	}
}

void APortal::OpenLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
}

void APortal::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASplatoonCharacter* Player = Cast<ASplatoonCharacter>(OtherActor);
	if (Player)
	{
		PlayWidgetAnimation();
	}
}

