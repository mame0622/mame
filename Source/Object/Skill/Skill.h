#pragma once
#include "SkillManager.h"
#include "Math/Transform.h"
#include <vector>

class Skill
{
public:
    Skill(const SkillManager::SkillType& skillType);
    virtual ~Skill() {}

    virtual void Update(const float& elapsedTime)   = 0;
    virtual void DrawDebug()                        = 0;

    const SkillManager::SkillType GetSkillType() const { return skillType_; }

    const int GetTransformCount() const { return transforms_.size(); }
    const Transform2D GetTransform(const int& index) { return transforms_.at(index); }

private:
    const SkillManager::SkillType   skillType_;
    
protected:
    std::vector<Transform2D>        transforms_;
};

