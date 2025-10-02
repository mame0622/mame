#include "CollisionManager.h"
#include "Object/Character/Player/PlayerManager.h"
#include "Object/Character/Enemy/EnemyManager.h"
#include "Object/Character/Enemy/Enemy.h"

// XV
void CollisionManager::Update()
{
    if (EnemyManager::Instance().GetEnemyCount() == 0) return;
    // Player VS Enemy
    const DirectX::XMFLOAT2 playerPosition = PlayerManager::Instance().GetTransform()->GetPosition();
    const float playerCollisionRadius = PlayerManager::Instance().GetPlayer()->GetCollisionRadius();

    for (Enemy*& enemy : EnemyManager::Instance().GetEnemies())
    {
        DirectX::XMFLOAT2 resultPosition = {};
        if (IntersectCircleVsCircle(
            playerPosition, playerCollisionRadius,
            enemy->GetTransform()->GetPosition(), enemy->GetCollisionRadius(),
            resultPosition))
        {
            enemy->GetTransform()->SetPosition(resultPosition);
        }
    }
}

// ‰~ Vs ‰~
const bool CollisionManager::IntersectCircleVsCircle(const DirectX::XMFLOAT2& positionA, const float& radiusA, const DirectX::XMFLOAT2& positionB, const float& radiusB, DirectX::XMFLOAT2& resultPosition)
{
    const DirectX::XMFLOAT2 vec = positionB - positionA;
    const float length = XMFloat2Length(vec);
    const float overlap = radiusA + radiusB - length;

    // “–‚½‚Á‚Ä‚¢‚È‚¢
    if (overlap <= 0) return false;

    resultPosition = positionB + XMFloat2Normalize(vec) * overlap;

    return true;
}
