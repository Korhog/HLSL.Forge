
struct PixelShaderInput
{
    float3 color : COLOR0;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
    return float4(1.0f, 0.0f, 0.0f, 1.0f);
};