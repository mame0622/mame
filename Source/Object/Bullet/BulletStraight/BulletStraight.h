#pragma once
#include "Object/Bullet/Bullet.h"

class BulletStraight : public Bullet
{
public:
    BulletStraight();
    ~BulletStraight() override {}

    void Initialize(const float& length, const DirectX::XMFLOAT2& enemyCenterPosition, const DirectX::XMFLOAT2& moveDirection);
    void Update(const float& elapsedTime) override;
    void DrawDebug() override;

    void OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position) override;

    void Launch(const float& elapsedTime, const DirectX::XMFLOAT2& moveDirection);
private:
    DirectX::XMFLOAT2   moveDirection_ = {};
    float               moveSpeed_ = 500.0f;
};

