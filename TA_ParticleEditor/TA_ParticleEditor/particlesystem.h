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
		PARTICLESYSTEM(int m, XMVECTOR v, float ed, float lt, std::string tex)
		{
			maxparticles = m;
			velocity = v;
			emissiondelay = ed;
			lifetime = lt;
			texturename = tex;
		}


		int maxparticles;
		XMVECTOR velocity;
		float emissiondelay;
		float lifetime;
		std::string texturename;
	};





	ParticleSystem();
	~ParticleSystem();
	
	unsigned int ParticleCount();
	void AddParticle(POSITION p);
	void ModifyParticle(int id, POSITION p);
	void* ParticlePositionData(unsigned int &count);
	std::vector<POSITION> GetPositions();
	POSITION GetPosition(unsigned int id);
	unsigned int GetSize();

	void Initialize(unsigned int count);
	void Update();

private:
	PARTICLESYSTEM* ps;
	//std::vector<POSITION> positions;
	std::vector<PARTICLE> particles;
};