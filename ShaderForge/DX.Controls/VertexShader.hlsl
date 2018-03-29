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
	float3 normal: NORMAL;
	float3 color : COLOR0;		
};

VertexShaderOutput main(VertexShaderInput input)
{
	VertexShaderOutput output;
	float4 pos = float4(input.pos, 1.0f);
	// Transform the vertex position into projected space.
	pos = mul(pos, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	output.pos = pos;	

	float4 normal = float4(input.normal, 1.0f);
	// Transform the vertex position into projected space.
	normal = mul(normal, model);
	normal = mul(normal, view);
	normal = mul(normal, projection);
	output.normal = normal;

	output.color = input.color;

	return output;
}