#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGun.generated.h"

UENUM(BlueprintType)
enum class EFireMode : uint8
{
	FullAuto, // 연사
	SemiAuto, // 단발
};

class ULiquidTank;

UCLASS()
class SPLATOON_API ABaseGun : public AActor
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun|Sound")
	USoundBase* FireSound;
	
	virtual void BeginPlay() override;
	
/* Fire */
public:
	bool CanFire() const;
	bool Fire();
	int32 GetRemainingBullets() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun|Fire")
	float FireBulletInterval;
	
protected:
	// 탄환이 격발되는 시간 간격
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Gun|Fire")
	EFireMode FireMode;
	
/* Reload */
public:
	// 재장전 시작시 호출
	UFUNCTION(BlueprintCallable)
	void ReloadStart();
	// 재장전 종료
	UFUNCTION(BlueprintCallable)
	void ReloadStop();
	
protected:
	// 탄환이 장전되는 시간 간격
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Gun|Reload")
	float ReloadBulletInterval;
	
	FTimerHandle ReloadTimerHandle;

	bool CanReload() const;
	void Reload();
	
/* Bullets */
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun|Bullets")
	TSubclassOf<class ABaseBullet> BulletClass;
	
	// 남은 탄환 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun|Bullets")
	int32 RemainingBullets;

	// 최대 탄환 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun|Bullets")
	int32 MaxRemainingBullets;
	
	void AddRemainingBullets(const int Amount);
	
/* LiquidTank */
public:
	void SetLiquidTank(ULiquidTank* InLiquidTank);
	
protected:
	ULiquidTank* LiquidTank;
};
