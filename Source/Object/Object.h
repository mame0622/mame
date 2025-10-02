#pragma once
#include "Math/Transform.h"

class Object
{
public:
    Object();
    virtual ~Object() {}

    virtual void DrawDebug(); // ImGui

    Transform2D* GetTransform() { return &transform_; }

    const int GetObjectId() const { return objectId_; }

private:
    Transform2D transform_;
    const int   objectId_ = 0;    
    static int  objectIdCount_;
};

