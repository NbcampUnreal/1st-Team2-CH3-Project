#include "BaseBullet.h"
#include "PaintDecal.h"
#include "EnemyPaintDecal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"


ABaseBullet::ABaseBullet()
{
	PrimaryActorTick.bCanEverTick = false;

	BulletMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	SetRootComponent(BulletMeshComp);

	// �浹 ���� ����
	BulletMeshComp->SetCollisionProfileName(TEXT("Bullet"));
	BulletMeshComp->SetNotifyRigidBodyCollision(true);
	BulletMeshComp->OnComponentHit.AddDynamic(this, &ABaseBullet::OnHit);

	// Control
	Speed = 2500.f;
	TargetDistance = 2500.f;
}

void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();

	// 총알 방향 계산
	if (GetInstigator())
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		GetInstigator()->GetActorEyesViewPoint(CameraLocation, CameraRotation);
		FVector TraceStart = CameraLocation;
		FVector TraceEnd = TraceStart + (CameraRotation.Vector() * TargetDistance);
		TargetDirection = (TraceEnd - GetActorLocation()).GetSafeNormal();;
	}
}

void ABaseBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 목표 대상이 플레이어인 경우 
	if (OtherActor == GetInstigator()) return;

	// Bullet이 Character나 Pawn에 충돌 시 데칼 생성 X
	if (OtherActor && (OtherActor->IsA(ACharacter::StaticClass()) || OtherActor->IsA(APawn::StaticClass())))
	{
		OnBulletDestroyed();
		return;
	}

	// PaintDecal 생성
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	if (GetInstigatorController() == Controller) 
	{
		APaintDecal::SpawnPaintDecal(GetWorld(), Hit.ImpactPoint, (-Hit.ImpactNormal).Rotation());
	}
	else 
	{
		AEnemyPaintDecal::SpawnPaintDecal(GetWorld(), Hit.ImpactPoint, (-Hit.ImpactNormal).Rotation());
	}

	OnBulletDestroyed();
}

void ABaseBullet::OnBulletDestroyed()
{
	Destroy();
}