#include "Player.h"
#include "ImGui/ImGuiCtrl.h"

// �R���X�g���N�^
Player::Player()
    : sprite_(L"./Resources/Image/Stamina.png")
{
}

// �`��
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
