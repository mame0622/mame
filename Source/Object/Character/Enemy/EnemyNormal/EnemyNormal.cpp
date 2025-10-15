#include "EnemyNormal.h"
#include "Object/Character/Player/PlayerManager.h" 
#include "ImGui/ImGuiCtrl.h"
#include "Collision/CollisionManager.h"

EnemyNormal::EnemyNormal()
    : Enemy("EnemyNormal", EnemyManager::EnemyType::Normal, 
        Collision::Type::Enemy, this, 25.0f)
{
}

// ������
void EnemyNormal::Initialize()
{
    GetTransform()->SetSize(size_);
    GetTransform()->SetTexSize(size_);
    GetTransform()->SetPivot(size_ * 0.5f);
}

// �X�V
void EnemyNormal::Update(const float& elapsedTime)
{
    // �ǐՈړ�
    Pursuit(elapsedTime);

}

// ImGui
void EnemyNormal::DrawDebug()
{
#if USE_IMGUI
    const std::string name = GetName() + std::to_string(GetObjectId());
    if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_Framed))
    {
        Character::DrawDebug();
        Object::DrawDebug();

        ImGui::TreePop();
    }

#endif // USE_IMGUI
}

// �Փˌ��m
void EnemyNormal::OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position)
{
    if (type == Collision::Type::BulletOrbit)
    {
        GetTransform()->SetPosition(position);
    }

    if (type == Collision::Type::Player ||
        type == Collision::Type::Enemy)
    {
        GetTransform()->SetPosition(position);
    }

    if (type == Collision::Type::Bullet)
    {
        Remove();
        EnemyManager::Instance().Remove(this);
    }
}

// �ǐՈړ� Player�Ɍ������Đi�s����
void EnemyNormal::Pursuit(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 moveVec = XMFloat2Normalize(playerCenterPosition - enemyCenterPosition);

    GetTransform()->AddPosition(moveVec * moveSpeed_ * elapsedTime);
    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveVec.y, moveVec.x) + DirectX::XM_PIDIV2));
}


