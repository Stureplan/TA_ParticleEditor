#pragma once
#include <string>
#include "Shlwapi.h"
#include <Windows.h>
#include <DirectXMath.h>


#pragma comment (lib, "Shlwapi.lib")

using namespace DirectX;


// Defines a point in world space (XYZ).
// For our purposes it's a particle that will be used as a vertex.
struct POSITION
{
	POSITION() : X(0), Y(0), Z(0) { }
	POSITION(float x, float y, float z)
	{
		X = x; Y = y; Z = z;
	}

	float X, Y, Z;
};

struct PARTICLE
{
	PARTICLE(POSITION pos, float cl, bool a)
	{ 
		position = pos;
		currentlifetime = cl; 
		active = a; 
	}

	POSITION position;
	float currentlifetime;
	bool active;
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