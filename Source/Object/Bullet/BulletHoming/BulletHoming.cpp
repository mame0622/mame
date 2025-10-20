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

    const float detectionRange = 70.0f;

    if (detectionRange > length_)
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
void BulletHoming::Launch(const DirectX::XMFLOAT2& moveDirection)
{
    moveDirection_ = moveDirection;
}

void  BulletHoming::Pursuit(const float& elapsedTime)
{
    // �O�����x�N�g���Z�o
    const float angleRadians = DirectX::XMConvertToRadians(GetTransform()->GetAngle());
    const DirectX::XMFLOAT2 forward = { sinf(angleRadians),-cosf(angleRadians) };

    // �i�s�����x�N�g���Z�o
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 homingCenterPosition = GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 moveVec = playerCenterPosition - homingCenterPosition;
    length_ = XMFloat2Length(moveVec);
    moveDirection_ = XMFloat2Normalize(moveVec);
    const float dot = XMFloat2Dot(moveDirection_, forward);
    DirectX::XMFLOAT2 cent = moveDirection_ - (forward * dot);
    const float length = XMFloat2Length(cent);
    if (length > 1.0f)
    {
        cent /= length;
    }
    const DirectX::XMFLOAT2 Vec = cent * 5.0f;

    //const float angle = acosf(dot);
    //float radians = angle;
    //const DirectX::XMFLOAT2 Vec = { sinf(angle) + forward.x ,forward.y - cosf(angle)};

    GetTransform()->AddPosition(Vec * moveSpeed_ * elapsedTime);

    // �p�x
    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveDirection_.y, moveDirection_.x) + DirectX::XM_PIDIV2));
}
