#include "Bullet.h"
#include "ImGui/ImGuiCtrl.h"

// ImGui
void Bullet::DrawDebug()
{
#if USE_IMGUI
    const std::string name = "Bullet" + std::to_string(GetObjectId());
    if (ImGui::TreeNode(name.c_str()))
    {
        int level = static_cast<int>(level_);
        ImGui::SliderInt("Level", &level, 0, 4);
        level_ = static_cast<BulletLevel>(level);

        ImGui::TreePop();
    }

#endif // USE_IMGUI
}
