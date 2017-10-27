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

void ParticleSystem::AddParticle(VECTOR3 p)
{
	particles.push_back(PARTICLE(p,0.0f, true));
}

void ParticleSystem::ModifyParticle(int id, VECTOR3 p)
{
	particles[id].position = p;
}

std::vector<VECTOR3> ParticleSystem::ParticlePositionData(unsigned int &count)
{
	std::vector<VECTOR3> positions;
	count = particles.size();
	unsigned int actualCount = 0;



	for (int i = 0; i < count; i++)
	{
		if (particles[i].alive)
		{
			positions.push_back(particles[i].position);
			actualCount++;
		}
	}

	count = actualCount;
	return positions;
}

std::vector<VECTOR3> ParticleSystem::AllParticlePositions()
{
	unsigned int count = particles.size();
	std::vector<VECTOR3> positions;

	for (unsigned int i = 0; i < count; i++)
	{
		positions.push_back(particles[i].position);
	}

	return positions;
}

VECTOR3 ParticleSystem::GetPosition(unsigned int id)
{
	return particles[id].position;
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
	float grav = *(float*)data;

	switch (prop)
	{
	case PS_PROPERTY::PS_POSITION:
		ps->position = *(VECTOR3*)data;
		break;
	case PS_PROPERTY::PS_VELOCITY:
		ps->velocity = *(VECTOR3*)data;
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
		ps->colorIn = *(COLOR*)data;
		break;
	case PS_PROPERTY::PS_COLOR_OUT:
		ps->colorOut = *(COLOR*)data;
		break;
	}
}

void ParticleSystem::Initialize()
{
	ps = new PARTICLESYSTEM(VECTOR3(0,0,0),0, VECTOR3(0,0,0),0,0,0,"", COLOR(0,0,0,0), COLOR(0,0,0,0));


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

	particles.clear();

	for (unsigned int i = 0; i < ps->maxparticles; i++)
	{
		particles.push_back(PARTICLE(VECTOR3(0, 0, 0), 0, false));
	}
}

void ParticleSystem::Update(float dt)
{
	if (paused == false)
	{
		//unsigned int max = particles.size();
		unsigned int max = ps->maxparticles;

		for (unsigned int i = 0; i < max; i++)
		{
			PARTICLE p = particles[i];


			// Check for dead/alive
			if (p.alive == true)
			{
				if (p.currentlifetime < ps->lifetime)
				{
					VECTOR3 nPos = p.position;

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

		cooldown += dt;
	}

}