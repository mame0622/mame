#pragma once
#include "Object/Bullet/Bullet.h"

class BulletLevel1 : public Bullet
{
public:
    BulletLevel1();
    ~BulletLevel1() override {}

    void Initialize(const int& bulletNumber, const DirectX::XMFLOAT2& bulletSize,
        const float& length, const DirectX::XMFLOAT2& moveDirection);
    void Update(const float& elapsedTime) override;
    void DrawDebug() override;

private:
    DirectX::XMFLOAT2   moveDirection_  = {};
    float               moveSpeed_      = 500.0f;
};

