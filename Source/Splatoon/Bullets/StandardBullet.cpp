#include "StandardBullet.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"


AStandardBullet::AStandardBullet()
{
	// 탄환 메쉬
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (SphereMesh.Succeeded())
	{
		BulletMeshComp->SetStaticMesh(SphereMesh.Object);
	}

	BulletMeshComp->SetRelativeScale3D(FVector(0.2f));

	// 탄환 동작
	BulletMeshComp->SetSimulatePhysics(true);
	BulletMeshComp->SetEnableGravity(true);
	BulletMeshComp->SetCollisionProfileName(TEXT("BlockAll"));
}

void AStandardBullet::BeginPlay()
{
	Super::BeginPlay();

	BulletMeshComp->SetPhysicsLinearVelocity(GetActorForwardVector() * 1000.f); // 초기 속도 설정
	BulletMeshComp->SetMassOverrideInKg(NAME_None, 2.f); // 질량 증가
	BulletMeshComp->SetLinearDamping(0.5f); // 공기 저항 적용
	BulletMeshComp->SetAngularDamping(0.5f);
}

void AStandardBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("OnHit")));
}

void AStandardBullet::OnBulletDestroyed()
{
	Super::OnBulletDestroyed();
}
