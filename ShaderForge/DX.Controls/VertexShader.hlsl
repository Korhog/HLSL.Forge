cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix model;
	matrix view;
	matrix projection;
};

struct VertexShaderInput
{
	float3 pos : POSITION;
	float3 normal: NORMAL;
	float3 color : COLOR0;
};

struct VertexShaderOutput
{
	float4 pos : SV_POSITION;
	float4 world : POSITION;
	float3 normal: NORMAL;
	float3 color : COLOR0;		
};

VertexShaderOutput main(VertexShaderInput input)
{
	VertexShaderOutput output;
	float4 pos = float4(input.pos, 1.0f);

	pos = mul(pos, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	output.pos = pos;	

	output.world = mul(float4(input.pos, 1.0f), model);

	float4 normal = float4(input.normal, 1.0f);
	normal = mul(normal, model);
	output.normal = normal.xyz;

	output.color = input.color;

	return output;
}