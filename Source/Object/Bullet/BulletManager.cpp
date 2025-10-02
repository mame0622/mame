#include "BulletManager.h"
#include "Object/Character/Player/PlayerManager.h"
#include "ImGui/ImGuiCtrl.h"

BulletManager::BulletManager()
{
    // �o���b�g����
    for (int i = 0; i < maxBullets_; ++i)
    {
        Bullet bullet;
        bullet.GetTransform()->SetSize(bulletSize_);
        bullet.GetTransform()->SetTexSize(bulletSize_);
        bullet.GetTransform()->SetPivot(bulletSize_ * 0.5f);

        bullets_.emplace_back(bullet);
    }

    // �摜�o�^
    spriteBatches_.push_back(SpriteBatch(L"./Resources/Image/Bullet/Bullet_Level_1.png", 5/*�ő�`�搔*/));
    spriteBatches_.push_back(SpriteBatch(L"./Resources/Image/Bullet/Bullet_Level_2.png", 5));
    spriteBatches_.push_back(SpriteBatch(L"./Resources/Image/Bullet/Bullet_Level_3.png", 5));
    spriteBatches_.push_back(SpriteBatch(L"./Resources/Image/Bullet/Bullet_Level_4.png", 5));
    spriteBatches_.push_back(SpriteBatch(L"./Resources/Image/Bullet/Bullet_Level_5.png", 5));
}

// �X�V
void BulletManager::Update(const float& elapsedTime)
{
    // Player�̉摜�̒��S��Target�ɐݒ肷��
    const DirectX::XMFLOAT2 playerPosition = PlayerManager::Instance().GetTransform()->GetPosition();
    const DirectX::XMFLOAT2 playerSize = PlayerManager::Instance().GetTransform()->GetSize();
    const DirectX::XMFLOAT2 playerCenterPos = playerPosition + playerSize * 0.5f;

    // Target�ɑ΂��ĉ~��ɂȂ�悤��Bullet��z�u����
    for (int i = 0; i < maxBullets_; ++i)
    {
        float angle = angle_ + (2.0 * DirectX::XM_PI / maxBullets_) * i;

        // Bullet�̉摜�̒��S���w�肳�ꂽ�ʒu�Ɏ����Ă����ׂ�Offset
        const DirectX::XMFLOAT2 bulletOffset = bullets_.at(i).GetTransform()->GetSize() * 0.5f;

        bullets_.at(i).GetTransform()->SetPositionX(playerCenterPos.x + radius_ * cos(angle) - bulletOffset.x);
        bullets_.at(i).GetTransform()->SetPositionY(playerCenterPos.y + radius_ * sin(angle) - bulletOffset.y);
    }

    // Target�ɑ΂��ĕӂ������悤�ɂ���
    for (int i = 0; i < maxBullets_; ++i)
    {
        const DirectX::XMFLOAT2 bulletPosition = bullets_.at(i).GetTransform()->GetPosition();
        const DirectX::XMFLOAT2 bulletOffset = bullets_.at(i).GetTransform()->GetSize() * 0.5f;
        const DirectX::XMFLOAT2 direction = XMFloat2Normalize(bulletPosition + bulletOffset - playerCenterPos);

        bullets_.at(i).GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(direction.x, direction.y)));
    }
}

// �`��
void BulletManager::Render()
{
    const int maxBulletLevel = 5;
    for (int i = 0; i < maxBulletLevel; ++i)
    {
        std::vector<Transform2D> transforms_;
        for (Bullet& bullet : bullets_)
        {
            if (bullet.GetBulletLevel() == static_cast<Bullet::BulletLevel>(i))
            {                
                transforms_.emplace_back(*bullet.GetTransform());
            }
        }

        spriteBatches_.at(i).Render(transforms_);
    }
}

// ImGui
void BulletManager::DrawDebug()
{
#if USE_IMGUI
    ImGui::Begin("BulletManager");
    
    ImGui::DragFloat("Radius", &radius_, 1.0f);

    ImGui::DragFloat("Angle", &angle_, 1.0f);

    ImGui::End(); // BulletManager

#endif // USE_IMGUI
}
