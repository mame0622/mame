#include "EnemyPlanaria.h"
#include "Object/Character/Player/PlayerManager.h"
#include "Object/Character/Enemy/EnemyNormal/EnemyNormal.h"
#include <Input/Input.h>

EnemyPlanaria::EnemyPlanaria()
    :Enemy("EnemyPlanaria", EnemyManager::EnemyType::Planaria)
{
}

// ������
void EnemyPlanaria::Initialize()
{
    const float size = 100.0f;
    GetTransform()->SetSize(size);
    GetTransform()->SetTexSize(size);
    GetTransform()->SetPivot(size * 0.5f);

    SetCollisionRadius(50.0f);
}

// �X�V����
void EnemyPlanaria::Update(const float& elapsedTime)
{
    // �ǐՏ���
    Pursuit(elapsedTime);

    // ���̓{�^���Ŕ��肵�Ă�(�����HP��0�ɂȂ����u�ԓ���)
    if (Input::Instance().GetGamePad().GetButtonDown() & GamePad::BTN_X)
    {
        // �����̂̐�
        const int numberOfSplits = 3;

        for (int i = 0; i < numberOfSplits; ++i)
        {
            EnemyNormal* enemy = new EnemyNormal();
            // �����ʒu�ݒ�
            enemy->GetTransform()->SetPositionX(GetTransform()->GetPosition().x + i);
            enemy->GetTransform()->SetPositionY(GetTransform()->GetPosition().y);
            
            // �o�^
            EnemyManager::Instance().Register(enemy);
        }
        // �j��
        EnemyManager::Instance().Remove(this);
    }


}

// ImGui
void EnemyPlanaria::DrawDebug()
{
}

// �ǐՏ���
void EnemyPlanaria::Pursuit(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 moveVec = XMFloat2Normalize(playerCenterPosition - enemyCenterPosition);

    GetTransform()->AddPosition(moveVec * moveSpeed_ * elapsedTime);
    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveVec.y, moveVec.x) + DirectX::XM_PIDIV2));
}
