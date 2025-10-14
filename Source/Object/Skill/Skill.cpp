#include "Skill.h"
#include "SkillManager.h"

Skill::Skill()
{
    // マネージャーに登録
    SkillManager::Instance().Register(this);
}
