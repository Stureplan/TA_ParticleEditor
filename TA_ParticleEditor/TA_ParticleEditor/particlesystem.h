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
	struct PARTICLESYSTEM
	{
		PARTICLESYSTEM(POSITION pos, int m, POSITION v, float ed, float lt, float grv, std::string tex)
		{
			position = pos;
			maxparticles = m;
			velocity = v;
			emissiondelay = ed;
			lifetime = lt;
			gravity = grv;
			texturename = tex;
		}

		POSITION position;
		int maxparticles;
		POSITION velocity;
		float emissiondelay;
		float lifetime;
		float gravity;
		std::string texturename;
	};





	ParticleSystem();
	~ParticleSystem();
	
	unsigned int ParticleCount();
	void AddParticle(POSITION p);
	void ModifyParticle(int id, POSITION p);
	std::vector<POSITION> ParticlePositionData(unsigned int &count);
	std::vector<POSITION> AllParticlePositions();
	POSITION GetPosition(unsigned int id);
	bool IsAlive(unsigned int id) { return particles[id].active; }
	unsigned int GetSize();
	void Pause();

	void Initialize(unsigned int count);
	void Update(float dt);

private:
	PARTICLESYSTEM* ps;
	//std::vector<POSITION> positions;
	std::vector<PARTICLE> particles;
	bool paused = false;
};