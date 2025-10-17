#include "BulletStraight.h"
#include "Object/Character/Enemy/EnemyManager.h"

BulletStraight::BulletStraight()
    :Bullet("BulletLevel1", BulletLevel::One,
        Collision::Type::Bullet, this, 25.0f)
{

}

void BulletStraight::Initialize(const float& length, const DirectX::XMFLOAT2& moveDirection, 
    const DirectX::XMFLOAT2& enemyCenterPosition)
{
    // Bullet�̃T�C�Y�ݒ�
    const DirectX::XMFLOAT2 bulletSize = { 30.0f, 30.0f };
    GetTransform()->SetSize(bulletSize);
    GetTransform()->SetTexSize(bulletSize);
    GetTransform()->SetPivot(bulletSize * 0.5f);

    // �i�s�����ݒ�
    moveDirection_ = moveDirection;

    // �����ʒu�ݒ�
    const DirectX::XMFLOAT2 offsetPosition = GetTransform()->GetSize() * 0.5f;
    const DirectX::XMFLOAT2 createPosition = enemyCenterPosition + moveDirection_ * length - offsetPosition;
    GetTransform()->SetPosition(createPosition);

    // �p�x�ݒ�
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
