#include "INCPCTGaugeSprite.hlsli"

Texture2D g_texture : register(t0);
Texture2D g_colorTexture : register(t1);
SamplerState g_sampler : register(s0);

// �Q�l�F [Shader Graph��remap�m�[�h���֗������� - �Ȃ񂩂��](https://nanka.hateblo.jp/entry/2019/04/12/035111)
// Remap�֐�
float remap(float val, float inMin, float inMax, float outMin, float outMax)
{
    return clamp(outMin + (val - inMin) * (outMax - outMin) / (inMax - inMin), outMin, outMax);
}

float4 main(PSPCTInput input) : SV_TARGET
{
    // �x�[�X�̃e�N�X�`�����}�b�s���O
    float4 gradient = g_texture.Sample(g_sampler, input.tex);
    // ������0�`1��-Threshold�`1�Ƀ}�b�s���O
    float remapRatio = remap(Ratio, 0, 1, -Threshold, 1);
    // remapRatio��gradient.x���ׂ�
    float alpha = smoothstep(remapRatio, remapRatio + Threshold, gradient.x);
    // �Q�[�W�̐F
    float4 gaugeColor = Diffuse;
    // �O���f�[�V�����e�N�X�`��������ꍇ
    if (UseGradientTextureFlg)
    {
        // Ratio�ƌ��ɐF���擾
        gaugeColor = g_colorTexture.Sample(g_sampler, float2(Ratio, 0.0f));
    }
    // �w�i�̃A���t�@�l
    float BackgroundAlpha = IsBackground ? 1.0f : 0.0f;
    // �Q�[�W�����̐F
    float4 mainColor = (1 - alpha) > 0.0f ? float4(gaugeColor.xyz, 1.0f) : float4(0.0f, 0.0f, 0.0f, BackgroundAlpha);
    // ���̉摜�̃A���t�@��0�̏ꍇ�����I��0�ɂ���
    alpha = gradient.a > 0.0f ? 1.0f : 0.0f;
    return float4(mainColor.xyz, alpha);
}
