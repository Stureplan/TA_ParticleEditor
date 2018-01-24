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

		ParticleNoiseVS->Release();
		ParticleNoiseGS->Release();
		ParticleNoisePS->Release();
		pParticleNoiseVS->Release();
		pParticleNoiseGS->Release();
		pParticleNoisePS->Release();

		ParticleAnimatedVS->Release();
		ParticleAnimatedGS->Release();
		ParticleAnimatedPS->Release();
		pParticleAnimatedVS->Release();
		pParticleAnimatedGS->Release();
		pParticleAnimatedPS->Release();

		pGizmoLayout->Release();
		pParticleLayout->Release();
		pParticleNoiseLayout->Release();
		pParticleAnimatedLayout->Release();
		pParticleAnimatedNoiseLayout->Release();
	}

	void CompileIncludes(bool noise, bool interpolate)
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

		hr = device->CreateVertexShader	(GizmoVS->GetBufferPointer(), GizmoVS->GetBufferSize(), NULL, &pGizmoVS);
		hr = device->CreatePixelShader	(GizmoPS->GetBufferPointer(), GizmoPS->GetBufferSize(), NULL, &pGizmoPS);

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

		struct stat file;
		stat(shaderpath.c_str(), &file);
		time_t t = file.st_atime;

		lastLoadedShaderTime = t;
		lastLoadedShaderName = shadername;
	}

	void LoadParticleNoiseShader(ID3D11Device* device, ID3D11DeviceContext* context, const char* shadername)
	{
		HRESULT hr;
		ID3DBlob* errorBlob;

		std::string shaderpath = Utility::DataPath() + shadername;
		std::wstring shaderpath_wide;
		std::copy(shaderpath.begin(), shaderpath.end(), std::back_inserter(shaderpath_wide));

		ParticleNoiseVS = NULL;
		errorBlob = NULL;
		hr = D3DCompileFromFile(shaderpath_wide.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VShader", "vs_5_0", D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &ParticleNoiseVS, &errorBlob);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(errorBlob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "VS Error", MB_OK);
		}

		ParticleNoiseGS = NULL;
		errorBlob = NULL;
		hr = D3DCompileFromFile(shaderpath_wide.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "GShader", "gs_5_0", D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &ParticleNoiseGS, &errorBlob);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(errorBlob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "GS Error", MB_OK);
		}

		ParticleNoisePS = NULL;
		errorBlob = NULL;
		hr = D3DCompileFromFile(shaderpath_wide.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PShader", "ps_5_0", D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &ParticleNoisePS, &errorBlob);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(errorBlob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "PS Error", MB_OK);
		}

		hr = device->CreateVertexShader(ParticleNoiseVS->GetBufferPointer(), ParticleNoiseVS->GetBufferSize(), NULL, &pParticleNoiseVS);
		hr = device->CreateGeometryShader(ParticleNoiseGS->GetBufferPointer(), ParticleNoiseGS->GetBufferSize(), NULL, &pParticleNoiseGS);
		hr = device->CreatePixelShader(ParticleNoisePS->GetBufferPointer(), ParticleNoisePS->GetBufferSize(), NULL, &pParticleNoisePS);

		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "DIRECTION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "LIFETIME",  0, DXGI_FORMAT_R32_FLOAT,	   0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		hr = device->CreateInputLayout(ied, sizeof(ied) / sizeof(ied[0]),
			ParticleNoiseVS->GetBufferPointer(),
			ParticleNoiseVS->GetBufferSize(),
			&pParticleNoiseLayout);

		struct stat file;
		stat(shaderpath.c_str(), &file);
		time_t t = file.st_atime;

		lastLoadedShaderTime = t;
		lastLoadedShaderName = shadername;
	}

	void LoadParticleAnimatedShader(ID3D11Device* device, ID3D11DeviceContext* context, const char* shadername)
	{
		HRESULT hr;
		ID3DBlob* errorBlob;

		std::string		shaderpath = Utility::DataPath() + shadername;
		std::wstring	shaderpath_wide;
		std::copy	   (shaderpath.begin(), shaderpath.end(), std::back_inserter(shaderpath_wide));

		ParticleAnimatedVS = NULL;
		errorBlob = NULL;
		hr = D3DCompileFromFile(shaderpath_wide.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VShader", "vs_5_0", D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &ParticleAnimatedVS, &errorBlob);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(errorBlob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "VS Error", MB_OK);
		}

		ParticleAnimatedGS = NULL;
		errorBlob = NULL;
		hr = D3DCompileFromFile(shaderpath_wide.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "GShader", "gs_5_0", D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &ParticleAnimatedGS, &errorBlob);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(errorBlob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "GS Error", MB_OK);
		}

		ParticleAnimatedPS = NULL;
		errorBlob = NULL;
		hr = D3DCompileFromFile(shaderpath_wide.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PShader", "ps_5_0", D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &ParticleAnimatedPS, &errorBlob);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(errorBlob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "PS Error", MB_OK);
		}

		hr = device->CreateVertexShader		(ParticleAnimatedVS->GetBufferPointer(), ParticleAnimatedVS->GetBufferSize(), NULL, &pParticleAnimatedVS);
		hr = device->CreateGeometryShader	(ParticleAnimatedGS->GetBufferPointer(), ParticleAnimatedGS->GetBufferSize(), NULL, &pParticleAnimatedGS);
		hr = device->CreatePixelShader		(ParticleAnimatedPS->GetBufferPointer(), ParticleAnimatedPS->GetBufferSize(), NULL, &pParticleAnimatedPS);

		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "DIRECTION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "LIFETIME",  0, DXGI_FORMAT_R32_FLOAT,	   0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		hr = device->CreateInputLayout(ied, sizeof(ied) / sizeof(ied[0]),
			ParticleAnimatedVS->GetBufferPointer(),
			ParticleAnimatedVS->GetBufferSize(),
			&pParticleAnimatedLayout);

		struct stat file;
		stat(shaderpath.c_str(), &file);
		time_t t = file.st_atime;

		lastLoadedShaderTime = t;
		lastLoadedShaderName = shadername;
	}

	void LoadParticleAnimatedNoiseShader(ID3D11Device* device, ID3D11DeviceContext* context, const char* shadername)
	{
		HRESULT hr;
		ID3DBlob* errorBlob;

		std::string		shaderpath = Utility::DataPath() + shadername;
		std::wstring	shaderpath_wide;
		std::copy(shaderpath.begin(), shaderpath.end(), std::back_inserter(shaderpath_wide));

		ParticleAnimatedNoiseVS = NULL;
		errorBlob = NULL;
		hr = D3DCompileFromFile(shaderpath_wide.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VShader", "vs_5_0", D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &ParticleAnimatedNoiseVS, &errorBlob);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(errorBlob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "VS Error", MB_OK);
		}

		ParticleAnimatedNoiseGS = NULL;
		errorBlob = NULL;
		hr = D3DCompileFromFile(shaderpath_wide.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "GShader", "gs_5_0", D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &ParticleAnimatedNoiseGS, &errorBlob);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(errorBlob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "GS Error", MB_OK);
		}

		ParticleAnimatedNoisePS = NULL;
		errorBlob = NULL;
		hr = D3DCompileFromFile(shaderpath_wide.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PShader", "ps_5_0", D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &ParticleAnimatedNoisePS, &errorBlob);
		if (hr != S_OK)
		{
			// Something went wrong with the shader
			std::string error = static_cast<char*>(errorBlob->GetBufferPointer());
			MessageBoxA(NULL, error.c_str(), "PS Error", MB_OK);
		}

		hr = device->CreateVertexShader		(ParticleAnimatedNoiseVS->GetBufferPointer(), ParticleAnimatedNoiseVS->GetBufferSize(), NULL, &pParticleAnimatedNoiseVS);
		hr = device->CreateGeometryShader	(ParticleAnimatedNoiseGS->GetBufferPointer(), ParticleAnimatedNoiseGS->GetBufferSize(), NULL, &pParticleAnimatedNoiseGS);
		hr = device->CreatePixelShader		(ParticleAnimatedNoisePS->GetBufferPointer(), ParticleAnimatedNoisePS->GetBufferSize(), NULL, &pParticleAnimatedNoisePS);

		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "DIRECTION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "LIFETIME",  0, DXGI_FORMAT_R32_FLOAT,	   0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		hr = device->CreateInputLayout(ied, sizeof(ied) / sizeof(ied[0]),
			ParticleAnimatedNoiseVS->GetBufferPointer(),
			ParticleAnimatedNoiseVS->GetBufferSize(),
			&pParticleAnimatedNoiseLayout);

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

	void SetParticleNoiseShader(ID3D11DeviceContext* context)
	{
		// set to this before render
		context->VSSetShader(pParticleNoiseVS, 0, 0);
		context->GSSetShader(pParticleNoiseGS, 0, 0);
		context->PSSetShader(pParticleNoisePS, 0, 0);
		context->IASetInputLayout(pParticleNoiseLayout);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	}

	void SetParticleAnimatedShader(ID3D11DeviceContext* context)
	{
		// set to this before render
		context->VSSetShader(pParticleAnimatedVS, 0, 0);
		context->GSSetShader(pParticleAnimatedGS, 0, 0);
		context->PSSetShader(pParticleAnimatedPS, 0, 0);
		context->IASetInputLayout(pParticleAnimatedLayout);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	}

	void SetParticleAnimatedNoiseShader(ID3D11DeviceContext* context)
	{
		// set to this before render
		context->VSSetShader(pParticleAnimatedNoiseVS, 0, 0);
		context->GSSetShader(pParticleAnimatedNoiseGS, 0, 0);
		context->PSSetShader(pParticleAnimatedNoisePS, 0, 0);
		context->IASetInputLayout(pParticleAnimatedNoiseLayout);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	}

private:
	ID3DBlob*				GizmoVS;
	ID3DBlob*				GizmoPS;
	ID3D11VertexShader*		pGizmoVS;
	ID3D11PixelShader*		pGizmoPS;
	ID3D11InputLayout*		pGizmoLayout;

	ID3DBlob*				ParticleVS;
	ID3DBlob*				ParticleGS;
	ID3DBlob*				ParticlePS;
	ID3D11VertexShader*		pParticleVS;
	ID3D11GeometryShader*	pParticleGS;
	ID3D11PixelShader*		pParticlePS;
	ID3D11InputLayout*		pParticleLayout;


	ID3DBlob*				ParticleNoiseVS;
	ID3DBlob*				ParticleNoiseGS;
	ID3DBlob*				ParticleNoisePS;
	ID3D11VertexShader*		pParticleNoiseVS;
	ID3D11GeometryShader*	pParticleNoiseGS;
	ID3D11PixelShader*		pParticleNoisePS;
	ID3D11InputLayout*		pParticleNoiseLayout;

	ID3DBlob*				ParticleAnimatedVS;
	ID3DBlob*				ParticleAnimatedGS;
	ID3DBlob*				ParticleAnimatedPS;
	ID3D11VertexShader*		pParticleAnimatedVS;
	ID3D11GeometryShader*	pParticleAnimatedGS;
	ID3D11PixelShader*		pParticleAnimatedPS;
	ID3D11InputLayout*		pParticleAnimatedLayout;

	ID3DBlob*				ParticleAnimatedNoiseVS;
	ID3DBlob*				ParticleAnimatedNoiseGS;
	ID3DBlob*				ParticleAnimatedNoisePS;
	ID3D11VertexShader*		pParticleAnimatedNoiseVS;
	ID3D11GeometryShader*	pParticleAnimatedNoiseGS;
	ID3D11PixelShader*		pParticleAnimatedNoisePS;
	ID3D11InputLayout*		pParticleAnimatedNoiseLayout;

	std::string lastLoadedShaderName;
	time_t lastLoadedShaderTime;
};