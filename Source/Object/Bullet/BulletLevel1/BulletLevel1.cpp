#include "BulletLevel1.h"
#include "Object/Bullet/BulletManager.h"
#include "ImGui/ImGuiCtrl.h"
#include "Object/Character/Player/PlayerManager.h"

BulletLevel1::BulletLevel1()
    : Bullet("BulletLevel1", BulletLevel::One,
        Collision::Type::Bullet, this, 25.0f)
{
}

// ������
void BulletLevel1::Initialize(const int& bulletNumber, const DirectX::XMFLOAT2& bulletSize, const float& length)
{
    // BulletNumber�ݒ�
    SetBulletNumber(bulletNumber);

    // Bullet�̃T�C�Y�ݒ�
    GetTransform()->SetSize(bulletSize);
    GetTransform()->SetTexSize(bulletSize);
    GetTransform()->SetPivot(bulletSize * 0.5f);

    // �����ʒu�ݒ�
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 offsetPosition = GetTransform()->GetSize() * 0.5f;
    const DirectX::XMFLOAT2 createPosition = playerCenterPosition + moveDirection_ * length - offsetPosition;
    GetTransform()->SetPosition(createPosition);

    // �p�x�ݒ�
    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveDirection_.y, moveDirection_.x) + DirectX::XM_PIDIV2));
}

// �X�V
void BulletLevel1::Update(const float& elapsedTime)
{
    Bullet::Update(elapsedTime);

    GetTransform()->AddPosition(moveDirection_ * moveSpeed_ * elapsedTime);
}

// ImGui
void BulletLevel1::DrawDebug()
{
#if USE_IMGUI
    const std::string name = GetName() + std::to_string(GetObjectId());
    if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_Framed))
    {
        ImGui::DragFloat("MoveSpeed", &moveSpeed_);

        ImGui::TreePop();
    }

#endif // USE_IMGUI
}

// ����
void BulletLevel1::Launch(const DirectX::XMFLOAT2& direction)
{
    // �i�s�����ݒ�
    moveDirection_ = direction;
}

// �Փˌ��m
void BulletLevel1::OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position)
{
    if (type == Collision::Type::Enemy)
    {
        BulletManager::Instance().GetOrbitBullet(GetBulletNumber())->SetLevel(BulletLevel::Two);
        BulletManager::Instance().GetOrbitBullet(GetBulletNumber())->SetCollisionActive(true);

        // �������
        CollisionRemove();
        BulletManager::Instance().Remove(this);
    }
}
