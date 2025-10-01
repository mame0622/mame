#pragma once
#include "Object/Character/Character.h"
#include "EnemyManager.h"

class Enemy : public Character
{
public:
    Enemy(const EnemyManager::EnemyType& enemyType);
    virtual ~Enemy() {}

    virtual void Initialize();
    virtual void Update(const float& elapsedTime);

    const EnemyManager::EnemyType GetEnemyType() const { return enemyType_; }
    
    // ---------- EnemyId ----------
    void SetEnemyId(const int& enemyId) { enemyId_ = enemyId; }
    const int GetEnemyId() const { return enemyId_; }

private:
    const EnemyManager::EnemyType enemyType_ = EnemyManager::EnemyType::Normal;
    
    int enemyId_;
};

