#include "EnemyManager.h"
#include "Enemy.h"
#include "Application/Common.h"
#include "ImGui/ImGuiCtrl.h"

// コンストラクタ
EnemyManager::EnemyManager()
{
    // テクスチャ登録
    spriteBatches_.emplace_back(SpriteBatch(L"./Resources/Image/Player.png", 10));
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
