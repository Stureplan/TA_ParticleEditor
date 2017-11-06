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

void ParticleSystem::AddParticle(FLOAT3 p)
{
	particles.push_back(PARTICLE(p, p, 0.0f, true));
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
			particle_vertices.push_back(PARTICLE_VERTEX(particles[i].position, particles[i].direction, particles[i].currentlifetime));
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
		positions.push_back(PARTICLE_VERTEX(particles[i].position, particles[i].direction, particles[i].currentlifetime));
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
				return PARTICLE_VERTEX(particles[i].position, particles[i].direction, particles[i].currentlifetime);
			}
			aliveParticles++;
		}
	}

	return PARTICLE_VERTEX(FLOAT3(0, 0, 0), FLOAT3(0,0,0), 0);
}

void ParticleSystem::EmitterSize(float x, float z)
{
	ps->rectSizeX = x; ps->rectSizeZ = z;
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
	case PS_PROPERTY::PS_EMITTER_TYPE:
		ps->emittertype = *(EMITTER_TYPE*)data;
		break;
	}
}

void ParticleSystem::Initialize()
{
	ps = new PARTICLESYSTEM(EMITTER_TYPE::EMIT_POINT, FLOAT3(0,0,0),0, FLOAT3(0,0,0),0,0,0, FLOAT4(1,1,1,1), FLOAT4(1,1,1,1), 1.0f, 1.0f, 1.0f, 1.0f);

	for (unsigned int i = 0; i < ps->maxparticles; i++)
	{
		particles.push_back(PARTICLE(ps->position, ps->position+FLOAT3(0, 1, 0), 0, false));
	}


	rng = std::mt19937(rd());
}

FLOAT3 ParticleSystem::Position(EMITTER_TYPE type)
{
	if (type == EMITTER_TYPE::EMIT_POINT)
	{
		return ps->position;
	}
	if (type == EMITTER_TYPE::EMIT_RECTANGLE)
	{
		FLOAT3 pos = ps->position;

		pos.X = Random(-ps->rectSizeX * 2, ps->rectSizeX * 2);
		pos.Z = Random(-ps->rectSizeZ * 2, ps->rectSizeZ * 2);

		return pos;
	}
}

float ParticleSystem::Random(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(rng);
}


void ParticleSystem::Rebuild(PARTICLESYSTEM particlesystem)
{
	ps->emittertype = particlesystem.emittertype;
	ps->position = particlesystem.position;
	ps->maxparticles = particlesystem.maxparticles;
	ps->velocity= particlesystem.velocity;
	ps->emissiondelay= particlesystem.emissiondelay;
	ps->lifetime= particlesystem.lifetime;
	ps->gravity= particlesystem.gravity;
	ps->sizeX = particlesystem.sizeX;
	ps->sizeY = particlesystem.sizeY;

	//TODO: Check if this is OK.
	cooldown = ps->emissiondelay;

	particles.clear();

	for (unsigned int i = 0; i < ps->maxparticles; i++)
	{
		particles.push_back(PARTICLE(FLOAT3(0, 0, 0), FLOAT3(0, 1, 0), 0, false));
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
					FLOAT3 dir = p.position;

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
					particles[i].direction = nPos - (dir+FLOAT3(0, 0.001f, 0));
				}
				else
				{
					// Particle died by lifetime, reset
					particles[i].currentlifetime = 0;
					particles[i].alive = false;

					// Move particle back to PS origin
					particles[i].position = Position(ps->emittertype);
				}
			}
			else
			{
				// This particle is dead already since before.
				// Find out if we should emit it again!
				if (cooldown > ps->emissiondelay)
				{
					particles[i].position = Position(ps->emittertype);
					particles[i].alive = true;

					cooldown = 0.0f;
				}
			}
		}
	}
}