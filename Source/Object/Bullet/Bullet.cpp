#include "Bullet.h"
#include "ImGui/ImGuiCtrl.h"
#include "Graphics/Graphics.h"
#include "BulletManager.h"

Bullet::Bullet(const std::string& name, const BulletLevel & level)
    : Object(name), level_(level)
{
}

// �X�V
void Bullet::Update(const float& elapsedTime)
{
    // ��ʊO�ɏo���玩�g����������
    const DirectX::XMFLOAT2 minPosition = GetTransform()->GetSize() * -1.0f;
    const DirectX::XMFLOAT2 maxPosition = DirectX::XMFLOAT2(SCREEN_WIDTH, SCREEN_HEIGHT);
    const DirectX::XMFLOAT2 position = GetTransform()->GetPosition();

    if (position.x <= minPosition.x || position.y <= minPosition.y ||
        position.x >= maxPosition.x || position.y >= maxPosition.y)
    {
        // ��: Bullet�L����
        BulletManager::Instance().GetOrvitBullets().at(GetBulletNumber()).SetCollisionActive(true);
        
        BulletManager::Instance().Remove(this);
    }
}

// ImGui
void Bullet::DrawDebug()
{
#if USE_IMGUI
    const std::string name = "Bullet" + std::to_string(GetObjectId());
    if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Checkbox("CollisionActive", &isCollisionActive_);

        int level = static_cast<int>(level_);
        ImGui::SliderInt("Level", &level, 0, 4);
        level_ = static_cast<BulletLevel>(level);

        ImGui::DragFloat("CollisionRadius", &collisionRadius_);

        ImGui::TreePop();
    }

#endif // USE_IMGUI
}
