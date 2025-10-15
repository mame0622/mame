#include "Skill.h"
#include "SkillManager.h"

Skill::Skill(const SkillManager::SkillType& skillType)
    : skillType_(skillType)
{
    // マネージャーに登録
    SkillManager::Instance().Register(this);
}
