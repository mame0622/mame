#include "EnemyMadScientist.h"
#include "Object/Character/Player/PlayerManager.h"
#include "Input/Input.h"
#include "Object/Character/Enemy/EnemyRobot/EnemyRobot.h"

EnemyMadScientist::EnemyMadScientist()
    :Enemy("EnemyMadScientist", EnemyManager::EnemyType::MadScientist,
        Collision::Type::Enemy, this, 25.0f)
{

}

void EnemyMadScientist::Initialize()
{
    GetTransform()->SetSize(size_);
    GetTransform()->SetTexSize(size_);
    GetTransform()->SetPivot(size_ * 0.5f);

    // ��
    GetTransform()->SetPosition(300.0f, 400.0f);
}

void EnemyMadScientist::Update(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    moveDirection_ = XMFloat2Normalize(playerCenterPosition - enemyCenterPosition);

    Turn();

    // ���̓{�^���Ŕ��肵�Ă�(�����HP��0�ɂȂ����u�ԓ���)
    if (Input::Instance().GetGamePad().GetButtonDown() & GamePad::BTN_LEFT_SHOULDER)
    {
        EnemyRobot* robot = new EnemyRobot;

        // ���{�b�g�̐����ʒu
        robot->GetTransform()->SetPosition((GetTransform()->GetPosition() + moveDirection_ * 300.0f) - robot->GetTransform()->GetSize() * 0.5f);

        // ���{�b�g�̔w����擾���Ă�(�����X�V�ł��ĂȂ����玟���؂���񂪗�������)
        targetPosition = (robot->GetTransform()->GetPosition() - robot->GetMoveDirection() * 300.0f) - robot->GetTransform()->GetSize() * 0.5f;
    }
    
    Move(elapsedTime);
}

void EnemyMadScientist::DrawDebug()
{

}

void EnemyMadScientist::OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position)
{

}

// ���񏈗�
void EnemyMadScientist::Turn()
{
    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveDirection_.y, moveDirection_.x) + DirectX::XM_PIDIV2));
}

void EnemyMadScientist::Move(const float& elapsedTime)
{
    // ���{�b�g�̔w��Ɍ������Ĉړ�
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 targetDirection = XMFloat2Normalize(targetPosition - enemyCenterPosition);

    GetTransform()->AddPosition(targetDirection * moveSpeed_ * elapsedTime);
}
