#pragma once
#include "Object/Character/Character.h"
#include "Resource/Sprite/SpriteBatch.h"

class Player : public Character
{
public:
    Player();
    ~Player() override {}

    void Initialize();
    void Update(const float& elapsedTime);
    void Render();
    void DrawDebug() override;

    const DirectX::XMFLOAT2 GetMoveDirection() const { return moveDirection_; }

private:
    SpriteBatch spriteBatch_;

    // ---------- Move ----------
    DirectX::XMFLOAT2   moveDirection_ = { 0.0f, -1.0f };
    float               moveSpeed_      = 500.0f;
};

