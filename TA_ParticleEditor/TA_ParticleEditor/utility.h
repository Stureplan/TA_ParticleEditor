#pragma once
#include <string>
#include "Shlwapi.h"
#include <Windows.h>
#include <DirectXMath.h>

#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"

#pragma comment (lib, "Shlwapi.lib")



#define GRAVITY -9.81f
#define DELTA_TIME 0.016f
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
	PS_COLOR_IN,
	PS_COLOR_OUT,
	PS_SIZE_X,
	PS_SIZE_Y,
	PS_EMITTER_TYPE,
	PS_RECT_SIZE_X,
	PS_RECT_SIZE_Z,
	PS_SCALE_MODE
};

enum EMITTER_TYPE
{
	EMIT_POINT = 0,
	EMIT_RECTANGLE
};

struct PARTICLESYSTEM
{
	PARTICLESYSTEM(){}
	PARTICLESYSTEM(EMITTER_TYPE e, int m, FLOAT3 v, float ed, float lt, float grv, FLOAT4 colIn, FLOAT4 colOut, float sX, float sY, float rsX, float rsZ, float sM)
	{
		emittertype = e;
		maxparticles = m;
		velocity = v;
		emissiondelay = ed;
		lifetime = lt;
		gravity = grv;
		colorIn = colIn;
		colorOut = colOut;
		sizeX = sX;
		sizeY = sY;
		rectSizeX = rsX;
		rectSizeZ = rsZ;
		scalemode = sM;
	}
	// PS Export variables
	EMITTER_TYPE emittertype;
	int maxparticles;
	FLOAT3 velocity;
	float emissiondelay;
	float lifetime;
	float gravity;
	FLOAT4 colorIn;
	FLOAT4 colorOut;
	float sizeX;
	float sizeY;
	float rectSizeX;
	float rectSizeZ;
	float scalemode;
};






// Defines a point in world space, with colors (XYZ & RGB).
// For our purposes it's a vertex that is used in combination with other
// vertices to form a quad plane.
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

	static bool LoadTexture(ID3D11Device* device, ID3D11Resource* resource, ID3D11ShaderResourceView* &texture, std::string path)
	{
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
			return true; 
		}
		return false;
	}

	static float Dot(XMVECTOR v1, XMVECTOR v2)
	{
		XMFLOAT3 dest;
		XMStoreFloat3(&dest, XMVector3Dot(v1, v2));

		return dest.x;
	}
};