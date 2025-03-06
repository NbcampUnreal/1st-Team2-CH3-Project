#pragma once

#include "CoreMinimal.h"
#include "Perception/AIperceptionComponent.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 *
 */
UCLASS()
class SPLATOON_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	UPROPERTY(BlueprintReadWrite)
	class AEnemyBase* Agent;

	virtual FGenericTeamId GetGenericTeamId() const { return TeamId; }

protected:
	FGenericTeamId TeamId;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const;

};
