#include "EnemyCharger.h"
#include "Object/Character/Player/PlayerManager.h"

EnemyCharger::EnemyCharger()
    :Enemy(EnemyManager::EnemyType::Normal, "NormalEnemy")
{
}

void EnemyCharger::Initialize()
{
}

void EnemyCharger::Update(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    moveVec_ = playerCenterPosition - enemyCenterPosition;

    switch (state_)
    {
    case 0:
        Pursuit(elapsedTime);
        break;
    case 1:
        ChargeAttack(elapsedTime);
        break;
    }
}

void EnemyCharger::DrawDebug()
{
}

void EnemyCharger::Pursuit(const float& elapsedTime)
{
    // ù‰ñˆ—
    Turn();

    const float length = XMFloat2Length(moveVec_);
    
    float chargeRange_ = 500.0f;

    if (length < chargeRange_)
    {
        state_ = 1;
        moveSpeed_ = 0;
        chargeTime_ = 0;
    }

    Move(elapsedTime);
}

void EnemyCharger::ChargeAttack(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 moveDirection = XMFloat2Normalize(moveVec_);

    chargeTime_ += elapsedTime;
    if (chargeTime_ < 2.0f)
    {
        Turn();
    }
    else
    {
        moveSpeed_ = 5000.0f;
        Move(elapsedTime);
        if (chargeTime_ > 5.0f)
        {
            moveSpeed_ = 200.0f;
            state_ = 0;
        }
    }
}

void EnemyCharger::Turn()
{
    const DirectX::XMFLOAT2 moveDirection = XMFloat2Normalize(moveVec_);

    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveDirection.y, moveDirection.x) + DirectX::XM_PIDIV2));
}

void EnemyCharger::Move(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 moveDirection = XMFloat2Normalize(moveVec_);

    GetTransform()->AddPosition(moveDirection * moveSpeed_ * elapsedTime);
}


