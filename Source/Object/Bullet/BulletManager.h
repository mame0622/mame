#pragma once
#include "Bullet.h"

class BulletManager
{
private:
    BulletManager() {}
    ~BulletManager() {}

public:
    static BulletManager& Instance()
    {
        static BulletManager instance;
        return instance;
    }

private:

};

