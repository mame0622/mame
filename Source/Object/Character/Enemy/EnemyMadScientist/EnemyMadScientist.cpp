#include "EnemyMadScientist.h"
#include "Object/Character/Player/PlayerManager.h"
#include "Input/Input.h"

EnemyMadScientist::EnemyMadScientist()
    :Enemy("EnemyMadScientist", EnemyManager::EnemyType::MadScientist,
        Collision::Type::Enemy, this, 25.0f)
{

}

void EnemyMadScientist::Initialize()
{
    GetTransform()->SetSize(size_);
    GetTransform()->SetTexSize(size_);
    GetTransform()->SetPivot(size_ * 0.5f);

    // ‰¼
    GetTransform()->SetPosition(300.0f, 400.0f);
}

void EnemyMadScientist::Update(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    moveVec_ = playerCenterPosition - enemyCenterPosition;

    Turn();

    // ¡‚Íƒ{ƒ^ƒ“‚Å”»’è‚µ‚Ä‚é(¡Œã‚ÍHP‚ª0‚É‚È‚Á‚½uŠÔ“ü‚é)
    if (Input::Instance().GetGamePad().GetButtonDown() & GamePad::BTN_X)
    {
        
    }
}

void EnemyMadScientist::DrawDebug()
{

}

void EnemyMadScientist::OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position)
{

}

// ù‰ñˆ—
void EnemyMadScientist::Turn()
{
    const DirectX::XMFLOAT2 moveDirection = XMFloat2Normalize(moveVec_);

    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveDirection.y, moveDirection.x) + DirectX::XM_PIDIV2));
}
