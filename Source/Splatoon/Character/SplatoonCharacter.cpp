// Fill out your copyright notice in the Description page of Project Settings.


#include "SplatoonCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "Splatoon/Players/SplatoonPlayerController.h"

ASplatoonCharacter::ASplatoonCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// SpringArm
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;
	// Camera
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	// Character form
	bIsTransformed = false;

	// Paint
	bIsPaint = false;

	//Speed
	Speed = 400.0f;
	SpeedUp = 1.5f;
	SpeedDown = 0.7f;
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void ASplatoonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASplatoonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASplatoonCharacter::CheckPaint()
{
	FVector Start = GetActorLocation();
	FVector End = Start - FVector(0, 0, 200.0f);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel1, Params);

	// 데칼 작업 후 변경 예정
	if (bHit)
	{
		bIsPaint = true;
	}
}

void ASplatoonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ASplatoonPlayerController* PlayerController = Cast<ASplatoonPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&ASplatoonCharacter::Move);
			}
			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered,
					this,
					&ASplatoonCharacter::StartJump);
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,
					this,
					&ASplatoonCharacter::StopJump);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ASplatoonCharacter::Look);
			}
			if (PlayerController->FireAction)
			{
				EnhancedInput->BindAction(
					PlayerController->FireAction,
					ETriggerEvent::Triggered,
					this,
					&ASplatoonCharacter::Fire);
			}
			if (PlayerController->TransforAction)
			{
				EnhancedInput->BindAction(
					PlayerController->TransforAction,
					ETriggerEvent::Triggered,
					this,
					&ASplatoonCharacter::Transfor);
			}
		}
	}
}


void ASplatoonCharacter::Move(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}
void ASplatoonCharacter::StartJump(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		Jump();
	}
}
void ASplatoonCharacter::StopJump(const FInputActionValue& value)
{
	if (!value.Get<bool>())
	{
		StopJumping();
	}
}
void ASplatoonCharacter::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}
void ASplatoonCharacter::Fire(const FInputActionValue& value)
{
	if (!bIsTransformed)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire")));
	}
}
void ASplatoonCharacter::Transfor(const FInputActionValue& value)
{
	if (!bIsTransformed)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Transform")));
		GetWorldTimerManager().SetTimer(
			PaintCheckHandle,
			this,
			&ASplatoonCharacter::UpdatePaintCheck,
			0.01f,
			true
		);
		bIsTransformed = true;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Off")));
		GetCharacterMovement()->MaxWalkSpeed = Speed;
		GetWorldTimerManager().ClearTimer(PaintCheckHandle);
		bIsTransformed = false;
	}
}

void ASplatoonCharacter::UpdatePaintCheck()
{
	if (bIsPaint)
	{
		GetCharacterMovement()->MaxWalkSpeed = Speed * SpeedUp;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = Speed * SpeedDown;
	}
}