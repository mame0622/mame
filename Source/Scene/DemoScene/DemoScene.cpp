#include "DemoScene.h"
#include "Graphics/Graphics.h"
#include "ImGui/ImGuiCtrl.h"
#include "Object/Character/Player/PlayerManager.h"
#include "Object/Character/Enemy/EnemyManager.h"
#include "Object/Bullet/BulletManager.h"
#include "Collision/CollisionManager.h"

// ���\�[�X����
void DemoScene::CreateResource()
{
    // Player����
    PlayerManager::Instance().GetPlayer() = std::make_unique<Player>();
}

// ������
void DemoScene::Initialize()
{
    PlayerManager::Instance().Initialize();
}

// �I����
void DemoScene::Finalize()
{
    EnemyManager::Instance().Finalize();
}

// �X�V
void DemoScene::Update(const float& elapsedTime)
{
    PlayerManager::Instance().Update(elapsedTime);

    EnemyManager::Instance().Update(elapsedTime);

    BulletManager::Instance().Update(elapsedTime);

    CollisionManager::Instance().Update();
}

// �`��
void DemoScene::Render()
{
    Graphics::Instance().SetBlendState(Shader::BlendState::Alpha);
    Graphics::Instance().SetRasterizerState(Shader::RasterState::CullNone);
    Graphics::Instance().SetDepthStencileState(Shader::DepthState::ZT_OFF_ZW_OFF);

    PlayerManager::Instance().Render();

    EnemyManager::Instance().Render();

    BulletManager::Instance().Render();
}

// ImGui
void DemoScene::DrawDebug()
{
    PlayerManager::Instance().DrawDebug();

    EnemyManager::Instance().DrawDebug();

    BulletManager::Instance().DrawDebug();
}
