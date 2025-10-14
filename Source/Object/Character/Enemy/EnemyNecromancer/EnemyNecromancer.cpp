#include "EnemyNecromancer.h"
#include "Object/Character/Player/PlayerManager.h"
#include "Object/Character/Enemy/EnemyNormal/EnemyNormal.h"

EnemyNecromancer::EnemyNecromancer()
    :Enemy("EnemyNecromancer", EnemyManager::EnemyType::Necromancer,
        Collision::Type::Enemy, this, 25.0f)
{

}

void EnemyNecromancer::Initialize()
{
    const float size = 100.0f;
    GetTransform()->SetSize(size);
    GetTransform()->SetTexSize(size);
    GetTransform()->SetPivot(size * 0.5f);

    SetCollisionRadius(50.0f);
}

void EnemyNecromancer::Update(const float& elapsedTime)
{
    // �i�s�����x�N�g���Z�o
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    moveVec_ = playerCenterPosition - enemyCenterPosition;

    generationTime_ += elapsedTime;

    Pursuit(elapsedTime);

    
}

void EnemyNecromancer::DrawDebug()
{

}

// �Փˌ��m
void EnemyNecromancer::OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position)
{
}

// �ǐՏ���
void EnemyNecromancer::Pursuit(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 moveDirection = XMFloat2Normalize(moveVec_);

    GetTransform()->AddPosition(moveDirection * moveSpeed_ * elapsedTime);
    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveDirection.y, moveDirection.x) + DirectX::XM_PIDIV2));
}

void EnemyNecromancer::UndeadGeneration()
{
    // ��������G�̐�
    const int undead = 4;

    for (int i = 0; i < undead; i++)
    {
        EnemyNormal* enemy = new EnemyNormal();
        // �����ʒu�ݒ�
        enemy->GetTransform()->SetPositionX(GetTransform()->GetPosition().x);
        enemy->GetTransform()->SetPositionY(GetTransform()->GetPosition().y);

        // �o�^
        EnemyManager::Instance().Register(enemy);
    }
}
