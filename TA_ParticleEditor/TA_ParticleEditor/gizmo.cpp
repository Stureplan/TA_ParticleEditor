#include "gizmo.h"

Gizmo::Gizmo()
{

}

Gizmo::~Gizmo()
{
	constantBuffer->Release();
	vertexBuffer->Release();
}

void Gizmo::VertexBuffer(ID3D11Device* device, std::vector<GIZMO_VERTEX> vtx)
{
	HRESULT hr;

	vertices = vtx;

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(D3D11_BUFFER_DESC));
	vertexDesc.ByteWidth = sizeof(GIZMO_VERTEX) * vertices.size();
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.CPUAccessFlags = 0;
	vertexDesc.MiscFlags = 0;
	vertexDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory(&vertexData, sizeof(vertexData));
	vertexData.pSysMem = vertices.data();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(&vertexDesc, &vertexData, &vertexBuffer);
}

void Gizmo::ConstantBuffer(ID3D11Device* device)
{
	/*===================================================================================*/
	// CONSTANT BUFFER VERTEX SETUP
	HRESULT hr;
	D3D11_BUFFER_DESC cb_vertex_Desc;
	ZeroMemory(&cb_vertex_Desc, sizeof(D3D11_BUFFER_DESC));
	cb_vertex_Desc.Usage = D3D11_USAGE_DEFAULT;
	cb_vertex_Desc.ByteWidth = sizeof(cBufferVertex);
	cb_vertex_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb_vertex_Desc.CPUAccessFlags = 0;
	cb_vertex_Desc.MiscFlags = 0;
	cb_vertex_Desc.StructureByteStride = 0;
	hr = device->CreateBuffer(&cb_vertex_Desc, NULL, &constantBuffer);
	/*===================================================================================*/
}

void Gizmo::UpdateConstantBuffer(ID3D11DeviceContext* context, XMMATRIX wvp)
{
	cBufferVertex.wvp = XMMatrixTranspose(wvp);
	context->UpdateSubresource(constantBuffer, 0, NULL, &cBufferVertex, 0, 0);
	context->VSSetConstantBuffers(0, 1, &constantBuffer);
}

void Gizmo::Render(ID3D11DeviceContext* context, ID3D11SamplerState* sampler, ID3D11ShaderResourceView* texture)
{
	//TODO: Remember to ChangeRasterization() before and after this.

	UINT stride;
	UINT offset;

	stride = sizeof(GIZMO_VERTEX);
	offset = 0;

	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->PSSetSamplers(0, 1, &sampler);
	context->PSSetShaderResources(0, 1, &texture);
	context->Draw(vertices.size(), 0);
}