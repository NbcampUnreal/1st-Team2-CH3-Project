#include "EnemyBase.h"
#include "EnemyAIController.h"

AEnemyBase::AEnemyBase()
{
    // �� ĳ���͸� ��Ʈ���� AIController Ŭ������ EnemyAIController�� ����
    AIControllerClass = AEnemyAIController::StaticClass();
    // ������ ��ġ�ǰų� �����Ǹ� �ڵ����� AIController�� �Ҵ�ǵ��� ����
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

