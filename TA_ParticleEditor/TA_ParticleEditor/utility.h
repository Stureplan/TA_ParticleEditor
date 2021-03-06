#pragma once
#include <string>
#include "Shlwapi.h"
#include <Windows.h>
#include <DirectXMath.h>

#include "comdef.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"

#pragma comment (lib, "Shlwapi.lib")

#define GRAVITY -9.81f
#define COLOR_WHITE		FLOAT4(1,1,1,1)
#define COLOR_PINK		FLOAT4(1,0,1,1)

#define FLOAT3_ZERO		FLOAT3(0,0,0)
#define FLOAT3_UP		FLOAT3(0,1,0)
#define FLOAT3_DOWN		FLOAT3(0,-1,0)
#define FLOAT3_LEFT		FLOAT3(-1,0,0)
#define FLOAT3_RIGHT	FLOAT3(1,0,0)


#define FLOAT4_0 FLOAT4(0,0,0,0)

#define DEFAULT_TEXTURE Utility::Path() + "Data\\Textures\\plasmaball.dds"
#define DEFAULT_NOISE_TEXTURE Utility::Path() + "Data\\Textures\\noise_cloud.dds"

using namespace DirectX;


struct FLOAT3
{
	FLOAT3() : X(0), Y(0), Z(0) { }
	FLOAT3(float x, float y, float z)
	{
		X = x; Y = y; Z = z;
	}

	FLOAT3(float value)
	{
		X = value; Y = value; Z = value;
	}

	FLOAT3 operator+(FLOAT3 const &F3)
	{
		return FLOAT3(X + F3.X, Y + F3.Y, Z + F3.Z);
	}
	FLOAT3 operator-(FLOAT3 const &F3)
	{
		return FLOAT3(X - F3.X, Y - F3.Y, Z - F3.Z);
	}

	float X, Y, Z;
};

struct FLOAT4
{
	FLOAT4() : X(0), Y(0), Z(0), W(0) { }
	FLOAT4(float x, float y, float z, float w)
	{
		X = x; Y = y; Z = z; W = w;
	}

	float X, Y, Z, W;
};


// Defines a point in world space, with colors (XYZ & RGB), used for gizmos.
struct GIZMO_VERTEX
{
	GIZMO_VERTEX(float x, float y, float z,
		float r, float g, float b)
	{
		X = x; Y = y; Z = z;
		R = r; G = g; B = b;
	}

	float X, Y, Z;
	float R, G, B;
};

struct VERTEX
{
	VERTEX(float x, float y, float z,
		float u, float v)
	{
		X = x; Y = y; Z = z;
		U = u; V = v;
	}

	float X, Y, Z;
	float U, V;
};

// Defines a point in world space (XYZ) + a lifetime (0-1).
// For our purposes it's a particle that will be used as a vertex.
struct PARTICLE_VERTEX
{
	PARTICLE_VERTEX() : position(0,0,0), direction(0,0,0), currentlifetime(0) { }
	PARTICLE_VERTEX(FLOAT3 pos, FLOAT3 dir, float cl)
	{
		position = pos;
		direction = dir;
		currentlifetime = cl;
	}

	FLOAT3 position;
	FLOAT3 direction;
	float currentlifetime;
};

struct PARTICLE
{
	PARTICLE(FLOAT3 pos, FLOAT3 dir, float cl, bool a, int rX, int rY, int tE)
	{ 
		position = pos;
		direction = dir;
		currentlifetime = cl; 
		alive = a;
		
		randX = rX;
		randY = rY;

		timesemitted = tE;
	}

	FLOAT3 position;
	FLOAT3 direction;
	float currentlifetime;
	bool alive;

	int randX;
	int randY;

	int timesemitted;
};

enum PS_PROPERTY
{
	PS_POSITION = 0,
	PS_VELOCITY,
	PS_OFFSET,
	PS_EMISSIONDELAY,
	PS_LIFETIME,
	PS_GRAVITY,
	PS_COLOR_0,
	PS_COLOR_1,
	PS_COLOR_2,
	PS_START_SIZE_X,
	PS_START_SIZE_Y,
	PS_END_SIZE_X,
	PS_END_SIZE_Y,
	PS_EMITTER_TYPE,
	PS_RECT_SIZE_X,
	PS_RECT_SIZE_Z,
	PS_ROTATION,
	PS_TEXTURE_TYPE,
	PS_TEXTURE_COLUMNS,
	PS_TEXTURE_ROWS,
	PS_LOOPING,
	PS_NOISE_DISSOLVE,
	PS_INTERPOLATION,
	PS_BLOOM_PARTICLES,
	PS_SHADER
};

enum EMITTER_TYPE
{
	EMIT_POINT = 0,
	EMIT_RECTANGLE
};

enum TEXTURE_TYPE
{
	TEXTURE = 0,
	TEXTURE_NOISE
};



struct EMITTER
{
	EMITTER()
	{
		emittertype = EMITTER_TYPE::EMIT_POINT;
		maxparticles = 0;
		velocity = FLOAT3_ZERO;
		emissiondelay = 0;
		lifetime = 0;
		gravity = 0;
		color0 = FLOAT4(1, 1, 1, 1);
		color1 = FLOAT4(1, 1, 1, 1);
		color2 = FLOAT4(1, 1, 1, 1);
		startSizeX = 1.0f;
		startSizeY = 1.0f;
		endSizeX = 1.0f;
		endSizeY = 1.0f;
		rectSizeX = 1.0f;
		rectSizeZ = 1.0f;
		rotation = 0;
		interpolation = 0;
		textureType = 0;
		textureColumns = 4;
		textureRows = 4;
		looping = 0;
		noiseDissolve = 0;
		bloomParticles = 1;
		shader = 0;
	}
	EMITTER (EMITTER_TYPE e, int m, FLOAT3 v, float ed, float lt, float grv, FLOAT4 col0, FLOAT4 col1, FLOAT4 col2, float sX, float sY, float eX, float eY, float rsX, float rsZ, float r, int i, int tT, int tC, int tR, int l, int nD, int b)
	{
		emittertype = e;
		maxparticles = m;
		velocity = v;
		emissiondelay = ed;
		lifetime = lt;
		gravity = grv;
		color0 = col0;
		color1 = col1;
		color2 = col2;
		startSizeX = sX;
		startSizeY = sY;
		endSizeX = eX;
		endSizeY = eY;
		rectSizeX = rsX;
		rectSizeZ = rsZ;
		rotation = r;
		interpolation = i;
		textureType = tT;
		textureColumns = tC;
		textureRows = tR;
		looping = l;
		noiseDissolve = nD;
		bloomParticles = b;
		shader = 0;
	}
	// PS Export variables
	EMITTER_TYPE emittertype;
	int maxparticles;
	FLOAT3 velocity;
	FLOAT3 offset;
	float emissiondelay;
	float lifetime;
	float gravity;
	FLOAT4 color0;
	FLOAT4 color1;
	FLOAT4 color2;
	float startSizeX;
	float startSizeY;
	float endSizeX;
	float endSizeY;
	float rectSizeX;
	float rectSizeZ;
	float rotation;
	int interpolation;
	int textureType;
	int textureColumns;
	int textureRows;
	int looping;
	int noiseDissolve;
	int bloomParticles;
	int shader; // 0=particle.hlsl, 1=particle_animated.hlsl, 2=particle_noise.hlsl, 3=particle_animated_noise.hlsl
};

#pragma region CONSTANT BUFFERS
struct CBUFFER_PARTICLESYSTEM
{
	XMMATRIX wvp;
	XMVECTOR campos;
	XMVECTOR camup;
	FLOAT4 col0;
	FLOAT4 col1;
	FLOAT4 col2;
	XMFLOAT2 startsize;
	XMFLOAT2 endsize;
	float rotation;
	float lifetime;
};

struct CBUFFER_PARTICLESYSTEM_ANIMATED
{
	XMMATRIX wvp;
	XMVECTOR campos;
	XMVECTOR camup;
	FLOAT4 col0;
	FLOAT4 col1;
	FLOAT4 col2;
	XMFLOAT2 startsize;
	XMFLOAT2 endsize;
	float rotation;
	float lifetime;
	int interpolation;
	int columns;
	int rows;
};

struct CBUFFER_VERTEX
{
	XMMATRIX wvp;
};
#pragma endregion







class Utility
{
public:

	static std::string Path()
	{
		std::string path = "";

		// Full path to program
		char p[MAX_PATH];
		GetModuleFileNameA(NULL, p, MAX_PATH + 1);
		std::string fullpath = p;

		// Only the .exe
		std::string f = PathFindFileNameA(fullpath.c_str());

		// Remove program.exe from full path
		fullpath.erase(fullpath.size() - f.size(), f.size());

		return fullpath;
	}

	static std::string DataPath()
	{
		std::string path = "Data\\";

		// Full path to program
		char p[MAX_PATH];
		GetModuleFileNameA(NULL, p, MAX_PATH + 1);
		std::string fullpath = p;

		// Only the .exe
		std::string f = PathFindFileNameA(fullpath.c_str());

		// Remove program.exe from full path
		fullpath.erase(fullpath.size() - f.size(), f.size());

		// Insert Data folder
		fullpath += path;

		return fullpath;
	}

	static bool FindSubstring(std::wstring str, std::wstring sub)
	{
		size_t index;

		index = str.find(sub);
		if (index != std::wstring::npos)
		{
			// Found substring
			return true;
		}

		return false;
	}
};


class DX
{
public:

	static bool LoadTexture(ID3D11Device* device, ID3D11ShaderResourceView* &texture, std::string path)
	{
		ID3D11Resource* resource = nullptr;

		HRESULT hr;

		std::wstring wide_path = std::wstring(path.begin(), path.end());
		if (Utility::FindSubstring(wide_path, L".dds") || Utility::FindSubstring(wide_path, L".DDS"))
		{
			// Found DDS in texturename
			hr = CreateDDSTextureFromFile(device, wide_path.c_str(), &resource, &texture);
		}
		else
		{
			// Didn't find DDS, so we assume it's PNG or something else
			hr = CreateWICTextureFromFile(device, wide_path.c_str(), &resource, &texture);
		}

		if (hr == S_OK) 
		{
			// Texture loaded OK
			resource->Release();
			return true;
		}
		else
		{
			// Something's bad, let's just load a default 4x4 black texture and warn the user
			std::string error = path + " not found! \nUsing a black default texture instead.";
			MessageBoxA(NULL, error.c_str(), "Texture not found!", MB_OK);
			Create4x4BlackTexture(device, texture);
			return false;
		}
	}

	static void Create4x4BlackTexture(ID3D11Device* device, ID3D11ShaderResourceView* &texture)
	{
		HRESULT hr;

		ID3D11Texture2D* tex;
		D3D11_TEXTURE2D_DESC desc;
		D3D11_SUBRESOURCE_DATA data;

		unsigned int w = 4;
		unsigned int h = 4;
		int* buffer = new int[w*h];
		for (unsigned int x = 0; x < w; x++)
		{
			for (unsigned int y = 0; y < h; y++)
			{
				buffer[x*w + y] = 0xFF000000;
			}
		}

		data.pSysMem = (void*)buffer;
		data.SysMemPitch = w * 4;
		data.SysMemSlicePitch = w * h * 4;

		desc.Width = w;
		desc.Height = h;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		hr = device->CreateTexture2D(&desc, &data, &tex);
		hr = device->CreateShaderResourceView(tex, NULL, &texture);

		delete[] buffer;
	}

	static float Dot(XMVECTOR v1, XMVECTOR v2)
	{
		XMFLOAT3 dest;
		XMStoreFloat3(&dest, XMVector3Dot(v1, v2));

		return dest.x;
	}
};