#include "EnemyRobot.h"
#include "Object/Character/Player/PlayerManager.h"

EnemyRobot::EnemyRobot()
    :Enemy("EnemyRobot", EnemyManager::EnemyType::Robot,
        Collision::Type::Enemy, this, 100.0f)
{
}

void EnemyRobot::Initialize()
{
    GetTransform()->SetSize(size_);
    GetTransform()->SetTexSize(size_);
    GetTransform()->SetPivot(size_ * 0.5f);
}

void EnemyRobot::Update(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    moveVec_ = playerCenterPosition - enemyCenterPosition;

    // ’ÇÕˆ—
    Pursuit(elapsedTime);


}

void EnemyRobot::DrawDebug()
{
}

void EnemyRobot::OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position)
{
}

// ’ÇÕˆ—
void EnemyRobot::Pursuit(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 moveDirection = XMFloat2Normalize(moveVec_);

    GetTransform()->AddPosition(moveDirection * moveSpeed_ * elapsedTime);
    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveDirection.y, moveDirection.x) + DirectX::XM_PIDIV2));
}
