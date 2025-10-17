#include "Skill.h"
#include "SkillManager.h"

Skill::Skill(const std::string& name, const SkillManager::SkillType& skillType)
    : Object(name), skillType_(skillType)
{
    // �}�l�[�W���[�ɓo�^
    SkillManager::Instance().Register(this);
}
