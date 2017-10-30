#pragma once
#include <string>
#include "Shlwapi.h"
#include <Windows.h>
#include <DirectXMath.h>


#pragma comment (lib, "Shlwapi.lib")



#define GRAVITY -9.81f
#define DELTA_TIME 0.016f


using namespace DirectX;


struct FLOAT3
{
	FLOAT3() : X(0), Y(0), Z(0) { }
	FLOAT3(float x, float y, float z)
	{
		X = x; Y = y; Z = z;
	}

	float X, Y, Z;
};

struct COLOR
{
	COLOR() : R(0), G(0), B(0), A(0) { }
	COLOR(float r, float g, float b, float a)
	{
		R = r; G = g; B = b; A = a;
	}

	float R, G, B, A;
};

// Defines a point in world space (XYZ) + a lifetime (0-1).
// For our purposes it's a particle that will be used as a vertex.
struct PARTICLE_VERTEX
{
	PARTICLE_VERTEX() : position(0,0,0), currentlifetime(0) { }
	PARTICLE_VERTEX(FLOAT3 pos, float cl)
	{
		position = pos;
		currentlifetime = cl;
	}

	FLOAT3 position;
	float currentlifetime;
};

struct PARTICLE
{
	PARTICLE(FLOAT3 pos, float cl, bool a)
	{ 
		position = pos;
		currentlifetime = cl; 
		alive = a;
	}

	FLOAT3 position;
	float currentlifetime;
	bool alive;
};

enum PS_PROPERTY
{
	PS_POSITION = 0,
	PS_VELOCITY,
	PS_EMISSIONDELAY,
	PS_LIFETIME,
	PS_GRAVITY,
	PS_COLOR_IN,
	PS_COLOR_OUT
};

struct PARTICLESYSTEM
{
	PARTICLESYSTEM(FLOAT3 pos, int m, FLOAT3 v, float ed, float lt, float grv, std::string tex, COLOR colIn, COLOR colOut)
	{
		position = pos;
		maxparticles = m;
		velocity = v;
		emissiondelay = ed;
		lifetime = lt;
		gravity = grv;
		texturename = tex;
		colorIn = colIn;
		colorOut = colOut;
	}
	// PS Export variables
	FLOAT3 position;
	int maxparticles;
	FLOAT3 velocity;
	float emissiondelay;
	float lifetime;
	float gravity;
	std::string texturename;
	COLOR colorIn;
	COLOR colorOut;
};






// Defines a point in world space, with UV coordinates (XYZ & UV).
// For our purposes it's a vertex that is used in combination with other
// vertices to form a quad plane.
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

	static float Dot(XMVECTOR v1, XMVECTOR v2)
	{
		XMFLOAT3 dest;
		XMStoreFloat3(&dest, XMVector3Dot(v1, v2));

		return dest.x;
	}


};