#include "Skill.h"
#include "SkillManager.h"

Skill::Skill()
{
    // �}�l�[�W���[�ɓo�^
    SkillManager::Instance().Register(this);
}
