#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

#include <vector>
#include <random>
#include "utility.h"

// FORWARD DECLARATIONS
//struct FLOAT3;
//struct PARTICLE;
//struct PARTICLE_VERTEX;
//struct PARTICLESYSTEM;
//enum PS_PROPERTY;
//enum EMITTER_TYPE;

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void VertexBuffer(ID3D11Device* device);
	void ConstantBuffer(ID3D11Device* device);
	void UpdateConstantBuffer(ID3D11DeviceContext* context, XMMATRIX wvp, XMMATRIX world, XMVECTOR campos, XMVECTOR camup);
	void UploadParticleBuffer(ID3D11DeviceContext* context);
	void Render(ID3D11DeviceContext* context, ID3D11SamplerState* sampler, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* noise);
	void RenderDebug(ID3D11DeviceContext* context, ID3D11SamplerState* sampler, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* noise);


	bool IsAlive(unsigned int id);

	void SetProperty(PS_PROPERTY prop, void* data);
	void* GetProperty(PS_PROPERTY prop);


	void Initialize();
	void Rebuild(EMITTER e);
	void Update(float dt);

	EMITTER Emitter();

private:
	unsigned int GetSize();
	std::vector<PARTICLE_VERTEX> ParticleData(unsigned int &count);
	std::vector<PARTICLE_VERTEX> AllParticleData();
	float RandomFloat(float min, float max);
	int RandomInt(int min, int max);
	int RandomIntMinusPlus();
	FLOAT3 Position(EMITTER_TYPE type);

private:
	ID3D11Buffer* constantBuffer;
	ID3D11Buffer* constantBufferAnimated;
	ID3D11Buffer* vertexBuffer;

	CBUFFER_PARTICLESYSTEM cBufferParticle;
	CBUFFER_PARTICLESYSTEM_ANIMATED cBufferParticleAnimated;



	// Private variables
	EMITTER emitter;
	std::vector<PARTICLE> particles;
	float cooldown = 0.0f;

	std::random_device rd;
	std::mt19937 rng;
};