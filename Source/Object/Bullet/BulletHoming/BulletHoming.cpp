#include "BulletHoming.h"
#include "Object/Character/Enemy/EnemyManager.h"
#include "Object/Character/Player/PlayerManager.h"

BulletHoming::BulletHoming()
    :Bullet("BulletLevel1", BulletLevel::One,
        Collision::Type::Bullet, this, 25.0f)
{

}

void BulletHoming::Initialize(const DirectX::XMFLOAT2& generatePosition)
{
    // Bullet�̃T�C�Y�ݒ�
    const DirectX::XMFLOAT2 bulletSize = { 30.0f, 30.0f };
    GetTransform()->SetSize(bulletSize);
    GetTransform()->SetTexSize(bulletSize);
    GetTransform()->SetPivot(bulletSize * 0.5f);

    // �����ʒu�ݒ�
    const DirectX::XMFLOAT2 offsetPosition = GetTransform()->GetSize() * 0.5f;
    GetTransform()->SetPosition(generatePosition - offsetPosition);

    // �p�x�ݒ�
    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveDirection_.y, moveDirection_.x) + DirectX::XM_PIDIV2));
}

void BulletHoming::Update(const float& elapsedTime)
{
    Bullet::Update(elapsedTime);

    Pursuit(elapsedTime);
}

void BulletHoming::DrawDebug()
{
}

void BulletHoming::OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position)
{
}

// ����
void BulletHoming::Launch(const DirectX::XMFLOAT2& moveDirection)
{
    moveDirection_ = moveDirection;
}

void  BulletHoming::Pursuit(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 homingCenterPosition = GetTransform()->GetCenterPosition();
    moveDirection_ = XMFloat2Normalize(playerCenterPosition - homingCenterPosition);
    GetTransform()->AddPosition(moveDirection_ * moveSpeed_ * elapsedTime);
    // �p�x
    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveDirection_.y, moveDirection_.x) + DirectX::XM_PIDIV2));
}
