#pragma once
#include "Math/Transform.h"

class Enemy
{
public:
    Enemy() {}
    virtual ~Enemy() {}

    Transform2D* GetTransform() { return &transform_; }

private:
    Transform2D transform_;
};

