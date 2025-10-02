#include "Player.h"
#include "ImGui/ImGuiCtrl.h"
#include "Input/Input.h"

Player::Player()
    : spriteBatch_(L"./Resources/Image/Player/Player.png", 1)
{
}

// ‰Šú‰»
void Player::Initialize()
{
    GetTransform()->SetSize(100.0f);
    GetTransform()->SetTexSize(100.0f);
    GetTransform()->SetPivot(50.0f);
}

// XV
void Player::Update(const float& elapsedTime)
{
    // ˆÚ“®ˆ—
    const float aLx = Input::Instance().GetGamePad().GetAxisLx();
    const float aLy = Input::Instance().GetGamePad().GetAxisLy();
    const DirectX::XMFLOAT2 moveVec = XMFloat2Normalize({ aLx, -aLy });
    GetTransform()->AddPositionX(moveSpeed_ * moveVec.x * elapsedTime);
    GetTransform()->AddPositionY(moveSpeed_ * moveVec.y * elapsedTime);

    // ù‰ñˆ—
    if(moveVec.x != 0.0f || moveVec.y != 0.0f)
    {
        GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveVec.y, moveVec.x) + DirectX::XM_PIDIV2));
    }
}

// •`‰æ
void Player::Render()
{
    std::vector<Transform2D> transforms_;
    transforms_.emplace_back(*GetTransform());
    spriteBatch_.Render(transforms_);
}

// ImGui
void Player::DrawDebug()
{
#if USE_IMGUI
    ImGui::Begin("Player");

    Object::DrawDebug();

    ImGui::End();
#endif
}
