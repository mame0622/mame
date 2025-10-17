#include "BulletStraight.h"
#include "Object/Character/Enemy/EnemyManager.h"

BulletStraight::BulletStraight()
    :Bullet("BulletLevel1", BulletLevel::One,
        Collision::Type::Bullet, this, 25.0f)
{

}

void BulletStraight::Initialize(const DirectX::XMFLOAT2& generatePosition)
{
    // Bulletのサイズ設定
    const DirectX::XMFLOAT2 bulletSize = { 30.0f, 30.0f };
    GetTransform()->SetSize(bulletSize);
    GetTransform()->SetTexSize(bulletSize);
    GetTransform()->SetPivot(bulletSize * 0.5f);

    // 生成位置設定
    const DirectX::XMFLOAT2 offsetPosition = GetTransform()->GetSize() * 0.5f;
    GetTransform()->SetPosition(generatePosition - offsetPosition);

    // 角度設定
    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveDirection_.y, moveDirection_.x) + DirectX::XM_PIDIV2));
}

void BulletStraight::Update(const float& elapsedTime)
{
    Bullet::Update(elapsedTime);
    GetTransform()->AddPosition(moveDirection_ * moveSpeed_ * elapsedTime);
}

void BulletStraight::DrawDebug()
{
}

void BulletStraight::OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position)
{
}

// 発射
void BulletStraight::Launch(const DirectX::XMFLOAT2& moveDirection)
{
    moveDirection_ = moveDirection;
}
