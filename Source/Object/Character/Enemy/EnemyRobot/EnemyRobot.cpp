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

// 初期化
void EnemyRobot::Initialize()
{
    GetTransform()->SetSize(size_);
    GetTransform()->SetTexSize(size_);
    GetTransform()->SetPivot(size_ * 0.5f);

    GetTransform()->SetPosition(300.0f, 400.0f);
}

// 更新
void EnemyRobot::Update(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    moveDirection_ = XMFloat2Normalize(playerCenterPosition - enemyCenterPosition);


    // 追跡処理
    Pursuit(elapsedTime);
    //switch (state_)
    //{
    //case 0:
    // 今はボタンで判定してる(今後はHPが0になった瞬間入る)
    if (Input::Instance().GetGamePad().GetButtonDown() & GamePad::BTN_LEFT_SHOULDER) 
    {        
        BulletStraight* bulletStraight = new BulletStraight;
        BulletManager::Instance().Register(bulletStraight);
        
        // 弾の生成位置を決める
        const DirectX::XMFLOAT2 generatePosition = enemyCenterPosition + moveDirection_ * generateOffset_;

        bulletStraight->Initialize(generatePosition);
        bulletStraight->Launch(moveDirection_);
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

// 追跡処理
void EnemyRobot::Pursuit(const float& elapsedTime)
{
    GetTransform()->AddPosition(moveDirection_ * moveSpeed_ * elapsedTime);
    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveDirection_.y, moveDirection_.x) + DirectX::XM_PIDIV2));
}
