#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

#include "utility.h"

class Renderable
{
public:
	virtual void VertexBuffer(ID3D11Device* device) {}
	virtual void ConstantBuffer(ID3D11Device* device) {}
	virtual void Render(ID3D11DeviceContext* context, ID3D11SamplerState* sampler, ID3D11ShaderResourceView* texture) {}

protected:
	ID3D11Buffer* constantBuffer;
	ID3D11Buffer* vertexBuffer;
};