#include "EnemyCharger.h"
#include "Object/Character/Player/PlayerManager.h"
#include "ImGui/ImGuiCtrl.h"

EnemyCharger::EnemyCharger()
    :Enemy(EnemyManager::EnemyType::Charge, "EnemyCharger")
{
}

void EnemyCharger::Initialize()
{
    const float size_ = 50.0f;
    GetTransform()->SetSize(size_);
    GetTransform()->SetTexSize(size_);
    GetTransform()->SetPivot(size_ * 0.5f);

    SetCollisionRadius(25.0f);
}

void EnemyCharger::Update(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    moveVec_ = playerCenterPosition - enemyCenterPosition;

    switch (state_)
    {
    case 0:
        Pursuit(elapsedTime);
        break;
    case 1:
        ChargeAttack(elapsedTime);
        break;
    }
}

void EnemyCharger::DrawDebug()
{
    const std::string name = GetName() + std::to_string(GetObjectId());
    if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_Framed))
    {
        Object::DrawDebug();
        Character::DrawDebug();

        ImGui::TreePop();
    }
}

void EnemyCharger::Pursuit(const float& elapsedTime)
{
    moveSpeed_ = 200.0f;
    // ���񏈗�
    Turn();

    const float length = XMFloat2Length(moveVec_);

    // �ːi�U���ɐ؂�ւ��͈�
    const float chargeRange_ = 300.0f;

    if (length < chargeRange_)
    {
        state_ = 1;
        moveSpeed_ = 0;
        chargeTime_ = 0;
    }
    // �ړ�����
    Move(elapsedTime);
}

void EnemyCharger::ChargeAttack(const float& elapsedTime)
{
    // �ːi�����J�n
    chargeTime_ += elapsedTime;
    if (chargeTime_ < 2.0f)
    {
        // ���񏈗�
        Turn();

        // �ːi�X�s�[�h�ݒ�
        moveSpeed_ = 3000.0f;
    }
    else
    {
        // ����
        const float deceleration_ = 40.0f;
        moveSpeed_ -= deceleration_;
        
        // �O�����x�N�g���Z�o
        const float angleRadians = DirectX::XMConvertToRadians(GetTransform()->GetAngle());
        const DirectX::XMFLOAT2 forward = { sinf(angleRadians),-cosf(angleRadians) };
        GetTransform()->AddPosition(forward * moveSpeed_ * elapsedTime);

        if (moveSpeed_ <= 0)
        {
            moveSpeed_ = 0;
            state_ = 0;
        }
    }
}

// ���񏈗�
void EnemyCharger::Turn()
{
    const DirectX::XMFLOAT2 moveDirection = XMFloat2Normalize(moveVec_);

    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveDirection.y, moveDirection.x) + DirectX::XM_PIDIV2));
}

// �ړ�����
void EnemyCharger::Move(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 moveDirection = XMFloat2Normalize(moveVec_);

    GetTransform()->AddPosition(moveDirection * moveSpeed_ * elapsedTime);
}


