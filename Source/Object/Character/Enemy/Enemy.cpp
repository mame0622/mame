#include "Enemy.h"

Enemy::Enemy(const EnemyManager::EnemyType& enemyType, const std::string& name)
    : enemyType_(enemyType), name_(name)
{
}

// ������
void Enemy::Initialize()
{
}

// �X�V
void Enemy::Update(const float& elapsedTime)
{
}
