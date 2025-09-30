#pragma once
#include "Resource/Sprite/Sprite.h"

class Player
{
public:
    Player();
    ~Player() {}

    void Render();
    void DrawDebug();

private:
    Sprite sprite_;
};

