#pragma once
#include "Object/Character/Enemy/Enemy.h"

class EnemyNecromancer : public Enemy
{
public:
    EnemyNecromancer();
    ~EnemyNecromancer(){}

    void Initialize() override;
    void Update(const float& elapsedTime) override;
    void DrawDebug() override;

private:
    void Pursuit(const float& elapsedTime);

private:
    float moveSpeed_ = 300.0f;

    

};
