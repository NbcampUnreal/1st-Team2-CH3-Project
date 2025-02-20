// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SplatoonCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
struct  FInputActionValue;

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

	// Character form
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Transform")
	bool bIsTransformed;

	//Paint
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Paint")
	bool bIsPaint;

	// RayCast
	void PaintCheck();

	//TimerHandle
	FTimerHandle PaintCheckHandle;
	void UpdatePaintCheck();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

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
	void Fire(const FInputActionValue& value);
	UFUNCTION()
	void Transfor(const FInputActionValue& value);

};
