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

private:
    BulletLevel level_ = BulletLevel::One;
};

