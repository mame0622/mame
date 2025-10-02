#include "EnemyNormal.h"
#include "Object/Character/Player/PlayerManager.h" 

EnemyNormal::EnemyNormal()
    : Enemy(EnemyManager::EnemyType::Normal, "NormalEnemy")
{
}

// ������
void EnemyNormal::Initialize()
{
    GetTransform()->SetSize(size_);
    GetTransform()->SetTexSize(size_);
    GetTransform()->SetPivot(size_ * 0.5f);
}

// �X�V
void EnemyNormal::Update(const float& elapsedTime)
{
    // �ǐՈړ�
    Pursuit(elapsedTime);

}

// �ǐՈړ� Player�Ɍ������Đi�s����
void EnemyNormal::Pursuit(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 moveVec = XMFloat2Normalize(playerCenterPosition - enemyCenterPosition);

    GetTransform()->AddPosition(moveVec * moveSpeed_ * elapsedTime);
    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveVec.y, moveVec.x) + DirectX::XM_PIDIV2));
}


