#include <compiled_includes.hlsli>

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
};

struct VOut
{
	float4 position : SV_POSITION;
	float3 direction : DIRECTION;
	float2 texcoord : TEXCOORD;
	float currentLifetime : LIFETIME;
};

Texture2D particleTexture : register(t0);
Texture2D noiseTexture : register(t1);
SamplerState smp;

float4 triple_lerp(float4 c1, float4 c2, float4 c3, float t) 
{
	float y1 = t * 2.0;
	float y2 = t * 2.0 - 1.0;

	float4 g, g2, g3;

	g = lerp(c1, c2, y1) * step(y1, 1.0);
	g2 = lerp(c2, c3, y2) * step(y2, 1.0) * step(1.0, y1);

	g = g + g2;
	return g;
}

VOut VShader(float4 position : POSITION, float3 direction : DIRECTION, float lifetime : LIFETIME)
{
	VOut output;

	output.position = position;
	output.direction = direction;
	output.texcoord = float2(0,0);
	output.currentLifetime = lifetime;

	return output;
}

float3 rotate(float3 pos, float3 dir, float d)
{
	// Specify the angle in radians:
	float angle = d * 3.14 / 180.0; // 90 degrees, CCW

	float3 q;
	q.x = pos.x * (dir.x*dir.x * (1.0 - cos(angle)) + cos(angle))
		+ pos.y * (dir.x*dir.y * (1.0 - cos(angle)) + dir.z * sin(angle))
		+ pos.z * (dir.x*dir.z * (1.0 - cos(angle)) - dir.y * sin(angle));

	q.y = pos.x * (dir.y*dir.x * (1.0 - cos(angle)) - dir.z * sin(angle))
		+ pos.y * (dir.y*dir.y * (1.0 - cos(angle)) + cos(angle))
		+ pos.z * (dir.y*dir.z * (1.0 - cos(angle)) + dir.x * sin(angle));

	q.z = pos.x * (dir.z*dir.x * (1.0 - cos(angle)) + dir.y * sin(angle))
		+ pos.y * (dir.z*dir.y * (1.0 - cos(angle)) - dir.x * sin(angle))
		+ pos.z * (dir.z*dir.z * (1.0 - cos(angle)) + cos(angle));

	return q;
}

[maxvertexcount(4)]
void GShader(point VOut input[1], inout TriangleStream<VOut> OutputStream)
{
	float3 pos      = input[0].position.xyz;
	float3 dir		= input[0].direction.xyz;
	float percent	= input[0].currentLifetime / lifetime;

	float2 scale = lerp(startsize, endsize, percent);


	float w = scale.x;
	float h = scale.y;

	float3 up;
	float3 normal;
	float3 right;


	up = normalize(dir);//normalize(camup.xyz);
	up = normalize(camup.xyz);
	up *= h;

	normal = normalize(pos - campos.xyz);
	right = normalize(cross(normal, up)) * w;
	

	//TODO: This is the golden ticket.
	//Keep working on this rotation to get a good back and forth.
	//TODO: Implement all these features (noise, rotation, includes) in all shaders.
	float d = percent * 100;
	up = rotate(up, normal, d);
	right = rotate(right, normal, d);

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
		
		
		output.currentLifetime = percent;
		output.direction = dir;

		output.position.xyz = vtx[i];
		output.position = mul(output.position, wvp);


		
		output.texcoord = uv[i];
		OutputStream.Append(output);
	}
}

float4 PShader(VOut input) : SV_TARGET
{
	float4 pos = input.position;
	float2 uv = input.texcoord;
	float lt = input.currentLifetime;
	
#ifdef NOISE
	uv -= ((noiseTexture.Sample(smp, uv).xy) - 0.5) * 2 * 0.2 * lt;
#endif
	
	float4 color = particleTexture.Sample(smp, uv) * triple_lerp(col0, col1, col2, lt);

	return color;
}