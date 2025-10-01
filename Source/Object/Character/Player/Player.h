#pragma once
#include "Object/Character/Character.h"
#include "Resource/Sprite/SpriteBatch.h"

class Player : public Character
{
public:
    Player();
    ~Player() override {}

    void Initialize();
    void Update(const float& elapsedTime);
    void Render();
    void DrawDebug() override;

private:
    SpriteBatch spriteBatch_;

    float moveSpeed_ = 500.0f;
};

