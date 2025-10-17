#pragma once
#include "Object/Bullet/Bullet.h"

class BulletStraight : public Bullet
{
public:
    BulletStraight();
    ~BulletStraight() override {}

    void Initialize(const float& length, const DirectX::XMFLOAT2& moveDirection, const DirectX::XMFLOAT2& enemyCenterPosition);
    void Update(const float& elapsedTime) override;
    void DrawDebug() override;

    void OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position) override;

private:
    DirectX::XMFLOAT2   moveDirection_ = {};
    float               moveSpeed_ = 500.0f;
};

