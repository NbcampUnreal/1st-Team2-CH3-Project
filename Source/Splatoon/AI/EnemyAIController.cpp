#include "EnemyAIController.h"
#include "EnemyBase.h"
#include "Navigation/PathFollowingComponent.h"

void AEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
}

void AEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

	AEnemyBase* Chr = Cast<AEnemyBase>(GetPawn());
	if (Chr)
	{
		Agent = Chr;
		TeamId = FGenericTeamId(Agent->ID);
	}
}

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);
}

ETeamAttitude::Type AEnemyAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	// Check if Pawn
	const APawn* OtherPawn = Cast<APawn>(&Other);
	if (OtherPawn == nullptr)
	{
		return ETeamAttitude::Neutral;
	}

	auto PlayerTI = Cast<IGenericTeamAgentInterface>(&Other);
	class IGenericTeamAgentInterface* BotTI = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController());
	if (BotTI == nullptr && PlayerTI == nullptr)
	{
		return ETeamAttitude::Neutral;
	}

	FGenericTeamId OtherActorTeamId = NULL;
	if (BotTI != nullptr)
	{
		OtherActorTeamId = BotTI->GetGenericTeamId();
	}
	else if (PlayerTI != nullptr)
	{
		OtherActorTeamId = PlayerTI->GetGenericTeamId();
	}

	FGenericTeamId ThisId = GetGenericTeamId();
	if (OtherActorTeamId == 8)
	{
		return ETeamAttitude::Neutral;
	}
	else if (OtherActorTeamId == ThisId)
	{
		return ETeamAttitude::Friendly;
	}
	else
	{
		return ETeamAttitude::Hostile;
	}
}
