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
    void Pursuit(const float& elapsedTime);

private:

    float moveSpeed_ = 500.0f;
};