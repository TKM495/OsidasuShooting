#include "INCPCTGaugeSprite.hlsli"

Texture2D g_texture : register(t0);
Texture2D g_colorTexture : register(t1);
SamplerState g_sampler : register(s0);

// [Shader Graph��remap�m�[�h���֗������� - �Ȃ񂩂��](https://nanka.hateblo.jp/entry/2019/04/12/035111)
float remap(float val, float inMin, float inMax, float outMin, float outMax)
{
    return clamp(outMin + (val - inMin) * (outMax - outMin) / (inMax - inMin), outMin, outMax);
}

float4 main(PSPCTInput input) : SV_TARGET
{
    // Diffuse��Emissive��K�p
    float4 Light = (saturate(input.color) * Diffuse) + Emissive;
    Light.a = Diffuse.a;
    // �x�[�X�̃e�N�X�`�����}�b�s���O
    float4 color = g_texture.Sample(g_sampler, input.tex);
    // ������0�`1��-Threshold�`1�Ƀ}�b�s���O
    float remapRatio = remap(Ratio, 0, 1, -Threshold, 1);
    // remapRatio��color.x���ׂ�
    float alpha = smoothstep(remapRatio, remapRatio + Threshold, color.x);
    // ���̉摜�̃A���t�@��0�̏ꍇ�����I��0�ɂ���
    alpha = color.a > 0.0f ? (1 - alpha) : 0.0f;
    // Ratio�ƌ��ɐF���擾
    float3 gaugeColor = g_colorTexture.Sample(g_sampler, float2(Ratio, 0.0f));
    return float4(gaugeColor, alpha);
}

