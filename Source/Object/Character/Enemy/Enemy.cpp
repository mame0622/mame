#include "Enemy.h"
#include "Collision/CollisionManager.h"

Enemy::Enemy(const std::string& name, const EnemyManager::EnemyType& enemyType, const Collision::Type& type, Object* owner, const float& radius)
    : Character(name), enemyType_(enemyType), collision_(new Collision(type, owner, radius))
{
}

// ‰Šú‰»
void Enemy::Initialize()
{
}

// XV
void Enemy::Update(const float& elapsedTime)
{   
}

void Enemy::Remove()
{
    CollisionManager::Instance().Remove(collision_);
    collision_ = nullptr;
}