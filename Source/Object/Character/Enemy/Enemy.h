#pragma once
#include "Object/Character/Character.h"
#include "EnemyManager.h"

class Enemy : public Character
{
public:
    Enemy(const std::string& name, const EnemyManager::EnemyType& enemyType);
    virtual ~Enemy() {}

    virtual void Initialize();
    virtual void Update(const float& elapsedTime);

    const EnemyManager::EnemyType GetEnemyType() const { return enemyType_; }
    
private:
    const EnemyManager::EnemyType enemyType_ = EnemyManager::EnemyType::Normal;
};

