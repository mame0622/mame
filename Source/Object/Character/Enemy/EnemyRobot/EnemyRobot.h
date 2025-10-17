#pragma once

#include "Object/Character/Enemy/Enemy.h"

class EnemyRobot : public Enemy
{
public:
    EnemyRobot();
    ~EnemyRobot() {}

    void Initialize() override;
    void Update(const float& elapsedTime) override;
    void DrawDebug() override;

    void OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position) override;

private:
    void Pursuit(const float& elapsedTime);

private:
    DirectX::XMFLOAT2 moveVec_ = {};
    float moveSpeed_ = 100.0f;

    const float size_ = 200.0f;
};