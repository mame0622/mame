#pragma once
#include <vector>
#include <set>
#include "Resource/Sprite/SpriteBatch.h"

class Enemy;

class EnemyManager
{
public:
    enum class EnemyType : int
    {
        Normal,
        Max,
    };

private:
    EnemyManager();
    ~EnemyManager() {}

public:
    static EnemyManager& Instance()
    {
        static EnemyManager instance;
        return instance;
    }

    void Finalize();
    void Update(const float& elapsedTime);
    void Render();
    void DrawDebug();

    void Register(Enemy* enemy) { generates_.insert(enemy); }
    void Remove(Enemy* enemy) { removes_.insert(enemy); }
    void Clear();

private:
    std::vector<Enemy*>         enemies_;
    std::set<Enemy*>            removes_;
    std::set<Enemy*>            generates_;
    std::vector<SpriteBatch>    spriteBatches_;
    
    int enemyId_ = 0;
};

