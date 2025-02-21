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

	// Transform Charater
	TransformMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TransformMesh"));
	TransformMeshComp->SetupAttachment(GetMesh());
	TransformMeshComp->SetVisibility(false);
	TransformMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	

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

	// Fire
	bIsFire = false;

	//Speed
	Speed = 400.0f;
	SpeedUp = 1.5f;
	SpeedDown = 0.7f;
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void ASplatoonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GunClass)
	{
		Gun = GetWorld()->SpawnActor<ABaseGun>(GunClass);

		if (Gun)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
			Gun->AttachToComponent(GetMesh(), AttachmentRules, FName("hand_r"));
		}
	}

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
					&ASplatoonCharacter::StartFire);
				EnhancedInput->BindAction(
					PlayerController->FireAction,
					ETriggerEvent::Completed,
					this,
					&ASplatoonCharacter::StopFire);
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
void ASplatoonCharacter::StartFire(const FInputActionValue& value)
{
	if (!bIsTransformed && !bIsFire)
	{
		Gun->FirePressed();
		GetWorldTimerManager().SetTimer(
			FireTimerHandle,
			Gun,
			&ABaseGun::FirePressed,
			Gun->FireBulletInterval,
			true
		);
		GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage);
		bIsFire = true;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire")));

	}
}
void ASplatoonCharacter::StopFire(const FInputActionValue& value)
{
	if (bIsFire)
	{
		GetWorldTimerManager().ClearTimer(FireTimerHandle);
		bIsFire = false;
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

		TransformMeshComp->SetVisibility(true);
		TransformMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		GetMesh()->SetVisibility(false);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Off")));
		GetCharacterMovement()->MaxWalkSpeed = Speed;
		GetWorldTimerManager().ClearTimer(PaintCheckHandle);
		bIsTransformed = false;

		GetMesh()->SetVisibility(true);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		TransformMeshComp->SetVisibility(false);
		TransformMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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