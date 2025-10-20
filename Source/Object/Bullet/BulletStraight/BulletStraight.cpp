#include "BulletStraight.h"
#include "Object/Character/Enemy/EnemyManager.h"

BulletStraight::BulletStraight()
    :Bullet("BulletLevel1", BulletLevel::One,
        Collision::Type::Bullet, this, 25.0f)
{

}

void BulletStraight::Initialize(const DirectX::XMFLOAT2& generatePosition)
{
    // Bullet�̃T�C�Y�ݒ�
    GetTransform()->SetColorA(alpha_);

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

void BulletStraight::Update(const float& elapsedTime)
{
    Bullet::Update(elapsedTime);
    alpha_ += elapsedTime;
    
    if (alpha_ >= 1.0f)
    {
        alpha_ = 1.0f;
        moveSpeed_ = 500.0f;
    }
    GetTransform()->SetColorA(alpha_);

    // �O�����x�N�g���Z�o
    const float angleRadians = DirectX::XMConvertToRadians(GetTransform()->GetAngle());
    const DirectX::XMFLOAT2 forward = { sinf(angleRadians),-cosf(angleRadians) };
    GetTransform()->AddPosition(forward * moveSpeed_ * elapsedTime);

    // �p�x
    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveDirection_.y, moveDirection_.x) + DirectX::XM_PIDIV2));
}

void BulletStraight::DrawDebug()
{
}

void BulletStraight::OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position)
{
}

// ����
void BulletStraight::Launch(const DirectX::XMFLOAT2& moveDirection)
{
    moveDirection_ = moveDirection;
}
