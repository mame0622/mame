#pragma once
#include "Skill.h"
#include <vector>
#include <set>

class SkillManager
{
private:
    SkillManager() {}
    ~SkillManager() {}

public:
    static SkillManager& Instance()
    {
        static SkillManager instance;
        return instance;
    }

    void Update(const float& elapsedTime);

    void Regiset(Skill* skill) { generates_.insert(skill); }
    void Remove(Skill* skill) { removes_.insert(skill); }
    void Clear();

private:
    std::vector<Skill*> skills_;
    std::set<Skill*>    generates_;
    std::set<Skill*>    removes_;
};

