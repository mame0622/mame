#pragma once
#include <DirectXMath.h>

class CollisionManager
{
private:
    CollisionManager() {}
    ~CollisionManager() {}

public:
    static CollisionManager& Instance()
    {
        static CollisionManager instance;
        return instance;
    }

    void Update();

    // ‰~ Vs ‰~
    const bool IntersectCircleVsCircle(
        const DirectX::XMFLOAT2& positionA, const float& radiusA,
        const DirectX::XMFLOAT2& positionB, const float& radiusB,
        DirectX::XMFLOAT2& resultPosition);
};

