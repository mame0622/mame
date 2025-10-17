#include "EnemyRobot.h"
#include "Object/Character/Player/PlayerManager.h"
#include "Object/Bullet/BulletStraight/BulletStraight.h"
#include "Object/Bullet/BulletManager.h"
#include "Input/Input.h"

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

    GetTransform()->SetPosition(300.0f, 400.0f);
}

void EnemyRobot::Update(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    moveVec_ = playerCenterPosition - enemyCenterPosition;


    // ’ÇÕˆ—
    Pursuit(elapsedTime);
    //switch (state_)
    //{
    //case 0:
    // ¡‚Íƒ{ƒ^ƒ“‚Å”»’è‚µ‚Ä‚é(¡Œã‚ÍHP‚ª0‚É‚È‚Á‚½uŠÔ“ü‚é)
    if (Input::Instance().GetGamePad().GetButtonDown() & GamePad::BTN_LEFT_SHOULDER) {
        BulletStraight* bulletStraight = new BulletStraight;
        BulletManager::Instance().Register(bulletStraight);
        

        const DirectX::XMFLOAT2 moveDirection = XMFloat2Normalize(moveVec_);

        bulletStraight->Initialize(100.0f, GetTransform()->GetCenterPosition(), moveDirection);

        bulletStraight->Launch(elapsedTime, moveDirection);
    }
    //    break;
    //}

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
