#include "DemoScene.h"
#include "Graphics/Graphics.h"
#include "ImGui/ImGuiCtrl.h"

// ���\�[�X����
void DemoScene::CreateResource()
{
}

// ������
void DemoScene::Initialize()
{
}

// �I����
void DemoScene::Finalize()
{
}

// �X�V
void DemoScene::Update(const float& elapsedTime)
{
}

// �`��
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
