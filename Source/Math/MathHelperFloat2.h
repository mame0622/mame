#pragma once
#include <DirectXMath.h>
#include <algorithm>

// =============================================
//                  �Z�p���Z�q
// =============================================

#pragma region ---------- �Z�p���Z�q ----------
// ----- float2 + float2 -----
inline const DirectX::XMFLOAT2 operator+(
    const DirectX::XMFLOAT2& float2_1,
    const DirectX::XMFLOAT2& float2_2)
{
    const DirectX::XMFLOAT2 result =
    {
        float2_1.x + float2_2.x,
        float2_1.y + float2_2.y,
    };
    
    return result;
}

// ----- float2 += float2 -----
inline const DirectX::XMFLOAT2 operator +=(
    DirectX::XMFLOAT2& float2_1,
    const DirectX::XMFLOAT2& float2_2)
{
    float2_1.x += float2_2.x;
    float2_1.y += float2_2.y;

    return float2_1;
}

// ----- float2 - float2 -----
inline const DirectX::XMFLOAT2 operator-(
    const DirectX::XMFLOAT2& float2_1,
    const DirectX::XMFLOAT2& float2_2)
{
    const DirectX::XMFLOAT2 result =
    {
        float2_1.x - float2_2.x,
        float2_1.y - float2_2.y,
    };

    return result;
}

// ----- float2 -= float2 -----
inline const DirectX::XMFLOAT2 operator-=(
    DirectX::XMFLOAT2& float2_1,
    const DirectX::XMFLOAT2& float2_2)
{
    float2_1.x -= float2_2.x;
    float2_1.y -= float2_2.y;

    return float2_1;
}

// ----- float2 * float2 -----
inline const DirectX::XMFLOAT2 operator*(
    const DirectX::XMFLOAT2& float2_1,
    const DirectX::XMFLOAT2& float2_2)
{
    const DirectX::XMFLOAT2 result =
    {
        float2_1.x * float2_2.x,
        float2_1.y * float2_2.y,
    };

    return result;
}

// ----- float2 *= float2 -----
inline const DirectX::XMFLOAT2 operator*=(
    DirectX::XMFLOAT2& float2_1,
    const DirectX::XMFLOAT2& float2_2)
{
    float2_1.x *= float2_2.x;
    float2_1.y *= float2_2.y;

    return float2_1;
}

// ----- float2 * float -----
inline const DirectX::XMFLOAT2 operator*(
    const DirectX::XMFLOAT2& float2,
    const float& f)
{
    const DirectX::XMFLOAT2 result =
    {
        float2.x * f,
        float2.y * f,
    };

    return result;
}

// ----- float2 *= float -----
inline const DirectX::XMFLOAT2 operator*=(
    DirectX::XMFLOAT2& float2,
    const float& f)
{
    float2.x *= f;
    float2.y *= f;

    return float2;
}

// ----- float2 / float2 -----
inline const DirectX::XMFLOAT2 operator/(
    const DirectX::XMFLOAT2& float2_1,
    const DirectX::XMFLOAT2& float2_2)
{
    const DirectX::XMFLOAT2 result =
    {
        float2_1.x / float2_2.x,
        float2_1.y / float2_2.y,
    };

    return result;
}

// ----- float2 /= float2 -----
inline const DirectX::XMFLOAT2 operator/=(
    DirectX::XMFLOAT2& float2_1,
    const DirectX::XMFLOAT2& float2_2)
{
    float2_1.x /= float2_2.x;
    float2_1.y /= float2_2.y;

    return float2_1;
}

// ----- float2 / float -----
inline const DirectX::XMFLOAT2 operator/(
    const DirectX::XMFLOAT2& float2,
    const float& f)
{
    const DirectX::XMFLOAT2 result =
    {
        float2.x / f,
        float2.y / f,
    };

    return result;
}

// ----- float2 /= float -----
inline const DirectX::XMFLOAT2 operator/=(
    DirectX::XMFLOAT2& float2,
    const float& f)
{
    float2.x /= f;
    float2.y /= f;

    return float2;
}

#pragma endregion ---------- �Z�p���Z�q ----------

// =============================================
//                  �Z�p�֐�
// =============================================

#pragma region ---------- �Z�p�֐� ----------
// ----- XMFLOAT2���m�̓��ς��v�Z -----
inline const float XMFloat2Dot(
    const DirectX::XMFLOAT2& v1,
    const DirectX::XMFLOAT2& v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y);
}

// ----- XMFLOAT2���m�̋������v�Z -----
inline const float XMFloat2Length(const DirectX::XMFLOAT2& v)
{
    return ::sqrtf(XMFloat2Dot(v, v));
}

// ----- XMFLOAT2�̐��K�� ( �P�ʃx�N�g���� ) -----
inline const DirectX::XMFLOAT2 XMFloat2Normalize(const DirectX::XMFLOAT2& v)
{
    const float length = XMFloat2Length(v);

    if (length <= 0.0f) return DirectX::XMFLOAT2(0, 0);

    return (v / length);
}

// ----- XMFLOAT2���m�̊O�ς��v�Z ( ���Ԃɒ��� ) -----
inline const float XMFloat2Cross(
    const DirectX::XMFLOAT2& v1,
    const DirectX::XMFLOAT2& v2)
{
    return (v1.y * v2.x) - (v1.x * v2.y);
}

// ----- ���`��� -----
inline const DirectX::XMFLOAT2 XMFloat2Lerp(
    const DirectX::XMFLOAT2& start,
    const DirectX::XMFLOAT2& end,
    const float& timer)
{
    DirectX::XMFLOAT2 result =
    {
        start.x + timer * (end.x - start.x),
        start.y + timer * (end.y - start.y),
    };

    return result;
}

#pragma endregion ---------- �Z�p�֐� ----------