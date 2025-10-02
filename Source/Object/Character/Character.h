#pragma once
#include "Object/Object.h"

class Character : public Object
{
public:
    Character() {}
    ~Character() override {}

    // ë¨ìxéÊìæ
    const DirectX::XMFLOAT2 GetVelocity() const { return velosity_; }

    // ë¨ìxê›íË
    void SetVelocity(const DirectX::XMFLOAT2& velosity) { velosity_ = velosity; }
    
private:
    DirectX::XMFLOAT2 velosity_;

};

