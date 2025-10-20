#include "EnemyNecromancerState.h"
#include "EnemyNecromancer.h"
#include "Object/Character/Player/PlayerManager.h"
#include "Object/Character/Enemy/EnemyNormal/EnemyNormal.h"

// PursuitState
namespace EnemyNecromancerState
{
    // ������
    void PursuitState::Initialize()
    {
        pursuitTimer_ = pursuitTime_;

        owner_->SetMoveSpeed(moveSpeed_);
    }

    // �X�V
    void PursuitState::Update(const float& elapsedTime)
    {
        const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
        const DirectX::XMFLOAT2 ownerCenterPosition = owner_->GetTransform()->GetPosition();
        const DirectX::XMFLOAT2 moveDirection = XMFloat2Normalize(playerCenterPosition - ownerCenterPosition);

        pursuitTimer_ -= elapsedTime;

        // �ǐՏ���
        owner_->GetTransform()->AddPosition(moveDirection * owner_->GetMoveSpeed() * elapsedTime);

        // �J�ڃ`�F�b�N
        if (pursuitTimer_ <= 0.0f)
        {
            EnemyNecromancer* owner = dynamic_cast<EnemyNecromancer*>(owner_);
            owner->ChangeState(EnemyNecromancer::State::Necromancy);
            return;
        }
    }

    // ImGui
    void PursuitState::DrawDebug()
    {
#if USE_IMGUI


#endif // USE_IMGUI
    }
}

// NecromancyState
namespace EnemyNecromancerState
{
    // ������
    void NecromancyState::Initialize()
    {
        generationTimer_ = generationTime_;

        owner_->SetMoveSpeed(moveSpeed_);
    }

    // �X�V
    void NecromancyState::Update(const float& elapsedTime)
    {
        generationTimer_ -= elapsedTime;

        if (generationTimer_ <= 0.0f)
        {
            // EnemyNormal�𐶐�����
            UndeadGeneration();

            // �ǐՂɑJ�ڂ���
            EnemyNecromancer* owner = dynamic_cast<EnemyNecromancer*>(owner_);
            owner->ChangeState(EnemyNecromancer::State::Pursuit);
            return;
        }
    }

    // ImGui
    void NecromancyState::DrawDebug()
    {
#if USE_IMGUI


#endif // USE_IMGUI
    }

    // EnemyNormal�𐶐�����
    void NecromancyState::UndeadGeneration()
    {
        // �����ʒu�����肷��(4�ӏ�)
        static const int generateNum = 4;
        constexpr float angle[generateNum] =
        {
            DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(-45.0f),
            DirectX::XMConvertToRadians(135.0f), DirectX::XMConvertToRadians(-135.0f),
        };
        const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
        const DirectX::XMFLOAT2 ownerCenterPosition = owner_->GetTransform()->GetCenterPosition();
        const DirectX::XMFLOAT2 moveDirection = XMFloat2Normalize(playerCenterPosition - ownerCenterPosition);

        // ��������
        for (int generateIndex = 0; generateIndex < generateNum; ++generateIndex)
        {
            const DirectX::XMFLOAT2 newMoveDirection =
            {
                moveDirection.x * cosf(angle[generateIndex]) - moveDirection.y * sinf(angle[generateIndex]),
                moveDirection.x * sinf(angle[generateIndex]) + moveDirection.y * cosf(angle[generateIndex])
            };

            const DirectX::XMFLOAT2 generatePosition = owner_->GetTransform()->GetPosition() +
                owner_->GetTransform()->GetPivot() * 0.5f + newMoveDirection * 100.0f;

            EnemyNormal* enemy = new EnemyNormal();
            enemy->GetTransform()->SetPosition(generatePosition);
        }
    }
}