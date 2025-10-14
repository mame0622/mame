#include "SkillManager.h"
#include "Application/Common.h"
#include "Skill.h"

// XV
void SkillManager::Update(const float& elapsedTime)
{
    // “o˜^
    for (Skill* skill : generates_)
    {
        skills_.emplace_back(skill);
    }
    generates_.clear();

    // XV
    for (Skill*& skill : skills_)
    {
        skill->Update(elapsedTime);
    }

    // ”jŠü
    for (Skill* skill : removes_)
    {
        auto it = std::find(skills_.begin(), skills_.end(), skill);

        if (it != skills_.end()) skills_.erase(it);

        SafeDeletePtr(skill);
    }
    removes_.clear();
}