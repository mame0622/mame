#pragma once

class Skill
{
public:
    Skill() {}
    virtual ~Skill() {}

    virtual void Update(const float& elapsedTime) = 0;
};

