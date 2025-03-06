#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "EnemyBase.generated.h"

UCLASS()
class SPLATOON_API AEnemyBase : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AEnemyBase();

	// TeamId
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	int32 ID = 0;

	virtual FGenericTeamId GetGenericTeamId() const { return TeamId; }

protected:
	FGenericTeamId TeamId;
};

