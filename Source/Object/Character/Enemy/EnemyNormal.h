#pragma once
#include "Enemy.h"

class EnemyNormal : public Enemy
{
public:
    EnemyNormal();
    ~EnemyNormal() {}

    void Initialize() override;
    void Update(const float& elapsedTime) override;

private:
    void Move(const float& elapsedTime);
    void Pursuit();

private:

    float moveSpeed_ = 500.0f;
};