// Fill out your copyright notice in the Description page of Project Settings.


#include "ClearBox.h"
#include "Splatoon/Character/SplatoonCharacter.h"
#include "Splatoon/Players/SplatoonPlayerController.h"
#include "Splatoon/LevelActors/Portal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AClearBox::AClearBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxCollisionComp);
	BoxCollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxCollisionComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoxCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AClearBox::OnOverlap);

	BoxStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxStaticMesh"));
	BoxStaticMeshComp->SetupAttachment(RootComponent);
	BoxStaticMeshComp->SetVisibility(false);

	BoxNiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("BoxNiagaraComp"));
	BoxNiagaraComp->SetupAttachment(RootComponent);
	BoxNiagaraComp->SetVisibility(false);
}

void AClearBox::ActiveBox()
{
	if (BoxCollisionComp) {
		BoxCollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		BoxCollisionComp->SetGenerateOverlapEvents(true);
	}

	if (BoxStaticMeshComp)
	{
		BoxStaticMeshComp->SetVisibility(true);
	}

	if (BoxNiagaraComp)
	{
		BoxNiagaraComp->SetVisibility(true);
	}
}

// Called when the game starts or when spawned
void AClearBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AClearBox::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASplatoonCharacter* Player = Cast<ASplatoonCharacter>(OtherActor);
	if (Player)
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		ASplatoonPlayerController* SplatoonPlayerController = Cast<ASplatoonPlayerController>(PlayerController);
		if (SplatoonPlayerController) {
			SplatoonPlayerController->ShowClearWidget();
			
			Player->CameraChange();
		}
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("TEST")));
	}
}


