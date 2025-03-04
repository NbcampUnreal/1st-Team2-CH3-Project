#include "Balloon.h"
#include "Pearl.h"
#include "splatoon/Bullets/BaseBullet.h"
#include "Splatoon/Games/SplatoonGameMode.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"


ABalloon::ABalloon()
{
    // 풍선 충돌체
    BalloonCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("BalloonCollisionComp"));
    SetRootComponent(BalloonCollisionComp);
    BalloonCollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    BalloonCollisionComp->SetCollisionResponseToAllChannels(ECR_Overlap);
    BalloonCollisionComp->SetGenerateOverlapEvents(true);
    BalloonCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ABalloon::OnOverlap);
    
    // 풍선 메쉬
    BalloonMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BalloonMeshComp"));
    BalloonMeshComp->SetupAttachment(RootComponent);

    // 타임라인 (풍선 둥실둥실)
    FloatingTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("FloatingTimeline"));

    MaxHealth = 3;
    CurrentHealth = MaxHealth;
}

void ABalloon::BeginPlay()
{
    Super::BeginPlay();

    InitialLocation = GetActorLocation();

    if (FloatingCurve)
    {
        FOnTimelineFloat ProgressFunction; // 타임라인에서 값을 변화시킬 때 호출되는 델리게이트 (이벤트 함수 포인터)
        ProgressFunction.BindUFunction(this, FName("UpdateFloatingMovement"));
        FloatingTimeline->AddInterpFloat(FloatingCurve, ProgressFunction); // FloatingCurve의 Y값을 Value로 넘겨줌
        FloatingTimeline->SetLooping(true);
        FloatingTimeline->Play();
    }
}

void ABalloon::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ABaseBullet* Bullet = Cast<ABaseBullet>(OtherActor);
    if (!Bullet) return;

    CurrentHealth--;

    if (CurrentHealth <= 0)
    {
        DestroyBalloon();
    }
}

void ABalloon::UpdateFloatingMovement(float Value)
{
    FVector NewLocation = InitialLocation;
    NewLocation.Z += Value * 10.f;

    SetActorLocation(NewLocation);
}

void ABalloon::DestroyBalloon()
{
    if (BalloonPopEffect)
    {
        UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            BalloonPopEffect,
            GetActorLocation()
        );

        if (NiagaraComp)
        {
            NiagaraComp->SetAutoDestroy(true);
        }
    }

    if (PearlClass)
    {
        FActorSpawnParameters SpawnParams;
        GetWorld()->SpawnActor<APearl>(PearlClass, GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
    }

    ASplatoonGameMode* GameMode = Cast<ASplatoonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GameMode)
    {
        GameMode->DecreaseBalloonCount();
    }

    Destroy();
}




