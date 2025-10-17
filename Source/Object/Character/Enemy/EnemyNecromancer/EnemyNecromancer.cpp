#include "EnemyNecromancer.h"
#include "Object/Character/Player/PlayerManager.h"
#include "Object/Character/Enemy/EnemyNormal/EnemyNormal.h"
#include "Input/Input.h"

EnemyNecromancer::EnemyNecromancer()
    :Enemy("EnemyNecromancer", EnemyManager::EnemyType::Necromancer,
        Collision::Type::Enemy, this, 50.0f)
{

}

void EnemyNecromancer::Initialize()
{
    GetTransform()->SetSize(size_);
    GetTransform()->SetTexSize(size_);
    GetTransform()->SetPivot(size_ * 0.5f);

    GetTransform()->SetPosition(400.0f, 300.0f);
}

void EnemyNecromancer::Update(const float& elapsedTime)
{
    // 進行方向ベクトル算出
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    moveVec_ = playerCenterPosition - enemyCenterPosition;

    generationTime_ += elapsedTime;

    switch (state_)
    {
    case State::Pursuit:
        // 追跡処理
        Pursuit(elapsedTime);

        if (generationTime_ > 3.0f)
        {
            generationTime_ = 0;
            moveSpeed_ = 0;
            state_ = State::Necromancy;
        }
        break;
    case State::Necromancy:

        Turn();

        if (generationTime_ > 2.0f)
        {
            UndeadGeneration();
            generationTime_ = 0;
            moveSpeed_ = 100;
            state_ = State::Pursuit;
        }
        break;
    }

}

void EnemyNecromancer::DrawDebug()
{

}

// 衝突検知
void EnemyNecromancer::OnHit(const Collision::Type& type, const DirectX::XMFLOAT2& position)
{
}

// 追跡処理
void EnemyNecromancer::Pursuit(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 moveDirection = XMFloat2Normalize(moveVec_);

    GetTransform()->AddPosition(moveDirection * moveSpeed_ * elapsedTime);
    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveDirection.y, moveDirection.x) + DirectX::XM_PIDIV2));
}

// 旋回処理
void EnemyNecromancer::Turn()
{
    const DirectX::XMFLOAT2 moveDirection = XMFloat2Normalize(moveVec_);

    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveDirection.y, moveDirection.x) + DirectX::XM_PIDIV2));
}

void EnemyNecromancer::UndeadGeneration()
{
    const DirectX::XMFLOAT2 moveDirection = XMFloat2Normalize(moveVec_);
    const DirectX::XMFLOAT3 up = { 0.0f,1.0f,0.0f };
    const DirectX::XMFLOAT3 moveVec3 = { moveDirection.x,0.0f,moveDirection.y };
    const DirectX::XMVECTOR Up = DirectX::XMLoadFloat3(&up);
    const DirectX::XMVECTOR MoveVec3 = DirectX::XMLoadFloat3(&moveVec3);
    const DirectX::XMVECTOR RightVec3 = DirectX::XMVector3Cross(Up, MoveVec3);
    DirectX::XMFLOAT3 rightVec3;
    DirectX::XMStoreFloat3(&rightVec3, RightVec3);
    const DirectX::XMFLOAT2 rightVec = { rightVec3.x, rightVec3.z };
    const DirectX::XMFLOAT2 rightDirection = XMFloat2Normalize(rightVec);
    const DirectX::XMFLOAT2 diagonallyVec = XMFloat2Normalize(moveDirection + rightVec);

    // 右上
    const DirectX::XMFLOAT2 fr = XMFloat2Normalize(moveDirection + rightVec);
    // 右下
    const DirectX::XMFLOAT2 fl = XMFloat2Normalize(rightVec - moveDirection);
    // 左上
    const DirectX::XMFLOAT2 br = XMFloat2Normalize(moveDirection - rightVec);
    // 左下
    const DirectX::XMFLOAT2 bl = XMFloat2Normalize(fr * -1.0f);

    // 生成する敵の数
    const int undead = 4;

    for (int i = 0; i < undead; ++i)
    {
        EnemyNormal* enemy = new EnemyNormal();

        if (i == 0) {
            // 生成位置設定
            enemy->GetTransform()->SetPositionX(GetTransform()->GetPosition().x + GetTransform()->GetPivotX() * 0.5f + (fr.x * 100.0f));
            enemy->GetTransform()->SetPositionY(GetTransform()->GetPosition().y + GetTransform()->GetPivotY() * 0.5f + (fr.y * 100.0f));
        }
        else if (i == 1)
        {
            enemy->GetTransform()->SetPositionX(GetTransform()->GetPosition().x + GetTransform()->GetPivotX() * 0.5f + (fl.x * 100.0f));
            enemy->GetTransform()->SetPositionY(GetTransform()->GetPosition().y + GetTransform()->GetPivotY() * 0.5f + (fl.y * 100.0f));
        }
        else if (i == 2)
        {
            enemy->GetTransform()->SetPositionX(GetTransform()->GetPosition().x + GetTransform()->GetPivotX() * 0.5f + (br.x * 100.0f));
            enemy->GetTransform()->SetPositionY(GetTransform()->GetPosition().y + GetTransform()->GetPivotY() * 0.5f + (br.y * 100.0f));
        }
        else if (i == 3)
        {
            enemy->GetTransform()->SetPositionX(GetTransform()->GetPosition().x + GetTransform()->GetPivotX() * 0.5f + (bl.x * 100.0f));
            enemy->GetTransform()->SetPositionY(GetTransform()->GetPosition().y + GetTransform()->GetPivotY() * 0.5f + (bl.y * 100.0f));
        }
    }
}
