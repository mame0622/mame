#include "PlayerManager.h"

// ������
void PlayerManager::Initialize()
{
    player_->Initialize();
}

// �X�V
void PlayerManager::Update(const float& elapsedTime)
{
    player_->Update(elapsedTime);
}

// �`��
void PlayerManager::Render()
{
    player_->Render();
}

// ImGui
void PlayerManager::DrawDebug()
{
    player_->DrawDebug();
}
