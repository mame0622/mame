#include "EnemyNormal.h"
#include "Object/Character/Player/PlayerManager.h" 
#include "ImGui/ImGuiCtrl.h"

EnemyNormal::EnemyNormal()
    : Enemy("EnemyNormal", EnemyManager::EnemyType::Normal)
{
}

// 初期化
void EnemyNormal::Initialize()
{
    GetTransform()->SetSize(size_);
    GetTransform()->SetTexSize(size_);
    GetTransform()->SetPivot(size_ * 0.5f);

    SetCollisionRadius(25.0f);
}

// 更新
void EnemyNormal::Update(const float& elapsedTime)
{
    // 追跡移動
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

        ImGui::TreePop();
    }

#endif // USE_IMGUI
}

// 追跡移動 Playerに向かって進行する
void EnemyNormal::Pursuit(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 moveVec = XMFloat2Normalize(playerCenterPosition - enemyCenterPosition);

    GetTransform()->AddPosition(moveVec * moveSpeed_ * elapsedTime);
    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveVec.y, moveVec.x) + DirectX::XM_PIDIV2));
}


