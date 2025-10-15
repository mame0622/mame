#include "SkillManager.h"
#include "Application/Common.h"
#include "Skill.h"
#include "ImGui/ImGuiCtrl.h"

SkillManager::SkillManager()
{
    // �e�N�X�`���o�^
    spriteBatches_.emplace_back(SpriteBatch(L"./Resources/Image/Skill/ChainLightning/ChainLightning.png", 50/*�ő�`�搔*/));
}

// �X�V
void SkillManager::Update(const float& elapsedTime)
{
    // �o�^
    for (Skill* skill : generates_)
    {
        skills_.emplace_back(skill);
    }
    generates_.clear();

    // �X�V
    for (Skill*& skill : skills_)
    {
        skill->Update(elapsedTime);
    }

    // �j��
    for (Skill* skill : removes_)
    {
        auto it = std::find(skills_.begin(), skills_.end(), skill);

        if (it != skills_.end()) skills_.erase(it);

        SafeDeletePtr(skill);
    }
    removes_.clear();
}

void SkillManager::Render()
{
    // �e�N�X�`���̎�ނ��Ƃɕ`�悷��
    for (int textureIndex = 0; textureIndex < static_cast<int>(SkillType::Max); ++textureIndex)
    {
        std::vector<Transform2D> transforms;
        for (Skill*& skill : skills_)
        {
            if (skill->GetSkillType() == static_cast<SkillType>(textureIndex))
            {
                if (skill->GetTransformCount() == 0) continue;

                for (int i = 0; i < skill->GetTransformCount(); ++i)
                {
                    transforms.emplace_back(skill->GetTransform(i));
                }
            }
        }
        spriteBatches_.at(textureIndex).Render(transforms);
    }
}

void SkillManager::DrawDebug()
{
#if USE_IMGUI
    ImGui::Begin("SkillManager");

    for (Skill*& skill : skills_)
    {
        skill->DrawDebug();
    }

    ImGui::End();

#endif // USE_IMGUI
}