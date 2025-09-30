#pragma once
#include <d3d11.h>

class BaseScene
{
public:
    BaseScene() {}
    virtual ~BaseScene() {}

    virtual void CreateResource()                   = 0; // ���\�[�X����
    virtual void Initialize()                       = 0; // ������
    virtual void Finalize()                         = 0; // �I����
    virtual void Update(const float& elapsedTime)   = 0; // �X�V
    virtual void Render()                           = 0; // �`��
    virtual void DrawDebug()                        = 0; // ImGui

public:
    [[nodiscard]] const bool IsReady() const { return isReady_; }
    void SetReady() { isReady_ = true; }

private:
    bool isReady_ = false; // ���������t���O
};