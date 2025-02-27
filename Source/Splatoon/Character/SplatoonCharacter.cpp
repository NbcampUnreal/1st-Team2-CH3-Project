// Fill out your copyright notice in the Description page of Project Settings.


#include "SplatoonCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"
#include "Splatoon/Guns/Magazine/LiquidTank.h"
#include "Splatoon/Players/SplatoonPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"


ASplatoonCharacter::ASplatoonCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Main Character
	GetMesh()->SetReceivesDecals(false);
	
	// Transform Charater
	TransformMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TransformMesh"));
	TransformMeshComp->SetupAttachment(GetMesh());
	TransformMeshComp->SetVisibility(false);
	TransformMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TransformMeshComp->SetWorldScale3D(FVector3d(15.0f, 15.0f, 15.0f));
	TransformMeshComp->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	TransformMeshComp->SetReceivesDecals(false);

	//Niagara
	NiagaraPaintComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraPaintComponent->SetupAttachment(GetMesh());
	NiagaraPaintComponent->SetAutoActivate(false);
	

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
	SpeedDown = 0.3f;
	GetCharacterMovement()->MaxWalkSpeed = Speed;

	// HP
	MaxHealth = 3;
	Health = MaxHealth;
}

void ASplatoonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Create Gun Magazine
	{
		LiquidTank = NewObject<ULiquidTank>(this, ULiquidTank::StaticClass());

		if (LiquidTank && GetMesh())
		{
			if (UMaterialInstanceDynamic* LiquidTankMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(LiquidTankMaterialIndex), this))
			{
				GetMesh()->SetMaterial(LiquidTankMaterialIndex, LiquidTankMaterial);
				LiquidTank->Init(LiquidTankMaterial);
			}
		}
	}
	
	if (GunClass)
	{
		Gun = GetWorld()->SpawnActor<ABaseGun>(GunClass);

		if (Gun)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
			Gun->AttachToComponent(GetMesh(), AttachmentRules, FName("GunSocket"));
			Gun->SetLiquidTank(LiquidTank);
			Gun->SetInstigator(this);
		}
	}

	// Niagara
	if (NiagaraPaintEffect)
	{
		NiagaraPaintComponent->SetAsset(NiagaraPaintEffect);
	}

	// Excluding collision
	QueryParams.AddIgnoredActor(this);

	// Effect
	if (HitEffectWidgetClass)
	{
		HitEffectWidget = CreateWidget<UUserWidget>(GetWorld(), HitEffectWidgetClass);
	}
	
}

void ASplatoonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
					ETriggerEvent::Started,
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
	if (!GunClass) return;

	if (!bIsTransformed && !bIsFire)
	{
		if (Gun->GetRemainingBullets() <= 0) return;

		GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage);
		GetWorldTimerManager().SetTimer(
			FireTimerHandle,
			this,
			&ASplatoonCharacter::Attack,
			Gun->FireBulletInterval,
			true,
			0.0f
		);
		
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
			true,
			0.0f
		);
		bIsTransformed = true;

		GetMesh()->SetVisibility(false);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Gun->SetActorHiddenInGame(true);

		Crouch();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Off")));
		GetCharacterMovement()->MaxWalkSpeed = Speed;
		GetWorldTimerManager().ClearTimer(PaintCheckHandle);
		bIsTransformed = false;

		GetMesh()->SetVisibility(true);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Gun->SetActorHiddenInGame(false);

		if (TransformMeshComp->IsVisible() == true)
		{
			TransformMeshComp->SetVisibility(false);
			TransformMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}

		if (NiagaraPaintComponent->IsActive())
		{
			NiagaraPaintComponent->Deactivate();
		}

		Gun->ReloadStop();

		UnCrouch();
	}
}

void ASplatoonCharacter::CheckPaint()
{
	FVector Start = GetActorLocation();
	FVector End = Start - FVector(0, 0, 2000.0f);

	FHitResult HitResult;

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor && HitActor->ActorHasTag("PaintDecal"))
		{
			bIsPaint = true;
		}
		else
		{
			bIsPaint = false;
		}
	}
}

void ASplatoonCharacter::UpdatePaintCheck()
{
	CheckPaint();
	if (bIsPaint)
	{
		GetCharacterMovement()->MaxWalkSpeed = Speed * SpeedUp;
		if (NiagaraPaintComponent)
		{
			NiagaraPaintComponent->Activate();
		}

		if (TransformMeshComp->IsVisible() == true)
		{
			TransformMeshComp->SetVisibility(false);
			TransformMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}

		Gun->ReloadStart();
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = Speed * SpeedDown;
		TransformMeshComp->SetVisibility(true);
		TransformMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		if (NiagaraPaintComponent->IsActive())
		{
			NiagaraPaintComponent->Deactivate();
		}

		Gun->ReloadStop();
	}
}

void ASplatoonCharacter::Attack()
{
	Gun->Fire();
}

float ASplatoonCharacter::TakeDamage(
	float DamageAmount, 
	struct FDamageEvent const& DamageEvent, 
	AController* EventInstigator,
	AActor* DamageCauser)
{
	float SDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Hit")));
	Health--;

	if (Health <= 0)
	{
		OnDeath();
		return SDamage;
	}

	FVector PlayerLocation = GetActorLocation();
	FVector AttackerLocation = DamageCauser->GetActorLocation();

	FVector KnockbackDirection = (PlayerLocation - AttackerLocation).GetSafeNormal();

	float KnockbackStrength = 500.0f;
	FVector Knockback = KnockbackDirection * KnockbackStrength;

	//LaunchCharacter(Knockback, true, true);
	
	if (HitEffectWidget)
	{
		HitEffectWidget->RemoveFromParent();
		HitEffectWidget->AddToViewport();
	}

	return SDamage;
}

void ASplatoonCharacter::OnDeath()
{
	AController* PlayerController = GetController();
	if (PlayerController)
	{
		PlayerController->DisableInput(Cast<ASplatoonPlayerController>(PlayerController));
		bUseControllerRotationYaw = false;
	}
}

void ASplatoonCharacter::OnDropDeath()
{
	if (!CameraComp) return;
	ASplatoonPlayerController* NewPlayerController = Cast<ASplatoonPlayerController>(GetController());

	AActor* DeathCamera = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), GetActorLocation() + FVector(0, 0, 300), FRotator(-90, 0, 0));

	NewPlayerController->SetViewTargetWithBlend(DeathCamera, 3.0f);

	GetWorldTimerManager().SetTimer(
		DropTimerHandle,
		this,
		&ASplatoonCharacter::OnDeath,
		1.0f,
		false
	);
}