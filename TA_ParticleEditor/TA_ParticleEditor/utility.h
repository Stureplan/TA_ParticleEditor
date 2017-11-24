#pragma once
#include <string>
#include "Shlwapi.h"
#include <Windows.h>
#include <DirectXMath.h>

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


using namespace DirectX;


struct FLOAT3
{
	FLOAT3() : X(0), Y(0), Z(0) { }
	FLOAT3(float x, float y, float z)
	{
		X = x; Y = y; Z = z;
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
	PARTICLE(FLOAT3 pos, FLOAT3 dir, float cl, bool a, int rX, int rY)
	{ 
		position = pos;
		direction = dir;
		currentlifetime = cl; 
		alive = a;
		
		randX = rX;
		randY = rY;
	}

	FLOAT3 position;
	FLOAT3 direction;
	float currentlifetime;
	bool alive;

	int randX;
	int randY;
};

enum PS_PROPERTY
{
	PS_POSITION = 0,
	PS_VELOCITY,
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
	PS_TEXTURE_TYPE,
	PS_TEXTURE_COLUMNS,
	PS_TEXTURE_ROWS
};

enum EMITTER_TYPE
{
	EMIT_POINT = 0,
	EMIT_RECTANGLE
};

struct PARTICLESYSTEM
{
	PARTICLESYSTEM(){}
	PARTICLESYSTEM(EMITTER_TYPE e, int m, FLOAT3 v, float ed, float lt, float grv, FLOAT4 col0, FLOAT4 col1, FLOAT4 col2, float sX, float sY, float eX, float eY, float rsX, float rsZ, int tT, int tC, int tR)
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
		textureType = tT;
		textureColumns = tC;
		textureRows = tR;
	}
	// PS Export variables
	EMITTER_TYPE emittertype;
	int maxparticles;
	FLOAT3 velocity;
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
	int textureType;
	int textureColumns;
	int textureRows;
};

#pragma region CONSTANT BUFFERS
struct CBUFFER_PARTICLESYSTEM
{
	XMMATRIX wvp;
	XMMATRIX world;
	XMVECTOR campos;
	XMVECTOR camup;
	FLOAT4 col0;
	FLOAT4 col1;
	FLOAT4 col2;
	XMFLOAT2 startsize;
	XMFLOAT2 endsize;
	float lifetime;
};

struct CBUFFER_PARTICLESYSTEM_ANIMATED
{
	XMMATRIX wvp;
	XMMATRIX world;
	XMVECTOR campos;
	XMVECTOR camup;
	FLOAT4 col0;
	FLOAT4 col1;
	FLOAT4 col2;
	XMFLOAT2 startsize;
	XMFLOAT2 endsize;
	float lifetime;
	int columns;
	int rows;
};
#pragma endregion

struct CBUFFER_VERTEX
{
	XMMATRIX wvp;
};







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