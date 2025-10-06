#pragma once
#include "Object/Character/Enemy/Enemy.h"

class EnemyPlanaria : public Enemy
{
public:
    EnemyPlanaria();
    ~EnemyPlanaria(){}

    void Initialize() override;
    void Update(const float& elapsedTime) override;
    void DrawDebug() override;
};