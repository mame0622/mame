#include "Enemy.h"

Enemy::Enemy(const std::string& name, const EnemyManager::EnemyType& enemyType)
    : Character(name), enemyType_(enemyType)
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
