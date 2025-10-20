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

    GetTransform()->SetPosition(300.0f, 400.0f);
}

// �X�V
void EnemyRobot::Update(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    moveDirection_ = XMFloat2Normalize(playerCenterPosition - enemyCenterPosition);


    // �ǐՏ���
    Pursuit(elapsedTime);

    const int bulletNum = 5;

    const DirectX::XMFLOAT3 up = { 0.0f,1.0f,0.0f };
    const DirectX::XMFLOAT3 moveVec3 = { moveDirection_.x,0.0f,moveDirection_.y };
    const DirectX::XMVECTOR Up = DirectX::XMLoadFloat3(&up);
    const DirectX::XMVECTOR MoveVec3 = DirectX::XMLoadFloat3(&moveVec3);
    const DirectX::XMVECTOR RightVec3 = DirectX::XMVector3Cross(Up, MoveVec3);
    DirectX::XMFLOAT3 rightVec3;
    DirectX::XMStoreFloat3(&rightVec3, RightVec3);
    const DirectX::XMFLOAT2 rightVec = { rightVec3.x, rightVec3.z };
    const DirectX::XMFLOAT2 rightDirection = XMFloat2Normalize(rightVec);
    const DirectX::XMFLOAT2 diagonallyVec = XMFloat2Normalize(moveDirection_ + rightVec);

    // �E��
    const DirectX::XMFLOAT2 fr = XMFloat2Normalize(moveDirection_ + rightDirection);
    // �E��̔���
    const DirectX::XMFLOAT2 frh = XMFloat2Normalize(moveDirection_ + rightDirection * 0.45f);
    // �E��
    const DirectX::XMFLOAT2 fl = XMFloat2Normalize(rightDirection - moveDirection_);
    // ����
    const DirectX::XMFLOAT2 br = XMFloat2Normalize(moveDirection_ - rightDirection);
    // �����̔���
    const DirectX::XMFLOAT2 brh = XMFloat2Normalize(moveDirection_ - rightDirection * 0.45f);
    // ����
    const DirectX::XMFLOAT2 bl = XMFloat2Normalize(fr * -1.0f);

    // ���̓{�^���Ŕ��肵�Ă�(�����HP��0�ɂȂ����u�ԓ���)
    if (Input::Instance().GetGamePad().GetButtonDown() & GamePad::BTN_LEFT_SHOULDER)
    {
        for (int i = 0; i < bulletNum; ++i)
        {
             BulletStraight* bulletStraight = new BulletStraight;

            // ���͉��Ńz�[�~���O�ƃX�g���[�g�����Ă�B�����Ƃ��ꂢ�ɂ��Ȃ�����B
            // BulletHoming* bulletStraight = new BulletHoming;
            BulletManager::Instance().Register(bulletStraight);

            // �e�̐����ʒu�����߂�
            const DirectX::XMFLOAT2 generatePosition = enemyCenterPosition + moveDirection_ * generateOffset_;

            if (i == 0)
            {
                bulletStraight->Initialize(enemyCenterPosition + fr * generateOffset_);
                bulletStraight->Launch(fr);
            }
            else if (i == 1)
            {
                bulletStraight->Initialize(enemyCenterPosition + frh * generateOffset_);
                bulletStraight->Launch(frh);
            }
            else if (i == 2)
            {
                bulletStraight->Initialize(generatePosition);
                bulletStraight->Launch(moveDirection_);
            }
            else if (i == 3)
            {
                bulletStraight->Initialize(enemyCenterPosition + brh * generateOffset_);
                bulletStraight->Launch(brh);
            }
            else if (i == 4)
            {
                bulletStraight->Initialize(enemyCenterPosition + br * generateOffset_);
                bulletStraight->Launch(br);
            }
        }
    }

}

void EnemyRobot::DrawDebug()
{
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
