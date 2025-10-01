#pragma once
#include "Resource/Sprite/Sprite.h"

class Player
{
public:
    Player();
    ~Player() {}

    void Initialize();
    void Update(const float& elapsedTime);
    void Render();
    void DrawDebug();

    Transform2D* GetTransform() { return sprite_.GetTransform(); }

private:
    Sprite sprite_;

    float moveSpeed_ = 500.0f;
};

