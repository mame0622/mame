#include "Player.h"
#include "ImGui/ImGuiCtrl.h"

// コンストラクタ
Player::Player()
    : sprite_(L"./Resources/Image/Stamina.png")
{
}

// 描画
void Player::Render()
{
    sprite_.Render();
}

// ImGui
void Player::DrawDebug()
{
    ImGui::Begin("Player");

    sprite_.DrawDebug();

    ImGui::End();
}
