#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBullet.generated.h"

class UStaticMeshComponent;

UCLASS()
class SPLATOON_API ABaseBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseBullet();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category = "Bullet|Component")
	UStaticMeshComponent* BulletMeshComp;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void OnBulletDestroyed();

/* Control */
protected:
	FVector TargetDirection;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet | Control")
	float TargetDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet | Control")
	float Speed;
};
