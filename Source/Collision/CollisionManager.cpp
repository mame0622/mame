#include "CollisionManager.h"
#include "Object/Character/Player/PlayerManager.h"
#include "Object/Character/Enemy/EnemyManager.h"
#include "Object/Character/Enemy/Enemy.h"
#include "Object/Bullet/BulletManager.h"
#include "Application/Common.h"

// 更新
void CollisionManager::Update()
{
    // 生成処理
    for (Collision* collision : generates_)
    {
        collisions_.emplace_back(collision);
    }
    generates_.clear();

    // 更新
    for (int i = 0; i < collisions_.size(); ++i)
    {
        for (int j = i + 1; j < collisions_.size(); ++j)
        {
            auto collision1 = collisions_.at(i);
            auto collision2 = collisions_.at(j);

            if (collisionMatrix[(int)collision1->GetType()][(int)collision2->GetType()] == false)
            {
                continue;
            }
            
            DirectX::XMFLOAT2 resultPositionA = {};
            DirectX::XMFLOAT2 resultPositionB = {};
            if (IntersectCircleVsCircle(
                collision1->GetTransform()->GetPosition(), collision1->GetRadius(),
                collision2->GetTransform()->GetPosition(), collision2->GetRadius(),
                resultPositionA, resultPositionB))
            {
                collision1->OnHit(collision2->GetType(), resultPositionA);
                collision2->OnHit(collision1->GetType(), resultPositionB);
            }
        }
    }

    // 削除処理
    for (Collision* collision : removes_)
    {
        auto it = std::find(collisions_.begin(), collisions_.end(), collision);

        if (it != collisions_.end()) collisions_.erase(it);

        SafeDeletePtr(collision);
    }
    removes_.clear();
}

// 円 Vs 円
const bool CollisionManager::IntersectCircleVsCircle(const DirectX::XMFLOAT2& positionA, const float& radiusA, const DirectX::XMFLOAT2& positionB, const float& radiusB, DirectX::XMFLOAT2& resultPositionA, DirectX::XMFLOAT2& resultPositionB)
{
    const DirectX::XMFLOAT2 vec = positionB - positionA;
    const float length = XMFloat2Length(vec);
    const float overlap = radiusA + radiusB - length;

    // 当たっていない
    if (overlap <= 0) return false;

    resultPositionA = positionA + XMFloat2Normalize(vec) * -1.0f * overlap;
    resultPositionB = positionB + XMFloat2Normalize(vec) * overlap;

    return true;
}