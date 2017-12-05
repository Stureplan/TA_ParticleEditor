#pragma once
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
#include "gizmo.h"

#pragma comment (lib, "d3d11.lib")



#define WIDTH width()
#define HEIGHT height()
#define VSYNC 1

using namespace DirectX;

class Graphics : public QWidget 
{
public:
	Graphics(QWidget* parent = Q_NULLPTR);
	~Graphics();

	void Initialize();
	void SetupCamera(XMVECTOR pos, XMVECTOR dir, XMVECTOR up);
	void MoveCamera(float z);
	void RotateCamera(float rotX, float rotY);
	void SetLastCameraMovement(Qt::Key key, bool released);
	void SetLastCameraRotation(Qt::Key key, bool released);
	void LoadParticles();
	void LoadDebugParticle();
	void LoadFullscreenQuad();
	void LoadTextures();
	void ChangeRasterization(D3D11_FILL_MODE fillmode);

	void GainedFocus();
	void Retexture(std::string path);
	void RecompileShader(int type, bool noise, bool interpolate, bool rotate);
	void Rebuild(EMITTER ps);
	void PauseSimulation();

	void ParticleInspectionLabel(QLabel* label);
	void UpdateInspectorText();
	int TestIntersection(int x, int y, XMFLOAT3 &particlePos);
	bool PointInTriangle(float x, float y, float x1, float y1, float x2, float y2, float x3, float y3);

	void ResizeParticleSystem(unsigned int count);
	void UploadParticleBuffer();
	void AddParticle(FLOAT3 p);

	void Debug(bool active);
	void Update();
	void UpdateOnce();
	void Render();
	void RenderDebugObject(unsigned int vtxcount);
	void RenderDebugParticle(unsigned int particleID);

	ParticleSystem* ParticleSystemPtr() { return particlesystem; }
	void AddParticleSystem(EMITTER ps);
	void RemoveParticleSystem(int index);
	EMITTER ParticleSystemByIndex(int index);

	virtual QPaintEngine* paintEngine() const { return NULL; }

	Q_OBJECT
	Q_DISABLE_COPY(Graphics)

private:
	//TODO: Implement the array of all particle systems here. Use functions to add() and remove().
	//std::vector<ParticleSystem*> allParticleSystems;
	bool paused = false;
	bool debug = false;
	unsigned int frame = 0;

	QTimer* timer;
	QLabel* inspectorLabel;

	ULONGLONG last = 0;
	float ms = 0;

	XMMATRIX v;

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

	// Camera & matrices
	XMMATRIX WVP;
	XMMATRIX World;
	XMMATRIX View;
	XMMATRIX Projection;

	float camvel;
	float camrotX;
	float camrotY;
	XMVECTOR campos;
	XMVECTOR camdir;
	XMVECTOR camup;
	Qt::Key lastMoveKey;
	Qt::Key lastRotKey;
	float movespeed = 20.0f;
	float rotspeed = 2.5f;


	// Constant Buffer Particles
	ID3D11Buffer* constantBufferParticle;
	CBUFFER_PARTICLESYSTEM cBufferParticle;

	// Constant Buffer Particles Animated
	ID3D11Buffer* constantBufferParticleAnimated;
	CBUFFER_PARTICLESYSTEM_ANIMATED cBufferParticleAnimated;
	
	ID3D11Buffer* particleVertexBuffer;
	ID3D11Buffer* particleDebugVertexBuffer;
	ID3D11Buffer* fullscreenQuadVertexBuffer;

	ID3D11ShaderResourceView* fullscreenQuadTexture;
	ID3D11Texture2D* sharedTexture;

	int particleDebugID = -1;
	std::vector<VERTEX>		  fullscreenQuadVertexData;
	PARTICLE_VERTEX debugParticle;

	std::vector<ID3D11ShaderResourceView*> textures;
	ID3D11ShaderResourceView* texture_debug;

	ParticleSystem* particlesystem;
	std::vector<EMITTER> particlesystems;
	Shaders shaders;

	Gizmo* positionGizmo;
	Gizmo* emitterGizmo;
};
