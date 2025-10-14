#pragma once
#include "Object/Character/Character.h"
#include "Resource/Sprite/SpriteBatch.h"
#include "Collision/Collision.h"

class Player : public Character
{
public:
    Player();
    ~Player() override {}

    void Initialize();
    void Update(const float& elapsedTime);
    void Render();
    void DrawDebug() override;

    void OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position) override;

    const DirectX::XMFLOAT2 GetMoveDirection() const { return moveDirection_; }

private:
    SpriteBatch spriteBatch_;

    // ---------- Move ----------
    DirectX::XMFLOAT2   moveDirection_ = { 0.0f, -1.0f };
    float               moveSpeed_      = 500.0f;

    Collision* collision_;

    DirectX::XMFLOAT2 collisionOffset_ = { 40.0f, 40.0f };
};

