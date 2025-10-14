#include "EnemyNecromancer.h"
#include "Object/Character/Player/PlayerManager.h"
#include "Object/Character/Enemy/EnemyNormal/EnemyNormal.h"
#include "Input/Input.h"

EnemyNecromancer::EnemyNecromancer()
    :Enemy("EnemyNecromancer", EnemyManager::EnemyType::Necromancer,
        Collision::Type::Enemy, this, 50.0f)
{

}

void EnemyNecromancer::Initialize()
{
    const float size = 100.0f;
    GetTransform()->SetSize(size);
    GetTransform()->SetTexSize(size);
    GetTransform()->SetPivot(size * 0.5f);

    GetTransform()->SetPosition(400.0f, 300.0f);
}

void EnemyNecromancer::Update(const float& elapsedTime)
{
    // êiçsï˚å¸ÉxÉNÉgÉãéZèo
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    moveVec_ = playerCenterPosition - enemyCenterPosition;

    generationTime_ += elapsedTime;

    Pursuit(elapsedTime);
    // ç°ÇÕÉ{É^ÉìÇ≈îªíËÇµÇƒÇÈ(ç°å„ÇÕHPÇ™0Ç…Ç»Ç¡ÇΩèuä‘ì¸ÇÈ)
    if (Input::Instance().GetGamePad().GetButtonDown() & GamePad::BTN_X) {
        UndeadGeneration();
    }
}

void EnemyNecromancer::DrawDebug()
{

}

// è’ìÀåüím
void EnemyNecromancer::OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position)
{
}

// í«ê’èàóù
void EnemyNecromancer::Pursuit(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 moveDirection = XMFloat2Normalize(moveVec_);

    GetTransform()->AddPosition(moveDirection * moveSpeed_ * elapsedTime);
    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveDirection.y, moveDirection.x) + DirectX::XM_PIDIV2));
}

void EnemyNecromancer::UndeadGeneration()
{
    const DirectX::XMFLOAT2 moveDirection = XMFloat2Normalize(moveVec_);
    const DirectX::XMFLOAT3 up = { 0.0f,1.0f,0.0f };
    const DirectX::XMFLOAT3 moveVec3 = { moveDirection.x,0.0f,moveDirection.y };
    const DirectX::XMVECTOR Up = DirectX::XMLoadFloat3(&up);
    const DirectX::XMVECTOR MoveVec3 = DirectX::XMLoadFloat3(&moveVec3);
    const DirectX::XMVECTOR RightVec3 = DirectX::XMVector3Cross(MoveVec3, Up);
    DirectX::XMFLOAT3 rightVec3;
    DirectX::XMStoreFloat3(&rightVec3, RightVec3);
    const DirectX::XMFLOAT2 rightVec = { rightVec3.x, rightVec3.z };
    const DirectX::XMFLOAT2 rightDirection = XMFloat2Normalize(rightVec);
    const DirectX::XMFLOAT2 diagonallyVec = XMFloat2Normalize(moveDirection + rightVec);

        // ê∂ê¨Ç∑ÇÈìGÇÃêî
    const int undead = 1;

    for (int i = 0; i < undead; ++i)
    {
        EnemyNormal* enemy = new EnemyNormal();

        if (i == 0) {
            // ê∂ê¨à íuê›íË
            enemy->GetTransform()->SetPositionX(GetTransform()->GetCenterPosition().x + (diagonallyVec.x * 100.0f));
            enemy->GetTransform()->SetPositionY(GetTransform()->GetCenterPosition().y + (diagonallyVec.y * 100.0f));
        }
        else if (i == 1)
        {
            enemy->GetTransform()->SetPositionX(GetTransform()->GetCenterPosition().x - (diagonallyVec.x * 100.0f));
            enemy->GetTransform()->SetPositionY(GetTransform()->GetCenterPosition().y + (diagonallyVec.y * 100.0f));
        }
        else if (i == 2)
        {
            enemy->GetTransform()->SetPositionX(GetTransform()->GetCenterPosition().x + (diagonallyVec.x * 100.0f));
            enemy->GetTransform()->SetPositionY(GetTransform()->GetCenterPosition().y - (diagonallyVec.y * 100.0f));
        }
        else if (i == 3)
        {
            enemy->GetTransform()->SetPositionX(GetTransform()->GetCenterPosition().x - (diagonallyVec.x * 100.0f));
            enemy->GetTransform()->SetPositionY(GetTransform()->GetCenterPosition().y - (diagonallyVec.y * 100.0f));
        }
        // ìoò^
        EnemyManager::Instance().Register(enemy);
    }
}
