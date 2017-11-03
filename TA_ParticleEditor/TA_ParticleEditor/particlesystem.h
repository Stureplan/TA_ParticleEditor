#pragma once
#include <d3d11.h>
#include <d3dX11.h>
#include <DirectXMath.h>
#include <string>
#include <vector>
#include <random>

#include "utility.h"

using namespace DirectX;


class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
	
	unsigned int ParticleCount();
	void AddParticle(FLOAT3 p);
	void ModifyParticle(int id, FLOAT3 p);
	std::vector<PARTICLE_VERTEX> ParticleData(unsigned int &count);
	std::vector<PARTICLE_VERTEX> AllParticleData();
	PARTICLE_VERTEX GetParticle(unsigned int id);
	void EmitterSize(float x, float z);
	FLOAT4 GetInColor() { return ps->colorIn; }
	FLOAT4 GetOutColor() { return ps->colorOut; }
	bool IsAlive(unsigned int id) { return particles[id].alive; }
	unsigned int GetSize();
	void Pause();

	void SetProperty(PS_PROPERTY prop, void* data);

	void Initialize();
	void Rebuild(PARTICLESYSTEM particlesystem);
	void Update(float dt);

	bool Paused()						{ return paused; }
	float Lifetime()					{ return ps->lifetime; }
	PARTICLESYSTEM* GetParticleSystem() { return ps; }

private:
	float Random(float min, float max);
	FLOAT3 Position(EMITTER_TYPE type);

private:
	// Private variables
	PARTICLESYSTEM* ps;
	std::vector<PARTICLE> particles;
	bool paused = false;
	float cooldown = 0.0f;


	std::random_device rd;
	std::mt19937 rng;
};