#pragma once
#include <d3d11.h>
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
	bool IsAlive(unsigned int id) { return particles[id].alive; }
	unsigned int GetSize();

	void SetProperty(PS_PROPERTY prop, void* data);
	void* GetProperty(PS_PROPERTY prop);


	void Initialize();
	void Rebuild(PARTICLESYSTEM particlesystem);
	void Update(float dt);

	PARTICLESYSTEM* GetParticleSystem() { return ps; }

private:
	float RandomFloat(float min, float max);
	int RandomInt(int min, int max);
	int RandomIntMinusPlus();
	FLOAT3 Position(EMITTER_TYPE type);

private:
	// Private variables
	PARTICLESYSTEM* ps;
	std::vector<PARTICLE> particles;
	float cooldown = 0.0f;


	std::random_device rd;
	std::mt19937 rng;
};