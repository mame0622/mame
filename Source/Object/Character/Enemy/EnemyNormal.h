#pragma once
#include "Enemy.h"

class EnemyNormal : public Enemy
{
public:
    EnemyNormal();
    ~EnemyNormal() {}

    void Initialize() override;
    void Update(const float& elapsedTime) override;

    
};