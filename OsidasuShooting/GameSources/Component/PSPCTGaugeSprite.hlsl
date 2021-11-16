#include "INCPCTGaugeSprite.hlsli"

Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);

// [Shader Graph‚Ìremapƒm[ƒh‚ª•Ö—˜‚¾‚Á‚½ - ‚È‚ñ‚©‚â‚é](https://nanka.hateblo.jp/entry/2019/04/12/035111)
float remap(float val, float inMin, float inMax, float outMin, float outMax)
{
    return clamp(outMin + (val - inMin) * (outMax - outMin) / (inMax - inMin), outMin, outMax);
}

float4 main(PSPCTInput input) : SV_TARGET
{
    float4 Light = (saturate(input.color) * Diffuse) + Emissive;
    Light.a = Diffuse.a;
    float4 color = g_texture.Sample(g_sampler, input.tex);
    float remapRatio = remap(Ratio, 0, 1, -Threshold, 1);
    float alpha = smoothstep(remapRatio, remapRatio + Threshold, color.x);
    alpha = color.a > 0.0f ? (1 - alpha) : 0.0f;
    return float4(color.xyz, alpha);
}

