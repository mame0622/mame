#include "DemoScene.h"
#include "Graphics/Graphics.h"
#include "ImGui/ImGuiCtrl.h"

// リソース生成
void DemoScene::CreateResource()
{
}

// 初期化
void DemoScene::Initialize()
{
}

// 終了化
void DemoScene::Finalize()
{
}

// 更新
void DemoScene::Update(const float& elapsedTime)
{
}

// 描画
void DemoScene::Render()
{
    Graphics::Instance().SetBlendState(Shader::BlendState::Alpha);
    Graphics::Instance().SetRasterizerState(Shader::RasterState::CullNone);
    Graphics::Instance().SetDepthStencileState(Shader::DepthState::ZT_OFF_ZW_OFF);

    player_.Render();
}

// ImGui
void DemoScene::DrawDebug()
{
    player_.DrawDebug();
}
