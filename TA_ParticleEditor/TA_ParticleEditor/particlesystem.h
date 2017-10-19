#pragma once
#include <d3dX11.h>
#include <DirectXMath.h>

using namespace DirectX;

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
	
	void Render();

private:


	DirectX::XMVECTOR position;
};