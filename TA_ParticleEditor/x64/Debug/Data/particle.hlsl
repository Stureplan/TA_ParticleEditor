cbuffer CBUFFER
{
	float4x4 wvp;
	float4x4 world;
	float4 campos;
	float4 camup;
	float4 colin;
	float4 colout;
	float2 size;
	float scalemode;
	float lifetime;
};

struct VOut
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
	float3 worldPos : NORMAL;
	float currentLifetime : LIFETIME;
};

Texture2D tex;
SamplerState smp;

//TODO: Check constant buffer PADDING / VALUES
//TODO: Semantics input

VOut VShader(float4 position : POSITION, float lifetime : LIFETIME)
{
	VOut output;

	output.worldPos = position.xyz;
	//output.position = mul(position, wvp);
	//output.position = mul(position, wvp);
	output.position = position;
	output.texcoord = float2(0,0);
	output.currentLifetime = lifetime;

	return output;
}

[maxvertexcount(4)]
void GShader(point VOut input[1], inout TriangleStream<VOut> OutputStream)
{
	float3 pos      = input[0].worldPos;
	float percent  = input[0].currentLifetime / lifetime;


	float lifetimeScale = (1 - percent) * scalemode;


	float w = size.x + lifetimeScale;
	float h = size.y + lifetimeScale;

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
		output.currentLifetime = lifetime;

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
	float lt = 1 - input.currentLifetime;
	
	float4 color = tex.Sample(smp, uv) * lerp(colin, colout, 1-lt);
	
	return color;
}