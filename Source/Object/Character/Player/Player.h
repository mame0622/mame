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
    void Move(const float& elapsedTime);    // ˆÚ“®ˆ—
    void Turn();                            // ù‰ñˆ—
    void Blink();                            // ‰ñ”ğ
    void ClampPosition();                   // ‰æ–Ê“à‚ÉˆÊ’u‚ğû‚ß‚é


private:
    SpriteBatch spriteBatch_;

    // ---------- Move ----------
    DirectX::XMFLOAT2   moveDirection_ = { 0.0f, -1.0f };
    float               moveSpeed_      = 500.0f;

    DirectX::XMFLOAT2   blinkDirection_     = {};
    float               blinkPower_         = 2000.0f;
    float               currentBlinkPower_  = 0.0f;
    float               deceleration_       = 8000.0f;


    Collision* collision_;

    DirectX::XMFLOAT2 collisionOffset_ = { 40.0f, 40.0f };
};

