#include "particlesystem.h"

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
	//delete ps;
}

unsigned int ParticleSystem::ParticleCount()
{ 
	return particles.size();
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
		emitter.velocity= *((FLOAT3*)data);
		break;
	case PS_PROPERTY::PS_EMISSIONDELAY:
		emitter.emissiondelay = *((float*)data);
		cooldown = emitter.emissiondelay;
		break;
	case PS_PROPERTY::PS_LIFETIME:
		emitter.lifetime = *((float*)data);
		break;
	case PS_PROPERTY::PS_GRAVITY:
		emitter.gravity = *((float*)data);
		break;
	case PS_PROPERTY::PS_COLOR_0:
		emitter.color0 = *((FLOAT4*)data);
		break;
	case PS_PROPERTY::PS_COLOR_1:
		emitter.color1 = *((FLOAT4*)data);
		break;
	case PS_PROPERTY::PS_COLOR_2:
		emitter.color2 = *((FLOAT4*)data);
		break;
	case PS_PROPERTY::PS_START_SIZE_X:
		emitter.startSizeX = *((float*)data);
		break;
	case PS_PROPERTY::PS_START_SIZE_Y:
		emitter.startSizeY = *((float*)data);
		break;
	case PS_PROPERTY::PS_END_SIZE_X:
		emitter.endSizeX = *((float*)data);
		break;
	case PS_PROPERTY::PS_END_SIZE_Y:
		emitter.endSizeY = *((float*)data);
		break;
	case PS_PROPERTY::PS_EMITTER_TYPE:
		emitter.emittertype = *((EMITTER_TYPE*)data);
		break;
	case PS_PROPERTY::PS_RECT_SIZE_X:
		emitter.rectSizeX = *((float*)data);
		break;
	case PS_PROPERTY::PS_RECT_SIZE_Z:
		emitter.rectSizeZ = *((float*)data);
		break;
	case PS_PROPERTY::PS_TEXTURE_TYPE:
		emitter.textureType = *((int*)data);
		break;
	case PS_PROPERTY::PS_TEXTURE_COLUMNS:
		emitter.textureColumns = *((int*)data);
		break;
	case PS_PROPERTY::PS_TEXTURE_ROWS:
		emitter.textureRows = *((int*)data);
		break;
	case PS_PROPERTY::PS_LOOPING:
		emitter.looping = *((int*)data);
		break;
	}
}

void* ParticleSystem::GetProperty(PS_PROPERTY prop)
{
	switch (prop)
	{
	case PS_PROPERTY::PS_VELOCITY:
		return &emitter.velocity;
		break;
	case PS_PROPERTY::PS_EMISSIONDELAY:
		return &emitter.emissiondelay;
		break;
	case PS_PROPERTY::PS_LIFETIME:
		return &emitter.lifetime;
		break;
	case PS_PROPERTY::PS_GRAVITY:
		return &emitter.gravity;
		break;
	case PS_PROPERTY::PS_COLOR_0:
		return &emitter.color0;
		break;
	case PS_PROPERTY::PS_COLOR_1:
		return &emitter.color1;
		break;
	case PS_PROPERTY::PS_COLOR_2:
		return &emitter.color2;
		break;
	case PS_PROPERTY::PS_START_SIZE_X:
		return &emitter.startSizeX;
		break;
	case PS_PROPERTY::PS_START_SIZE_Y:
		return &emitter.startSizeY;
		break;
	case PS_PROPERTY::PS_END_SIZE_X:
		return &emitter.endSizeX;
		break;
	case PS_PROPERTY::PS_END_SIZE_Y:
		return &emitter.endSizeY;
		break;
	case PS_PROPERTY::PS_EMITTER_TYPE:
		return &emitter.emittertype;
		break;
	case PS_PROPERTY::PS_RECT_SIZE_X:
		return &emitter.rectSizeX;
		break;
	case PS_PROPERTY::PS_RECT_SIZE_Z:
		return &emitter.rectSizeZ;
		break;
	case PS_PROPERTY::PS_TEXTURE_TYPE:
		return &emitter.textureType;
		break;
	case PS_PROPERTY::PS_TEXTURE_COLUMNS:
		return &emitter.textureColumns;
		break;
	case PS_PROPERTY::PS_TEXTURE_ROWS:
		return &emitter.textureRows;
		break;
	case PS_PROPERTY::PS_LOOPING:
		return &emitter.looping;
		break;
	}

	return NULL;
}

void ParticleSystem::Initialize()
{
	emitter = EMITTER(EMITTER_TYPE::EMIT_POINT,0, FLOAT3_ZERO, 0,0,0, FLOAT4(1,1,1,1), FLOAT4(1,1,1,1), FLOAT4(1,1,1,1), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0, 4, 4, 0);

	for (unsigned int i = 0; i < emitter.maxparticles; i++)
	{
		particles.push_back(PARTICLE(FLOAT3_ZERO, FLOAT3_ZERO + FLOAT3(0, 1, 0), 0, false, RandomIntMinusPlus(), RandomIntMinusPlus(),0));
	}

	cooldown = 0.0f;
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

		pos.X = RandomFloat(-emitter.rectSizeX * 2, emitter.rectSizeX * 2);
		pos.Z = RandomFloat(-emitter.rectSizeZ * 2, emitter.rectSizeZ * 2);

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


void ParticleSystem::Rebuild(EMITTER e)
{
	emitter = e;
	cooldown = emitter.emissiondelay;

	particles.clear();

	for (unsigned int i = 0; i < emitter.maxparticles; i++)
	{
		particles.push_back(PARTICLE(FLOAT3(0, 0, 0), emitter.velocity, 0, false, RandomIntMinusPlus(), RandomIntMinusPlus(),0));
	}
}

void ParticleSystem::Update(float dt)
{
	cooldown += dt;

	unsigned int max = particles.size();


	for (unsigned int i = 0; i < max; i++)
	{
		PARTICLE p = particles[i];


		// Check for dead/alive
		if (p.alive == true)
		{
			if (p.currentlifetime < emitter.lifetime)
			{
				FLOAT3 nPos = p.position;
				FLOAT3 dir = p.position;

				float percent = p.currentlifetime / emitter.lifetime;

				// Add gravity
				nPos.Y += ((GRAVITY - (percent * 10)) * dt) * emitter.gravity;

				// Add velocity
				nPos.X += ((emitter.velocity.X) * dt);
				nPos.Y += ((emitter.velocity.Y) * dt);
				nPos.Z += ((emitter.velocity.Z) * dt);

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
				particles[i].position = Position(emitter.emittertype);
			}
		}
		else
		{
			// This particle is dead already since before.
			// Find out if we should emit it again!
			if (cooldown > emitter.emissiondelay)
			{
				if (emitter.looping == 0) // emit all particles only once
				{
					if (p.timesemitted == 0)
					{
						particles[i].position = Position(emitter.emittertype);
						particles[i].alive = true;
						particles[i].timesemitted++;

						cooldown = 0.0f;
					}
				}

				if (emitter.looping == 1) // continuous emission
				{
					particles[i].position = Position(emitter.emittertype);
					particles[i].alive = true;
					particles[i].timesemitted++;

					cooldown = 0.0f;
				}
			}



		}
	}
}