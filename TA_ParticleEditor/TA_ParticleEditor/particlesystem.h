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
	void AddParticle(POSITION p);
	void ModifyParticle(int id, POSITION p);
	std::vector<POSITION> ParticlePositionData(unsigned int &count);
	std::vector<POSITION> AllParticlePositions();
	POSITION GetPosition(unsigned int id);
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