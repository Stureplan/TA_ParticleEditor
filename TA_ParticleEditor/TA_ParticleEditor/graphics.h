﻿#pragma once
#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>
#include <QDebug>
#include <QLabel>

#include <string>
#include <vector>
#include <ctime>

#include <d3d11.h>
#include <DirectXMath.h>


#include "utility.h"
#include "particlesystem.h"
#include "shaders.h"

#pragma comment (lib, "d3d11.lib")



#define WIDTH width()
#define HEIGHT height()

#define VSYNC_1

using namespace DirectX;

class Graphics : public QWidget 
{
	Q_OBJECT
	Q_DISABLE_COPY(Graphics)


public:


	struct CBUFFER_PARTICLESYSTEM
	{
		XMMATRIX wvp;
		XMMATRIX world;
		XMVECTOR campos;
		XMVECTOR camup;
		FLOAT4 colin;
		FLOAT4 colout;
		XMFLOAT2 size;
		float scale;
		float lifetime;
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
	void MoveBack();
	void MoveCamera(float z);
	void RotateCamera(float rot);
	void SetLastCameraMovement(Qt::Key key, bool released);
	void SetLastCameraRotation(Qt::Key key, bool released);
	void LoadParticles();
	void LoadDebugParticle();
	void LoadPositionGizmo();
	void LoadEmitterTypeGizmo(EMITTER_TYPE type);
	void LoadTextures();
	void ChangeRasterization(D3D11_FILL_MODE fillmode);

	void Retexture(std::string path);
	void Rebuild(PARTICLESYSTEM ps);
	void PauseSimulation();

	void EmitterGizmo(EMITTER_TYPE type);

	void ParticleInspectionLabel(QLabel* label);
	void UpdateInspectorText();
	int TestIntersection(int x, int y, XMFLOAT3 &particlePos);
	bool PointInTriangle(float x, float y, float x1, float y1, float x2, float y2, float x3, float y3);

	void ResizeParticleSystem(unsigned int count);
	void UploadParticleBuffer();
	void AddParticle(FLOAT3 p);

	void Debug(bool active);
	void Update();
	void Render();
	void RenderDebugObject(unsigned int vtxcount);
	void RenderDebugParticle(unsigned int particleID);

	ParticleSystem* ParticleSystemPtr() { return particlesystem; }

	virtual QPaintEngine* paintEngine() const { return NULL; }

private:
	bool paused = false;
	bool debug = false;
	int amt = 0;
	unsigned int frame = 0;

	QTimer* timer;
	QLabel* inspectorLabel;

	ULONGLONG last = 0;

	float ms = 0;

	XMMATRIX v;

	EMITTER_TYPE emitterType;

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

	float camvel;
	float camrot;
	XMVECTOR campos;
	XMVECTOR camdir;
	XMVECTOR camup;
	Qt::Key lastMoveKey;
	Qt::Key lastRotKey;
	float movespeed = 20.0f;
	float rotspeed = 2.5f;

	// Constant Buffer Vertices
	ID3D11Buffer* constantBufferVertex;
	CBUFFER_VERTEX cBufferVertex;

	// Constant Buffer Particles
	ID3D11Buffer* constantBufferParticle;
	CBUFFER_PARTICLESYSTEM cBufferParticle;

	// Constant Buffer Variables
	FLOAT4 colIn = (FLOAT4(1, 1, 1, 1));
	FLOAT4 colOut= (FLOAT4(1, 1, 1, 1));

	ID3D11Buffer* particleVertexBuffer;
	ID3D11Buffer* positionGizmoVertexBuffer;
	ID3D11Buffer* emitterTypeGizmoVertexBuffer;
	ID3D11Buffer* particleDebugVertexBuffer;

	int particleDebugID = -1;
	//std::vector<POINT>	particleVertexData;
	std::vector<GIZMO_VERTEX> positionGizmoVertexData;
	std::vector<GIZMO_VERTEX> emitterTypeGizmoVertexData;
	PARTICLE_VERTEX debugParticle;

	std::vector<ID3D11ShaderResourceView*> textures;
	ID3D11Resource* textureResource;
	ID3D11ShaderResourceView* texture_debug;


	ParticleSystem* particlesystem;
	Shaders shaders;
};
