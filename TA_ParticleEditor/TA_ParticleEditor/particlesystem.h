#pragma once
#include <d3dX11.h>
#include <DirectXMath.h>
#include <string>
#include <vector>

using namespace DirectX;

struct PSys
{
	XMVECTOR velocity;
	std::string texturename;

};

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
	
	void Render();

private:
	DirectX::XMVECTOR position;
};