#include "EnemyManager.h"
#include "Enemy.h"
#include "EnemyNormal.h"
#include "Application/Common.h"
#include "ImGui/ImGuiCtrl.h"

EnemyManager::EnemyManager()
{
    // テクスチャ登録
    spriteBatches_.emplace_back(SpriteBatch(L"./Resources/Image/Enemy/Enemy0.png", 50/*最大描画数*/));
    spriteBatches_.emplace_back(SpriteBatch(L"./Resources/Image/Enemy/Enemy1.png", 50));
}

// 終了化
void EnemyManager::Finalize()
{
    enemyId_ = 0; // リセット
    Clear();
}

// 更新
void EnemyManager::Update(const float& elapsedTime)
{
    // 生成処理
    for (Enemy* enemy : generates_)
    {
        enemies_.emplace_back(enemy);
        enemy->Initialize();
    }
    generates_.clear();

    // 更新
    for (Enemy*& enemy : enemies_)
    {
        enemy->Update(elapsedTime);
    }

    // 削除処理
    for (Enemy* enemy : removes_)
    {
        auto it = std::find(enemies_.begin(), enemies_.end(), enemy);

        if (it != enemies_.end()) enemies_.erase(it);

        SafeDeletePtr(enemy);
    }
    removes_.clear();
}

// 描画
void EnemyManager::Render()
{
    // テクスチャの種類ごとに描画する
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

    ImGui::Text("Register Button");
    if (ImGui::Button("Normal Enemy"))
    {
        Register(new EnemyNormal());
    }
    if (ImGui::Button("Homing Enemy"))
    {
        Register(new Enemy(EnemyType::Homing, "HomingEnemy"));
    }

    ImGui::End(); // EnemyManager

    ImGui::Begin("Enemy List");

    for (Enemy*& enemy : enemies_)
    {
        const std::string name = enemy->GetName() + std::to_string(enemy->GetObjectId());
        if (ImGui::TreeNodeEx(name.c_str()))
        {
            enemy->DrawDebug();

            ImGui::TreePop();
        }
    }

    ImGui::End(); // Enemy List

#endif // USE_IMGUI
}

// 全削除
void EnemyManager::Clear()
{
    for (Enemy*& enemy : enemies_)
    {
        SafeDeletePtr(enemy);
    }
    enemies_.clear();
    enemies_.shrink_to_fit();
}
