#pragma once
#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>
#include <QDebug>
#include <QLabel>

#include <string>
#include <vector>
#include <ctime>

//#include <dxgi.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <DirectXMath.h>

#include "utility.h"
#include "particlesystem.h"
#include "shaders.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")


#define W width()
#define H height()

#define VSYNC_1

using namespace DirectX;

class Graphics : public QWidget 
{
	Q_OBJECT
	Q_DISABLE_COPY(Graphics)


public:


	struct CBUFFER_PARTICLE
	{
		XMMATRIX wvp;
		XMMATRIX world;
		XMVECTOR campos;
		XMVECTOR camup;
		XMFLOAT2 size;
	};

	struct CBUFFER_VERTEX
	{
		XMMATRIX wvp;
	};

public:
	Graphics(QWidget* parent = Q_NULLPTR);
	~Graphics();

	void Initialize();
	void SetupCamera(XMVECTOR pos, XMVECTOR dir, XMVECTOR up);
	void MoveCamera(XMVECTOR pos);
	void SetLastCameraMovement(Qt::Key key, bool released);
	void LoadParticles();
	void LoadDebugParticle();
	void LoadGroundPlane();
	void LoadTextures();
	void ChangeRasterization(D3D11_FILL_MODE fillmode);

	void Rebuild(PARTICLESYSTEM ps);
	void PauseSimulation();

	void ParticleInspectionLabel(QLabel* label);
	void UpdateInspectorText();
	int TestIntersection(int x, int y, XMFLOAT3 &particlePos);
	bool PointInTriangle(float x, float y, float x1, float y1, float x2, float y2, float x3, float y3);

	void ResizeParticleSystem(unsigned int count);
	void UploadParticleBuffer();
	void AddParticle(POSITION p);

	void Debug(bool active);
	void Update();
	void Render();
	void RenderDebugObject(unsigned int vtxcount);
	void RenderDebugParticle(unsigned int particleID);


	virtual QPaintEngine* paintEngine() const { return NULL; }

private:
	bool debug = false;
	int amt = 0;
	unsigned int frame = 0;

	QTimer* timer;
	QLabel* inspectorLabel;

	ULONGLONG last = 0;

	float ms = 0;

private slots:
	void Loop();

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
	ID3D11RasterizerState* rasterizerState;

	// Shaders
	ID3D11InputLayout*		pLayout;
	ID3D11VertexShader*		pVS;
	ID3D11PixelShader*		pPS;
	ID3D11GeometryShader*	pGS;
	ID3D10Blob*				VS;
	ID3D10Blob*				PS;
	ID3D10Blob*				GS;

	// Camera & matrices
	XMMATRIX WVP;
	XMMATRIX World;
	XMMATRIX View;
	XMMATRIX Projection;

	XMVECTOR camvel;
	XMVECTOR campos;
	XMVECTOR camdir;
	XMVECTOR camup;
	Qt::Key lastKey;
	float camspeed = 10.0f;

	// Constant Buffer Vertices
	ID3D11Buffer* constantBufferVertex;
	CBUFFER_VERTEX cBufferVertex;

	// Constant Buffer Particles
	ID3D11Buffer* constantBufferParticle;
	CBUFFER_PARTICLE cBufferParticle;



	ID3D11Buffer* particleVertexBuffer;
	ID3D11Buffer* groundVertexBuffer;
	ID3D11Buffer* particleDebugVertexBuffer;

	int particleDebugID = -1;
	//std::vector<POINT>	particleVertexData;
	std::vector<VERTEX> groundVertexData;
	POSITION debugParticle;

	std::vector<ID3D11ShaderResourceView*> textures;
	ID3D11ShaderResourceView* texture_debug;

	float sizeX = 1.0f;
	float sizeY = 1.0f;

	ParticleSystem* particlesystem;
	Shaders shaders;
};
