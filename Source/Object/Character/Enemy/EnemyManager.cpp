#include "EnemyManager.h"
#include "Enemy.h"
#include "Application/Common.h"
#include "ImGui/ImGuiCtrl.h"

// �R���X�g���N�^
EnemyManager::EnemyManager()
{
    // �e�N�X�`���o�^
    spriteBatches_.emplace_back(SpriteBatch(L"./Resources/Image/Player.png", 10));
}

// �I����
void EnemyManager::Finalize()
{
    enemyId_ = 0; // ���Z�b�g
    Clear();
}

// �X�V
void EnemyManager::Update(const float& elapsedTime)
{
    // ��������
    for (Enemy* enemy : generates_)
    {
        enemies_.emplace_back(enemy);
        enemy->Initialize();
        enemy->SetEnemyId(enemyId_++);
    }
    generates_.clear();

    for (Enemy*& enemy : enemies_)
    {
        enemy->Update(elapsedTime);
    }

    for (Enemy* enemy : removes_)
    {
        auto it = std::find(enemies_.begin(), enemies_.end(), enemy);

        if (it != enemies_.end()) enemies_.erase(it);

        SafeDeletePtr(enemy);
    }
    removes_.clear();
}

// �`��
void EnemyManager::Render()
{
    // �e�N�X�`���̎�ނ��Ƃɕ`�悷��
    for (int i = 0; i < static_cast<int>(EnemyType::Max); ++i)
    {
        std::vector<Transform2D> transforms_;
        for (Enemy*& enemy : enemies_)
        {
            if (enemy->GetEnemyType() == static_cast<EnemyType>(i))
            {
                transforms_.emplace_back(*enemy->GetTransform());
            }
        }

        spriteBatches_.at(i).Render(transforms_);
    }
}

// ImGui
void EnemyManager::DrawDebug()
{
#if USE_IMGUI

    ImGui::Begin("EnemyManager");

    if (ImGui::Button("Generate Enemy"))
    {
        Register(new Enemy(EnemyType::Normal));
    }

    ImGui::End(); // EnemyManager

    ImGui::Begin("Enemy List");

    for (Enemy*& enemy : enemies_)
    {
        const std::string id = "Enemy" + std::to_string(enemy->GetEnemyId());
        if (ImGui::TreeNodeEx(id.c_str()))
        {
            enemy->DrawDebug();

            ImGui::TreePop();
        }
    }

    ImGui::End(); // Enemy List

#endif // USE_IMGUI
}

// �S�폜
void EnemyManager::Clear()
{
    for (Enemy*& enemy : enemies_)
    {
        SafeDeletePtr(enemy);
    }
    enemies_.clear();
    enemies_.shrink_to_fit();
}
