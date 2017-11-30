#pragma once

#include <sys/stat.h>

#include <string>
#include <iterator>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment (lib, "D3DCompiler.lib")

class Shaders
{
public:
	enum SHADER_TYPE
	{

	};

	~Shaders()
	{
		GizmoVS->Release();
		GizmoPS->Release();
		pGizmoVS->Release();
		pGizmoPS->Release();

		ParticleVS->Release();
		ParticleGS->Release();
		ParticlePS->Release();
		pParticleVS->Release();
		pParticleGS->Release();
		pParticlePS->Release();

		pGizmoLayout->Release();
		pParticleLayout->Release();
	}

	void CompileIncludes(bool noise, bool interpolate, bool rotate)
	{
		std::string includepath = Utility::Path() + "Data\\compiled_includes.hlsli";

		FILE* file = fopen(includepath.c_str(), "w");
		if (file != NULL)
		{
			if (noise)
			{
				const char* n = "#define NOISE\n";
				fwrite(n, sizeof(const char), strlen(n), file);
			}

			if (interpolate)
			{
				const char* i = "#define INTERPOLATE\n";
				fwrite(i, sizeof(const char), strlen(i), file);
			}

			if (rotate)
			{
				const char* r = "#define ROTATE\n";
				fwrite(r, sizeof(const char), strlen(r), file);
			}
		}

		int result = fclose(file);
		if (result != 0)
		{
			return;
		}
	}

	void LoadGizmoShader(ID3D11Device* device, ID3D11DeviceContext* context)
	{
		HRESULT hr;
		ID3DBlob* errorBlob;
		
		std::string shaderpath = Utility::Path() + "Data\\gizmo.hlsl";
		std::wstring shaderpath_wide;
		std::copy(shaderpath.begin(), shaderpath.end(), std::back_inserter(shaderpath_wide));

		GizmoVS = NULL;
		errorBlob = NULL;
		hr = D3DCompileFromFile(shaderpath_wide.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VShader", "vs_5_0", D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &GizmoVS, &errorBlob);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(errorBlob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "VS Error", MB_OK);
		}

		GizmoPS = NULL;
		errorBlob = NULL;
		hr = D3DCompileFromFile(shaderpath_wide.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PShader", "ps_5_0", D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &GizmoPS, &errorBlob);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(errorBlob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "PS Error", MB_OK);
		}

		hr = device->CreateVertexShader(GizmoVS->GetBufferPointer(), GizmoVS->GetBufferSize(), NULL, &pGizmoVS);
		hr = device->CreatePixelShader(GizmoPS->GetBufferPointer(), GizmoPS->GetBufferSize(), NULL, &pGizmoPS);

		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",	   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }

		};

		hr = device->CreateInputLayout(ied, sizeof(ied) / sizeof(ied[0]), 
										GizmoVS->GetBufferPointer(),
										GizmoVS->GetBufferSize(),
									   &pGizmoLayout);
	}

	void LoadParticleShader(ID3D11Device* device, ID3D11DeviceContext* context, const char* shadername)
	{
		HRESULT hr;
		ID3DBlob* errorBlob;

		std::string shaderpath = Utility::DataPath() + shadername;
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

		hr = device->CreateVertexShader(ParticleVS->GetBufferPointer(), ParticleVS->GetBufferSize(), NULL, &pParticleVS);
		hr = device->CreateGeometryShader(ParticleGS->GetBufferPointer(), ParticleGS->GetBufferSize(), NULL, &pParticleGS);
		hr = device->CreatePixelShader(ParticlePS->GetBufferPointer(), ParticlePS->GetBufferSize(), NULL, &pParticlePS);

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

		struct stat file;
		stat(shaderpath.c_str(), &file);
		time_t t = file.st_atime;

		lastLoadedShaderTime = t;
		lastLoadedShaderName = shadername;
	}

	void ReloadLastShader(ID3D11Device* device, ID3D11DeviceContext* context)
	{
		struct stat file;
		stat(lastLoadedShaderName.c_str(), &file);
		time_t t = file.st_atime;

		if (t == lastLoadedShaderTime)
		{
			return;
		}

		LoadParticleShader(device, context, lastLoadedShaderName.c_str());
	}

	void SetGizmoShader(ID3D11DeviceContext* context)
	{
		// set to this before render
		context->VSSetShader(pGizmoVS, 0, 0);
		context->GSSetShader(nullptr, 0, 0);
		context->PSSetShader(pGizmoPS, 0, 0);
		context->IASetInputLayout(pGizmoLayout);
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
	ID3DBlob* GizmoVS;
	ID3DBlob* GizmoPS;
	ID3D11VertexShader*		pGizmoVS;
	ID3D11PixelShader*		pGizmoPS;
	ID3D11InputLayout*		pGizmoLayout;

	ID3DBlob* ParticleVS;
	ID3DBlob* ParticleGS;
	ID3DBlob* ParticlePS;
	ID3D11VertexShader*		pParticleVS;
	ID3D11GeometryShader*	pParticleGS;
	ID3D11PixelShader*		pParticlePS;
	ID3D11InputLayout*		pParticleLayout;

	std::string lastLoadedShaderName;
	time_t lastLoadedShaderTime;
};