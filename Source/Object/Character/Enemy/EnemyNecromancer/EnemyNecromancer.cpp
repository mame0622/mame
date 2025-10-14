#include "EnemyNecromancer.h"
#include "Object/Character/Player/PlayerManager.h"
#include "Object/Character/Enemy/EnemyNormal/EnemyNormal.h"

EnemyNecromancer::EnemyNecromancer()
    :Enemy("EnemyNecromancer", EnemyManager::EnemyType::Necromancer,
        Collision::Type::Enemy, this, 25.0f)
{

}

void EnemyNecromancer::Initialize()
{
    const float size = 100.0f;
    GetTransform()->SetSize(size);
    GetTransform()->SetTexSize(size);
    GetTransform()->SetPivot(size * 0.5f);

    SetCollisionRadius(50.0f);
}

void EnemyNecromancer::Update(const float& elapsedTime)
{
    // 進行方向ベクトル算出
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    moveVec_ = playerCenterPosition - enemyCenterPosition;

    generationTime_ += elapsedTime;

    Pursuit(elapsedTime);

    
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

void EnemyNecromancer::UndeadGeneration()
{
    // 生成する敵の数
    const int undead = 4;

    for (int i = 0; i < undead; i++)
    {
        EnemyNormal* enemy = new EnemyNormal();
        // 生成位置設定
        enemy->GetTransform()->SetPositionX(GetTransform()->GetPosition().x);
        enemy->GetTransform()->SetPositionY(GetTransform()->GetPosition().y);

        // 登録
        EnemyManager::Instance().Register(enemy);
    }
}
