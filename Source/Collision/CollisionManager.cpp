#include "CollisionManager.h"
#include "Object/Character/Player/PlayerManager.h"
#include "Object/Character/Enemy/EnemyManager.h"
#include "Object/Character/Enemy/Enemy.h"
#include "Object/Bullet/BulletManager.h"

// XV
void CollisionManager::Update()
{
    if (EnemyManager::Instance().GetEnemyCount() == 0) return;

    const DirectX::XMFLOAT2 playerPosition = PlayerManager::Instance().GetTransform()->GetPosition();
    std::vector<Enemy*> enemies = EnemyManager::Instance().GetEnemies();
    const int maxEnemyCount = EnemyManager::Instance().GetEnemyCount();


    // ----- Enemy Vs Enemy -----
    for (int i = 0; i < maxEnemyCount; ++i)
    {
        for (int j = 0; j < maxEnemyCount; ++j)
        {
            // “¯‚¶ŒÂ‘Ì“¯Žm‚ÍƒXƒLƒbƒv
            if (i == j) continue;

            DirectX::XMFLOAT2 resultPosition = {};
            if (IntersectCircleVsCircle(
                enemies.at(i)->GetTransform()->GetPosition(), enemies.at(i)->GetCollisionRadius(),
                enemies.at(j)->GetTransform()->GetPosition(), enemies.at(j)->GetCollisionRadius(),
                resultPosition))
            {
                enemies.at(j)->GetTransform()->SetPosition(resultPosition);
            }
        }
    }

    // ----- Bullet Vs Enemy -----
    // -----  PushCollider   -----
    std::vector<Bullet> bullets = BulletManager::Instance().GetBullets();
    const int maxBulletCount = BulletManager::Instance().GetBulletCount();
    for (int bulletIndex = 0; bulletIndex < maxBulletCount; ++bulletIndex)
    {
        for (int enemyIndex = 0; enemyIndex < maxEnemyCount; ++enemyIndex)
        {
            DirectX::XMFLOAT2 resultPosition = {};
            if (IntersectCircleVsCircle(
                bullets.at(bulletIndex).GetTransform()->GetPosition(), bullets.at(bulletIndex).GetCollisionRadius(),
                enemies.at(enemyIndex)->GetTransform()->GetPosition(), enemies.at(enemyIndex)->GetCollisionRadius(),
                resultPosition))
            {
                enemies.at(enemyIndex)->GetTransform()->SetPosition(resultPosition);
            }
        }
    }

    // Player VS Enemy
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
