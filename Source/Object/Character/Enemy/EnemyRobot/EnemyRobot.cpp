#include "EnemyRobot.h"
#include "Object/Character/Player/PlayerManager.h"
#include "Object/Bullet/BulletStraight/BulletStraight.h"
#include "Object/Bullet/BulletHoming/BulletHoming.h"
#include "Object/Bullet/BulletManager.h"
#include "Input/Input.h"

EnemyRobot::EnemyRobot()
    :Enemy("EnemyRobot", EnemyManager::EnemyType::Robot,
        Collision::Type::Enemy, this, 100.0f)
{
}

// ������
void EnemyRobot::Initialize()
{
    GetTransform()->SetSize(size_);
    GetTransform()->SetTexSize(size_);
    GetTransform()->SetPivot(size_ * 0.5f);

}

// �X�V
void EnemyRobot::Update(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    moveDirection_ = XMFloat2Normalize(playerCenterPosition - enemyCenterPosition);


    // �ǐՏ���
    Pursuit(elapsedTime);

    // ���̓{�^���Ŕ��肵�Ă�(����͓G�̒e�̏����𕡐�����čU���̃X�e�[�g�ɐ؂�ւ���)
    if (Input::Instance().GetGamePad().GetButtonDown() & GamePad::BTN_LEFT_SHOULDER)
    {
        // �e�̐���
        BulletGeneration(enemyCenterPosition);
    }
}

void EnemyRobot::DrawDebug()
{
    ImGui::DragInt("Power", &power_);
}

void EnemyRobot::OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position)
{
}

// �ǐՏ���
void EnemyRobot::Pursuit(const float& elapsedTime)
{
    GetTransform()->AddPosition(moveDirection_ * moveSpeed_ * elapsedTime);
    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveDirection_.y, moveDirection_.x) + DirectX::XM_PIDIV2));
}

// �e�̐���
void EnemyRobot::BulletGeneration(const DirectX::XMFLOAT2 enemyCenterPosition)
{
    const int bulletNum = 5;

    // �����ʒu�����肷��(4�ӏ�)
    static const int generateNum = 5;
    constexpr float angle[generateNum] =
    {
        DirectX::XMConvertToRadians(50.0f), DirectX::XMConvertToRadians(-50.0f),
        DirectX::XMConvertToRadians(25.0f), DirectX::XMConvertToRadians(-25.0f),
        DirectX::XMConvertToRadians(0),
    };

    for (int generateIndex = 0; generateIndex < generateNum; ++generateIndex)
    {
        // BulletStraight* bulletStraight = new BulletStraight;

        // ���͉��Ńz�[�~���O�ƃX�g���[�g�����Ă�B�����Ƃ��ꂢ�ɂ��Ȃ�����B
        BulletHoming* bulletStraight = new BulletHoming;

        const DirectX::XMFLOAT2 newMoveDirection =
        {
            moveDirection_.x * cosf(angle[generateIndex]) - moveDirection_.y * sinf(angle[generateIndex]),
            moveDirection_.x * sinf(angle[generateIndex]) + moveDirection_.y * cosf(angle[generateIndex])
        };

        // �e�̐����ʒu�����߂�
        const DirectX::XMFLOAT2 generatePosition = enemyCenterPosition + newMoveDirection * generateOffset_;

        bulletStraight->Initialize(generatePosition);
        bulletStraight->Launch(newMoveDirection, power_);
    }
}
