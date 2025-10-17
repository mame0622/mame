#include "Enemy.h"
#include "Collision/CollisionManager.h"

Enemy::Enemy(const std::string& name, const EnemyManager::EnemyType& enemyType, const Collision::Type& type, Object* owner, const float& radius)
    : Character(name), enemyType_(enemyType), collision_(new Collision(type, owner, radius))
{
    // �������g��o�^����
    EnemyManager::Instance().Register(this);
}

Enemy::~Enemy()
{
    CollisionRemove();
}

// ������
void Enemy::Initialize()
{
}

// �X�V
void Enemy::Update(const float& elapsedTime)
{
    // �̗͂��Ȃ��Ȃ�������ł���
    if (health_ <= 0)
    {
        EnemyManager::Instance().Remove(this);
    }
}

// �R���W�����̌㏈��
void Enemy::CollisionRemove()
{
    CollisionManager::Instance().Remove(collision_);
    collision_ = nullptr;
}