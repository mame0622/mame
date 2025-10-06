#pragma once
#include "Object/Character/Enemy/Enemy.h"

class EnemyNormal : public Enemy
{
public:
    EnemyNormal();
    ~EnemyNormal() {}

    void Initialize() override;
    void Update(const float& elapsedTime) override;
    void DrawDebug() override;

private:
    void Pursuit(const float& elapsedTime);

private:
    float moveSpeed_ = 100.0f;

    const float size_ = 50.0f;
};