#pragma once

#include "Object/Character/Enemy/Enemy.h"

class EnemyMadScientist : public Enemy
{
public:
    EnemyMadScientist();
    ~EnemyMadScientist() {}

    void Initialize() override;
    void Update(const float& elapsedTime) override;
    void DrawDebug() override;

    void OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position) override;

private:
    void Turn();

private:
    DirectX::XMFLOAT2 moveVec_ = {};
    float moveSpeed_ = 300.0f;

    const float size_ = 100.0f;
};