#include "Player.h"
#include "ImGui/ImGuiCtrl.h"
#include "Input/Input.h"

// コンストラクタ
Player::Player()
    : spriteBatch_(L"./Resources/Image/Player.png", 1)
{
}

// 初期化
void Player::Initialize()
{
    GetTransform()->SetSize(100.0f);
    GetTransform()->SetTexSize(100.0f);
    GetTransform()->SetPivot(50.0f);
}

// 更新
void Player::Update(const float& elapsedTime)
{
    // 移動処理
    const float aLx = Input::Instance().GetGamePad().GetAxisLx();
    const float aLy = Input::Instance().GetGamePad().GetAxisLy();
    const DirectX::XMFLOAT2 moveVec = XMFloat2Normalize({ aLx, aLy });
    GetTransform()->AddPositionX(moveSpeed_ * moveVec.x * elapsedTime);
    GetTransform()->AddPositionY(moveSpeed_ * moveVec.y * -1.0f * elapsedTime);

    // 旋回処理
    if(moveVec.x != 0.0f || moveVec.y != 0.0f)
    {
        GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveVec.x, moveVec.y)));
    }
}

// 描画
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
