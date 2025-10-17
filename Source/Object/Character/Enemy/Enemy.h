#pragma once
#include "Object/Character/Character.h"
#include "EnemyManager.h"
#include "Collision/Collision.h"

class Enemy : public Character
{
public:
    Enemy(const std::string& name, const EnemyManager::EnemyType& enemyType,
        const Collision::Type& type, Object* owner, const float& radius);
    virtual ~Enemy();

    virtual void Initialize();
    virtual void Update(const float& elapsedTime);

    const EnemyManager::EnemyType GetEnemyType() const { return enemyType_; }
    
    // ---------- ‘Ì—Í ----------
    const int GetHealth() const { return health_; }
    void SetHealth(const int& health) { health_ = health; }
    void Damage(const int& damage) { health_ -= damage; }


private:
    // Collision‚ÌŒãˆ—
    void CollisionRemove();

private:
    const EnemyManager::EnemyType enemyType_ = EnemyManager::EnemyType::Normal;

    Collision* collision_;

    int health_ = 1;
};

