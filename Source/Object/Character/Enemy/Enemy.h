#pragma once
#include "Object/Character/Character.h"
#include "EnemyManager.h"

class Enemy : public Character
{
public:
    Enemy(const EnemyManager::EnemyType& enemyType, const std::string& name);
    virtual ~Enemy() {}

    virtual void Initialize();
    virtual void Update(const float& elapsedTime);

    const EnemyManager::EnemyType GetEnemyType() const { return enemyType_; }
    const std::string GetName() const { return name_; }
    
private:
    const EnemyManager::EnemyType enemyType_ = EnemyManager::EnemyType::Normal;
    const std::string name_ = "";
};

