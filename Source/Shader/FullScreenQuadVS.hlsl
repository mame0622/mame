#include "FullScreenQuad.hlsli"

PSIn main(in uint vertexid : SV_VERTEXID)
{
    PSIn vout;
    const float2 position[4] = { { -1, +1 }, { +1, +1 }, { -1, -1 }, { +1, -1 } };
    const float2 texcoords[4] = { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } };
    vout.position_ = float4(position[vertexid], 0, 1);
    vout.texcoord_ = texcoords[vertexid];
    return vout;
}