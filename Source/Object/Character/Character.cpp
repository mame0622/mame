#include "Character.h"
#include "ImGui/ImGuiCtrl.h"

void Character::DrawDebug()
{
#if USE_IMGUI
    ImGui::DragFloat("Radius", &collisionRadius_);

#endif // USE_IMGUI
}
