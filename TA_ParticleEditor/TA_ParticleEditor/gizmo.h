#pragma once
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>

#include "utility.h"

class Gizmo
{
public:
	Gizmo();
	~Gizmo();

	void VertexBuffer(ID3D11Device* device, std::vector<GIZMO_VERTEX> vtx);
	void ConstantBuffer(ID3D11Device* device);
	void UpdateConstantBuffer(ID3D11DeviceContext* context, XMMATRIX wvp);
	void Render(ID3D11DeviceContext* context, ID3D11SamplerState* sampler, ID3D11ShaderResourceView* texture);

private:
	ID3D11Buffer* constantBuffer;
	ID3D11Buffer* vertexBuffer;

	std::vector <GIZMO_VERTEX> vertices;
	CBUFFER_VERTEX cBufferVertex;
};