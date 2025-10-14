#pragma once
#include "Object/Skill/Skill.h"
#include "Math/Transform.h"
#include <vector>

class SkillChainLightning : public Skill
{
public:
    SkillChainLightning();
    ~SkillChainLightning() override {}

    void Initialize();
    void Update(const float& elapsedTime);

private:
    void FindNearestEnemy(const int& index);

private:
    std::vector<int> enemyIndexes_;

    std::vector<Transform2D> transforms_;
};

