#pragma once
#include "BaseScene.h"

class SceneManager
{
private:
    SceneManager() {}
    ~SceneManager() {}

public:
    static SceneManager& Instance()
    {
        static SceneManager instance;
        return instance;
    }

public:
    void Initilaize();                      // ������
    void Finalize();                        // �I����
    void Update(const float& elapsedTime);  // �X�V
    void Render();                          // �`��
    void DrawDebug();                       // ImGui

    void Clear();                           // Scene�N���A
    void ChangeScene(BaseScene* scene);     // Scene�؂�ւ�

private:
    BaseScene* currentScene_    = nullptr; // ���݂�Scene
    BaseScene* nextScene_       = nullptr; // ����Scene
};

