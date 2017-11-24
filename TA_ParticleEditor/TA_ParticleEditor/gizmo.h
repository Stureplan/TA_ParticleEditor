#pragma once
#include <vector>

#include "renderable.h"


class Gizmo : public Renderable
{
public:
	Gizmo();
	~Gizmo();

	void VertexBuffer(ID3D11Device* device, std::vector<GIZMO_VERTEX> vtx);
	void ConstantBuffer(ID3D11Device* device);
	void UpdateConstantBuffer(ID3D11DeviceContext* context, XMMATRIX wvp);
	void Render(ID3D11DeviceContext* context, ID3D11SamplerState* sampler, ID3D11ShaderResourceView* texture);

private:
	std::vector <GIZMO_VERTEX> vertices;
	CBUFFER_VERTEX cBufferVertex;
};