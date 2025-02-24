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

	// �浹 ���� ����
	BulletMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BulletMeshComp->SetNotifyRigidBodyCollision(true);

	// �浹 �̺�Ʈ ���ε�
	BulletMeshComp->OnComponentHit.AddDynamic(this, &ABaseBullet::OnHit);
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

	// PaintDecal ����
	APaintDecal::SpawnPaintDecal(GetWorld(), Hit.ImpactPoint, Hit.ImpactNormal.Rotation());

	OnBulletDestroyed();
}

void ABaseBullet::OnBulletDestroyed()
{
	Destroy();
}

