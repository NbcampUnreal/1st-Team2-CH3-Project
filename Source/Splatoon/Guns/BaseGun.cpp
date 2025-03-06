#include "BaseGun.h"
#include "Magazine/LiquidTank.h"
#include "Components/StaticMeshComponent.h"
#include "Splatoon/Bullets/BaseBullet.h"
#include "Splatoon/Character/SplatoonCharacter.h"
#include "Kismet/GameplayStatics.h"

ABaseGun::ABaseGun()
{
	PrimaryActorTick.bCanEverTick = false;

	/* 컴포넌트 초기화 */
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComp);
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(GetRootComponent());
	StaticMeshComp->SetCollisionProfileName(FName("NoCollision"));
	StaticMeshComp->SetReceivesDecals(false);
	
	FrontOfGun = CreateDefaultSubobject<USceneComponent>(TEXT("FrontOfGun"));
	FrontOfGun->SetupAttachment(GetRootComponent());

	/* Fire 초기화 */
	FireMode = EFireMode::FullAuto;
	FireBulletInterval = 0.2f;

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

void ABaseGun::ReloadStart()
{
	if (UWorld* World = GetWorld())
	{
		if (!World->GetTimerManager().IsTimerActive(ReloadTimerHandle))
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
}

void ABaseGun::ReloadStop()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(ReloadTimerHandle);
	}
}

bool ABaseGun::CanFire() const
{
	return RemainingBullets > 0 && GetWorld();
}


bool ABaseGun::Fire()
{
	// 1. 남은 탄환 확인
	if (!CanFire()) return false;

	// 2. 탄환 감소
	AddRemainingBullets(-1);

	// 3. 소리 출력
	UGameplayStatics::PlaySound2D(GetWorld(), FireSound, 1.0f, 1.0f, 0.0f);

	// 4. 탄환 생성
	if (APlayerController* Controller = GetWorld()->GetFirstPlayerController())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this; // 총알을 생성한 액터              
		SpawnParams.Instigator = Controller->GetPawn(); // 총알을 발사한 주체
	
		GetWorld()->SpawnActor<AActor>(
			BulletClass,
			FrontOfGun->GetComponentLocation(),
			FrontOfGun->GetComponentRotation(),
			SpawnParams
		);
	}
	
	return true;
}

bool ABaseGun::CanReload() const
{
	return RemainingBullets < MaxRemainingBullets;
}

int32 ABaseGun::GetRemainingBullets() const
{
	return RemainingBullets;
}

void ABaseGun::Reload()
{
	if (!CanReload()) return;
	
	AddRemainingBullets(1);
}

void ABaseGun::AddRemainingBullets(const int Amount)
{
	RemainingBullets = FMath::Clamp(RemainingBullets + Amount, 0, MaxRemainingBullets);

	if (LiquidTank)
	{
		LiquidTank->SetPercent(static_cast<float>(RemainingBullets) / MaxRemainingBullets);
	}
}

void ABaseGun::SetLiquidTank(ULiquidTank* InLiquidTank)
{
	LiquidTank = InLiquidTank;
}