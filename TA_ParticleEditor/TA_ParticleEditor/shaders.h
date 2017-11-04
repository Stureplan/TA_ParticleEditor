#pragma once

#include <string>
#include <d3d11.h>
#include <d3dx11.h>


class Shaders
{
public:
	enum RENDER_TYPE
	{
		GIZMO = 0,
		PARTICLE
	};


	void LoadGizmoShader(ID3D11Device* device, ID3D11DeviceContext* context)
	{
		std::string shaderpath = Utility::Path();

		shaderpath.insert(shaderpath.size(), "Data\\gizmo.hlsl");

		HRESULT hr;
		ID3D10Blob* blob;

		blob = NULL;
		hr = D3DX11CompileFromFileA(shaderpath.c_str(), 0, 0, "VShader", "vs_4_0", 0, 0, 0, &ObjectVS, &blob, 0);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(blob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "VS Error", MB_OK);
		}

		blob = NULL;
		hr = D3DX11CompileFromFileA(shaderpath.c_str(), 0, 0, "PShader", "ps_4_0", 0, 0, 0, &ObjectPS, &blob, 0);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(blob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "PS Error", MB_OK);
		}


		hr = device->CreateVertexShader(ObjectVS->GetBufferPointer(), ObjectVS->GetBufferSize(), NULL, &pObjectVS);
		hr = device->CreatePixelShader(ObjectPS->GetBufferPointer(), ObjectPS->GetBufferSize(), NULL, &pObjectPS);



		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",	   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }

		};

		hr = device->CreateInputLayout(ied, sizeof(ied) / sizeof(ied[0]), 
									   ObjectVS->GetBufferPointer(),
									   ObjectVS->GetBufferSize(), 
									   &pObjectLayout);
		


	}



	void LoadParticleShader(ID3D11Device* device, ID3D11DeviceContext* context)
	{
		std::string shaderpath = Utility::Path();

		shaderpath.insert(shaderpath.size(), "Data\\particle.hlsl");

		HRESULT hr;
		ID3D10Blob* blob;

		blob = NULL;
		hr = D3DX11CompileFromFileA(shaderpath.c_str(), 0, 0, "VShader", "vs_4_0", 0, 0, 0, &ParticleVS, &blob, 0);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(blob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "VS Error", MB_OK);
		}

		hr = D3DX11CompileFromFileA(shaderpath.c_str(), 0, 0, "GShader", "gs_4_0", 0, 0, 0, &ParticleGS, &blob, 0);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(blob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "VS Error", MB_OK);
		}

		blob = NULL;
		hr = D3DX11CompileFromFileA(shaderpath.c_str(), 0, 0, "PShader", "ps_4_0", 0, 0, 0, &ParticlePS, &blob, 0);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(blob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "PS Error", MB_OK);
		}


		hr = device->CreateVertexShader	 (ParticleVS->GetBufferPointer(), ParticleVS->GetBufferSize(), NULL, &pParticleVS);
		hr = device->CreateGeometryShader(ParticleGS->GetBufferPointer(), ParticleGS->GetBufferSize(), NULL, &pParticleGS);
		hr = device->CreatePixelShader	 (ParticlePS->GetBufferPointer(), ParticlePS->GetBufferSize(), NULL, &pParticlePS);



		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "LIFETIME",  0, DXGI_FORMAT_R32_FLOAT,	   0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		hr = device->CreateInputLayout(ied, sizeof(ied) / sizeof(ied[0]),
			ParticleVS->GetBufferPointer(),
			ParticleVS->GetBufferSize(),
			&pParticleLayout);
	}

	void SetObjectShader(ID3D11DeviceContext* context)
	{
		// set to this before render
		context->VSSetShader(pObjectVS, 0, 0);
		context->GSSetShader(nullptr, 0, 0);
		context->PSSetShader(pObjectPS, 0, 0);
		context->IASetInputLayout(pObjectLayout);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void SetGizmoShader(ID3D11DeviceContext* context)
	{
		// set to this before render
		context->VSSetShader(pObjectVS, 0, 0);
		context->GSSetShader(nullptr, 0, 0);
		context->PSSetShader(pObjectPS, 0, 0);
		context->IASetInputLayout(pObjectLayout);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	}

	void SetParticleShader(ID3D11DeviceContext* context)
	{
		// set to this before render
		context->VSSetShader(pParticleVS, 0, 0);
		context->GSSetShader(pParticleGS, 0, 0);
		context->PSSetShader(pParticlePS, 0, 0);
		context->IASetInputLayout(pParticleLayout);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	}


private:
	ID3D10Blob* ObjectVS;
	ID3D10Blob* ObjectPS;
	ID3D11VertexShader*		pObjectVS;
	ID3D11PixelShader*		pObjectPS;
	ID3D11InputLayout*		pObjectLayout;


	ID3D10Blob* ParticleVS;
	ID3D10Blob* ParticleGS;
	ID3D10Blob* ParticlePS;
	ID3D11VertexShader*		pParticleVS;
	ID3D11GeometryShader*	pParticleGS;
	ID3D11PixelShader*		pParticlePS;
	ID3D11InputLayout*		pParticleLayout;

};