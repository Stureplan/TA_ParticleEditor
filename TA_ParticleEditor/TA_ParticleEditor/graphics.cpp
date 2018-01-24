#include "graphics.h"

Graphics::Graphics(QWidget * parent)
{
	setParent(parent);
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);
	
	particlesystems.push_back(new ParticleSystem());
	positionGizmo = new Gizmo();
	emitterGizmo = new Gizmo();

	Initialize();

	timer = new QTimer;
	timer->setInterval(16.666);
	connect(timer, SIGNAL(timeout()), this, SLOT(Loop()));
	timer->start(0);

}



Graphics::~Graphics()
{
	delete timer;
	for (int i = 0; i < particlesystems.size(); i++)
	{
		delete particlesystems[i];
	}


	device->Release();
	context->Release();
	swapChain->Release();
	renderTargetView->Release();
	backBuffer->Release();
	textureSamplerState->Release();
	blendState->Release();
	rasterizerState->Release();


	for (unsigned int i = 0; i < textures.size(); i++)
	{
		textures[i]->Release();
	}
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

	SetupCamera(XMVectorSet(0, 1, -10.0f, 0),	//pos
				XMVectorSet(0, 1, -9.0f,  0),	//dir
				XMVectorSet(0, 2, 0, 0));		//up

	shaders.LoadGizmoShader(device, context);
	shaders.LoadParticleAnimatedNoiseShader(device, context, "particle_animated_noise.hlsl");
	shaders.LoadParticleAnimatedShader(device, context, "particle_animated.hlsl");
	shaders.LoadParticleNoiseShader(device, context, "particle_noise.hlsl");
	shaders.LoadParticleShader(device, context, "particle.hlsl");


	for (int i = 0; i < particlesystems.size(); i++)
	{
		particlesystems[i]->Initialize();
		particlesystems[i]->VertexBuffer(device);
		particlesystems[i]->ConstantBuffer(device);
	}
	
	positionGizmo->VertexBuffer(device, std::vector<GIZMO_VERTEX>({{0,0,0,1,0,0},{1,0,0,1,0,0},{0,0,0,1,0,0},{0,1,0,0,1,0},{0,0,0,0,1,0},{0,0,1,0,0,1},{0,0,0,0,0,1}}));
	positionGizmo->ConstantBuffer(device);

	emitterGizmo->VertexBuffer(device, std::vector<GIZMO_VERTEX>({{-2,0,2,1,0,1},{2,0,2,1,0,1},{2,0,-2,1,0,1},{-2,0,-2,1,0,1},{-2,0,2,1,0,1}}));
	emitterGizmo->ConstantBuffer(device);

	LoadTextures();



	shaders.CompileIncludes(false, false);
	shaders.ReloadLastShader(device, context);
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

void Graphics::LoadFullscreenQuad()
{
	HRESULT hr;

	fullscreenQuadVertexData = 
	{
		{ -1, -1, -1, 0, 1 },
		{ -1,  1, -1, 0, 0 },
		{  1,  1, -1, 1, 0 },

		{ -1, -1, -1, 0, 1 },
		{  1,  1, -1, 1, 0 },
		{  1, -1, -1, 1, 1 }
	};
	
	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(D3D11_BUFFER_DESC));
	vertexDesc.ByteWidth = sizeof(VERTEX) * fullscreenQuadVertexData.size();
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.CPUAccessFlags = 0;
	vertexDesc.MiscFlags = 0;
	vertexDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory(&vertexData, sizeof(vertexData));
	vertexData.pSysMem = fullscreenQuadVertexData.data();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(&vertexDesc, &vertexData, &fullscreenQuadVertexBuffer);
	hr = device->CreateShaderResourceView(sharedTexture, NULL, &fullscreenQuadTexture);
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

	DX::LoadTexture(device, textures[0], Utility::Path() + "Data\\Textures\\debug.png");
	DX::LoadTexture(device, textures[1], Utility::Path() + "Data\\Textures\\debug_transparent.png");
	DX::LoadTexture(device, textures[2], Utility::Path() + "Data\\Textures\\debug_wireframe.png");

	for (int i = 0; i < particlesystems.size(); i++)
	{
		particlesystems[i]->LoadParticleTexture	(device, DEFAULT_TEXTURE);
		particlesystems[i]->LoadNoiseTexture	(device, DEFAULT_NOISE_TEXTURE);
	}
}

void Graphics::Retexture(int index, TEXTURE_TYPE type, std::string path)
{
	if (type == TEXTURE_TYPE::TEXTURE)
	{
		bool result = particlesystems[index]->LoadParticleTexture(device, path);
		//bool result = DX::LoadTexture(device, textures[1], path);
		if (result == false)
		{
			MessageBoxA(NULL, std::string("Texture at: " + path + " was not found!\nLoading default texture.").c_str(), "Texture Missing", MB_OK);
			Retexture(index, TEXTURE_TYPE::TEXTURE, Utility::Path() + "Data\\Textures\\plasmaball.png");
		}
	}
	if (type == TEXTURE_TYPE::TEXTURE_NOISE)
	{
		bool result = particlesystems[index]->LoadNoiseTexture(device, path);
		//bool result = DX::LoadTexture(device, textures[3], path);
		if (result == false)
		{
			MessageBoxA(NULL, std::string("Texture at: " + path + " was not found!\nLoading default texture.").c_str(), "Texture Missing", MB_OK);
			Retexture(index, TEXTURE_TYPE::TEXTURE_NOISE, Utility::Path() + "Data\\Textures\\noise_cloud.png");
		}
	}
}

void Graphics::RecompileShader(int index, int type, bool noise)
{
	shaders.CompileIncludes(noise, false);
	int shader = 0;

	if (type == 0 && noise == false)
	{
		// single texture
		shaders.LoadParticleShader(device, context, "particle.hlsl");
		shader = 0;
	}
	if (type == 1 && noise == false)
	{
		// texture sheet
		shaders.LoadParticleAnimatedShader(device, context, "particle_animated.hlsl");
		shader = 1;
	}


	if (type == 0 && noise == true)
	{
		// single texture (with noise)
		shaders.LoadParticleNoiseShader(device, context, "particle_noise.hlsl");
		shader = 2;
	}
	if (type == 1 && noise == true)
	{
		// texture sheet (with noise)
		shaders.LoadParticleAnimatedNoiseShader(device, context, "particle_animated_noise.hlsl");
		shader = 3;
	}

	particlesystems[index]->SetShader(shader);
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

void Graphics::Rebuild(int index, EMITTER ps)
{
	if ((EMITTER_TYPE)ps.emittertype == EMITTER_TYPE::EMIT_POINT)
	{
		//emitterGizmo->VertexBuffer(device,{{0,0,0,0,0,0}});
	}
	if ((EMITTER_TYPE)ps.emittertype == EMITTER_TYPE::EMIT_RECTANGLE)
	{
		//emitterGizmo->VertexBuffer(device,{{-2,0,2,1,0,1},{2,0,2,1,0,1},{2,0,-2,1,0,1},{-2,0,-2,1,0,1},{-2,0,2,1,0,1}});
	}
	particlesystems[index]->Rebuild(ps);
	particlesystems[index]->VertexBuffer(device);
}

void Graphics::PauseSimulation()
{
	paused = !paused;
}

void Graphics::AddParticleSystem(int index, EMITTER ps)
{
	particlesystems.push_back(new ParticleSystem());
	particlesystems[index]->Initialize();
	particlesystems[index]->VertexBuffer(device);
	particlesystems[index]->ConstantBuffer(device);
	particlesystems[index]->Rebuild(ps);
	particlesystems[index]->LoadParticleTexture(device, DEFAULT_TEXTURE);
	particlesystems[index]->LoadNoiseTexture(device, DEFAULT_NOISE_TEXTURE);
	cEmitter = index;
}

void Graphics::RemoveParticleSystem(int index)
{
	particlesystems.erase(particlesystems.begin() + index);
}

EMITTER Graphics::EmitterByIndex(int index)
{
	return particlesystems.at(index)->Emitter();
}

ParticleSystem* Graphics::ParticleSystemByIndex(int index)
{
	return particlesystems.at(index);
}

void Graphics::Debug(bool active)
{
	debug = active;
}

void Graphics::Update()
{
	if (paused == false)
	{
		for (int i = 0; i < particlesystems.size(); i++)
		{
			particlesystems[i]->Update(ms);
		}
		
	}
}

void Graphics::UpdateOnce()
{
	for (int i = 0; i < particlesystems.size(); i++)
	{
		particlesystems[i]->Update(ms);
	}
}

void Graphics::CurrentEmitterIndex(int index)
{
	cEmitter = index;
}

void Graphics::Render()
{
	float color[4]  = { 0.2f, 0.2f, 0.2f, 1.0f };
	context->ClearRenderTargetView(renderTargetView, color);


	for (int i = 0; i < particlesystems.size(); i++)
	{
		// DRAW PARTICLES
		World = XMMatrixIdentity();
		WVP = World * View * Projection;
		camup = XMVector3Transform(XMVectorSet(0, 1, 0, 1), XMMatrixTranspose(View));
		int shader = particlesystems[i]->ShaderIndex();
		if (shader == 0)
		{
			shaders.SetParticleShader(context);
		}
		if (shader == 1)
		{
			shaders.SetParticleAnimatedShader(context);
		}
		if (shader == 2)
		{
			shaders.SetParticleNoiseShader(context);
		}
		if (shader == 3)
		{
			shaders.SetParticleAnimatedNoiseShader(context);
		}
		particlesystems[i]->UploadParticleBuffer(context);
		particlesystems[i]->UpdateConstantBuffer(context, WVP, World, campos, camup);
		particlesystems[i]->Render(context, textureSamplerState);

		// DRAW DEBUG PARTICLES
		if (debug == true)
		{
			ChangeRasterization(D3D11_FILL_WIREFRAME);
			particlesystems[i]->RenderDebug(context, textureSamplerState, textures[2]);
			ChangeRasterization(D3D11_FILL_SOLID);
		}


		// DRAW POSITION GIZMO
		FLOAT3 pos = *(FLOAT3*)particlesystems[i]->GetProperty(PS_PROPERTY::PS_OFFSET);
		World = XMMatrixIdentity() * XMMatrixTranslation(pos.X, pos.Y, pos.Z);
		WVP = World * View * Projection;
		shaders.SetGizmoShader(context);
		positionGizmo->UpdateConstantBuffer(context, WVP);
		positionGizmo->Render(context, textureSamplerState, textures[2]);
	}





	// DRAW EMITTER GIZMO
	if (*(EMITTER_TYPE*)particlesystems[cEmitter]->GetProperty(PS_PROPERTY::PS_EMITTER_TYPE) == EMITTER_TYPE::EMIT_RECTANGLE)
	{
		World = XMMatrixScaling(*(float*)particlesystems[cEmitter]->GetProperty(PS_PROPERTY::PS_RECT_SIZE_X), 1.0f, *(float*)particlesystems[cEmitter]->GetProperty(PS_PROPERTY::PS_RECT_SIZE_Z));
		WVP = World * View * Projection;
		emitterGizmo->UpdateConstantBuffer(context, WVP);
		emitterGizmo->Render(context, textureSamplerState, textures[2]);
	}



	
	camup = XMVectorSet(0, 1, 0, 1);
	swapChain->Present(VSYNC, 0);
}

void Graphics::paintEvent(QPaintEvent* evt)
{
	//qt paint
	//Render();
}