#include "BulletLevel1.h"
#include "Object/Bullet/BulletManager.h"
#include "ImGui/ImGuiCtrl.h"
#include "Object/Character/Player/PlayerManager.h"

BulletLevel1::BulletLevel1()
    : Bullet("BulletLevel1", BulletLevel::One)
{
    // �}�l�[�W���[�ɓo�^
    BulletManager::Instance().Register(this);
}

// ������
void BulletLevel1::Initialize(const int& bulletNumber, const DirectX::XMFLOAT2& bulletSize, const float& length, const DirectX::XMFLOAT2& moveDirection)
{
    // BulletNumber�ݒ�
    SetBulletNumber(bulletNumber);

    // Bullet�̃T�C�Y�ݒ�
    GetTransform()->SetSize(bulletSize);
    GetTransform()->SetTexSize(bulletSize);
    GetTransform()->SetPivot(bulletSize * 0.5f);

    // �i�s�����ݒ�
    moveDirection_ = moveDirection;

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
