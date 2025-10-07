#include "EnemyNecromancer.h"
#include "Object/Character/Player/PlayerManager.h"

EnemyNecromancer::EnemyNecromancer()
    :Enemy("EnemyNecromancer", EnemyManager::EnemyType::Necromancer)
{

}

void EnemyNecromancer::Initialize()
{
    const float size = 100.0f;
    GetTransform()->SetSize(size);
    GetTransform()->SetTexSize(size);
    GetTransform()->SetPivot(size * 0.5f);

    SetCollisionRadius(50.0f);
}

void EnemyNecromancer::Update(const float& elapsedTime)
{
    float generationTime +=


    Pursuit(elapsedTime);
}

void EnemyNecromancer::DrawDebug()
{

}

// ’ÇÕˆ—
void EnemyNecromancer::Pursuit(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 moveVec = XMFloat2Normalize(playerCenterPosition - enemyCenterPosition);

    GetTransform()->AddPosition(moveVec * moveSpeed_ * elapsedTime);
    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveVec.y, moveVec.x) + DirectX::XM_PIDIV2));
}
