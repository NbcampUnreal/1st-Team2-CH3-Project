#include "Pearl.h"
#include "Splatoon/character/SplatoonCharacter.h"
#include "Splatoon/Games/SplatoonGameMode.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


APearl::APearl()
{
	// 진주 충돌체
	PearlCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("PearlCollisionComp"));
	SetRootComponent(PearlCollisionComp);
	PearlCollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PearlCollisionComp->SetCollisionResponseToAllChannels(ECR_Block);
	PearlCollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	PearlCollisionComp->SetSimulatePhysics(true);
	PearlCollisionComp->SetEnableGravity(true);

	PearlCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APearl::OnOverlap);

	// 진주 메쉬
	PearlMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PearlMeshComp"));
	PearlMeshComp->SetupAttachment(RootComponent);
}

void APearl::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASplatoonCharacter* Player = Cast<ASplatoonCharacter>(OtherActor);
	if (Player)
	{
		ASplatoonGameMode* GameMode = Cast<ASplatoonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode)
		{
			GameMode->IncreaseGameScore(100);
		}
		Destroy();
	}
}

