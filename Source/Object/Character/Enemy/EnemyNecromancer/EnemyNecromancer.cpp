#include "EnemyNecromancer.h"
#include "Object/Character/Player/PlayerManager.h"
#include "Object/Character/Enemy/EnemyNormal/EnemyNormal.h"
#include "EnemyNecromancerState.h"

EnemyNecromancer::EnemyNecromancer()
    :Enemy("EnemyNecromancer", EnemyManager::EnemyType::Necromancer,
        Collision::Type::Enemy, this, 50.0f)
{
    GetStateMachine()->RegisterState(new EnemyNecromancerState::PursuitState(this));
    GetStateMachine()->RegisterState(new EnemyNecromancerState::NecromancyState(this));

    GetStateMachine()->SetState(static_cast<int>(State::Pursuit));
    SetCurrentState(static_cast<int>(State::Pursuit));
}

// ������
void EnemyNecromancer::Initialize()
{
    GetTransform()->SetSize(size_);
    GetTransform()->SetTexSize(size_);
    GetTransform()->SetPivot(size_ * 0.5f);
}

// �X�V
void EnemyNecromancer::Update(const float& elapsedTime)
{
    // �X�e�[�g�}�V���X�V
    GetStateMachine()->Update(elapsedTime);

    // ���񏈗�
    Turn();
}

// ImGui
void EnemyNecromancer::DrawDebug()
{
}

// �Փˌ��m
void EnemyNecromancer::OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position)
{
}

// ���񏈗�
void EnemyNecromancer::Turn()
{
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 moveDirection = XMFloat2Normalize(playerCenterPosition - enemyCenterPosition);

    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveDirection.y, moveDirection.x) + DirectX::XM_PIDIV2));
}
