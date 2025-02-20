#pragma once

#include "CoreMinimal.h"
#include "GunInterface.h"
#include "GameFramework/Actor.h"
#include "BaseGun.generated.h"

UENUM(BlueprintType)
enum class EFireMode : uint8
{
	FullAuto, // 연사
	SemiAuto, // 단발
};

UCLASS()
class SPLATOON_API ABaseGun : public AActor, public IGunInterface
{
	GENERATED_BODY()

public:	
	ABaseGun();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun")
	TObjectPtr<USceneComponent> RootComp;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun")
	TObjectPtr<USceneComponent> FrontOfGun;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;
	
	virtual void BeginPlay() override;
	
/* IGunInterface */
public:
	UFUNCTION(BlueprintCallable)
	virtual void FirePressed() override;
	UFUNCTION(BlueprintCallable)
	virtual void FireReleased() override;

	UFUNCTION(BlueprintCallable)
	virtual void ReloadStart() override;
	UFUNCTION(BlueprintCallable)
	virtual void ReloadEnd() override;

/* Fire */
protected:
	// 탄환이 격발되는 시간 간격
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Gun|Interval")
	float FireBulletInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Gun|Fire")
	EFireMode FireMode;

	FTimerHandle FireTimerHandle;
	
	void Fire();
	
/* Reload */
protected:
	// 탄환이 장전되는 시간 간격
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Gun|Interval")
	float ReloadBulletInterval;
	
	FTimerHandle ReloadTimerHandle;
	
	void Reload();
	
/* Bullets */
protected:
	// TODO: AActor -> BaseBullet
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun|Bullets")
	TSubclassOf<AActor> BulletClass;
	
	// 남은 탄환 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun|Bullets")
	int32 RemainingBullets;

	// 최대 탄환 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun|Bullets")
	int32 MaxRemainingBullets;
};
