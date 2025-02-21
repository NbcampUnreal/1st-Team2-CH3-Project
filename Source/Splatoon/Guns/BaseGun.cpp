#include "BaseGun.h"

#include "Kismet/GameplayStatics.h"

ABaseGun::ABaseGun()
{
	PrimaryActorTick.bCanEverTick = false;

	/* 컴포넌트 초기화 */
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComp);
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(GetRootComponent());
	
	FrontOfGun = CreateDefaultSubobject<USceneComponent>(TEXT("FrontOfGun"));
	FrontOfGun->SetupAttachment(GetRootComponent());

	/* Fire 초기화 */
	FireMode = EFireMode::FullAuto;
	FireBulletInterval = 0.1f;

	/* Reload 초기화 */
	ReloadBulletInterval = 0.1f;

	/* Bullets 초기화 */
	MaxRemainingBullets = 20;
	RemainingBullets = MaxRemainingBullets;
}

void ABaseGun::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseGun::FirePressed()
{
	Fire();
}

void ABaseGun::ReloadStart()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(
			ReloadTimerHandle,
			this,
			&ABaseGun::Reload,
			ReloadBulletInterval,
			true
		);
	}
}

void ABaseGun::ReloadStop()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(ReloadTimerHandle);
	}
}

bool ABaseGun::Fire()
{
	// 1. 남은 탄환 확인
	if (RemainingBullets <= 0) return false;
	if (GetWorld() == nullptr) return false;

	// 2. 탄환 감소
	RemainingBullets -= 1;

	// 3. 탄환 생성
	GetWorld()->SpawnActor<AActor>(
		BulletClass,
		FrontOfGun->GetComponentLocation(),
		FrontOfGun->GetComponentRotation()
	);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Fire / RemainingBullets = %d"), RemainingBullets));
	return true;
}

void ABaseGun::Reload()
{
	if (RemainingBullets >= MaxRemainingBullets) return;
	
	RemainingBullets += 1;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Reload / RemainingBullets = %d"), RemainingBullets));
}
