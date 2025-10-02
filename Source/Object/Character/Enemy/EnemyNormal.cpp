#include "EnemyNormal.h"
#include "Object/Character/Player/PlayerManager.h" 

EnemyNormal::EnemyNormal()
    : Enemy(EnemyManager::EnemyType::Normal, "NormalEnemy")
{
}

void EnemyNormal::Initialize()
{

}

void EnemyNormal::Update(const float& elapsedTime)
{
    //’ÇÕ
    Pursuit();

    Move(elapsedTime);
}

void EnemyNormal::Move(const float& elapsedTime)
{
    GetTransform()->AddPosition(GetVelocity() * moveSpeed_ * elapsedTime);
}

void EnemyNormal::Pursuit()
{
    DirectX::XMFLOAT2 playerPosition = PlayerManager::Instance().GetTransform()->GetPosition();

    SetVelocity(playerPosition - GetTransform()->GetPosition());
    float length = sqrtf(GetVelocity().x * GetVelocity().x + GetVelocity().y + GetVelocity().y);
    SetVelocity(GetVelocity() / length);

    GetTransform()->SetAngle(atan2(GetVelocity().y, GetVelocity().x));
}


