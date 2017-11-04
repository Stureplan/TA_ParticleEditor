cbuffer CBUFFER
{
	float4x4 wvp;
};

struct VOut
{
	float4 position : SV_POSITION;
	nointerpolation float3 color : COLOR;
};

Texture2D tex;
SamplerState smp;

VOut VShader(float4 position : POSITION, float3 color : COLOR)
{
	VOut output;

	output.position = mul(position, wvp);
	output.color = color;

	return output;
}

float4 PShader(VOut input) : SV_TARGET
{
	float4 pos = input.position;
	float3 col = input.color;

	return float4(col, 1.0);
}