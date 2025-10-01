#include "DemoScene.h"
#include "Graphics/Graphics.h"
#include "ImGui/ImGuiCtrl.h"
#include "Object/Character/Player/PlayerManager.h"

// リソース生成
void DemoScene::CreateResource()
{
    // Player生成
    PlayerManager::Instance().GetPlayer() = std::make_unique<Player>();
}

// 初期化
void DemoScene::Initialize()
{
    PlayerManager::Instance().Initialize();
}

// 終了化
void DemoScene::Finalize()
{
}

// 更新
void DemoScene::Update(const float& elapsedTime)
{
    PlayerManager::Instance().Update(elapsedTime);
}

// 描画
void DemoScene::Render()
{
    Graphics::Instance().SetBlendState(Shader::BlendState::Alpha);
    Graphics::Instance().SetRasterizerState(Shader::RasterState::CullNone);
    Graphics::Instance().SetDepthStencileState(Shader::DepthState::ZT_OFF_ZW_OFF);

    PlayerManager::Instance().Render();
}

// ImGui
void DemoScene::DrawDebug()
{
    PlayerManager::Instance().DrawDebug();
}
