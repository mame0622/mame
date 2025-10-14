#pragma once
#include "Object/Character/Character.h"
#include "EnemyManager.h"
#include "Collision/Collision.h"

class Enemy : public Character
{
public:
    Enemy(const std::string& name, const EnemyManager::EnemyType& enemyType,
        const Collision::Type& type, Object* owner, const float& radius);
    virtual ~Enemy() {}

    virtual void Initialize();
    virtual void Update(const float& elapsedTime);

    const EnemyManager::EnemyType GetEnemyType() const { return enemyType_; }
    
    void Remove();

private:
    const EnemyManager::EnemyType enemyType_ = EnemyManager::EnemyType::Normal;

    Collision* collision_;
};

