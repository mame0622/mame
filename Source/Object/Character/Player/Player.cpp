#include "Player.h"
#include "ImGui/ImGuiCtrl.h"
#include "Input/Input.h"

// �R���X�g���N�^
Player::Player()
    : sprite_(L"./Resources/Image/Player.png")
{
}

// ������
void Player::Initialize()
{
    GetTransform()->SetSize(100.0f);
    GetTransform()->SetTexSize(100.0f);
    GetTransform()->SetPivot(50.0f);
}

// �X�V
void Player::Update(const float& elapsedTime)
{
    // �ړ�����
    const float aLx = Input::Instance().GetGamePad().GetAxisLx();
    const float aLy = Input::Instance().GetGamePad().GetAxisLy();
    const DirectX::XMFLOAT2 moveVec = XMFloat2Normalize({ aLx, aLy });
    sprite_.GetTransform()->AddPositionX(moveSpeed_ * moveVec.x * elapsedTime);
    sprite_.GetTransform()->AddPositionY(moveSpeed_ * moveVec.y * -1.0f * elapsedTime);

    // ���񏈗�
    if(moveVec.x != 0.0f || moveVec.y != 0.0f)
    {
        sprite_.GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveVec.x, moveVec.y)));
    }
}

// �`��
void Player::Render()
{
    sprite_.Render();
}

// ImGui
void Player::DrawDebug()
{
#if USE_IMGUI
    ImGui::Begin("Player");

    sprite_.DrawDebug();

    ImGui::End();
#endif
}
