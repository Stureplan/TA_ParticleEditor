#pragma once
#include <d3d11.h>
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
	
	unsigned int ParticleCount();
	std::vector<PARTICLE_VERTEX> ParticleData(unsigned int &count);
	std::vector<PARTICLE_VERTEX> AllParticleData();
	PARTICLE_VERTEX GetParticle(unsigned int id);
	bool IsAlive(unsigned int id);
	unsigned int GetSize();

	void SetProperty(PS_PROPERTY prop, void* data);
	void* GetProperty(PS_PROPERTY prop);


	void Initialize();
	void Rebuild(EMITTER emitter);
	void Update(float dt);

private:
	float RandomFloat(float min, float max);
	int RandomInt(int min, int max);
	int RandomIntMinusPlus();
	FLOAT3 Position(EMITTER_TYPE type);

private:
	// Private variables
	EMITTER emitter;
	std::vector<PARTICLE> particles;
	float cooldown = 0.0f;


	std::random_device rd;
	std::mt19937 rng;
};