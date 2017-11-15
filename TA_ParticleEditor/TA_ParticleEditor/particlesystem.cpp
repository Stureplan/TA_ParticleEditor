

#include "particlesystem.h"

#include "utility.h"

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
	delete ps;
}

unsigned int ParticleSystem::ParticleCount()
{ 
	return particles.size();
}

void ParticleSystem::AddParticle(FLOAT3 p)
{
	particles.push_back(PARTICLE(p, p, 0.0f, true, 1, 1));
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

	return PARTICLE_VERTEX(FLOAT3_ZERO, FLOAT3_ZERO, 0);
}

bool ParticleSystem::IsAlive(unsigned int id)
{
	return particles[id].alive;
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

void ParticleSystem::SetProperty(PS_PROPERTY prop, void* data)
{
	switch (prop)
	{
	case PS_PROPERTY::PS_VELOCITY:
		ps->velocity = *(FLOAT3*)data;
		break;
	case PS_PROPERTY::PS_EMISSIONDELAY:
		ps->emissiondelay = *(float*)data;
		cooldown = ps->emissiondelay;
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
	case PS_PROPERTY::PS_START_SIZE_X:
		ps->startSizeX = *(float*)data;
		break;
	case PS_PROPERTY::PS_START_SIZE_Y:
		ps->startSizeY = *(float*)data;
		break;
	case PS_PROPERTY::PS_END_SIZE_X:
		ps->endSizeX = *(float*)data;
		break;
	case PS_PROPERTY::PS_END_SIZE_Y:
		ps->endSizeY = *(float*)data;
		break;
	case PS_PROPERTY::PS_EMITTER_TYPE:
		ps->emittertype = *(EMITTER_TYPE*)data;
		break;
	case PS_PROPERTY::PS_RECT_SIZE_X:
		ps->rectSizeX = *(float*)data;
		break;
	case PS_PROPERTY::PS_RECT_SIZE_Z:
		ps->rectSizeZ = *(float*)data;
		break;
	case PS_PROPERTY::PS_TEXTURE_TYPE:
		ps->textureType = *(int*)data;
		break;
	case PS_PROPERTY::PS_TEXTURE_COLUMNS:
		ps->textureColumns = *(int*)data;
		break;
	case PS_PROPERTY::PS_TEXTURE_ROWS:
		ps->textureRows = *(int*)data;
		break;
	}
}

void* ParticleSystem::GetProperty(PS_PROPERTY prop)
{
	switch (prop)
	{
	case PS_PROPERTY::PS_VELOCITY:
		return &ps->velocity;
		break;
	case PS_PROPERTY::PS_EMISSIONDELAY:
		return &ps->emissiondelay;
		break;
	case PS_PROPERTY::PS_LIFETIME:
		return &ps->lifetime;
		break;
	case PS_PROPERTY::PS_GRAVITY:
		return &ps->gravity;
		break;
	case PS_PROPERTY::PS_COLOR_IN:
		return &ps->colorIn;
		break;
	case PS_PROPERTY::PS_COLOR_OUT:
		return &ps->colorOut;
		break;
	case PS_PROPERTY::PS_START_SIZE_X:
		return &ps->startSizeX;
		break;
	case PS_PROPERTY::PS_START_SIZE_Y:
		return &ps->startSizeY;
		break;
	case PS_PROPERTY::PS_END_SIZE_X:
		return &ps->endSizeX;
		break;
	case PS_PROPERTY::PS_END_SIZE_Y:
		return &ps->endSizeY;
		break;
	case PS_PROPERTY::PS_EMITTER_TYPE:
		return &ps->emittertype;
		break;
	case PS_PROPERTY::PS_RECT_SIZE_X:
		return &ps->rectSizeX;
		break;
	case PS_PROPERTY::PS_RECT_SIZE_Z:
		return &ps->rectSizeZ;
		break;
	case PS_PROPERTY::PS_TEXTURE_TYPE:
		return &ps->textureType;
		break;
	case PS_PROPERTY::PS_TEXTURE_COLUMNS:
		return &ps->textureColumns;
		break;
	case PS_PROPERTY::PS_TEXTURE_ROWS:
		return &ps->textureRows;
		break;
	}

	return NULL;
}

void ParticleSystem::Initialize()
{
	ps = new PARTICLESYSTEM(EMITTER_TYPE::EMIT_POINT,0, FLOAT3_ZERO, 0,0,0, FLOAT4(1,1,1,1), FLOAT4(1,1,1,1), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0, 4, 4);

	for (unsigned int i = 0; i < ps->maxparticles; i++)
	{
		particles.push_back(PARTICLE(FLOAT3_ZERO, FLOAT3_ZERO + FLOAT3(0, 1, 0), 0, false, RandomIntMinusPlus(), RandomIntMinusPlus()));
	}


	rng = std::mt19937(rd());
}

FLOAT3 ParticleSystem::Position(EMITTER_TYPE type)
{
	if (type == EMITTER_TYPE::EMIT_POINT)
	{
		return FLOAT3_ZERO;
	}
	if (type == EMITTER_TYPE::EMIT_RECTANGLE)
	{
		FLOAT3 pos = FLOAT3_ZERO;

		pos.X = RandomFloat(-ps->rectSizeX * 2, ps->rectSizeX * 2);
		pos.Z = RandomFloat(-ps->rectSizeZ * 2, ps->rectSizeZ * 2);

		return pos;
	}
	return FLOAT3(0, 0, 0);
}

float ParticleSystem::RandomFloat(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(rng);
}

int ParticleSystem::RandomInt(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	int r = dist(rng);
	if (r == 0) { r = 1; }

	return r;
}

int ParticleSystem::RandomIntMinusPlus()
{
	std::uniform_int_distribution<int> dist(0, 1);
	int r = dist(rng);

	if (r == 0) { r = -1; }
	return r;
}


void ParticleSystem::Rebuild(PARTICLESYSTEM particlesystem)
{
	ps->emittertype = particlesystem.emittertype;
	ps->maxparticles = particlesystem.maxparticles;
	ps->velocity= particlesystem.velocity;
	ps->emissiondelay= particlesystem.emissiondelay;
	ps->lifetime= particlesystem.lifetime;
	ps->gravity= particlesystem.gravity;
	ps->startSizeX = particlesystem.startSizeX;
	ps->startSizeY = particlesystem.startSizeY;
	ps->endSizeX = particlesystem.endSizeX;
	ps->endSizeY = particlesystem.endSizeY;
	ps->rectSizeX = particlesystem.rectSizeX;
	ps->rectSizeZ = particlesystem.rectSizeZ;
	ps->textureType = particlesystem.textureType;
	ps->textureColumns = particlesystem.textureColumns;
	ps->textureRows = particlesystem.textureRows;

	cooldown = ps->emissiondelay;

	particles.clear();

	for (unsigned int i = 0; i < ps->maxparticles; i++)
	{
		particles.push_back(PARTICLE(FLOAT3(0, 0, 0), FLOAT3(0, 1, 0), 0, false, RandomIntMinusPlus(), RandomIntMinusPlus()));
	}
}

void ParticleSystem::Update(float dt)
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
				nPos.X += ((ps->velocity.X) * dt);
				nPos.Y += ((ps->velocity.Y) * dt);
				nPos.Z += ((ps->velocity.Z) * dt);

				// Add time to particle life
				particles[i].currentlifetime += dt;

				// Move particle
				particles[i].position = nPos;
				particles[i].direction = nPos - (dir+FLOAT3(0, 0.001f, 0));

				//TODO: Find a good way to incorporate random directions without fucking too much shit up.
				//particles[i].direction.X *= particles[i].randX;
				//particles[i].direction.Y *= particles[i].randY;
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