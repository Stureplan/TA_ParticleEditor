cbuffer CBUFFER
{
	float4x4 wvp;
	float4x4 world;
	float4 campos;
	float4 camup;
};

struct VOut
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;

	float3 worldPos : NORMAL;
};

Texture2D tex;
SamplerState smp;

VOut VShader(float4 position : POSITION)
{
	VOut output;

	output.worldPos = position.xyz;
	//output.position = mul(position, wvp);
	output.position = mul(position, wvp);

	output.texcoord = float2(0,0);

	return output;
}

[maxvertexcount(4)]
void GShader(point VOut input[1], inout TriangleStream<VOut> OutputStream)
{
	float w = 5.0f;
	float h = 5.0f;

	float3 pos = input[0].worldPos;

	float3 up;
	float3 normal;
	float3 right;


	up = normalize(camup.xyz);
	up *= h;

	normal = normalize(pos - campos.xyz);
	right = normalize(cross(normal, up)) * w;
	

	float3 vtx[4];
	vtx[0] = pos - right + up;
	vtx[1] = pos - right - up;
	vtx[2] = pos + right + up;
	vtx[3] = pos + right - up;

	float2 uv[4];
	uv[0] = float2(1, 0);
	uv[1] = float2(1, 1);
	uv[2] = float2(0, 0);
	uv[3] = float2(0, 1);

	VOut output;
	for (int i = 0; i < 4; i++)
	{
		output.position.w = input[0].position.w;
		output.position.xyz = vtx[i];
		output.worldPos = vtx[i];
		output.position = mul(output.position, wvp);

		output.texcoord = uv[i];
		OutputStream.Append(output);
	}

	//OutputStream.RestartStrip();

	// 0
/*	output.position.xyz = vtx[0];
	output.texcoord = uv[0];
	OutputStream.Append(output);

	// 1
	output.position.xyz = vtx[1];
	output.texcoord = uv[1];
	OutputStream.Append(output);

	// 2
	output.position.xyz = vtx[2];
	output.texcoord = uv[2];
	OutputStream.Append(output);

	 // 3
	output.position.xyz = vtx[3];
	output.texcoord = uv[3];
	OutputStream.Append(output);*/
}

float4 PShader(VOut input) : SV_TARGET
{
	float4 pos = input.position;
	float2 uv = input.texcoord;
	return tex.Sample(smp, uv);
	//return float4(input.worldPos,1);
}