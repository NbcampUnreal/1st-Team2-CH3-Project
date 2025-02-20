#include "BaseBullet.h"
#include "PaintDecal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"


ABaseBullet::ABaseBullet()
{
	PrimaryActorTick.bCanEverTick = false;

	BulletMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	SetRootComponent(BulletMeshComp);

	// 충돌 감지 설정
	BulletMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BulletMeshComp->SetNotifyRigidBodyCollision(true);

	// 충돌 이벤트 바인딩
	BulletMeshComp->OnComponentHit.AddDynamic(this, &ABaseBullet::OnHit);
}

void ABaseBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Bullet이 Character나 Pawn에 충돌 시 데칼 생성 X
	if (OtherActor && (OtherActor->IsA(ACharacter::StaticClass()) || OtherActor->IsA(APawn::StaticClass())))
	{
		OnBulletDestroyed();
		return;
	}

	// PaintDecal 생성
	APaintDecal::SpawnPaintDecal(GetWorld(), Hit.ImpactPoint, Hit.ImpactNormal.Rotation());

	OnBulletDestroyed();
}

void ABaseBullet::OnBulletDestroyed()
{
	Destroy();
}

