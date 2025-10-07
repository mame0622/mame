#include "EnemyCharger.h"
#include "Object/Character/Player/PlayerManager.h"
#include "ImGui/ImGuiCtrl.h"

EnemyCharger::EnemyCharger()
    :Enemy("EnemyCharger", EnemyManager::EnemyType::Charger)
{
}

// ������
void EnemyCharger::Initialize()
{
    const float size = 50.0f;
    GetTransform()->SetSize(size);
    GetTransform()->SetTexSize(size);
    GetTransform()->SetPivot(size * 0.5f);

    SetCollisionRadius(25.0f);
}

// �X�V����
void EnemyCharger::Update(const float& elapsedTime)
{
    // �i�s�����x�N�g���Z�o
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    moveVec_ = playerCenterPosition - enemyCenterPosition;

    switch (state_)
    {
    case State::Pursuit:
        // �ǐՏ���
        Pursuit(elapsedTime);
        break;
    case State::ChargeAttack:
        // �ːi�U��
        ChargeAttack(elapsedTime);
        break;
    }
}
// ImGui
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

// �ǐՏ���
void EnemyCharger::Pursuit(const float& elapsedTime)
{
    moveSpeed_ = 200.0f;
    // ���񏈗�
    Turn();

    const float length = XMFloat2Length(moveVec_);

    // �ːi�U���ɐ؂�ւ��͈�
    const float chargeRange = 300.0f;

    //�X�e�[�g�X�V
    if (length < chargeRange)
    {
        moveSpeed_ = 0;
        chargeTime_ = 0;
        state_ = State::ChargeAttack;
    }

    // �ړ�����
    Move(elapsedTime);
}

// �ːi����
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
        const float deceleration = 20.0f;
        moveSpeed_ -= deceleration;
        
        // �O�����x�N�g���Z�o
        const float angleRadians = DirectX::XMConvertToRadians(GetTransform()->GetAngle());
        const DirectX::XMFLOAT2 forward = { sinf(angleRadians),-cosf(angleRadians) };
        GetTransform()->AddPosition(forward * moveSpeed_ * elapsedTime);

        // �X�e�[�g�X�V
        if (moveSpeed_ <= 0)
        {
            moveSpeed_ = 0;
            state_ = State::Pursuit;
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


