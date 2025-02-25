#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Balloon.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UTimelineComponent;
class UCurveFloat;
class UNiagaraSystem;
class APearl;

UCLASS()
class SPLATOON_API ABalloon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABalloon();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Balloon|Component")
	UStaticMeshComponent* BalloonMeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Balloon|Component")
	USphereComponent* BalloonCollisionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Balloon|FloatingMovement")
	UTimelineComponent* FloatingTimeline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Balloon|FloatingMovement")
	UCurveFloat* FloatingCurve; // Curve Float ¿¡¼Â
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Balloon|Health")
	int32 MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Balloon|Health")
	int32 CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Balloon|Effect")
	UNiagaraSystem* BalloonPopEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Balloon|Reward")
	TSubclassOf<APearl> PearlClass;

	FVector InitialLocation;

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void UpdateFloatingMovement(float Value);
	void DestroyBalloon();

	virtual void BeginPlay() override;
};
