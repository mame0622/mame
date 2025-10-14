#pragma once
#include "SkillManager.h"

class Skill
{
public:
    Skill();
    virtual ~Skill() {}

    virtual void Update(const float& elapsedTime) = 0;

private:
    const SkillManager::SkillType skillType_ = SkillManager::SkillType::ChainLightning;
};

