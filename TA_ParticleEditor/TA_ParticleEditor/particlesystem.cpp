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
		if (particles[i].alive)
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
		positions.push_back(particles[i].position);
	}

	return positions;
}

POSITION ParticleSystem::GetPosition(unsigned int id)
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

void ParticleSystem::Initialize()
{
	ps = new PARTICLESYSTEM(POSITION(0,0,0),0,POSITION(0,0,0),0,0,0,"");


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
		particles.push_back(PARTICLE(POSITION(0, 0, 0), 0, true));
	}
}

void ParticleSystem::Update(float dt)
{
	if (paused == false)
	{
		unsigned int max = particles.size();
		for (unsigned int i = 0; i < max; i++)
		{
			PARTICLE p = particles[i];


			// Check for dead/alive
			if (p.alive == true)
			{
				if (p.currentlifetime < ps->lifetime)
				{
					POSITION nPos = p.position;

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