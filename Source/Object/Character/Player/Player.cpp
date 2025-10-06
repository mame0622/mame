#include "Player.h"
#include "ImGui/ImGuiCtrl.h"
#include "Input/Input.h"
#include "Object/Bullet/BulletManager.h"
#include "Graphics/Graphics.h"

Player::Player()
    : Character("Player"), 
    spriteBatch_(L"./Resources/Image/Player/Player.png", 1)
{
}

// ‰Šú‰»
void Player::Initialize()
{
    GetTransform()->SetPosition(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

    GetTransform()->SetSize(50.0f);
    GetTransform()->SetTexSize(50.0f);
    GetTransform()->SetPivot(25.0f);
    
    SetCollisionRadius(25.0f);
}

// XV
void Player::Update(const float& elapsedTime)
{
    // ˆÚ“®ˆ—
    const float aLx = Input::Instance().GetGamePad().GetAxisLx();
    const float aLy = Input::Instance().GetGamePad().GetAxisLy();
    const DirectX::XMFLOAT2 moveDirection = XMFloat2Normalize({ aLx, -aLy });
    GetTransform()->AddPositionX(moveDirection.x * moveSpeed_ * elapsedTime);
    GetTransform()->AddPositionY(moveDirection.y * moveSpeed_ * elapsedTime);

    // ù‰ñˆ—
    if(moveDirection.x != 0.0f || moveDirection.y != 0.0f)
    {
        GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveDirection.y, moveDirection.x) + DirectX::XM_PIDIV2));

        moveDirection_ = moveDirection; // •Û‘¶‚·‚é
    }

    // ’e”­ŽË Aƒ{ƒ^ƒ“ Space
    if (Input::Instance().GetGamePad().GetButtonDown() & GamePad::BTN_A)
    {
        BulletManager::Instance().Launch();
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
    ImGui::Begin(GetName().c_str());

    Object::DrawDebug();
    Character::DrawDebug();

    ImGui::End();
#endif
}
