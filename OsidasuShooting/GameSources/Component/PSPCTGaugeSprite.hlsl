#include "INCPCTGaugeSprite.hlsli"

Texture2D g_texture : register(t0);
Texture2D g_colorTexture : register(t1);
SamplerState g_sampler : register(s0);

// 参考： [Shader Graphのremapノードが便利だった - なんかやる](https://nanka.hateblo.jp/entry/2019/04/12/035111)
// Remap関数
float remap(float val, float inMin, float inMax, float outMin, float outMax)
{
    return clamp(outMin + (val - inMin) * (outMax - outMin) / (inMax - inMin), outMin, outMax);
}

float4 main(PSPCTInput input) : SV_TARGET
{
    // ベースのテクスチャをマッピング
    float4 gradient = g_texture.Sample(g_sampler, input.tex);
    // 割合の0～1を-Threshold～1にマッピング
    float remapRatio = remap(Ratio, 0, 1, -Threshold, 1);
    // remapRatioとgradient.xを比べる
    float alpha = smoothstep(remapRatio, remapRatio + Threshold, gradient.x);
    // ゲージの色
    float4 gaugeColor = Diffuse;
    // グラデーションテクスチャがある場合
    if (UseGradientTextureFlg)
    {
        // Ratioと元に色を取得
        gaugeColor = g_colorTexture.Sample(g_sampler, float2(Ratio, 0.0f));
    }
    // 背景のアルファ値
    float BackgroundAlpha = IsBackground ? 1.0f : 0.0f;
    // ゲージ部分の色
    float4 mainColor = (1 - alpha) > 0.0f ? float4(gaugeColor.xyz, 1.0f) : float4(0.0f, 0.0f, 0.0f, BackgroundAlpha);
    // 元の画像のアルファが0の場合強制的に0にする
    alpha = gradient.a > 0.0f ? 1.0f : 0.0f;
    return float4(mainColor.xyz, alpha);
}
