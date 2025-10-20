#include "EffectBlink.h"

EffectBlink::EffectBlink()
    : Effect("EffectBlink", EffectManager::EffectType::Blink)
{
}

void EffectBlink::Initialize(const DirectX::XMFLOAT2& centerPosition, const float& minSize, const float& maxSize)
{
    centerPosition_ = centerPosition;
    minSize_ = minSize;
    maxSize_ = maxSize;
}

// �X�V
void EffectBlink::Update(const float& elapsedTime)
{
    alpha_ -= elapsedTime;
    if (alpha_ <= 0.0f) alpha_ = 0.0f;
    
    // �����x
    GetTransform()->SetColorA(alpha_ + 0.3f);
    
    // �傫��
    const float size = XMFloatLerp(maxSize_, minSize_, alpha_);
    GetTransform()->SetSize(size);
    GetTransform()->SetTexSize(size);
    GetTransform()->SetPivot(size * 0.5f);

    // �ʒu
    const DirectX::XMFLOAT2 position = centerPosition_ - DirectX::XMFLOAT2(size, size) * 0.5f;
    GetTransform()->SetPosition(position);

    if (alpha_ <= 0.0f)
    {
        EffectManager::Instance().Remove(this);
    }
}