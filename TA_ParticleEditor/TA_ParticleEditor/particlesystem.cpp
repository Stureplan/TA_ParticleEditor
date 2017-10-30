#include "particlesystem.h"

ParticleSystem::ParticleSystem(PARTICLESYSTEM particlesystem)
{
	ps = new PARTICLESYSTEM(particlesystem);
}

ParticleSystem::~ParticleSystem()
{

}

unsigned int ParticleSystem::ParticleCount()
{
	return particles.size();
}

void ParticleSystem::AddParticle(FLOAT3 p)
{
	particles.push_back(PARTICLE(p,0.0f, true));
}

void ParticleSystem::ModifyParticle(int id, FLOAT3 p)
{
	particles[id].position = p;
}

std::vector<PARTICLE_VERTEX> ParticleSystem::ParticleData(unsigned int &count)
{
	std::vector<PARTICLE_VERTEX> particle_vertices;
	count = particles.size();

	unsigned int actualCount = 0;



	for (int i = 0; i < count; i++)
	{
		if (particles[i].alive)
		{
			particle_vertices.push_back(PARTICLE_VERTEX(particles[i].position, particles[i].currentlifetime));
			actualCount++;
		}
	}

	count = actualCount;
	return particle_vertices;
}

std::vector<PARTICLE_VERTEX> ParticleSystem::AllParticleData()
{
	unsigned int count = particles.size();
	std::vector<PARTICLE_VERTEX> positions;

	for (unsigned int i = 0; i < count; i++)
	{
		positions.push_back(PARTICLE_VERTEX(particles[i].position, particles[i].currentlifetime));
	}

	return positions;
}

PARTICLE_VERTEX ParticleSystem::GetParticle(unsigned int id)
{
	unsigned int aliveParticles = 0;
	for (unsigned int i = 0; i < particles.size(); i++)
	{
		if (particles[i].alive)
		{
			if (aliveParticles == id)
			{
				return PARTICLE_VERTEX(particles[i].position, particles[i].currentlifetime);
			}
			aliveParticles++;
		}
	}

	return PARTICLE_VERTEX(FLOAT3(0, 0, 0), 0);
}

unsigned int ParticleSystem::GetSize()
{
	unsigned int count = 0;
	for (unsigned int i = 0; i < particles.size(); i++)
	{
		if (particles[i].alive)
		{
			count++;
		}
	}

	return count;
}

void ParticleSystem::Pause()
{
	paused = !paused;
}

void ParticleSystem::SetProperty(PS_PROPERTY prop, void* data)
{
	switch (prop)
	{
	case PS_PROPERTY::PS_POSITION:
		ps->position = *(FLOAT3*)data;
		break;
	case PS_PROPERTY::PS_VELOCITY:
		ps->velocity = *(FLOAT3*)data;
		break;
	case PS_PROPERTY::PS_EMISSIONDELAY:
		ps->emissiondelay = *(float*)data;
		break;
	case PS_PROPERTY::PS_LIFETIME:
		ps->lifetime = *(float*)data;
		break;
	case PS_PROPERTY::PS_GRAVITY:
		ps->gravity = *(float*)data;
		break;
	case PS_PROPERTY::PS_COLOR_IN:
		ps->colorIn = *(FLOAT4*)data;
		break;
	case PS_PROPERTY::PS_COLOR_OUT:
		ps->colorOut = *(FLOAT4*)data;
		break;
	case PS_PROPERTY::PS_SIZE_X:
		ps->sizeX = *(float*)data;
		break;
	case PS_PROPERTY::PS_SIZE_Y:
		ps->sizeY = *(float*)data;
		break;
	}
}

void ParticleSystem::Initialize()
{
	ps = new PARTICLESYSTEM(FLOAT3(0,0,0),0, FLOAT3(0,0,0),0,0,0,"", FLOAT4(1,1,1,1), FLOAT4(1,1,1,1), 1.0f, 1.0f);


	for (unsigned int i = 0; i < ps->maxparticles; i++)
	{
		particles.push_back(PARTICLE(ps->position,0, false));
	}
}

void ParticleSystem::Rebuild(PARTICLESYSTEM particlesystem)
{
	ps->position = particlesystem.position;
	ps->maxparticles = particlesystem.maxparticles;
	ps->velocity= particlesystem.velocity;
	ps->emissiondelay= particlesystem.emissiondelay;
	ps->lifetime= particlesystem.lifetime;
	ps->gravity= particlesystem.gravity;
	ps->texturename= particlesystem.texturename;
	ps->sizeX = particlesystem.sizeX;
	ps->sizeY = particlesystem.sizeY;



	particles.clear();

	for (unsigned int i = 0; i < ps->maxparticles; i++)
	{
		particles.push_back(PARTICLE(FLOAT3(0, 0, 0), 0, false));
	}
}

void ParticleSystem::Update(float dt)
{
	if (paused == false)
	{
		cooldown += dt;

		unsigned int max = particles.size();
		//unsigned int max = ps->maxparticles;



		for (unsigned int i = 0; i < max; i++)
		{
			PARTICLE p = particles[i];


			// Check for dead/alive
			if (p.alive == true)
			{
				if (p.currentlifetime < ps->lifetime)
				{
					FLOAT3 nPos = p.position;

					float percent = p.currentlifetime / ps->lifetime;

					// Add gravity
					nPos.Y += ((GRAVITY - (percent * 10)) * dt) * ps->gravity;

					// Add velocity
					nPos.X += (ps->velocity.X);
					nPos.Y += (ps->velocity.Y);
					nPos.Z += (ps->velocity.Z);

					// Add time to particle life
					particles[i].currentlifetime += dt;

					// Move particle
					particles[i].position = nPos;
				}
				else
				{
					// Particle died by lifetime, reset
					particles[i].currentlifetime = 0;
					particles[i].alive = false;

					// Move particle back to PS origin
					particles[i].position = ps->position;
				}
			}
			else
			{
				// This particle is dead already since before.
				// Find out if we should emit it again!
				if (cooldown > ps->emissiondelay)
				{
					particles[i].alive = true;

					cooldown = 0.0f;
				}
			}

		}

	}

}