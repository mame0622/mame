#include "Skill.h"
#include "SkillManager.h"

Skill::Skill(const SkillManager::SkillType& skillType)
    : skillType_(skillType)
{
    // �}�l�[�W���[�ɓo�^
    SkillManager::Instance().Register(this);
}
