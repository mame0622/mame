#pragma once
#include <memory>
#include "Shader/Shader.h"

CONST LONG      SCREEN_WIDTH = 1920;
CONST LONG      SCREEN_HEIGHT = 1080;
CONST BOOL      FULLSCREEN = FALSE;
CONST LPCWSTR   APPLICATION_NAME = L"Mame";

class Graphics
{
public:
    Graphics(HWND hwnd);
    ~Graphics() {}

    static Graphics& Instance() { return *instance_; }

    void RenderInitialize();    // �`�揉����
    void Draw();                // �`����s

    ID3D11Device*           GetDevice()             const { return device_.Get(); }
    IDXGISwapChain*         GetSwapChain()          const { return swapchain_.Get(); }
    ID3D11DeviceContext*    GetDeviceContext()      const { return deviceContext_.Get(); }
    ID3D11RenderTargetView* GetRenderTargetView()   const { return renderTargetView_.Get(); }
    ID3D11DepthStencilView* GetDepthStencilView()   const { return depthStencilView_.Get(); }

    HRESULT CreateVsFromCso(const char* csoName, ID3D11VertexShader** vertexShader, ID3D11InputLayout** inputLayout, D3D11_INPUT_ELEMENT_DESC* inputElementDesc, UINT numElements) { return shader_->CreateVsFromCso(device_.Get(), csoName, vertexShader, inputLayout, inputElementDesc, numElements); }
    HRESULT CreatePsFromCso(const char* csoName, ID3D11PixelShader** pixelShader) { return shader_->CreatePsFromCso(device_.Get(), csoName, pixelShader); }
    HRESULT CreateGsFromCso(const char* csoName, ID3D11GeometryShader** geometryShader) { return shader_->CreateGsFromCso(device_.Get(), csoName, geometryShader); }
    HRESULT CreateCsFromCso(const char* csoName, ID3D11ComputeShader** computeShader) { return shader_->CreateCsFromCso(device_.Get(), csoName, computeShader); }
    HRESULT CreateDsFromCso(const char* csoName, ID3D11DomainShader** domainShader) { return shader_->CreateDsFromCso(device_.Get(), csoName, domainShader); }
    HRESULT CreateHsFromCso(const char* csoName, ID3D11HullShader** hullShader) { return shader_->CreateHsFromCso(device_.Get(), csoName, hullShader); }
    void SetDepthStencileState(const Shader::DepthState& depthStencileState) { shader_->SetDepthStencileState(deviceContext_.Get(), depthStencileState); }
    void SetBlendState(const Shader::BlendState& blendState) { shader_->SetBlendState(deviceContext_.Get(), blendState); }
    void SetRasterizerState(const Shader::RasterState& rasterizerState) { shader_->SetRasterizerState(deviceContext_.Get(), rasterizerState); }


private:
    void CreateSwapChain(const HWND& hwnd); // �X���b�v�`�F�[���쐬
    void CreateRenderTargetView();          // �����_�[�^�[�Q�b�g�r���[�쐬
    void CreateDepthStencilView();          // �f�v�X�X�e���V���r���[�쐬
    void SetViewport();                     // �r���[�|�[�g�̐ݒ�

private:
    static Graphics* instance_;
    std::unique_ptr<Shader> shader_;

    Microsoft::WRL::ComPtr<ID3D11Device>                device_;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>         deviceContext_;
    Microsoft::WRL::ComPtr<IDXGISwapChain>              swapchain_;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>      renderTargetView_;
    Microsoft::WRL::ComPtr<ID3D11Texture2D>             depthStencilBuffer_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>      depthStencilView_;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>    depthShaderResourceView_;

    DirectX::XMFLOAT4   clearColor_ = { 0.0f, 1.0f, 1.0f, 1.0f };   // �������F
    UINT                syncInterval_ = 0;                          // ��������
};