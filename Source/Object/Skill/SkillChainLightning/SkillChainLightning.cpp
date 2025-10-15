#include "SkillChainLightning.h"
#include "Object/Character/Player/PlayerManager.h"
#include "Object/Character/Enemy/EnemyManager.h"
#include "Object/Character/Enemy/Enemy.h"
#include "ImGui/ImGuiCtrl.h"

SkillChainLightning::SkillChainLightning()
    : Skill(SkillManager::SkillType::ChainLightning)
{
}

// ������
const bool SkillChainLightning::Initialize()
{
    // �G�����݂��Ă��Ȃ���Ό��ĂȂ�
    if (EnemyManager::Instance().GetEnemyCount() == 0) return false;

    // �ő哢������ݒ�(�ő�5��)
    const int maxChainCount = (EnemyManager::Instance().GetEnemyCount() > 5) ? 5 : EnemyManager::Instance().GetEnemyCount();

    // Player����ł��߂��G���珇�Ԃɋ��߂�(�ő�5��)
    const DirectX::XMFLOAT2 playerPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    float minLength = FLT_MAX;
    int nearestEnemyIndex = 0;
    for (int enemyIndex = 0; enemyIndex < EnemyManager::Instance().GetEnemyCount(); ++enemyIndex)
    {
        const DirectX::XMFLOAT2 enemyPosition = EnemyManager::Instance().GetEnemy(enemyIndex)->GetTransform()->GetCenterPosition();
        const float length = XMFloat2Length(enemyPosition - playerPosition);

        if (minLength > length)
        {
            minLength = length;
            nearestEnemyIndex = enemyIndex;
        }
    }
    enemyIndexes_.emplace_back(nearestEnemyIndex);

    for (int i = 0; i < maxChainCount - 1; ++i)
    {
        FindNearestEnemy(enemyIndexes_.at(i));
    }

    // ���߂������̓G�̈ʒu��o�^����
    for (int i = 0; i < enemyIndexes_.size(); ++i)
    {
        transforms_.emplace_back(*EnemyManager::Instance().GetEnemy(enemyIndexes_.at(i))->GetTransform());
    }

    // Transform��ݒ肷��
    BuildTransform(PlayerManager::Instance().GetTransform()->GetPosition(),
        EnemyManager::Instance().GetEnemy(enemyIndexes_.at(0))->GetTransform()->GetPosition(),
        PlayerManager::Instance().GetTransform()->GetSize(), 0/*TransformIndex*/);
    for (int enemyIndex = 0; enemyIndex < enemyIndexes_.size() - 1; ++enemyIndex)
    {
        BuildTransform(EnemyManager::Instance().GetEnemy(enemyIndexes_.at(enemyIndex))->GetTransform()->GetPosition(),
            EnemyManager::Instance().GetEnemy(enemyIndexes_.at(enemyIndex + 1))->GetTransform()->GetPosition(),
            EnemyManager::Instance().GetEnemy(enemyIndexes_.at(enemyIndex))->GetTransform()->GetSize(), enemyIndex + 1/*TransformIndex*/);
    }

    return true;
}

// �X�V
void SkillChainLightning::Update(const float& elapsedTime)
{
    timer_ -= elapsedTime;

    for (int i = 0; i < transforms_.size(); ++i)
    {
        transforms_.at(i).SetColorA(timer_);
    }

    if (timer_ <= 0.0f) SkillManager::Instance().Remove(this);
}

// ImGui
void SkillChainLightning::DrawDebug()
{
#if USE_IMGUI
    if (ImGui::TreeNodeEx("SkillChainLightning"))
    {
        transforms_.at(0).DrawDebug();

        ImGui::TreePop();
    }

#endif // USE_IMGUI
}

// ��ԋ߂��̓G��������
void SkillChainLightning::FindNearestEnemy(const int& index)
{
    const DirectX::XMFLOAT2 startPosition = EnemyManager::Instance().GetEnemy(index)->GetTransform()->GetCenterPosition();

    float minLength = FLT_MAX;
    int nearestEnemyIndex = 0;
    for (int enemyIndex = 0; enemyIndex < EnemyManager::Instance().GetEnemyCount(); ++enemyIndex)
    {
        if (enemyIndex == index) continue;
        // ���Ƀ��X�g�ɓo�^����Ă���G�͏��O����
        bool isContinue = false;
        for (int listIndex = 0; listIndex < enemyIndexes_.size(); ++listIndex)
        {
            if (enemyIndex == enemyIndexes_.at(listIndex)) isContinue = true;
        }
        if (isContinue) continue;

        const DirectX::XMFLOAT2 enemyPosition = EnemyManager::Instance().GetEnemy(enemyIndex)->GetTransform()->GetPosition();
        const float length = XMFloat2Length(enemyPosition - startPosition);

        if (minLength > length)
        {
            minLength = length;
            nearestEnemyIndex = enemyIndex;
        }
    }

    enemyIndexes_.emplace_back(nearestEnemyIndex);
}

void SkillChainLightning::BuildTransform(const DirectX::XMFLOAT2& positionA, const DirectX::XMFLOAT2& positionB, const DirectX::XMFLOAT2& sizeA, const int& transformIndex)
{
    const DirectX::XMFLOAT2 vec         = positionB - positionA;
    const float             length      = XMFloat2Length(vec);
    const DirectX::XMFLOAT2 direction   = XMFloat2Normalize(vec);

    // Size, TextureSize �ݒ�
    const DirectX::XMFLOAT2 size = { 200.0f, length };
    transforms_.at(transformIndex).SetSize(size);
    transforms_.at(transformIndex).SetTexSize(size);

    // Position �ݒ�
    const DirectX::XMFLOAT2 position =
    {
        positionA.x + sizeA.x * 0.5f - size.x * 0.5f,
        positionA.y + sizeA.y * 0.5f
    };
    transforms_.at(transformIndex).SetPosition(position);   
    
    // Pivot, Angle �ݒ�
    transforms_.at(transformIndex).SetPivot(size.x * 0.5f, 0.0f);
    transforms_.at(transformIndex).SetAngle(DirectX::XMConvertToDegrees(atan2f(direction.y, direction.x) - DirectX::XM_PIDIV2));
}