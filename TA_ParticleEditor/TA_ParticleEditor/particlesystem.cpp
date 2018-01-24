#include "particlesystem.h"

ParticleSystem::ParticleSystem()
{
	texture_particle	= nullptr;
	texture_noise		= nullptr;
}

ParticleSystem::~ParticleSystem()
{
	//delete ps;
	constantBuffer			->Release();
	constantBufferAnimated	->Release();
	vertexBuffer			->Release();
	texture_particle		->Release();
	texture_noise			->Release();
}

void ParticleSystem::VertexBuffer(ID3D11Device* device)
{
	HRESULT hr;

	std::vector<PARTICLE_VERTEX> positions = AllParticleData();
	unsigned int count = positions.size();

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(vertexDesc));
	//vertexDesc.ByteWidth = sizeof(POSITION) * count*2;	//NOTE!!!!!! this is just simply reserved space for further vertices.
	vertexDesc.ByteWidth = sizeof(PARTICLE_VERTEX) * count;
	vertexDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexDesc.MiscFlags = 0;
	vertexDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory(&vertexData, sizeof(vertexData));
	vertexData.pSysMem = positions.data();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(&vertexDesc, &vertexData, &vertexBuffer);
	int b = 1;
}

void ParticleSystem::ConstantBuffer(ID3D11Device* device)
{
	/*===================================================================================*/
	// CONSTANT BUFFER PARTICLE SETUP
	HRESULT hr;
	D3D11_BUFFER_DESC cb_particle_Desc;
	ZeroMemory(&cb_particle_Desc, sizeof(D3D11_BUFFER_DESC));
	cb_particle_Desc.Usage = D3D11_USAGE_DEFAULT;
	cb_particle_Desc.ByteWidth = sizeof(cBufferParticle);
	cb_particle_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb_particle_Desc.CPUAccessFlags = 0;
	cb_particle_Desc.MiscFlags = 0;
	cb_particle_Desc.StructureByteStride = 0;
	hr = device->CreateBuffer(&cb_particle_Desc, NULL, &constantBuffer);
	/*===================================================================================*/

	/*===================================================================================*/
	// CONSTANT BUFFER PARTICLE ANIMATED SETUP
	D3D11_BUFFER_DESC cb_particle_animated_Desc;
	ZeroMemory(&cb_particle_animated_Desc, sizeof(D3D11_BUFFER_DESC));
	cb_particle_animated_Desc.Usage = D3D11_USAGE_DEFAULT;
	cb_particle_animated_Desc.ByteWidth = sizeof(cBufferParticleAnimated);
	cb_particle_animated_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb_particle_animated_Desc.CPUAccessFlags = 0;
	cb_particle_animated_Desc.MiscFlags = 0;
	cb_particle_animated_Desc.StructureByteStride = 0;
	hr = device->CreateBuffer(&cb_particle_animated_Desc, NULL, &constantBufferAnimated);
	/*===================================================================================*/
}

void ParticleSystem::UpdateConstantBuffer(ID3D11DeviceContext* context, XMMATRIX wvp, XMMATRIX world, XMVECTOR campos, XMVECTOR camup)
{
	if (emitter.textureType == 0)
	{
		// Regular particle
		cBufferParticle.wvp = XMMatrixTranspose(wvp);
		cBufferParticle.world = XMMatrixTranspose(world);
		cBufferParticle.campos = campos;
		cBufferParticle.camup = camup;
		cBufferParticle.startsize = XMFLOAT2(emitter.startSizeX, emitter.startSizeY);
		cBufferParticle.endsize = XMFLOAT2(emitter.endSizeX, emitter.endSizeY);
		cBufferParticle.rotation = emitter.rotation;
		cBufferParticle.col0 = emitter.color0;
		cBufferParticle.col1 = emitter.color1;
		cBufferParticle.col2 = emitter.color2;
		cBufferParticle.lifetime = emitter.lifetime;

		context->UpdateSubresource(constantBuffer, 0, NULL, &cBufferParticle, 0, 0);
		context->VSSetConstantBuffers(0, 1, &constantBuffer);
		context->GSSetConstantBuffers(0, 1, &constantBuffer);
		context->PSSetConstantBuffers(0, 1, &constantBuffer);
	}
	else
	{
		// Animated particle
		cBufferParticleAnimated.wvp = XMMatrixTranspose(wvp);
		cBufferParticleAnimated.world = XMMatrixTranspose(world);
		cBufferParticleAnimated.campos = campos;
		cBufferParticleAnimated.camup = camup;
		cBufferParticleAnimated.startsize = XMFLOAT2(emitter.startSizeX, emitter.startSizeY);
		cBufferParticleAnimated.col0 = emitter.color0;
		cBufferParticleAnimated.col1 = emitter.color1;
		cBufferParticleAnimated.col2 = emitter.color2;
		cBufferParticleAnimated.endsize = XMFLOAT2(emitter.endSizeX, emitter.endSizeY);
		cBufferParticleAnimated.rotation = emitter.rotation;
		cBufferParticleAnimated.lifetime = emitter.lifetime;
		cBufferParticleAnimated.interpolation = emitter.interpolation;
		cBufferParticleAnimated.columns = emitter.textureColumns;
		cBufferParticleAnimated.rows = emitter.textureRows;

		context->UpdateSubresource(constantBufferAnimated, 0, NULL, &cBufferParticleAnimated, 0, 0);
		context->VSSetConstantBuffers(0, 1, &constantBufferAnimated);
		context->GSSetConstantBuffers(0, 1, &constantBufferAnimated);
		context->PSSetConstantBuffers(0, 1, &constantBufferAnimated);
	}
}

void ParticleSystem::UploadParticleBuffer(ID3D11DeviceContext* context)
{
	unsigned int count = 0;

	// Fetch the data & count from the PS
	std::vector<PARTICLE_VERTEX> positions = ParticleData(count);

	if (count > 0)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));
		HRESULT hr = context->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy((PARTICLE_VERTEX*)mappedResource.pData, positions.data(), sizeof(PARTICLE_VERTEX) * count);
		context->Unmap(vertexBuffer, 0);
	}
}

bool ParticleSystem::LoadParticleTexture(ID3D11Device* device, std::string path)
{
	texture_particle_path = path;	//NOTE: path structure is C:/etc../particle.png
	return DX::LoadTexture(device, texture_particle, path);
}

bool ParticleSystem::LoadNoiseTexture(ID3D11Device* device, std::string path)
{
	texture_noise_path = path;		//NOTE: path structure is C:/etc../noise.png
	return DX::LoadTexture(device, texture_noise, path);
}

void ParticleSystem::Render(ID3D11DeviceContext* context, ID3D11SamplerState* sampler)
{
	UINT stride;
	UINT offset;

	stride = sizeof(PARTICLE_VERTEX);
	offset = 0;

	unsigned int particleCount = GetSize();

	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->PSSetSamplers(0, 1, &sampler);
	context->PSSetShaderResources(0, 1, &texture_particle);
	context->PSSetShaderResources(1, 1, &texture_noise);
	context->Draw(particleCount, 0);
}

void ParticleSystem::RenderDebug(ID3D11DeviceContext* context, ID3D11SamplerState* sampler, ID3D11ShaderResourceView* texture_debug)
{
	cBufferParticle.col0 = COLOR_WHITE;
	cBufferParticle.col1 = COLOR_WHITE;
	cBufferParticle.col2 = COLOR_WHITE;

	UINT stride;
	UINT offset;

	stride = sizeof(PARTICLE_VERTEX);
	offset = 0;

	unsigned int particleCount = GetSize();

	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->PSSetSamplers(0, 1, &sampler);
	context->PSSetShaderResources(0, 1, &texture_debug);
	context->PSSetShaderResources(1, 1, &texture_noise);
	context->Draw(particleCount, 0);
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

bool ParticleSystem::IsAlive(unsigned int id)
{
	return particles[id].alive;
}

int ParticleSystem::ShaderIndex()
{
	return shader_index;
}

void ParticleSystem::SetShader(int shader)
{
	shader_index = shader;
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
	case PS_PROPERTY::PS_OFFSET:
		emitter.offset = *((FLOAT3*)data);
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
	case PS_PROPERTY::PS_ROTATION:
		emitter.rotation = *((float*)data);
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
	case PS_PROPERTY::PS_NOISE_DISSOLVE:
		emitter.noiseDissolve = *((int*)data);
		break;
	case PS_PROPERTY::PS_INTERPOLATION:
		emitter.interpolation = *((int*)data);
		break;
	case PS_PROPERTY::PS_BLOOM_PARTICLES:
		emitter.bloomParticles = *((int*)data);
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
	case PS_PROPERTY::PS_OFFSET:
		return &emitter.offset;
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
	case PS_PROPERTY::PS_ROTATION:
		return &emitter.rotation;
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
	case PS_PROPERTY::PS_NOISE_DISSOLVE:
		return &emitter.noiseDissolve;
		break;
	case PS_PROPERTY::PS_INTERPOLATION:
		return &emitter.interpolation;
		break;
	case PS_PROPERTY::PS_BLOOM_PARTICLES:
		return &emitter.bloomParticles;
		break;
	}

	return NULL;
}

std::string ParticleSystem::TextureParticlePath()
{
	return std::string(PathFindFileNameA(texture_particle_path.c_str()));
}

std::string ParticleSystem::TextureNoisePath()
{
	return std::string(PathFindFileNameA(texture_noise_path.c_str()));
}

void ParticleSystem::Initialize()
{
	emitter = EMITTER(EMITTER_TYPE::EMIT_POINT,10, FLOAT3_ZERO, 0,0,0, FLOAT4(1,1,1,1), FLOAT4(1,1,1,1), FLOAT4(1,1,1,1), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,0,0, 0, 4, 4, 0, 0, 1);

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
		return emitter.offset;
	}
	if (type == EMITTER_TYPE::EMIT_RECTANGLE)
	{
		FLOAT3 pos = emitter.offset;

		pos.X += RandomFloat(-emitter.rectSizeX * 2, emitter.rectSizeX * 2);
		pos.Z += RandomFloat(-emitter.rectSizeZ * 2, emitter.rectSizeZ * 2);

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
		particles.push_back(PARTICLE(emitter.offset, emitter.velocity, 0, false, RandomIntMinusPlus(), RandomIntMinusPlus(),0));
	}
}

EMITTER ParticleSystem::Emitter()
{
	return emitter;
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