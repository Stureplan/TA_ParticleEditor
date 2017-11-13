#pragma once

#include <string>
#include <iterator>
#include <d3d11.h>
#include <d3dcompiler.h>

#include "utility.h"

#pragma comment (lib, "D3DCompiler.lib")



class Shaders
{
public:
	~Shaders()
	{
		ObjectVS->Release();
		ObjectPS->Release();
		pObjectVS->Release();
		pObjectPS->Release();

		ParticleVS->Release();
		ParticleGS->Release();
		ParticlePS->Release();
		pParticleVS->Release();
		pParticleGS->Release();
		pParticlePS->Release();

		pObjectLayout->Release();
		pParticleLayout->Release();
	}

	enum RENDER_TYPE
	{
		GIZMO = 0,
		PARTICLE
	};


	void LoadGizmoShader(ID3D11Device* device, ID3D11DeviceContext* context)
	{
		HRESULT hr;
		ID3DBlob* errorBlob;
		

		std::string shaderpath = Utility::Path() + "Data\\gizmo.hlsl";
		std::wstring shaderpath_wide;
		std::copy(shaderpath.begin(), shaderpath.end(), std::back_inserter(shaderpath_wide));



		ObjectVS = NULL;
		errorBlob = NULL;
		hr = D3DCompileFromFile(shaderpath_wide.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VShader", "vs_5_0", D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &ObjectVS, &errorBlob);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(errorBlob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "VS Error", MB_OK);
		}

		ObjectPS = NULL;
		errorBlob = NULL;
		hr = D3DCompileFromFile(shaderpath_wide.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PShader", "ps_5_0", D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &ObjectPS, &errorBlob);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(errorBlob->GetBufferPointer());
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
		HRESULT hr;
		ID3DBlob* errorBlob;
		
		std::string shaderpath = Utility::Path() + "Data\\particle.hlsl";
		std::wstring shaderpath_wide;
		std::copy(shaderpath.begin(), shaderpath.end(), std::back_inserter(shaderpath_wide));

		ParticleVS = NULL;
		errorBlob = NULL;
		hr = D3DCompileFromFile(shaderpath_wide.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VShader", "vs_5_0", D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &ParticleVS, &errorBlob);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(errorBlob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "VS Error", MB_OK);
		}

		ParticleGS = NULL;
		errorBlob = NULL;
		hr = D3DCompileFromFile(shaderpath_wide.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "GShader", "gs_5_0", D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &ParticleGS, &errorBlob);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(errorBlob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "GS Error", MB_OK);
		}

		ParticlePS = NULL;
		errorBlob = NULL;
		hr = D3DCompileFromFile(shaderpath_wide.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PShader", "ps_5_0", D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &ParticlePS, &errorBlob);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(errorBlob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "PS Error", MB_OK);
		}


		hr = device->CreateVertexShader	 (ParticleVS->GetBufferPointer(), ParticleVS->GetBufferSize(), NULL, &pParticleVS);
		hr = device->CreateGeometryShader(ParticleGS->GetBufferPointer(), ParticleGS->GetBufferSize(), NULL, &pParticleGS);
		hr = device->CreatePixelShader	 (ParticlePS->GetBufferPointer(), ParticlePS->GetBufferSize(), NULL, &pParticlePS);



		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "DIRECTION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "LIFETIME",  0, DXGI_FORMAT_R32_FLOAT,	   0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		hr = device->CreateInputLayout(ied, sizeof(ied) / sizeof(ied[0]),
			ParticleVS->GetBufferPointer(),
			ParticleVS->GetBufferSize(),
			&pParticleLayout);
	}

	void LoadAnimatedParticleShader(ID3D11Device* device, ID3D11DeviceContext* context)
	{
		HRESULT hr;
		ID3DBlob* errorBlob;

		std::string shaderpath = Utility::Path() + "Data\\particle_animated.hlsl";
		std::wstring shaderpath_wide;
		std::copy(shaderpath.begin(), shaderpath.end(), std::back_inserter(shaderpath_wide));

		ParticleVS = NULL;
		errorBlob = NULL;
		hr = D3DCompileFromFile(shaderpath_wide.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VShader", "vs_5_0", D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &ParticleVS, &errorBlob);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(errorBlob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "VS Error", MB_OK);
		}

		ParticleGS = NULL;
		errorBlob = NULL;
		hr = D3DCompileFromFile(shaderpath_wide.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "GShader", "gs_5_0", D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &ParticleGS, &errorBlob);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(errorBlob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "GS Error", MB_OK);
		}

		ParticlePS = NULL;
		errorBlob = NULL;
		hr = D3DCompileFromFile(shaderpath_wide.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PShader", "ps_5_0", D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &ParticlePS, &errorBlob);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(errorBlob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "PS Error", MB_OK);
		}


		hr = device->CreateVertexShader		(ParticleVS->GetBufferPointer(), ParticleVS->GetBufferSize(), NULL, &pParticleVS);
		hr = device->CreateGeometryShader	(ParticleGS->GetBufferPointer(), ParticleGS->GetBufferSize(), NULL, &pParticleGS);
		hr = device->CreatePixelShader		(ParticlePS->GetBufferPointer(), ParticlePS->GetBufferSize(), NULL, &pParticlePS);



		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "DIRECTION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "LIFETIME",  0, DXGI_FORMAT_R32_FLOAT,	   0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
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
	ID3DBlob* ObjectVS;
	ID3DBlob* ObjectPS;
	ID3D11VertexShader*		pObjectVS;
	ID3D11PixelShader*		pObjectPS;
	ID3D11InputLayout*		pObjectLayout;

	ID3DBlob* ParticleVS;
	ID3DBlob* ParticleGS;
	ID3DBlob* ParticlePS;
	ID3D11VertexShader*		pParticleVS;
	ID3D11GeometryShader*	pParticleGS;
	ID3D11PixelShader*		pParticlePS;
	ID3D11InputLayout*		pParticleLayout;
};