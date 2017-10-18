#pragma once

#include <dxgi.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <DirectXMath.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")

using namespace DirectX;

class Graphics
{
public:
	void Initialize();
	void Render();
private:
	//ParticleSystem ps;

};