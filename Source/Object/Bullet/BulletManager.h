#pragma once
#include "Bullet.h"
#include <vector>
#include "Resource/Sprite/SpriteBatch.h"

class BulletManager
{
private:
    BulletManager();
    ~BulletManager() {}

public:
    static BulletManager& Instance()
    {
        static BulletManager instance;
        return instance;
    }

    void Update(const float& elapsedTime);
    void Render();
    void DrawDebug();

    std::vector<Bullet>& GetBullets() { return bullets_; }
    const int GetBulletCount() const { return maxBullets_; }

private:
    const int maxBullets_ = 5;
    std::vector<Bullet> bullets_;
    
    const DirectX::XMFLOAT2 bulletSize_ = { 30.0f, 30.0f };

    float angle_ = 0.0f;
    float radius_ = 50.0f;

    std::vector<SpriteBatch> spriteBatches_;
};

