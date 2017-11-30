#include <compiled_includes.hlsli>
#include <functions.hlsli>

cbuffer CBUFFER
{
	float4x4 wvp;
	float4x4 world;
	float4 campos;
	float4 camup;
	float4 col0;
	float4 col1;
	float4 col2;
	float2 startsize;
	float2 endsize;
	float lifetime;

	int columns;
	int rows;
};

struct VOut
{
	float4 position : SV_POSITION;
	float3 direction : DIRECTION;
	float2 texcoord0 : TEXCOORD0;
	float currentLifetime : LIFETIME;
	float2 texcoord1 : TEXCOORD1;
	float framePercent : FOG;
};

Texture2D particleTexture;
Texture2D noiseTexture;
SamplerState smp;

VOut VShader(float4 position : POSITION, float3 direction : DIRECTION, float lifetime : LIFETIME)
{
	VOut output;

	output.position = position;
	output.direction = direction;
	output.texcoord0 = float2(0, 0);
	output.currentLifetime = lifetime;
	output.texcoord1 = float2(0, 0);
	output.framePercent = 0.0f;

	return output;
}

[maxvertexcount(4)]
void GShader(point VOut input[1], inout TriangleStream<VOut> OutputStream)
{
	float3 pos = input[0].position.xyz;
	float3 dir = input[0].direction.xyz;
	float percent = input[0].currentLifetime / lifetime;

	unsigned int totalframes = columns * rows;
	unsigned int currentframe = totalframes * percent;
	unsigned int nextframe = currentframe + 1;
	float framePercent = rescale(percent, (float)currentframe / totalframes, (float)nextframe / totalframes);

	float2 scale = lerp(startsize, endsize, percent);


	float w = scale.x;
	float h = scale.y;

	float3 up;
	float3 normal;
	float3 right;


	up = normalize(camup.xyz);//normalize(camup.xyz);
	up *= h;

	normal = normalize(pos - campos.xyz);
	right = normalize(cross(normal, up)) * w;


	float3 vtx[4];
	vtx[0] = pos - right + up;
	vtx[1] = pos - right - up;
	vtx[2] = pos + right + up;
	vtx[3] = pos + right - up;

	float2 cellUV;
	cellUV.x = (float)(currentframe % rows) / (float)rows;
	cellUV.y = floor(currentframe / columns) / (float)columns;

	float2 uv0[4];
	uv0[0] = cellUV + float2(1.0f / (float)rows, 0.0f / (float)columns);
	uv0[1] = cellUV + float2(1.0f / (float)rows, 1.0f / (float)columns);
	uv0[2] = cellUV + float2(0.0f / (float)rows, 0.0f / (float)columns);
	uv0[3] = cellUV + float2(0.0f / (float)rows, 1.0f / (float)columns);


	float2 nextCellUV;
	nextCellUV.x = (float)(nextframe % rows) / (float)rows;
	nextCellUV.y = floor(nextframe / columns) / (float)columns;

	float2 uv1[4];
	uv1[0] = nextCellUV + float2(1.0f / (float)rows, 0.0f / (float)columns);
	uv1[1] = nextCellUV + float2(1.0f / (float)rows, 1.0f / (float)columns);
	uv1[2] = nextCellUV + float2(0.0f / (float)rows, 0.0f / (float)columns);
	uv1[3] = nextCellUV + float2(0.0f / (float)rows, 1.0f / (float)columns);

	VOut output;

	for (int i = 0; i < 4; i++)
	{
		output.position.w = input[0].position.w;
		output.currentLifetime = percent;
		output.direction = dir;

		output.position.xyz = vtx[i];
		output.position = mul(output.position, wvp);
		output.texcoord0 = uv0[i];
		output.texcoord1 = uv1[i];
		output.framePercent = framePercent;

		OutputStream.Append(output);
	}
}

float4 PShader(VOut input) : SV_TARGET
{
	float4 pos = input.position;
	float2 uv0 = input.texcoord0;
	float2 uv1 = input.texcoord1;
	float framePercent = input.framePercent;
	float lt = input.currentLifetime;

	float4 color;

#ifdef INTERPOLATE
	float4 color0 = particleTexture.Sample(smp, uv0) * triple_lerp(col0, col1, col2, lt);
	float4 color1 = particleTexture.Sample(smp, uv1) * triple_lerp(col0, col1, col2, lt);
	color = lerp(color0, color1, framePercent);
#else
	color = particleTexture.Sample(smp, uv0) * triple_lerp(col0, col1, col2, lt);
#endif


#ifdef NOISE
	float2 noiseUV = uv0;
	noiseUV.x *= rows;
	noiseUV.y *= columns;
	noiseUV.y += (lt * 0.2);
	float4 noise = noiseTexture.Sample(smp, noiseUV);
	color.a *= floor(1 - lt + smoothstep(0, 1, noise.r));
#endif

	return color;
}




// sample noise texture in VS
//uint3 sam = uint3(currentframe, 0, 0);
//float4 c = noiseTexture.Load(sam);
//	
//dir.x = c.x;
//dir.y = c.y;
//dir.z = c.z;
