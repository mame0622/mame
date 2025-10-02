#include "Object.h"

int Object::objectIdCount_ = 0;

Object::Object()
    : objectId_(objectIdCount_++)
{
}

// ImGui
void Object::DrawDebug()
{
    transform_.DrawDebug();
}
