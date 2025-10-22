#include "BulletManager.h"
#include "Object/Character/Player/PlayerManager.h"
#include "ImGui/ImGuiCtrl.h"
#include "Application/Common.h"

#include "Object/Bullet/BulletLevel1/BulletLevel1.h"


BulletManager::BulletManager()
{
    // �v���C���[�̎�������Bullet����
    for (int orbitBullet = 0; orbitBullet < maxOrvitBullets_; ++orbitBullet)
    {
        BulletOrbit* bulletOrbit = new BulletOrbit();
        bulletOrbit->Initialize(bulletSize_);
        orvitBullets_.emplace_back(bulletOrbit);
    }

    // �摜�o�^
    spriteBatches_.push_back(SpriteBatch(L"./Resources/Image/Bullet/Bullet_Level_1.png", 50/*�ő�`�搔*/));
    spriteBatches_.push_back(SpriteBatch(L"./Resources/Image/Bullet/Bullet_Level_2.png", 50));
    spriteBatches_.push_back(SpriteBatch(L"./Resources/Image/Bullet/Bullet_Level_3.png", 50));
    spriteBatches_.push_back(SpriteBatch(L"./Resources/Image/Bullet/Bullet_Level_4.png", 50));
    spriteBatches_.push_back(SpriteBatch(L"./Resources/Image/Bullet/Bullet_Level_5.png", 50));
}

// �X�V
void BulletManager::Update(const float& elapsedTime)
{
    // ��������
    for (Bullet* firedBullet : generates_)
    {
        firedBullets_.emplace_back(firedBullet);
    }
    generates_.clear();

    // �X�V
    for (Bullet*& firedBullet : firedBullets_)
    {
        firedBullet->Update(elapsedTime);
    }

    // �폜����
    for (Bullet* firedBullet : removes_)
    {
        auto it = std::find(firedBullets_.begin(), firedBullets_.end(), firedBullet);

        if (it != firedBullets_.end()) firedBullets_.erase(it);

        SafeDeletePtr(firedBullet);
    }
    removes_.clear();

    // Player�̎���ɔz�u����Bullet�X�V
    UpdateOrvitBullets(elapsedTime);
}

// �`��
void BulletManager::Render()
{
    const int maxBulletLevel = 5;
    for (int i = 0; i < maxBulletLevel; ++i)
    {
        std::vector<Transform2D> transforms_;
        for (BulletOrbit*& orvitBullet : orvitBullets_)
        {
            if (orvitBullet->GetBulletLevel() == static_cast<Bullet::BulletLevel>(i))
            {                
                transforms_.emplace_back(*orvitBullet->GetTransform());
            }
        }

        spriteBatches_.at(i).Render(transforms_);
    }

    // ��U�����ŏ������ǁA��Ƃ܂Ƃ߂ꂽ�炢���ȁ`�`�`
    for (int i = 0; i < maxBulletLevel; ++i)
    {
        std::vector<Transform2D> transforms_;
        for (Bullet*& firedBullet : firedBullets_)
        {
            if (firedBullet->GetBulletLevel() == static_cast<Bullet::BulletLevel>(i))
            {
                transforms_.emplace_back(*firedBullet->GetTransform());
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
    
    ImGui::DragFloat("Radius", &orvitRadius_, 1.0f);

    ImGui::DragFloat("Angle", &orvitAngle_, 1.0f);

    ImGui::End(); // BulletManager

    ImGui::Begin("FiredBullets List");

    for (Bullet*& firedBullet : firedBullets_)
    {
        firedBullet->DrawDebug();
    }

    ImGui::End(); // FiredBullets List

    ImGui::Begin("OrvitBullet List");

    for (BulletOrbit*& bullet : orvitBullets_)
    {
        bullet->DrawDebug();
    }

    ImGui::End(); // OrvitBullet List

#endif // USE_IMGUI
}

// ����
void BulletManager::Launch()
{
    // �e�̃A�N�e�B�u���X�g���쐬
    const bool activeBulletList[maxOrvitBullets_] =
    {
        orvitBullets_.at(0)->IsCollisionActive(),
        orvitBullets_.at(1)->IsCollisionActive(),
        orvitBullets_.at(2)->IsCollisionActive(),
        orvitBullets_.at(3)->IsCollisionActive(),
        orvitBullets_.at(4)->IsCollisionActive(),
    };

    // ���˂ł���e�����邩�m�F
    bool isReadyToFire = false;
    for (int bulletIndex = 0; bulletIndex < maxOrvitBullets_; ++bulletIndex)
    {
        if (activeBulletList[bulletIndex]) isReadyToFire = true;
    }
    if (isReadyToFire == false) return;

    // ---------- Index���ɔ��� ----------
    // ���˔ԍ������肷��
    while (true)
    {
        // ���ˉ\�̂�T��
        if (activeBulletList[launchIndex_] == false)
        {
            // ���X�g�ԍ������ɐi�߂�
            ++launchIndex_;
            if (launchIndex_ >= maxOrvitBullets_) launchIndex_ = 0;
        }
        else
        {
            // ���ˉ\�� ����
            break;
        }
    }

    const Bullet::BulletLevel level = orvitBullets_.at(launchIndex_)->GetBulletLevel();
    const DirectX::XMFLOAT2 direction = PlayerManager::Instance().GetPlayer()->GetMoveDirection();
    
    switch (level)
    {
    case Bullet::BulletLevel::One:
    {
        BulletLevel1* level1 = new BulletLevel1();
        // �C������
        level1->Initialize(launchIndex_, bulletSize_, orvitRadius_);
        level1->Launch(direction);

        orvitBullets_.at(launchIndex_)->SetCollisionActive(false);
    }
        break;
    case Bullet::BulletLevel::Two:
        break;
    case Bullet::BulletLevel::Three:
        break;
    case Bullet::BulletLevel::Four:
        break;
    case Bullet::BulletLevel::Five:
        break;
    }

    ++launchIndex_;
    if (launchIndex_ >= maxOrvitBullets_) launchIndex_ = 0;
}

// �S�폜
void BulletManager::Clear()
{
    for (Bullet*& firedBullet : firedBullets_)
    {
        SafeDeletePtr(firedBullet);
    }
    firedBullets_.clear();
    firedBullets_.shrink_to_fit();
}

// Player�̎���ɔz�u����Bullet�X�V
void BulletManager::UpdateOrvitBullets(const float& elapsedTime)
{
    for (BulletOrbit*& orvitBullet : orvitBullets_)
    {
        orvitBullet->Update(elapsedTime);
    }

    // Player�̉摜�̒��S��Target�ɐݒ肷��
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();

    // Target�ɑ΂��ĉ~��ɂȂ�悤��Bullet��z�u����
    for (int i = 0; i < maxOrvitBullets_; ++i)
    {
        float angle = orvitAngle_ + (2.0f * DirectX::XM_PI / maxOrvitBullets_) * i;

        // Bullet�̉摜�̒��S���w�肳�ꂽ�ʒu�Ɏ����Ă����ׂ�Offset
        const DirectX::XMFLOAT2 orvitBulletOffset = orvitBullets_.at(i)->GetTransform()->GetSize() * 0.5f;

        orvitBullets_.at(i)->GetTransform()->SetPositionX(playerCenterPosition.x + orvitRadius_ * cosf(angle) - orvitBulletOffset.x);
        orvitBullets_.at(i)->GetTransform()->SetPositionY(playerCenterPosition.y + orvitRadius_ * sinf(angle) - orvitBulletOffset.y);
    }

    // Target�ɑ΂��ĕӂ������悤�ɂ���
    for (int i = 0; i < maxOrvitBullets_; ++i)
    {
        const DirectX::XMFLOAT2 orvitBulletCenterPosition = orvitBullets_.at(i)->GetTransform()->GetCenterPosition();

        const DirectX::XMFLOAT2 direction = XMFloat2Normalize(orvitBulletCenterPosition - playerCenterPosition);

        orvitBullets_.at(i)->GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(direction.y, direction.x) + DirectX::XM_PIDIV2));
    }

    orvitAngle_ += elapsedTime;
}
