#include "StandardBullet.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"


AStandardBullet::AStandardBullet()
{
	// źȯ �޽�
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (SphereMesh.Succeeded())
	{
		BulletMeshComp->SetStaticMesh(SphereMesh.Object);
	}

	BulletMeshComp->SetRelativeScale3D(FVector(0.2f));

	// źȯ ����
	BulletMeshComp->SetSimulatePhysics(true);
	BulletMeshComp->SetEnableGravity(true);
}

void AStandardBullet::BeginPlay()
{
	Super::BeginPlay();
	
	BulletMeshComp->SetPhysicsLinearVelocity(TargetDirection * Speed); // �ʱ� �ӵ� ����
	BulletMeshComp->SetMassOverrideInKg(NAME_None, 2.f); // ���� ����
	BulletMeshComp->SetLinearDamping(0.5f); // ���� ���� ����
	BulletMeshComp->SetAngularDamping(0.5f);
}

void AStandardBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}

void AStandardBullet::OnBulletDestroyed()
{
	Super::OnBulletDestroyed();
}
