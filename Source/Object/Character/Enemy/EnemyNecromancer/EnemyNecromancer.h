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

    void OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position) override;

private:
    void Pursuit(const float& elapsedTime);
    void UndeadGeneration();

private:
    DirectX::XMFLOAT2 moveVec_ = {};
    float moveSpeed_ = 300.0f;

    float generationTime_ = 0;

};
