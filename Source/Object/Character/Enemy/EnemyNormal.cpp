#include "EnemyNormal.h"
#include "Object/Character/Player/PlayerManager.h" 

EnemyNormal::EnemyNormal()
    : Enemy(EnemyManager::EnemyType::Normal)
{
}

void EnemyNormal::Initialize()
{

}

void EnemyNormal::Update(const float& elapsedTime)
{
    //’ÇÕˆÚ“®
    Pursuit(elapsedTime);

}

void EnemyNormal::Pursuit(const float& elapsedTime)
{
    DirectX::XMFLOAT2 playerPosition = PlayerManager::Instance().GetTransform()->GetPosition();
    DirectX::XMFLOAT2 moveVec = { 0,0 };
    moveVec = playerPosition - GetTransform()->GetPosition();
    moveVec = XMFloat2Normalize(moveVec);
    
    GetTransform()->AddPosition(moveVec * moveSpeed_ * elapsedTime);
    GetTransform()->SetAngle(atan2f(moveVec.y, moveVec.x) + DirectX::XM_PIDIV2);
}


