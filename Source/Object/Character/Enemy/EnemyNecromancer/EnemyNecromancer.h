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
    void Turn();
    void UndeadGeneration();

private:
    DirectX::XMFLOAT2 moveVec_ = {};
    float moveSpeed_ = 100;

    float generationTime_ = 0;

    const float size_ = 100.0f;

    int state_ = 0;

    enum class State
    {
        Pursuit,
        Necromancy,
        End
    };

    State state_ = State::Pursuit;

};
