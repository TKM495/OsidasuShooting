#include "INCPCTGaugeSprite.hlsli"

Texture2D g_texture : register(t0);
Texture2D g_colorTexture : register(t1);
SamplerState g_sampler : register(s0);

// [Shader Graphのremapノードが便利だった - なんかやる](https://nanka.hateblo.jp/entry/2019/04/12/035111)
float remap(float val, float inMin, float inMax, float outMin, float outMax)
{
    return clamp(outMin + (val - inMin) * (outMax - outMin) / (inMax - inMin), outMin, outMax);
}

float4 main(PSPCTInput input) : SV_TARGET
{
    // DiffuseとEmissiveを適用
    float4 Light = (saturate(input.color) * Diffuse) + Emissive;
    Light.a = Diffuse.a;
    // ベースのテクスチャをマッピング
    float4 color = g_texture.Sample(g_sampler, input.tex);
    // 割合の0～1を-Threshold～1にマッピング
    float remapRatio = remap(Ratio, 0, 1, -Threshold, 1);
    // remapRatioとcolor.xを比べる
    float alpha = smoothstep(remapRatio, remapRatio + Threshold, color.x);
    // 元の画像のアルファが0の場合強制的に0にする
    alpha = color.a > 0.0f ? (1 - alpha) : 0.0f;
    // Ratioと元に色を取得
    float3 gaugeColor = g_colorTexture.Sample(g_sampler, float2(Ratio, 0.0f));
    return float4(gaugeColor, alpha);
}

