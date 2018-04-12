// PixelShader
struct PixelShaderInput
{	
	float4 pos   : SV_POSITION;
	float4 world : POSITION;	
	float3 normal: NORMAL;
	float3 color : COLOR;
	float2 uv	 : TEXCOORD;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
	float x = input.uv.x - 0.5f;
	float y = input.uv.y - 0.5f;

	float l = sqrt(x * x + y * y);
	if (l <= 0.5f && l >= 0.49f)
		return float4(1.0f, 0.0f, 1.0f, 1.0f);

	return float4(0.0f, 0.0f, 0.0f, 0.0f);
};