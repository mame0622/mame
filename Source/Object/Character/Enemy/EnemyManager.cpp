#include "EnemyManager.h"
#include "Enemy.h"
#include "Object/Character/Enemy/EnemyNormal/EnemyNormal.h"
#include "Object/Character/Enemy/EnemyCharger/EnemyCharger.h"
#include "Object/Character/Enemy/EnemyPlanaria/EnemyPlanaria.h"
#include "Object/Character/Enemy/EnemyNecromancer/EnemyNecromancer.h"
#include "Application/Common.h"
#include "ImGui/ImGuiCtrl.h"

EnemyManager::EnemyManager()
{
    // �e�N�X�`���o�^
    spriteBatches_.emplace_back(SpriteBatch(L"./Resources/Image/Enemy/Enemy0.png", 500/*�ő�`�搔*/));
    spriteBatches_.emplace_back(SpriteBatch(L"./Resources/Image/Enemy/Enemy1.png", 500));
    spriteBatches_.emplace_back(SpriteBatch(L"./Resources/Image/Enemy/Enemy2.png", 500));
    spriteBatches_.emplace_back(SpriteBatch(L"./Resources/Image/Enemy/Enemy3.png", 500));
}

// �I����
void EnemyManager::Finalize()
{
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
    }
    generates_.clear();

    // �X�V
    for (Enemy*& enemy : enemies_)
    {
        enemy->Update(elapsedTime);
    }

    // �폜����
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
        std::vector<Transform2D> transforms;
        for (Enemy*& enemy : enemies_)
        {
            if (enemy->GetEnemyType() == static_cast<EnemyType>(i))
            {
                transforms.emplace_back(*enemy->GetTransform());
            }
        }

        spriteBatches_.at(i).Render(transforms);
    }
}

// ImGui
void EnemyManager::DrawDebug()
{
#if USE_IMGUI

    ImGui::Begin("EnemyManager");

    ImGui::Text("Register Button");
    if (ImGui::Button("Normal Enemy"))
    {
        EnemyNormal* enemy = new EnemyNormal();
    }
    if (ImGui::Button("Charger Enemy"))
    {
        EnemyCharger* enemy = new EnemyCharger();
    }
    if (ImGui::Button("Planaria Enemy"))
    {
        EnemyPlanaria* enemy = new EnemyPlanaria();
    }
    if (ImGui::Button("Necromancer Enemy"))
    {
        EnemyNecromancer* enemy = new EnemyNecromancer();
    }


    ImGui::End(); // EnemyManager

    ImGui::Begin("Enemy List");

    for (Enemy*& enemy : enemies_)
    {
        enemy->DrawDebug();
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
