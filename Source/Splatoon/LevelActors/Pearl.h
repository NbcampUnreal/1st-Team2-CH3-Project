#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pearl.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class SPLATOON_API APearl : public AActor
{
	GENERATED_BODY()
	
public:	
	APearl();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pearl|Component")
	UStaticMeshComponent* PearlMeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pearl|Component")
	USphereComponent* PearlCollisionComp;

private:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
