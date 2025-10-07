#include "EnemyPlanaria.h"
#include "Object/Character/Player/PlayerManager.h"
#include "Object/Character/Enemy/EnemyNormal/EnemyNormal.h"
#include <Input/Input.h>

EnemyPlanaria::EnemyPlanaria()
    :Enemy("EnemyPlanaria", EnemyManager::EnemyType::Planaria)
{
}

// ‰Šú‰»
void EnemyPlanaria::Initialize()
{
    const float size = 100.0f;
    GetTransform()->SetSize(size);
    GetTransform()->SetTexSize(size);
    GetTransform()->SetPivot(size * 0.5f);

    SetCollisionRadius(50.0f);
}

// XVˆ—
void EnemyPlanaria::Update(const float& elapsedTime)
{
    // ’ÇÕˆ—
    Pursuit(elapsedTime);

    // ¡‚Íƒ{ƒ^ƒ“‚Å”»’è‚µ‚Ä‚é(¡Œã‚ÍHP‚ª0‚É‚È‚Á‚½uŠÔ“ü‚é)
    if (Input::Instance().GetGamePad().GetButtonDown() & GamePad::BTN_X)
    {
        // •ª—ô‘Ì‚Ì”
        const int numberOfSplits = 3;

        for (int i = 0; i < numberOfSplits; ++i)
        {
            EnemyNormal* enemy = new EnemyNormal();
            // ¶¬ˆÊ’uİ’è
            enemy->GetTransform()->SetPositionX(GetTransform()->GetPosition().x + i);
            enemy->GetTransform()->SetPositionY(GetTransform()->GetPosition().y);
            
            // “o˜^
            EnemyManager::Instance().Register(enemy);
        }
        // ”jŠü
        EnemyManager::Instance().Remove(this);
    }


}

// ImGui
void EnemyPlanaria::DrawDebug()
{
}

// ’ÇÕˆ—
void EnemyPlanaria::Pursuit(const float& elapsedTime)
{
    const DirectX::XMFLOAT2 playerCenterPosition = PlayerManager::Instance().GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 enemyCenterPosition = GetTransform()->GetCenterPosition();
    const DirectX::XMFLOAT2 moveVec = XMFloat2Normalize(playerCenterPosition - enemyCenterPosition);

    GetTransform()->AddPosition(moveVec * moveSpeed_ * elapsedTime);
    GetTransform()->SetAngle(DirectX::XMConvertToDegrees(atan2f(moveVec.y, moveVec.x) + DirectX::XM_PIDIV2));
}
