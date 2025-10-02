#pragma once
#include "Object/Object.h"

class Bullet : public Object
{
public:
    enum class BulletLevel { One, Two, Three, Four, Five };

public:
    Bullet() {}
    ~Bullet() {}

    void DrawDebug();

    const BulletLevel GetBulletLevel() const { return level_; }

    void SetCollisionRadius(const float& radius) { collisionRadius_ = radius; }
    const float GetCollisionRadius() const { return collisionRadius_; }

private:
    BulletLevel level_ = BulletLevel::One;

    float collisionRadius_ = 1.0f;
};

