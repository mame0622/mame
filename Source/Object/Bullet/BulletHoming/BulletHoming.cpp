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

    switch (state_)
    {
    case 0:
        Pursuit(elapsedTime);

        break;
    case 1:

        // �O�����x�N�g���Z�o
        const float angleRadians = DirectX::XMConvertToRadians(GetTransform()->GetAngle());
        const DirectX::XMFLOAT2 forward = { sinf(angleRadians),-cosf(angleRadians) };
        GetTransform()->AddPosition(forward * moveSpeed_ * elapsedTime);

        break;
    }

    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 bulletCenterPosition = GetTransform()->GetCenterPosition();
    const float length = XMFloat2Length(playerCenterPosition - bulletCenterPosition);

    const float detectionRange = 70.0f;

    if (detectionRange > length)
    {
        state_ = 1;
    }
   
}

void BulletHoming::DrawDebug()
{
}

void BulletHoming::OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position)
{
}

// ����
void BulletHoming::Launch(const DirectX::XMFLOAT2& moveDirection, const int& power)
{
    moveDirection_ = XMFloat2Normalize(moveDirection);

    power_ = power;
}

void BulletHoming::Pursuit(const float& elapsedTime)
{
    // Player�Ɍ������������Z�o
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 bulletCenterPosition = GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 toPlayerDirection = XMFloat2Normalize(playerCenterPosition - bulletCenterPosition);

    DirectX::XMFLOAT2 newMoveDirection = CalcNewMoveDirection(moveDirection_, toPlayerDirection);

    for (int i = 0; i < power_; ++i)
    {
        newMoveDirection = CalcNewMoveDirection(moveDirection_, newMoveDirection);
    }

    GetTransform()->AddPosition(newMoveDirection * moveSpeed_ * elapsedTime);

    moveDirection_ = newMoveDirection;

    // �p�x
    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(newMoveDirection.y, newMoveDirection.x) + DirectX::XM_PIDIV2));
}

const DirectX::XMFLOAT2 BulletHoming::CalcNewMoveDirection(const DirectX::XMFLOAT2& direction0, const DirectX::XMFLOAT2& direction1)
{
    return XMFloat2Normalize(direction0 + direction1);
}
