// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Splatoon/Guns/BaseGun.h"
#include "Animation/AnimMontage.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "SplatoonCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ULiquidTank;
class UUserWidget;
struct FInputActionValue;

UCLASS()
class SPLATOON_API ASplatoonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASplatoonCharacter();

protected:
	virtual void BeginPlay() override;

	// Speed
	float Speed;
	float SpeedUp;
	float SpeedDown;

	// HP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 Health;

	//Paint
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Paint")
	bool bIsPaint;

	// RayCast
	void CheckPaint();

	//TimerHandle
	FTimerHandle PaintCheckHandle;
	void UpdatePaintCheck();

	// Gun
	FTimerHandle FireTimerHandle;
	bool bIsFire;
	void Attack();

	// LiquidTank
	UPROPERTY()
	ULiquidTank* LiquidTank;
	const int32 LiquidTankMaterialIndex = 4;

	// Excluding collision
	FCollisionQueryParams QueryParams;

	// Niagara
	UPROPERTY(EditAnywhere, Category = "Effects")
	UNiagaraSystem* NiagaraPaintEffect;
	UPROPERTY(VisibleAnywhere, Category = "Effects")
	UNiagaraComponent* NiagaraPaintComponent;

	// Effect
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> HitEffectWidgetClass;

	UPROPERTY()
	UUserWidget* HitEffectWidget;
	
	// Damage
	FTimerHandle DamageResetHandle;
	FTimerHandle RecoverHealthHandle;
	void StartRecoverHealth();
	void HealthUp();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	//Charater
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charater")
	UStaticMeshComponent* TransformMeshComp;

	// Animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* AttackMontage;

	// Character form
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Transform")
	bool bIsTransformed;

	// Gun
	UPROPERTY(EditDefaultsOnly, Category = "Gun")
	TSubclassOf<ABaseGun> GunClass;
	ABaseGun* Gun;

	// Damage
	void TakeDamage(AActor* DamageCauser);
	UFUNCTION(BlueprintCallable)
	float fHealthPercent();

	// Death
	UFUNCTION()
	void OnDeath();
	UFUNCTION()
	void OnDropDeath();
	FTimerHandle DropTimerHandle;

	// Input Function
	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void StartJump(const FInputActionValue& value);
	UFUNCTION()
	void StopJump(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void StartFire(const FInputActionValue& value);
	UFUNCTION()
	void StopFire(const FInputActionValue& value);
	UFUNCTION()
	void Transfor(const FInputActionValue& value);

};
