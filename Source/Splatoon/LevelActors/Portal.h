#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

class UBoxComponent;
class UNiagaraComponent;

UCLASS()
class SPLATOON_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	APortal();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentLevelIndex;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxLevels;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	FName NextLevelName;
	
	void ActivePortal();

	UFUNCTION(BlueprintCallable)
	void OpenLevel();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayWidgetAnimation();
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Portal")
	UBoxComponent* PortalCollisionComp;
	UPROPERTY(VisibleAnywhere, Category = "Portal")
	UNiagaraComponent* PortalNiagaraComp;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
