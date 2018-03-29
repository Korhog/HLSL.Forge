// PixelShader
struct PixelShaderInput
{
    float3 color : COLOR0;	
	float3 normal: NORMAL;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
	return float4(input.normal, 1.0f);
};