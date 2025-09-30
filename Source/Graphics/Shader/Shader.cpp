#include "Shader.h"
#include <fstream>
#include "Application/Misc.h"

Shader::Shader(ID3D11Device* device)
{
    // �e��X�e�[�g�쐬
    CreateBlendStates(device);        // �u�����h�X�e�[�g
    CreateRasterizerStates(device);   // ���X�^���C�U�[�X�e�[�g
    CreateDepthStencilStates(device); // �f�v�X�X�e���V���X�e�[�g
    CreateSamplerStates(device);      // �T���v���[�X�e�[�g
}

// �T���v���[�X�e�[�g �Z�b�g
void Shader::SetSamplerState(ID3D11DeviceContext* deviceContext)
{
    deviceContext->PSSetSamplers(0, 1, samplerStates_[static_cast<size_t>(SamplerState::Point)].GetAddressOf());
    deviceContext->PSSetSamplers(1, 1, samplerStates_[static_cast<size_t>(SamplerState::Linear)].GetAddressOf());
    deviceContext->PSSetSamplers(2, 1, samplerStates_[static_cast<size_t>(SamplerState::Anisotropic)].GetAddressOf());
    deviceContext->PSSetSamplers(3, 1, samplerStates_[static_cast<size_t>(SamplerState::LinearBorderBlack)].GetAddressOf());
    deviceContext->PSSetSamplers(4, 1, samplerStates_[static_cast<size_t>(SamplerState::LinearBorderWhite)].GetAddressOf());
    deviceContext->PSSetSamplers(5, 1, samplerStates_[static_cast<size_t>(SamplerState::Comparison)].GetAddressOf());
}

#pragma region �e��X�e�[�g�쐬
// �u�����h�X�e�[�g�쐬
void Shader::CreateBlendStates(ID3D11Device* device)
{
    HRESULT             result      = S_OK;
    D3D11_BLEND_DESC    blendDesc   = {};

    blendDesc.AlphaToCoverageEnable                 = FALSE;
    blendDesc.IndependentBlendEnable                = FALSE;
    blendDesc.RenderTarget[0].BlendEnable           = FALSE;
    blendDesc.RenderTarget[0].SrcBlend              = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].DestBlend             = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    result = device->CreateBlendState(&blendDesc, blendStates_[static_cast<int>(BlendState::None)].GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));

    blendDesc.AlphaToCoverageEnable                 = FALSE;
    blendDesc.IndependentBlendEnable                = FALSE;
    blendDesc.RenderTarget[0].BlendEnable           = TRUE;
    blendDesc.RenderTarget[0].SrcBlend              = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    result = device->CreateBlendState(&blendDesc, blendStates_[static_cast<int>(BlendState::Alpha)].GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));

    blendDesc.AlphaToCoverageEnable                 = FALSE;
    blendDesc.IndependentBlendEnable                = FALSE;
    blendDesc.RenderTarget[0].BlendEnable           = TRUE;
    blendDesc.RenderTarget[0].SrcBlend              = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend             = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    result = device->CreateBlendState(&blendDesc, blendStates_[static_cast<int>(BlendState::Add)].GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));

    blendDesc.AlphaToCoverageEnable                 = FALSE;
    blendDesc.IndependentBlendEnable                = FALSE;
    blendDesc.RenderTarget[0].BlendEnable           = TRUE;
    blendDesc.RenderTarget[0].SrcBlend              = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].DestBlend             = D3D11_BLEND_SRC_COLOR;
    blendDesc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_DEST_ALPHA;
    blendDesc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    result = device->CreateBlendState(&blendDesc, blendStates_[static_cast<int>(BlendState::Multiply)].GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));
}

// ���X�^���C�U�[�X�e�[�g�쐬
void Shader::CreateRasterizerStates(ID3D11Device* device)
{
    HRESULT                 result = S_OK;
    D3D11_RASTERIZER_DESC   rasterizerDesc = {};

    rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_BACK;
    rasterizerDesc.FrontCounterClockwise = TRUE;
    rasterizerDesc.DepthBias = 0;
    rasterizerDesc.DepthBiasClamp = 0;
    rasterizerDesc.SlopeScaledDepthBias = 0;
    rasterizerDesc.DepthClipEnable = TRUE;
    rasterizerDesc.ScissorEnable = FALSE;
    rasterizerDesc.MultisampleEnable = FALSE;
    rasterizerDesc.AntialiasedLineEnable = FALSE;
    result = device->CreateRasterizerState(&rasterizerDesc, rasterizerStates_[static_cast<size_t>(RasterState::Solid)].GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));

    rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
    rasterizerDesc.CullMode = D3D11_CULL_BACK;
    rasterizerDesc.AntialiasedLineEnable = TRUE;
    result = device->CreateRasterizerState(&rasterizerDesc, rasterizerStates_[static_cast<size_t>(RasterState::Wireframe)].GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));

    rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_NONE;
    rasterizerDesc.AntialiasedLineEnable = TRUE;
    result = device->CreateRasterizerState(&rasterizerDesc, rasterizerStates_[static_cast<size_t>(RasterState::CullNone)].GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));

    rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
    rasterizerDesc.CullMode = D3D11_CULL_NONE;
    rasterizerDesc.AntialiasedLineEnable = TRUE;
    result = device->CreateRasterizerState(&rasterizerDesc, rasterizerStates_[static_cast<size_t>(RasterState::WireframeCullNone)].GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));
}

// �f�v�X�X�e���V���X�e�[�g�쐬
void Shader::CreateDepthStencilStates(ID3D11Device* device)
{
    HRESULT                     result = S_OK;
    D3D11_DEPTH_STENCIL_DESC    depthStencilDesc = {};

    // �[�x�e�X�g�F�I���@�[�x���C�g�F�I��
    depthStencilDesc.DepthEnable = TRUE;	                        // �[�x�e�X�g��L���ɂ���
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;   // �[�x�X�e���V�� �o�b�t�@�[�ւ̏������݂�L���ɂ���
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;  // �[�x�f�[�^�Ɗ����f�[�^���r����֐�
    result = device->CreateDepthStencilState(&depthStencilDesc, depthStencilStates_[static_cast<int>(DepthState::ZT_ON_ZW_ON)].GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));

    // �[�x�e�X�g�F�I���@�[�x���C�g�F�I�t
    depthStencilDesc.DepthEnable = TRUE;                         // �[�x�e�X�g��L���ɂ���
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;  // �[�x�X�e���V�� �o�b�t�@�[�ւ̏������݂𖳌��ɂ���
    result = device->CreateDepthStencilState(&depthStencilDesc, depthStencilStates_[static_cast<int>(DepthState::ZT_ON_ZW_OFF)].GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));

    // �[�x�e�X�g�F�I�t�@�[�x���C�g�F�I��
    depthStencilDesc.DepthEnable = FALSE;                        // �[�x�e�X�g�𖳌��ɂ���
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;   // �[�x�X�e���V�� �o�b�t�@�[�ւ̏������݂�L���ɂ���
    result = device->CreateDepthStencilState(&depthStencilDesc, depthStencilStates_[static_cast<int>(DepthState::ZT_OFF_ZW_ON)].GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));

    // �[�x�e�X�g�F�I�t�@�[�x���C�g�F�I�t
    depthStencilDesc.DepthEnable = FALSE;                        // �[�x�e�X�g�𖳌��ɂ���
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;  // �[�x�X�e���V�� �o�b�t�@�[�ł̏������݂𖳌��ɂ���
    result = device->CreateDepthStencilState(&depthStencilDesc, depthStencilStates_[static_cast<int>(DepthState::ZT_OFF_ZW_OFF)].GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));
}

// �T���v���[�X�e�[�g�쐬
void Shader::CreateSamplerStates(ID3D11Device* device)
{
    HRESULT             result      = S_OK;
    D3D11_SAMPLER_DESC  samplerDesc = {};

    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MipLODBias = 0;
    samplerDesc.MaxAnisotropy = 16;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    samplerDesc.BorderColor[0] = 0;
    samplerDesc.BorderColor[1] = 0;
    samplerDesc.BorderColor[2] = 0;
    samplerDesc.BorderColor[3] = 0;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    result = device->CreateSamplerState(&samplerDesc, samplerStates_[static_cast<size_t>(SamplerState::Point)].GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));

    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    result = device->CreateSamplerState(&samplerDesc, samplerStates_[static_cast<size_t>(SamplerState::Linear)].GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));

    samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    result = device->CreateSamplerState(&samplerDesc, samplerStates_[static_cast<size_t>(SamplerState::Anisotropic)].GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));

    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.BorderColor[0] = 0;
    samplerDesc.BorderColor[1] = 0;
    samplerDesc.BorderColor[2] = 0;
    samplerDesc.BorderColor[3] = 0;
    result = device->CreateSamplerState(&samplerDesc, samplerStates_[static_cast<size_t>(SamplerState::LinearBorderBlack)].GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));

    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.BorderColor[0] = 1;
    samplerDesc.BorderColor[1] = 1;
    samplerDesc.BorderColor[2] = 1;
    samplerDesc.BorderColor[3] = 1;
    result = device->CreateSamplerState(&samplerDesc, samplerStates_[static_cast<size_t>(SamplerState::LinearBorderWhite)].GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));

    samplerDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.MipLODBias = 0;
    samplerDesc.MaxAnisotropy = 16;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
    samplerDesc.BorderColor[0] = 1;
    samplerDesc.BorderColor[1] = 1;
    samplerDesc.BorderColor[2] = 1;
    samplerDesc.BorderColor[3] = 1;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    result = device->CreateSamplerState(&samplerDesc, samplerStates_[static_cast<size_t>(SamplerState::Comparison)].GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));
}

#pragma endregion �e��X�e�[�g�쐬

#pragma region �V�F�[�_�[�쐬�֐� 
// ���_�V�F�[�_�[ 
HRESULT Shader::CreateVsFromCso(ID3D11Device* device, const char* csoName, ID3D11VertexShader** vertexShader, ID3D11InputLayout** inputLayout, D3D11_INPUT_ELEMENT_DESC* inputElementDesc, UINT numElements)
{
    HRESULT result = S_OK;

    FILE* fp = nullptr;
    fopen_s(&fp, csoName, "rb");
    _ASSERT_EXPR_A(fp, "CSO File not found");

    fseek(fp, 0, SEEK_END);
    long cso_sz = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    std::unique_ptr<unsigned char[]>cso_data = std::make_unique<unsigned char[]>(cso_sz);
    fread(cso_data.get(), cso_sz, 1, fp);
    fclose(fp);

    result = device->CreateVertexShader(cso_data.get(), cso_sz, nullptr, vertexShader);
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));

    if (inputLayout)
    {
        result = device->CreateInputLayout(inputElementDesc, numElements, cso_data.get(), cso_sz, inputLayout);
        _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));
    }

    return result;
}

// �s�N�Z���V�F�[�_�[ 
HRESULT Shader::CreatePsFromCso(ID3D11Device* device, const char* csoName, ID3D11PixelShader** pixelShader)
{
    HRESULT result = S_OK;

    FILE* fp = nullptr;
    fopen_s(&fp, csoName, "rb");
    _ASSERT_EXPR_A(fp, "CSO File not found");

    fseek(fp, 0, SEEK_END);
    long cso_sz = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    std::unique_ptr<unsigned char[]>cso_data = std::make_unique<unsigned char[]>(cso_sz);
    fread(cso_data.get(), cso_sz, 1, fp);
    fclose(fp);

    result = device->CreatePixelShader(cso_data.get(), cso_sz, nullptr, pixelShader);
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));

    return result;
}

// �W�I���g���V�F�[�_�[ 
HRESULT Shader::CreateGsFromCso(ID3D11Device* device, const char* csoName, ID3D11GeometryShader** geometryShader)
{
    HRESULT         result = S_OK;

    FILE* fp = nullptr;
    fopen_s(&fp, csoName, "rb");
    _ASSERT_EXPR_A(fp, "CSO File not found");

    fseek(fp, 0, SEEK_END);
    long csoSz = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    std::unique_ptr<unsigned char[]> csoData = std::make_unique<unsigned char[]>(csoSz);
    fread(csoData.get(), csoSz, 1, fp);
    fclose(fp);

    result = device->CreateGeometryShader(csoData.get(), csoSz, nullptr, geometryShader);
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));

    return result;
}

// �R���s���[�g�V�F�[�_�[ 
HRESULT Shader::CreateCsFromCso(ID3D11Device* device, const char* csoName, ID3D11ComputeShader** computeShader)
{
    HRESULT result = S_OK;

    FILE* fp = nullptr;
    fopen_s(&fp, csoName, "rb");
    _ASSERT_EXPR_A(fp, "CSO File not found");

    fseek(fp, 0, SEEK_END);
    long csoSz = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    std::unique_ptr<unsigned char[]> csoData = std::make_unique<unsigned char[]>(csoSz);
    fread(csoData.get(), csoSz, 1, fp);
    fclose(fp);

    result = device->CreateComputeShader(csoData.get(), csoSz, nullptr, computeShader);
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));

    return result;
}

// �h���C���V�F�[�_�[ 
HRESULT Shader::CreateDsFromCso(ID3D11Device* device, const char* csoName, ID3D11DomainShader** domainShader)
{
    HRESULT result = S_OK;

    FILE* fp = nullptr;
    fopen_s(&fp, csoName, "rb");
    _ASSERT_EXPR_A(fp, "CSO File not found");

    fseek(fp, 0, SEEK_END);
    long csoSz = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    std::unique_ptr<unsigned char[]> csoData = std::make_unique<unsigned char[]>(csoSz);
    fread(csoData.get(), csoSz, 1, fp);
    fclose(fp);

    result = device->CreateDomainShader(csoData.get(), csoSz, nullptr, domainShader);
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));

    return result;
}

// �n���V�F�[�_�[ 
HRESULT Shader::CreateHsFromCso(ID3D11Device* device, const char* csoName, ID3D11HullShader** hullShader)
{
    HRESULT result = S_OK;

    FILE* fp = nullptr;
    fopen_s(&fp, csoName, "rb");
    _ASSERT_EXPR_A(fp, "CSO File not found");

    fseek(fp, 0, SEEK_END);
    long csoSz = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    std::unique_ptr<unsigned char[]> csoData = std::make_unique<unsigned char[]>(csoSz);
    fread(csoData.get(), csoSz, 1, fp);
    fclose(fp);

    result = device->CreateHullShader(csoData.get(), csoSz, nullptr, hullShader);
    _ASSERT_EXPR(SUCCEEDED(result), HRTrace(result));

    return result;
}

#pragma endregion �V�F�[�_�[�쐬�֐�