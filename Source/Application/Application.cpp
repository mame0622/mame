#include "Application.h"
#include "Scene/SceneManager.h"
#include "Graphics/PostProcess/PostProcess.h"

// �R���X�g���N�^
Application::Application(HWND hwnd)
    : hwnd_(hwnd), graphics_(hwnd), input_(hwnd)
{
}

// ������
const bool Application::Initialize()
{
    // Input�����ݒ�
    input_.GetMouse().SetScreenWidth(SCREEN_WIDTH);
    input_.GetMouse().SetScreenHeight(SCREEN_HEIGHT);

    // Scene������
    SceneManager::Instance().Initilaize();

    return true;
}

// �I����
const bool Application::Finalize()
{
    // Scene�I����
    SceneManager::Instance().Finalize();

    return false;
}

// �X�V
void Application::Update(const float& elapsedTime)
{
    // ImGui�X�V
    IMGUI_CTRL_CLEAR_FRAME();

    // ���͍X�V
    input_.Update();

    // Scene�X�V
    SceneManager::Instance().Update(elapsedTime);

    // ImGui
    DrawDebug();
}

// �`��
void Application::Render()
{
    // �`�揉����
    graphics_.RenderInitialize();

    PostProcess::Instance().Activate();

    // Scene�`��
    SceneManager::Instance().Render();

    PostProcess::Instance().Deactivate();
    PostProcess::Instance().Draw();

    // ImGui�`��
    IMGUI_CTRL_DISPLAY();

    // �`����s
    graphics_.Draw();
}

// ImGui
void Application::DrawDebug()
{
#if USE_IMGUI
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGuiWindowFlags windowFlags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus |
        ImGuiWindowFlags_MenuBar |
        ImGuiWindowFlags_NoDocking;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin("MainDockSpace", nullptr, windowFlags);
    ImGui::PopStyleVar(2);

    ImGuiID dockSpaceID = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockSpaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

    ImGui::End();

    // Scene
    SceneManager::Instance().DrawDebug();

    PostProcess::Instance().DrawDebug();

#endif // USE_IMGUI
}

// ���s
const int Application::Run()
{
    MSG msg = {};

    if (Initialize() == false) return 0;

    // ImGui������(DirectX11�̏������̉��ɒu������)
    IMGUI_CTRL_INITIALIZE(hwnd_, graphics_.GetDevice(), graphics_.GetDeviceContext());

    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            tictoc_.Tick();
            CalculateFrameStats();
            Update(tictoc_.TimeInterval());
            Render();
        }
    }

    // ImGui�I����
    IMGUI_CTRL_UNINITIALIZE();

    BOOL fullscreen = 0;
    graphics_.GetSwapChain()->GetFullscreenState(&fullscreen, 0);
    if (fullscreen)
    {
        graphics_.GetSwapChain()->SetFullscreenState(FALSE, 0);
    }

    return Finalize() ? static_cast<int>(msg.wParam) : 0;
}

LRESULT Application::HandleMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    // ImGui
    IMGUI_CTRL_WND_PRC_HANDLER(hwnd, msg, wparam, lparam);

    switch (msg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps{};
        BeginPaint(hwnd, &ps);

        EndPaint(hwnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_CREATE:
        break;
    case WM_KEYDOWN:
        if (wparam == VK_ESCAPE)
        {
            PostQuitMessage(0);
        }
        break;
    case WM_ENTERSIZEMOVE:
        tictoc_.Stop();
        break;
    case WM_EXITSIZEMOVE:
        tictoc_.Start();
        break;
    default:
        return DefWindowProc(hwnd, msg, wparam, lparam);
    }

    return 0;
}

// �t���[���v�Z
void Application::CalculateFrameStats()
{
    if (++frames_, (tictoc_.TimeStamp() - elapsedTime_) >= 1.0f)
    {
        float fps = static_cast<float>(frames_);
        std::wostringstream outs;
        outs.precision(6);

        // �Q�[���^�C�g��
        outs << APPLICATION_NAME;

        // FPS
        outs << L" FPS : " << fps << L" / " << L"Frame Time : " << 1000.0f / fps << L" (ms)";

        SetWindowTextW(hwnd_, outs.str().c_str());

        frames_ = 0;
        elapsedTime_ += 1.0f;
    }
}
