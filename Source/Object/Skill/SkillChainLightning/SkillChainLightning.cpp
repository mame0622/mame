#include "SkillChainLightning.h"
#include "Object/Character/Player/PlayerManager.h"
#include "Object/Character/Enemy/EnemyManager.h"
#include "Object/Character/Enemy/Enemy.h"

SkillChainLightning::SkillChainLightning()
{
}

void SkillChainLightning::Initialize()
{
    // Player‚©‚çÅ‚à‹ß‚¢“G‚©‚ç‡”Ô‚É‚T‘Ì‹‚ß‚é
    const DirectX::XMFLOAT2 playerPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    float minLength = FLT_MAX;
    int nearestEnemyIndex = 0;
    for (int enemyIndex = 0; enemyIndex < EnemyManager::Instance().GetEnemyCount(); ++enemyIndex)
    {
        const DirectX::XMFLOAT2 enemyPosition = EnemyManager::Instance().GetEnemy(enemyIndex)->GetTransform()->GetCenterPosition();
        const float length = XMFloat2Length(enemyPosition - playerPosition);

        if (minLength > length)
        {
            minLength = length;
            nearestEnemyIndex = enemyIndex;
        }
    }
    enemyIndexes_.emplace_back(nearestEnemyIndex);

    for (int i = 0; i < 4; ++i)
    {
        FindNearestEnemy(enemyIndexes_.at(i));
    }

    int a = 0;
}

void SkillChainLightning::Update(const float& elapsedTime)
{

}

void SkillChainLightning::FindNearestEnemy(const int& index)
{
    const DirectX::XMFLOAT2 startPosition = EnemyManager::Instance().GetEnemy(index)->GetTransform()->GetCenterPosition();

    float minLength = FLT_MAX;
    int nearestEnemyIndex = 0;
    for (int enemyIndex = 0; enemyIndex < EnemyManager::Instance().GetEnemyCount(); ++enemyIndex)
    {
        if (enemyIndex == index) continue;

        const DirectX::XMFLOAT2 enemyPosition = EnemyManager::Instance().GetEnemy(enemyIndex)->GetTransform()->GetPosition();
        const float length = XMFloat2Length(enemyPosition - startPosition);

        if (minLength > length)
        {
            minLength = length;
            nearestEnemyIndex = enemyIndex;
        }
    }

    enemyIndexes_.emplace_back(nearestEnemyIndex);
}
