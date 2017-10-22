cbuffer CBUFFER
{
	float4x4 wvp;
};

struct VOut
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
};

Texture2D tex;
SamplerState smp;

VOut VShader(float4 position : POSITION, float2 texcoord : TEXCOORD)
{
	VOut output;

	output.position = mul(position, wvp);
	output.texcoord = texcoord;

	return output;
}

float4 PShader(VOut input) : SV_TARGET
{
	float4 pos = input.position;
	float2 uv = input.texcoord;

	return tex.Sample(smp, uv);
}