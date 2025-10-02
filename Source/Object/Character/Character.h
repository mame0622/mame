#pragma once
#include "Object/Object.h"

class Character : public Object
{
public:
    Character() {}
    ~Character() override {}

    void DrawDebug();

    void SetCollisionRadius(const float& radius) { collisionRadius_ = radius; }
    const float GetCollisionRadius() const { return collisionRadius_; }

private:
    float collisionRadius_ = 1.0f;
};

