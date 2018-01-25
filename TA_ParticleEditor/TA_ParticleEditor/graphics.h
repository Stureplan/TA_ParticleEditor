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
	void LoadFullscreenQuad();
	void LoadTextures();
	void ChangeRasterization(D3D11_FILL_MODE fillmode);

	void GainedFocus();
	void Retexture(int index, TEXTURE_TYPE type, std::string path);
	void RecompileShader(int index, int type, bool noise);
	void Rebuild(int index, EMITTER ps);
	void PauseSimulation();
	void Debug(bool active);
	void Update();
	void UpdateOnce();
	void CurrentEmitterIndex(int index);
	void Render();

	EMITTER EmitterByIndex(int index);
	ParticleSystem* ParticleSystemByIndex(int index);
	int EmitterCount() { return particlesystems.size(); }
	void AddParticleSystem(int index, EMITTER ps);
	void RemoveParticleSystem(int index);
	void ClearParticleSystems();

	virtual QPaintEngine* paintEngine() const { return NULL; }

	Q_OBJECT
	Q_DISABLE_COPY(Graphics)

private:
	//TODO: Implement the array of all particle systems here. Use functions to add() and remove().
	//std::vector<ParticleSystem*> allParticleSystems;
	bool paused = false;
	bool debug = false;

	QTimer* timer;

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
	int cEmitter = 0;


	ID3D11Buffer* fullscreenQuadVertexBuffer;

	ID3D11ShaderResourceView* fullscreenQuadTexture;
	ID3D11Texture2D* sharedTexture;

	std::vector<VERTEX>		  fullscreenQuadVertexData;
	PARTICLE_VERTEX debugParticle;

	std::vector<ID3D11ShaderResourceView*> textures;

	std::vector<ParticleSystem*> particlesystems;
	Shaders shaders;

	Gizmo* positionGizmo;
	Gizmo* emitterGizmo;
};
