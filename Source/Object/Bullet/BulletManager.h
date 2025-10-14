#pragma once
#include "Bullet.h"
#include "Resource/Sprite/SpriteBatch.h"
#include <vector>
#include <set>

#include "BulletOrbit/BulletOrbit.h"

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

    void Launch(); // ����

    void Register(Bullet* bullet) { generates_.insert(bullet); }
    void Remove(Bullet* bullet) { removes_.insert(bullet); }
    void Clear();

    const int GetFiredBulletCount() const { return static_cast<int>(firedBullets_.size()); }
    Bullet* GetFiredBullet(const int& firedBulletIndex) { return firedBullets_.at(firedBulletIndex); }
    std::vector<Bullet*> GetFiredBullets() { return firedBullets_; }

    std::vector<BulletOrbit*> GetOrvitBullets() { return orvitBullets_; }
    BulletOrbit* GetOrbitBullet(const int& index) { return orvitBullets_.at(index); }
    const int GetOrvitBulletCount() const { return maxOrvitBullets_; }

private:
    void UpdateOrvitBullets(const float& elapsedTime);

private:
    std::vector<SpriteBatch> spriteBatches_;
    const DirectX::XMFLOAT2 bulletSize_ = { 30.0f, 30.0f };

    // ---------- Player�̎���ɔz�u����Bullet ----------
    std::vector<BulletOrbit*>   orvitBullets_;
    static const int            maxOrvitBullets_    = 5;
    float                       orvitAngle_         = 0.0f;
    float                       orvitRadius_        = 50.0f;
    
    // ---------- ���˗p ----------
    std::vector<Bullet*>    firedBullets_;
    std::set<Bullet*>       generates_;
    std::set<Bullet*>       removes_;

    // ���˗p
    int launchIndex_ = 0;
};

