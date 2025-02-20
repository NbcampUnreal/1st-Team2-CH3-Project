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
	// Bullet�� Character�� Pawn�� �浹 �� ��Į ���� X
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

