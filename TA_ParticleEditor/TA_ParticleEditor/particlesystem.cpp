#include "particlesystem.h"

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{

}

unsigned int ParticleSystem::ParticleCount()
{
	return particles.size();
}

void ParticleSystem::AddParticle(POSITION p)
{
	particles.push_back(PARTICLE(p,0.0f, true));
}

void ParticleSystem::ModifyParticle(int id, POSITION p)
{
	particles[id].position = p;
}

std::vector<POSITION> ParticleSystem::ParticlePositionData(unsigned int &count)
{
	std::vector<POSITION> positions;
	count = particles.size();
	unsigned int actualCount = 0;



	for (int i = 0; i < count; i++)
	{
		if (particles[i].active)
		{
			positions.push_back(particles[i].position);
			actualCount++;
		}
	}

	count = actualCount;
	return positions;
}

std::vector<POSITION> ParticleSystem::AllParticlePositions()
{
	unsigned int count = particles.size();
	std::vector<POSITION> positions;

	for (unsigned int i = 0; i < count; i++)
	{
		if (particles[i].active)
		{
			positions.push_back(particles[i].position);
		}
	}

	return positions;
}

POSITION ParticleSystem::GetPosition(unsigned int id)
{
	return particles[id].position;
}

unsigned int ParticleSystem::GetSize()
{
	return particles.size();
}

void ParticleSystem::Initialize(unsigned int count)
{
	ps = new PARTICLESYSTEM(count, XMVectorSet(0, 0, 0, 0), 0.1f, 1.0f, "C:\\texture.png");


	for (unsigned int i = 0; i < count; i++)
	{
		particles.push_back(PARTICLE(POSITION(0,2,0),0, true));
	}
}

void ParticleSystem::Update()
{
	unsigned int max = particles.size();
	for (unsigned int i = 0; i < max; i++)
	{
		//update logic

		//positions[i] = newpos;
	}
}