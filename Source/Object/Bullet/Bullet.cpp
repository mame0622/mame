#include "Bullet.h"
#include "ImGui/ImGuiCtrl.h"
#include "Graphics/Graphics.h"
#include "BulletManager.h"
#include "Collision/CollisionManager.h"
#include "BulletManager.h"

Bullet::Bullet(const std::string& name, const BulletLevel & level, const Collision::Type& type, Object* owner, const float& radius)
    : Object(name), level_(level), collision_(new Collision(type, owner, radius))
{
    // �}�l�[�W���[�ɓo�^
    BulletManager::Instance().Register(this);
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
        BulletManager::Instance().GetOrbitBullet(GetBulletNumber())->SetCollisionActive(true);
        
        CollisionRemove();
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
        int level = static_cast<int>(level_);
        ImGui::SliderInt("Level", &level, 0, 4);
        level_ = static_cast<BulletLevel>(level);

        ImGui::TreePop();
    }

#endif // USE_IMGUI
}

void Bullet::CollisionRemove()
{
    CollisionManager::Instance().Remove(collision_);
    collision_ = nullptr;
}