#include "Player.h"
#include "ImGui/ImGuiCtrl.h"
#include "Input/Input.h"
#include "Object/Bullet/BulletManager.h"
#include "Graphics/Graphics.h"

Player::Player()
    : Character("Player"), 
    spriteBatch_(L"./Resources/Image/Player/Player.png", 1),
    collision_(new Collision(Collision::Type::Player, this, 25.0f))
{
}

// ������
void Player::Initialize()
{
    GetTransform()->SetPosition(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

    GetTransform()->SetSize(50.0f);
    GetTransform()->SetTexSize(50.0f);
    GetTransform()->SetPivot(25.0f);
}

// �X�V
void Player::Update(const float& elapsedTime)
{
    // �ړ�����
    const float aLx = Input::Instance().GetGamePad().GetAxisLx();
    const float aLy = Input::Instance().GetGamePad().GetAxisLy();
    const DirectX::XMFLOAT2 moveDirection = XMFloat2Normalize({ aLx, -aLy });
    GetTransform()->AddPositionX(moveDirection.x * moveSpeed_ * elapsedTime);
    GetTransform()->AddPositionY(moveDirection.y * moveSpeed_ * elapsedTime);

    // ���񏈗�
    if(moveDirection.x != 0.0f || moveDirection.y != 0.0f)
    {
        GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveDirection.y, moveDirection.x) + DirectX::XM_PIDIV2));

        moveDirection_ = moveDirection; // �ۑ�����
    }

    // �e���� A�{�^�� Space
    if (Input::Instance().GetGamePad().GetButtonDown() & GamePad::BTN_A)
    {
        BulletManager::Instance().Launch();
    }

    // ��(��ʊO)����
    DirectX::XMFLOAT2 position = GetTransform()->GetPosition();
    const DirectX::XMFLOAT2 size = GetTransform()->GetSize();
    const DirectX::XMFLOAT2 collisionWidth = { position.x - collisionOffset_.x, position.x + size.x + collisionOffset_.x};
    const DirectX::XMFLOAT2 collisionHeight = { position.y - collisionOffset_.y, position.y + size.y + collisionOffset_.y };
    if (collisionWidth.x <= 0.0f) position.x = collisionOffset_.x;
    if (collisionWidth.y >= SCREEN_WIDTH) position.x = SCREEN_WIDTH - size.x - collisionOffset_.x;
    if (collisionHeight.x <= 0.0f) position.y = collisionOffset_.y;
    if (collisionHeight.y >= SCREEN_HEIGHT) position.y = SCREEN_HEIGHT - size.y - collisionOffset_.y;
    GetTransform()->SetPosition(position);
}

// �`��
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

    ImGui::DragFloat2("CollisionOffset", &collisionOffset_.x);

    Object::DrawDebug();
    Character::DrawDebug();

    ImGui::End();
#endif
}

// �Փˌ��m
void Player::OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position)
{

    // ��:���S�����肵�āAObject����������Ƃ��ɓ����蔻�������
    //collision_.Remove();
}
