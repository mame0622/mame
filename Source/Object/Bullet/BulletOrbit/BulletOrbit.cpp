#include "BulletOrbit.h"

BulletOrbit::BulletOrbit()
    : Bullet("BulletOrbit")
{
}

// ‰Šú‰»
void BulletOrbit::Initialize(const DirectX::XMFLOAT2& bulletSize)
{
    GetTransform()->SetSize(bulletSize);
    GetTransform()->SetTexSize(bulletSize);
    GetTransform()->SetPivot(bulletSize * 0.5f);

    SetCollisionRadius(30.0f);
}

// XV
void BulletOrbit::Update(const float& elapsedTime)
{
    const float alpha = IsCollisionActive() ? 1.0f : 0.0f;
    GetTransform()->SetColorA(alpha);
}

// ImGui
void BulletOrbit::DrawDebug()
{
}
