#include "SceneManager.h"
#include "Application/Common.h"
#include "ImGui/ImGuiCtrl.h"
#include "DemoScene/DemoScene.h"
#include "TitleScene/TitleScene.h"

// ������
void SceneManager::Initilaize()
{
    SceneManager::Instance().ChangeScene(new DemoScene);
}

// �I����
void SceneManager::Finalize()
{
    // Scene�N���A
    Clear();
}

// �X�V
void SceneManager::Update(const float& elapsedTime)
{
    // ����Scene�ɐ؂�ւ���
    if (nextScene_)
    {
        // �Â�Scene���I��������
        Clear();

        // �V�����V�[����ݒ�
        currentScene_   = nextScene_;
        nextScene_      = nullptr;

        // Scene����������
        if (currentScene_->IsReady() == false)
        {
            currentScene_->CreateResource();
            currentScene_->Initialize();
        }
    }

    // ���݂�Scene�X�V����
    if (currentScene_)
    {
        currentScene_->Update(elapsedTime);
    }
}

// �`��
void SceneManager::Render()
{
    if (currentScene_ == nullptr) return;

    currentScene_->Render();
}

// ImGui
void SceneManager::DrawDebug()
{
    ImGui::Begin("SceneManager");

    if (ImGui::Button("DemoScene", ImVec2(100, 100)))
    {
        //SceneManager::Instance().ChangeScene(new DemoScene);
    }
    ImGui::SameLine();
    if (ImGui::Button("TitleScene", ImVec2(100, 100)))
    {
        //SceneManager::Instance().ChangeScene(new DemoScene);
    }

    ImGui::End();

    // �Y��Scene��ImGui
    if (currentScene_ != nullptr)
    {
        currentScene_->DrawDebug();
    }
}

// Scene�N���A
void SceneManager::Clear()
{
    if (currentScene_ == nullptr) return;

    currentScene_->Finalize();
    SafeDeletePtr(currentScene_);
}

// Scene�؂�ւ�
void SceneManager::ChangeScene(BaseScene* scene)
{
    nextScene_ = scene;
}
