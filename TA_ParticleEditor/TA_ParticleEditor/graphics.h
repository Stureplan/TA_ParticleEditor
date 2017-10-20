#pragma once
#include <QWidget>

#include <string>
#include <vector>


#include <dxgi.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <DirectXMath.h>

#include "utility.h"
#include "particlesystem.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")


#define W width()
#define H height()

using namespace DirectX;

class Graphics : public QWidget 
{
	Q_OBJECT
	Q_DISABLE_COPY(Graphics)

public:
	Graphics(QWidget* parent = Q_NULLPTR);
	~Graphics();

	void Initialize();
	void SetupCamera(XMVECTOR pos, XMVECTOR dir, XMVECTOR up);
	void LoadShaders();
	void LoadQuad();
	void LoadTextures();

	void Render();

	virtual QPaintEngine* paintEngine() const { return NULL; }

	struct VERTEX
	{
		float X, Y, Z;
		float U, V;
	};

	struct CBUFFER
	{
		XMMATRIX wvp;
		XMMATRIX world;
		XMVECTOR campos;
	};

private:
	
protected:
	virtual void paintEvent(QPaintEvent* evt);


private:
	// DX11 Pointers
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11Texture2D* backBuffer;
	ID3D11SamplerState* textureSamplerState;
	D3D11_VIEWPORT viewport;
	ID3D11BlendState* blendState;

	// Shaders
	ID3D11InputLayout*	pLayout;
	ID3D11VertexShader* pVS;
	ID3D11PixelShader*	pPS;
	ID3D10Blob* VS;
	ID3D10Blob* PS;

	// Camera & matrices
	XMMATRIX WVP;
	XMMATRIX World;
	XMMATRIX View;
	XMMATRIX Projection;

	XMVECTOR campos;
	XMVECTOR camdir;
	XMVECTOR camup;

	// Constant buffer
	ID3D11Buffer* constantBuffer;
	CBUFFER cBuffer;

	ID3D11Buffer* vertexBuffer;
	std::vector<VERTEX> vertices;
	std::vector<ID3D11ShaderResourceView*> textures;


	ParticleSystem* ps;
};
