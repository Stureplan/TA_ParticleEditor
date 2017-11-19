#include "graphics.h"

Graphics::Graphics(QWidget * parent)
{
	setParent(parent);
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);
	
	particlesystem = new ParticleSystem();


	Initialize();

	timer = new QTimer;
	timer->setInterval(16.666);
	connect(timer, SIGNAL(timeout()), this, SLOT(Loop()));
	timer->start(0);

}



Graphics::~Graphics()
{
	delete timer;
	delete particlesystem;


	device->Release();
	context->Release();
	swapChain->Release();
	renderTargetView->Release();
	backBuffer->Release();
	textureSamplerState->Release();
	blendState->Release();
	rasterizerState->Release();

	constantBufferVertex->Release();
	constantBufferParticle->Release();
	constantBufferParticleAnimated->Release();

	particleVertexBuffer->Release();
	positionGizmoVertexBuffer->Release();
	emitterTypeGizmoVertexBuffer->Release();
	particleDebugVertexBuffer->Release();


	for (unsigned int i = 0; i < textures.size(); i++)
	{
		textures[i]->Release();
	}
	texture_debug->Release();

}

void Graphics::Loop()
{

	// Measurement for time spent rendering
	//QElapsedTimer t;
	//t.start();

	// DT is 16 ms (0.016 seconds per frame)
	//camvel = XMVector4Transform(camvel, v);
	
	MoveCamera  (camvel * ms * movespeed);
	RotateCamera(camrotX * ms * rotspeed, camrotY * ms * rotspeed);
	Update();
	Render();

	
	ULONGLONG now = GetTickCount64() - last;
	if (now > 0)
	{
		ms = (float)now / 1000;
	}

	last = GetTickCount64();
	// Measure time spent rendering (does it even work?)
	//qint64 time = t.elapsed();
	//qint64 time = t.nsecsElapsed();
}


void Graphics::Initialize()
{
	HRESULT hr;
	

	/*===================================================================================*/
	// SWAP CHAIN DESCRIPTION
	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapDesc.BufferCount = 1;
	swapDesc.BufferDesc.Width = WIDTH;
	swapDesc.BufferDesc.Height = HEIGHT;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.SampleDesc.Count = 4;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.Windowed = true;
	swapDesc.OutputWindow = (HWND)winId();
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0,	NULL, NULL, D3D11_SDK_VERSION, &swapDesc, &swapChain, &device, NULL, &context);
	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
	hr = device->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
	backBuffer->Release();
	/*===================================================================================*/



	/*===================================================================================*/
	// TEXTURE DESCRIPTION
	D3D11_SAMPLER_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	textureDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	textureDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	textureDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	textureDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	textureDesc.MinLOD = 0;
	textureDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = device->CreateSamplerState(&textureDesc, &textureSamplerState);

	context->OMSetRenderTargets(1, &renderTargetView, NULL);
	/*===================================================================================*/



	/*===================================================================================*/
	// BLENDING DESCRIPTION
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_INV_DEST_ALPHA;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	device->CreateBlendState(&blendDesc, &blendState);
	float blendFactor[] = { 0,0,0,0 };
	UINT sampleMask = 0xffffffff;

	context->OMSetBlendState(blendState, blendFactor, sampleMask);
	/*===================================================================================*/



	/*===================================================================================*/
	// WIREFRAME DESCRIPTION
	D3D11_RASTERIZER_DESC wireframeDesc;
	ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
	wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
	wireframeDesc.CullMode = D3D11_CULL_NONE;

	device->CreateRasterizerState(&wireframeDesc, &rasterizerState);
	/*===================================================================================*/



	/*===================================================================================*/
	// VIEWPORT SETUP
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = WIDTH;
	viewport.Height = HEIGHT;
	context->RSSetViewports(1, &viewport);
	/*===================================================================================*/



	/*===================================================================================*/
	// CONSTANT BUFFER VERTEX SETUP
	D3D11_BUFFER_DESC cb_vertex_Desc;
	ZeroMemory(&cb_vertex_Desc, sizeof(D3D11_BUFFER_DESC));
	cb_vertex_Desc.Usage = D3D11_USAGE_DEFAULT;
	cb_vertex_Desc.ByteWidth = sizeof(cBufferVertex);
	cb_vertex_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb_vertex_Desc.CPUAccessFlags = 0;
	cb_vertex_Desc.MiscFlags = 0;
	cb_vertex_Desc.StructureByteStride = 0;
	hr = device->CreateBuffer(&cb_vertex_Desc, NULL, &constantBufferVertex);
	/*===================================================================================*/



	/*===================================================================================*/
	// CONSTANT BUFFER PARTICLE SETUP
	D3D11_BUFFER_DESC cb_particle_Desc;
	ZeroMemory(&cb_particle_Desc, sizeof(D3D11_BUFFER_DESC));
	cb_particle_Desc.Usage = D3D11_USAGE_DEFAULT;
	cb_particle_Desc.ByteWidth = sizeof(cBufferParticle);
	cb_particle_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb_particle_Desc.CPUAccessFlags = 0;
	cb_particle_Desc.MiscFlags = 0;
	cb_particle_Desc.StructureByteStride = 0;
	hr = device->CreateBuffer(&cb_particle_Desc, NULL, &constantBufferParticle);
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
	hr = device->CreateBuffer(&cb_particle_animated_Desc, NULL, &constantBufferParticleAnimated);
	/*===================================================================================*/

	cBufferVertex.wvp = XMMatrixIdentity();

	SetupCamera(XMVectorSet(0, 1, -10.0f, 0), //pos
				XMVectorSet(0, 1, -9.0f,  0), //dir
				XMVectorSet(0, 2, 0, 0));  //up

	shaders.LoadGizmoShader(device, context);
	shaders.LoadParticleShader(device, context, "particle.hlsl");
	
	particlesystem->Initialize();
	LoadParticles();
	LoadDebugParticle();
	LoadPositionGizmo();
	LoadEmitterTypeGizmo(EMITTER_TYPE::EMIT_POINT);

	LoadTextures();
}

void Graphics::SetupCamera(XMVECTOR pos, XMVECTOR dir, XMVECTOR up)
{
	camvel = 0.0f;
	camrotX = 0.0f;
	camrotY = 0.0f;

	lastMoveKey = Qt::Key::Key_0;
	lastRotKey  = Qt::Key::Key_0;

	campos = pos;
	camdir = dir;
	camup = up;
	
	World = XMMatrixIdentity();
	View = XMMatrixLookAtLH(campos, camdir, camup);
	Projection = XMMatrixPerspectiveFovLH(0.4f * 3.14f, (float)WIDTH / (float)HEIGHT, 1.0f, 1000.0f);

	v = XMMatrixIdentity();
}

void Graphics::MoveCamera(float z)
{
	float distance = XMVectorGetX(XMVector4Length(XMVectorSet(0,1.0f,0.0f,0) - (campos + (camdir*z))));

	if (distance > 2.0f && distance < 40.0f)
	{
		campos += (camdir * z);
		View = XMMatrixLookAtLH(campos, camdir, camup);
	}
}

void Graphics::RotateCamera(float rotX, float rotY)
{
	v = XMMatrixRotationX(rotX) * XMMatrixRotationY(rotY);

	campos = XMVector4Transform(campos, v);
	camdir = XMVector4Normalize(XMVector4Transform(camdir, v));
	View = XMMatrixLookAtLH(campos, camdir, camup);
}

void Graphics::SetLastCameraMovement(Qt::Key key, bool released)
{

	if (released == true && key == lastMoveKey)
	{
		camvel = 0.0f;
		return;
	}

	if (released == false)
	{
		switch (key)
		{
		case Qt::Key::Key_W:
			camvel = -1.0f;
			break;

		case Qt::Key::Key_S:
			camvel = 1.0f;
			break;

		default:
			break;
		}

		lastMoveKey = key;
	}
}

void Graphics::SetLastCameraRotation(Qt::Key key, bool released)
{
	if (released == true && key == lastRotKey)
	{
		camrotX = 0.0f;
		camrotY = 0.0f;
		return;
	}

	if (released == false)
	{
		switch (key)
		{
		case Qt::Key::Key_A:
			camrotY = 1.0f;
			break;

		case Qt::Key::Key_D:
			camrotY = -1.0f;
			break;

		case Qt::Key::Key_Shift:
			camrotX = 1.0f;
			break;

		case Qt::Key::Key_Control:
			camrotX = -1.0f;
			break;

		default:
			break;
		}

		lastRotKey = key;
	}
}

void Graphics::LoadParticles()
{
	HRESULT hr;

	std::vector<PARTICLE_VERTEX> positions = particlesystem->AllParticleData();
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

	hr = device->CreateBuffer(&vertexDesc, &vertexData, &particleVertexBuffer);
}

void Graphics::LoadDebugParticle()
{
	HRESULT hr;

	debugParticle = { {0, 0, 0}, {0, 0, 0}, 0 };

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(vertexDesc));
	vertexDesc.ByteWidth = sizeof(PARTICLE_VERTEX);
	vertexDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexDesc.MiscFlags = 0;
	vertexDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory(&vertexData, sizeof(vertexData));
	vertexData.pSysMem = &debugParticle;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(&vertexDesc, &vertexData, &particleDebugVertexBuffer);
}

void Graphics::LoadPositionGizmo()
{
	HRESULT hr;

	positionGizmoVertexData =
	{
		{ 0, 0, 0,	1, 0, 0 },
		
		// R
		{ 1, 0, 0,	1, 0, 0 },
		{ 0, 0, 0,	1, 0, 0 },

		// G
		{ 0, 1, 0,	0, 1, 0 },
		{ 0, 0, 0,	0, 1, 0 },

		// B
		{ 0, 0, 1,	0, 0, 1 },
		{ 0, 0, 0,	0, 0, 1 }
	};

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(D3D11_BUFFER_DESC));
	vertexDesc.ByteWidth = sizeof(GIZMO_VERTEX) * positionGizmoVertexData.size();
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.CPUAccessFlags = 0;
	vertexDesc.MiscFlags = 0;
	vertexDesc.StructureByteStride = 0;
	
	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory(&vertexData, sizeof(vertexData));
	vertexData.pSysMem = positionGizmoVertexData.data();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(&vertexDesc, &vertexData, &positionGizmoVertexBuffer);
}

void Graphics::LoadEmitterTypeGizmo(EMITTER_TYPE type)
{
	HRESULT hr;

	if (type == EMITTER_TYPE::EMIT_POINT)
	{
		emitterTypeGizmoVertexData =
		{
			{ 
				0, 0, 0, 
				0, 0, 0
			}
		};
	}

	if (type == EMITTER_TYPE::EMIT_RECTANGLE)
	{
		emitterTypeGizmoVertexData =
		{
			// QUAD: (TRIANGLELIST W. INDICES)
			// 0, 2, 1, 1, 2, 3 
			//{ -5, 0, 5, 0, 0 }, // TOP LEFT  (0)
			//{ -5, 0,-5, 0, 1 }, // BOT LEFT  (1)
			//{  5, 0, 5, 1, 0 }, // TOP RIGHT (2)
			//{  5, 0,-5, 1, 1 }, // BOT RIGHT (3)

			// QUAD: (LINESTRIP)
			{ 
				-2, 0, 2, 
				 1, 0, 1 
			}, // TOP LEFT  (0)
			{ 
				2, 0, 2, 
				1, 0, 1 
			}, // TOP RIGHT (2)
			{ 
				2, 0,-2, 
				1, 0, 1 
			}, // BOT RIGHT (3)
			{ 
				-2, 0,-2, 
				1, 0, 1 
			}, // BOT LEFT  (1)
			{ 
				-2, 0, 2, 
				1, 0, 1 
			}  // TOP LEFT  (0)

			// QUAD: (TRIANGLELIST W/O INDICES)
			// TRIANGLE 0
			//{ -5, -5, 5, 0, 0 },
			//{  5, -5, 5, 1, 0 },
			//{ -5, -5,-5, 0, 1 },

			// TRIANGLE 1
			//{ -5, -5,-5, 0, 1 },
			//{  5, -5, 5, 1, 0 },
			//{  5, -5,-5, 1, 1 }
		};
	}




	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(D3D11_BUFFER_DESC));
	vertexDesc.ByteWidth = sizeof(GIZMO_VERTEX) * emitterTypeGizmoVertexData.size();
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.CPUAccessFlags = 0;
	vertexDesc.MiscFlags = 0;
	vertexDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory(&vertexData, sizeof(vertexData));
	vertexData.pSysMem = emitterTypeGizmoVertexData.data();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(&vertexDesc, &vertexData, &emitterTypeGizmoVertexBuffer);
}

void Graphics::GainedFocus()
{
	shaders.ReloadLastShader(device, context);
}

void Graphics::LoadTextures()
{
	textures.push_back(nullptr);
	textures.push_back(nullptr);
	textures.push_back(nullptr);
	textures.push_back(nullptr);

	DX::LoadTexture(device, textures[0], Utility::Path() + "Data\\Textures\\debug.png");
	DX::LoadTexture(device, textures[1], Utility::Path() + "Data\\Textures\\plasmaball.png");
	DX::LoadTexture(device, textures[2], Utility::Path() + "Data\\Textures\\debug_transparent.png");
	DX::LoadTexture(device, textures[3], Utility::Path() + "Data\\Textures\\noise.png");
	DX::LoadTexture(device, texture_debug, Utility::Path() + "Data\\Textures\\debug_wireframe.png");
}

void Graphics::Retexture(std::string path)
{
	bool result = DX::LoadTexture(device, textures[1], path);
	if (result == false)
	{
		MessageBoxA(NULL, std::string("Texture at: " + path + " was not found!\nLoading default texture.").c_str(), "Texture Missing", MB_OK);
		Retexture(Utility::Path() + "Data\\Textures\\plasmaball.png");
	}
}

void Graphics::ChangeTextureType(int type)
{
	if (type == 0)
	{
		// single sprite
		shaders.LoadParticleShader(device, context, "particle.hlsl");
	}
	if (type == 1)
	{
		// sprite sheet
		shaders.LoadParticleShader(device, context, "particle_animated.hlsl");
	}
	if (type == 2)
	{
		// sprite sheet (faded)
		shaders.LoadParticleShader(device, context, "particle_animated_faded.hlsl");
	}
}

void Graphics::ChangeRasterization(D3D11_FILL_MODE fillmode)
{
	if (fillmode == D3D11_FILL_MODE::D3D11_FILL_WIREFRAME)
	{
		context->RSSetState(rasterizerState);
	}
	else if (fillmode == D3D11_FILL_MODE::D3D11_FILL_SOLID)
	{
		context->RSSetState(NULL);
	}
}

void Graphics::Rebuild(PARTICLESYSTEM ps)
{
	LoadEmitterTypeGizmo(ps.emittertype);
	particlesystem->Rebuild(ps);
	LoadParticles();
}

void Graphics::PauseSimulation()
{
	paused = !paused;
}

void Graphics::ParticleInspectionLabel(QLabel* label)
{
	inspectorLabel = label;
}

void Graphics::UpdateInspectorText()
{
	PARTICLE_VERTEX p = particlesystem->GetParticle(particleDebugID);
	FLOAT3 pos = p.position;
	float life = p.currentlifetime;

	char buffer[64];
	sprintf(buffer, "X: %.2f Y: %.2f Z: %.2f\nCurrent Lifetime: %.2f", pos.X, pos.Y, pos.Z, life);
	inspectorLabel->setText(buffer);
}

int Graphics::TestIntersection(int x, int y, XMFLOAT3 &particlePos)
{
	unsigned int count = -1;
	std::vector<PARTICLE_VERTEX> particles = particlesystem->ParticleData(count);

	for (unsigned int i = 0; i < count; i++)
	{
		// FIND ORIGINAL PARTICLE POS
		XMVECTOR pos = XMVectorSet(particles[i].position.X, particles[i].position.Y, particles[i].position.Z, 1.0f);
		XMVECTOR up = XMVector3Normalize(camup) * *(float*)particlesystem->GetProperty(PS_PROPERTY::PS_START_SIZE_Y);
		XMVECTOR normal = XMVector3Normalize(pos - campos);
		XMVECTOR right = XMVector3Normalize(XMVector3Cross(normal, up)) * *(float*)particlesystem->GetProperty(PS_PROPERTY::PS_START_SIZE_X);

		XMVECTOR vec0 = pos - right + up; //XMVectorSet(-5, 5, 0, 1);
		XMVECTOR vec1 = pos - right - up; //XMVectorSet(-5,-5, 0, 1);
		XMVECTOR vec2 = pos + right + up; //XMVectorSet(5, 5, 0, 1);
		XMVECTOR vec3 = pos + right - up; //XMVectorSet(5, -5, 0, 1);

		World = XMMatrixIdentity();
		XMVECTOR nVec0 = XMVector3Project(vec0, 0, 0, WIDTH, HEIGHT, 0, 1, Projection, View, World);
		XMVECTOR nVec1 = XMVector3Project(vec1, 0, 0, WIDTH, HEIGHT, 0, 1, Projection, View, World);
		XMVECTOR nVec2 = XMVector3Project(vec2, 0, 0, WIDTH, HEIGHT, 0, 1, Projection, View, World);
		XMVECTOR nVec3 = XMVector3Project(vec3, 0, 0, WIDTH, HEIGHT, 0, 1, Projection, View, World);

		XMFLOAT2 pixel0;
		XMStoreFloat2(&pixel0, nVec0);
		XMFLOAT2 pixel1;
		XMStoreFloat2(&pixel1, nVec1);
		XMFLOAT2 pixel2;
		XMStoreFloat2(&pixel2, nVec2);
		XMFLOAT2 pixel3;
		XMStoreFloat2(&pixel3, nVec3);


		bool t1 = PointInTriangle(x, y, pixel0.x, pixel0.y, pixel1.x, pixel1.y, pixel2.x, pixel2.y);
		bool t2 = PointInTriangle(x, y, pixel1.x, pixel1.y, pixel3.x, pixel3.y, pixel2.x, pixel2.y);

		if (t1 == true || t2 == true)
		{
			XMStoreFloat3(&particlePos, pos);
			particleDebugID = i;
			return i;
		}
	}

	particleDebugID = -1;
	return -1;
}
bool Graphics::PointInTriangle(float x, float y, float x1, float y1, float x2, float y2, float x3, float y3)
{
	float l1 = (x - x1)*(y3 - y1) - (x3 - x1)*(y - y1);
	float l2 = (x - x2)*(y1 - y2) - (x1 - x2)*(y - y2);
	float l3 = (x - x3)*(y2 - y3) - (x2 - x3)*(y - y3);

	return (l1>0 && l2>0 && l3>0) || (l1<0 && l2<0 && l3<0);
}

void Graphics::ResizeParticleSystem(unsigned int count)
{
	//This function clears every particle and recreates the data.
}

void Graphics::AddParticleSystem(PARTICLESYSTEM ps)
{
	particlesystems.push_back(ps);
}

void Graphics::RemoveParticleSystem(int index)
{
	particlesystems.erase(particlesystems.begin() + index);
}

PARTICLESYSTEM Graphics::ParticleSystemByIndex(int index)
{
	return particlesystems.at(index);
}

void Graphics::AddParticle(FLOAT3 p)
{
	//This function adds ONE particle to the existing particle amount.


	// Original vertex amount
	unsigned int originalParticleCount = particlesystem->ParticleCount();
	unsigned int newParticleCount = -1;

	// Add one particle to the vector
	particlesystem->AddParticle(p);

	// Get the data pointer
	std::vector<PARTICLE_VERTEX> positions = particlesystem->ParticleData(newParticleCount);
	
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	// Discard the whole old system and set a new one
	context->Map(particleVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy(mappedResource.pData, positions.data(), sizeof(PARTICLE_VERTEX) * newParticleCount);
	context->Unmap(particleVertexBuffer, 0);
}

void Graphics::UploadParticleBuffer()
{
	unsigned int count = -1;

	// Fetch the data & count from the PS
	std::vector<PARTICLE_VERTEX> positions = particlesystem->ParticleData(count);
	
	if (count > 0)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));
		HRESULT hr = context->Map(particleVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy((PARTICLE_VERTEX*)mappedResource.pData, positions.data(), sizeof(PARTICLE_VERTEX) * count);
		context->Unmap(particleVertexBuffer, 0);
	}
}


void Graphics::Debug(bool active)
{
	debug = active;
}

void Graphics::Update()
{
	frame++;

#ifdef VSYNC_1
	if (frame == 10)
	{
		if (particleDebugID > -1 && particlesystem->IsAlive(particleDebugID))
		{
			UpdateInspectorText();
		}
		frame = 0;
	}
#else
	if (frame == 1000)
	{
		if (particleDebugID > -1 && particlesystem->IsAlive(particleDebugID))
		{
			UpdateInspectorText();
		}
		frame = 0;
	}
#endif // VSYNC





	//if (frame == 0) { ms = 0.016f; }

	if (paused == false)
	{
		particlesystem->Update(0.016f);
	}
}

void Graphics::Render()
{
	float color[4]  = { 0.2f, 0.2f, 0.2f, 1.0f };
	context->ClearRenderTargetView(renderTargetView, color);
	amt++;
	if (amt > 99) amt = 0;

	// GENERAL SETTINGS
	UINT stride;
	UINT offset;
	World = XMMatrixIdentity();
	WVP = World * View * Projection;


	// DRAW POSITION GIZMO
	stride = sizeof(GIZMO_VERTEX);
	offset = 0;
	shaders.SetGizmoShader(context);
	context->IASetVertexBuffers(0, 1, &positionGizmoVertexBuffer, &stride, &offset);
	cBufferVertex.wvp = XMMatrixTranspose(WVP);
	context->UpdateSubresource(constantBufferVertex, 0, NULL, &cBufferVertex, 0, 0);
	context->VSSetConstantBuffers(0, 1, &constantBufferVertex);
	RenderDebugObject(positionGizmoVertexData.size());

	EMITTER_TYPE emitterType = *(EMITTER_TYPE*)particlesystem->GetProperty(PS_PROPERTY::PS_EMITTER_TYPE);
	if (emitterType == EMITTER_TYPE::EMIT_POINT)
	{
		// SETUP & DRAW POINT EMITTER GIZMO
	}

	if (emitterType == EMITTER_TYPE::EMIT_RECTANGLE)
	{
		// SETUP & DRAW EMITTER GIZMO
		World = XMMatrixScaling(*(float*)particlesystem->GetProperty(PS_PROPERTY::PS_RECT_SIZE_X), 1.0f, *(float*)particlesystem->GetProperty(PS_PROPERTY::PS_RECT_SIZE_X));
		WVP = World * View * Projection;
		stride = sizeof(GIZMO_VERTEX);
		offset = 0;
		shaders.SetGizmoShader(context);
		context->IASetVertexBuffers(0, 1, &emitterTypeGizmoVertexBuffer, &stride, &offset);
		cBufferVertex.wvp = XMMatrixTranspose(WVP);
		context->UpdateSubresource(constantBufferVertex, 0, NULL, &cBufferVertex, 0, 0);
		context->VSSetConstantBuffers(0, 1, &constantBufferVertex);
		RenderDebugObject(emitterTypeGizmoVertexData.size());
	}



	
	// SETUP & DRAW PARTICLES
	UploadParticleBuffer();
	stride = sizeof(PARTICLE_VERTEX);
	offset = 0;
	shaders.SetParticleShader(context);
	context->IASetVertexBuffers(0, 1, &particleVertexBuffer, &stride, &offset);
	
	World = XMMatrixIdentity();
	WVP = World * View * Projection;

	//TODO: Move entire rendering garbage to particlsystem
	//TODO: Decide if we want to move entire rendering garbage to particlesystem
	int textureType = *(int*)particlesystem->GetProperty(PS_PROPERTY::PS_TEXTURE_TYPE);
	if (textureType == 0)
	{
		cBufferParticle.wvp = XMMatrixTranspose(WVP);
		cBufferParticle.world = XMMatrixTranspose(World);
		cBufferParticle.campos = campos;
		cBufferParticle.camup = XMVectorSet(0, 1, 0, 1);
		cBufferParticle.startsize = XMFLOAT2(*(float*)particlesystem->GetProperty(PS_PROPERTY::PS_START_SIZE_X), *(float*)particlesystem->GetProperty(PS_PROPERTY::PS_START_SIZE_Y));
		cBufferParticle.endsize = XMFLOAT2(*(float*)particlesystem->GetProperty(PS_PROPERTY::PS_END_SIZE_X), *(float*)particlesystem->GetProperty(PS_PROPERTY::PS_END_SIZE_Y));
		cBufferParticle.colin = *(FLOAT4*)particlesystem->GetProperty(PS_PROPERTY::PS_COLOR_IN);
		cBufferParticle.colout = *(FLOAT4*)particlesystem->GetProperty(PS_PROPERTY::PS_COLOR_OUT);
		cBufferParticle.lifetime = *(float*)particlesystem->GetProperty(PS_PROPERTY::PS_LIFETIME);

		context->UpdateSubresource(constantBufferParticle, 0, NULL, &cBufferParticle, 0, 0);
		context->VSSetConstantBuffers(0, 1, &constantBufferParticle);
		context->GSSetConstantBuffers(0, 1, &constantBufferParticle);
		context->PSSetConstantBuffers(0, 1, &constantBufferParticle);
		context->PSSetSamplers(0, 1, &textureSamplerState);
	}
	
	if (textureType == 1 || textureType == 2)
	{
		cBufferParticleAnimated.wvp = XMMatrixTranspose(WVP);
		cBufferParticleAnimated.world = XMMatrixTranspose(World);
		cBufferParticleAnimated.campos = campos;
		cBufferParticleAnimated.camup = XMVectorSet(0, 1, 0, 1);
		cBufferParticleAnimated.startsize = XMFLOAT2(*(float*)particlesystem->GetProperty(PS_PROPERTY::PS_START_SIZE_X), *(float*)particlesystem->GetProperty(PS_PROPERTY::PS_START_SIZE_Y));
		cBufferParticleAnimated.endsize = XMFLOAT2(*(float*)particlesystem->GetProperty(PS_PROPERTY::PS_END_SIZE_X), *(float*)particlesystem->GetProperty(PS_PROPERTY::PS_END_SIZE_Y));
		cBufferParticleAnimated.colin = *(FLOAT4*)particlesystem->GetProperty(PS_PROPERTY::PS_COLOR_IN);
		cBufferParticleAnimated.colout = *(FLOAT4*)particlesystem->GetProperty(PS_PROPERTY::PS_COLOR_OUT);
		cBufferParticleAnimated.lifetime = *(float*)particlesystem->GetProperty(PS_PROPERTY::PS_LIFETIME);
		cBufferParticleAnimated.columns = *(int*)particlesystem->GetProperty(PS_PROPERTY::PS_TEXTURE_COLUMNS);
		cBufferParticleAnimated.rows = *(int*)particlesystem->GetProperty(PS_PROPERTY::PS_TEXTURE_ROWS);


		context->UpdateSubresource(constantBufferParticleAnimated, 0, NULL, &cBufferParticleAnimated, 0, 0);
		context->VSSetConstantBuffers(0, 1, &constantBufferParticleAnimated);
		context->GSSetConstantBuffers(0, 1, &constantBufferParticleAnimated);
		context->PSSetConstantBuffers(0, 1, &constantBufferParticleAnimated);
		context->PSSetSamplers(0, 1, &textureSamplerState);
	}


	if (debug == true)
	{
		// Pink Debug texture
		cBufferParticle.colin  = COLOR_WHITE;
		cBufferParticle.colout = COLOR_WHITE;
		context->UpdateSubresource(constantBufferParticle, 0, NULL, &cBufferParticle, 0, 0);
		context->PSSetConstantBuffers(0, 1, &constantBufferParticle);


		context->PSSetShaderResources(0, 1, &textures[0]);
		RenderDebugObject(particlesystem->GetSize());
	}
	else
	{
		unsigned int particleCount = particlesystem->GetSize();
		// Regular texture
		context->VSSetShaderResources(0, 1, &textures[3]);
		context->PSSetShaderResources(0, 1, &textures[1]);
		context->Draw(particleCount, 0);
	}

	if (particleDebugID > -1)
	{
		context->IASetVertexBuffers(0, 1, &particleDebugVertexBuffer, &stride, &offset);
		RenderDebugParticle(particleDebugID);
	}
	
	swapChain->Present(VSYNC, 0);
}

void Graphics::RenderDebugObject(unsigned int vtxcount)
{
	// Change to wireframe
	ChangeRasterization(D3D11_FILL_WIREFRAME);
	
	// Render wireframe
	context->PSSetSamplers(0, 1, &textureSamplerState);
	context->PSSetShaderResources(0, 1, &texture_debug);
	context->Draw(vtxcount, 0);

	// Change back to fill
	ChangeRasterization(D3D11_FILL_SOLID);
}

void Graphics::RenderDebugParticle(unsigned int particleID)
{
	debugParticle = particlesystem->GetParticle(particleID);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	context->Map(particleDebugVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy((PARTICLE_VERTEX*)mappedResource.pData, &debugParticle, sizeof(PARTICLE_VERTEX));
	context->Unmap(particleDebugVertexBuffer, 0);





	// Change to wireframe
	ChangeRasterization(D3D11_FILL_WIREFRAME);

	// Render wireframe
	context->PSSetSamplers(0, 1, &textureSamplerState);
	context->PSSetShaderResources(0, 1, &texture_debug);
	context->Draw(1, 0);

	// Change back to fill
	ChangeRasterization(D3D11_FILL_SOLID);
}

void Graphics::paintEvent(QPaintEvent* evt)
{
	//qt paint
	//Render();
}