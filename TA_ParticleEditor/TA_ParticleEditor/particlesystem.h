#pragma once
#include <d3d11.h>
#include <d3dX11.h>
#include <DirectXMath.h>
#include <string>
#include <vector>

#include "utility.h"

using namespace DirectX;


class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
	
	unsigned int ParticleCount();
	void AddParticle(VECTOR3 p);
	void ModifyParticle(int id, VECTOR3 p);
	std::vector<PARTICLE_VERTEX> ParticleData(unsigned int &count);
	std::vector<PARTICLE_VERTEX> AllParticleData();
	PARTICLE_VERTEX GetParticle(unsigned int id);
	COLOR GetInColor() { return ps->colorIn; }
	COLOR GetOutColor() { return ps->colorOut; }
	bool IsAlive(unsigned int id) { return particles[id].alive; }
	unsigned int GetSize();
	void Pause();

	void SetProperty(PS_PROPERTY prop, void* data);

	void Initialize();
	void Rebuild(PARTICLESYSTEM particlesystem);
	void Update(float dt);

private:
	// Private variables
	PARTICLESYSTEM* ps;
	std::vector<PARTICLE> particles;
	bool paused = false;
	float cooldown = 0.0f;
};