#include "graphics.h"

Graphics::Graphics(QWidget * parent)
{
	setParent(parent);
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);
	
	particlesystem = new ParticleSystem();
	timer = new QTimer;
	timer->setInterval(16.666);
	connect(timer, SIGNAL(timeout()), this, SLOT(Loop()));
	timer->start(0);

	Initialize();
}

void Graphics::Loop()
{

	// Measurement for time spent rendering
	//QElapsedTimer t;
	//t.start();

	// DT is 16 ms (0.016 seconds per frame)
	MoveCamera(camvel * 0.016f * camspeed);
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

Graphics::~Graphics()
{
}

void Graphics::Initialize()
{
	HRESULT hr;
	

	/*===================================================================================*/
	// SWAP CHAIN DESCRIPTION
	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapDesc.BufferCount = 1;
	swapDesc.BufferDesc.Width = W;
	swapDesc.BufferDesc.Height = H;
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
	viewport.Width = W;
	viewport.Height = H;
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





	SetupCamera(XMVectorSet(0, 0, -10, 0), //pos
				XMVectorSet(0, 0, -9,  0), //dir
				XMVectorSet(0, 1, 0, 0));  //up

	shaders.LoadObjectShader(device, context);
	shaders.LoadParticleShader(device, context);
	
	particlesystem->Initialize();
	LoadParticles();
	LoadDebugParticle();
	LoadGroundPlane();
	LoadTextures();
}

void Graphics::SetupCamera(XMVECTOR pos, XMVECTOR dir, XMVECTOR up)
{
	camvel = XMVectorSet(0, 0, 0, 0);
	lastKey = Qt::Key::Key_0;

	campos = pos;
	camdir = dir;
	camup = up;

	World = XMMatrixIdentity();
	View = XMMatrixLookAtLH(campos, camdir, camup);
	Projection = XMMatrixPerspectiveFovLH(0.4f * 3.14f, (float)W / (float)H, 1.0f, 1000.0f);
}

void Graphics::MoveCamera(XMVECTOR pos)
{
	XMVECTOR dir = XMVector4Normalize(camdir - campos);

	campos += pos;
	camdir += pos;
	
	View = XMMatrixLookAtLH(campos, camdir, camup);
}

void Graphics::SetLastCameraMovement(Qt::Key key, bool released)
{

	if (released == true && key == lastKey)
	{
		camvel = XMVectorSet(0, 0, 0, 0);
		return;
	}

	if (released == false)
	{
		switch (key)
		{
		case Qt::Key::Key_W:
			camvel = XMVectorSet(0, 0, 1, 0);
			break;

		case Qt::Key::Key_A:
			camvel = XMVectorSet(-1, 0, 0, 0);
			break;

		case Qt::Key::Key_S:
			camvel = XMVectorSet(0, 0, -1, 0);
			break;

		case Qt::Key::Key_D:
			camvel = XMVectorSet(1, 0, 0, 0);
			break;

		default:
			break;
		}

		lastKey = key;
	}
}

void Graphics::LoadParticles()
{
	HRESULT hr;

	std::vector<POSITION> positions = particlesystem->AllParticlePositions();
	unsigned int count = positions.size();

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(vertexDesc));
	//vertexDesc.ByteWidth = sizeof(POSITION) * count*2;	//NOTE!!!!!! this is just simply reserved space for further vertices.
	vertexDesc.ByteWidth = sizeof(POSITION) * count;
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

	debugParticle = { 0, 0, 0 };

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(vertexDesc));
	vertexDesc.ByteWidth = sizeof(POSITION);
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

void Graphics::LoadGroundPlane()
{
	HRESULT hr;
	groundVertexData =
	{
		// QUAD:
		// 0, 2, 1, 1, 2, 3 
		//{ -5, 0, 5, 0, 0 }, // TOP LEFT  (0)
		//{ -5, 0,-5, 0, 1 }, // BOT LEFT  (1)
		//{  5, 0, 5, 1, 0 }, // TOP RIGHT (2)
		//{  5, 0,-5, 1, 1 }, // BOT RIGHT (3)


		// TRIANGLE 0
		{ -5, -5, 5, 0, 0 },
		{  5, -5, 5, 1, 0 },
		{ -5, -5,-5, 0, 1 },

		// TRIANGLE 1
		{ -5, -5,-5, 0, 1 },
		{  5, -5, 5, 1, 0 },
		{  5, -5,-5, 1, 1 }
	};


	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(D3D11_BUFFER_DESC));
	vertexDesc.ByteWidth = sizeof(VERTEX) * groundVertexData.size();
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.CPUAccessFlags = 0;
	vertexDesc.MiscFlags = 0;
	vertexDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory(&vertexData, sizeof(vertexData));
	vertexData.pSysMem = groundVertexData.data();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(&vertexDesc, &vertexData, &groundVertexBuffer);
}

void Graphics::LoadTextures()
{
	HRESULT hr;
	ID3D11ShaderResourceView* texture;
	textures.push_back(texture);
	textures.push_back(texture);
	textures.push_back(texture);

	hr = D3DX11CreateShaderResourceViewFromFileA(device, std::string(Utility::Path() + "Data\\Textures\\debug.png").c_str(),			NULL, NULL, &textures[0],  NULL);
	hr = D3DX11CreateShaderResourceViewFromFileA(device, std::string(Utility::Path() + "Data\\Textures\\plasmaball.png").c_str(),		NULL, NULL, &textures[1],  NULL);
	hr = D3DX11CreateShaderResourceViewFromFileA(device, std::string(Utility::Path() + "Data\\Textures\\debug_transparent.png").c_str(),NULL, NULL, &textures[2],  NULL);
	hr = D3DX11CreateShaderResourceViewFromFileA(device, std::string(Utility::Path() + "Data\\Textures\\debug_wireframe.png").c_str(),	NULL, NULL, &texture_debug,NULL);
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

void Graphics::SetParticleSystem(PARTICLESYSTEM ps)
{
	particlesystem->Rebuild(ps);
}

void Graphics::PauseSimulation()
{
	particlesystem->Pause();
}

void Graphics::ParticleInspectionLabel(QLabel* label)
{
	inspectorLabel = label;
}

void Graphics::UpdateInspectorText()
{
	POSITION pos = particlesystem->GetPosition(particleDebugID);

	char buffer[64];
	sprintf(buffer, "X: %.2f Y: %.2f Z: %.2f", pos.X, pos.Y, pos.Z);
	inspectorLabel->setText(buffer);
}

int Graphics::TestIntersection(int x, int y, XMFLOAT3 &particlePos)
{
	//particlesystem->ModifyParticle(0, POSITION(0, 1, 0));



	//float nX = (2.0f * x / W - 1.0f);
	//float nY = (-2.0f * y / H + 1.0f);
	unsigned int count = -1;
	std::vector<POSITION> particles = particlesystem->ParticlePositionData(count);

	for (unsigned int i = 0; i < count; i++)
	{
		// FIND ORIGINAL PARTICLE POS
		XMVECTOR pos = XMVectorSet(particles[i].X, particles[i].Y, particles[i].Z, 1.0f);

		XMVECTOR up = XMVector3Normalize(camup) * sizeY;
		XMVECTOR normal = XMVector3Normalize(pos - campos);
		XMVECTOR right = XMVector3Normalize(XMVector3Cross(normal, up)) * sizeX;

		XMVECTOR vec0 = pos - right + up; //XMVectorSet(-5, 5, 0, 1);
		XMVECTOR vec1 = pos - right - up; //XMVectorSet(-5,-5, 0, 1);
		XMVECTOR vec2 = pos + right + up; //XMVectorSet(5, 5, 0, 1);
		XMVECTOR vec3 = pos + right - up; //XMVectorSet(5, -5, 0, 1);

		World = XMMatrixIdentity();
		XMVECTOR nVec0 = XMVector3Project(vec0, 0, 0, W, H, 0, 1, Projection, View, World);
		XMVECTOR nVec1 = XMVector3Project(vec1, 0, 0, W, H, 0, 1, Projection, View, World);
		XMVECTOR nVec2 = XMVector3Project(vec2, 0, 0, W, H, 0, 1, Projection, View, World);
		XMVECTOR nVec3 = XMVector3Project(vec3, 0, 0, W, H, 0, 1, Projection, View, World);

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

void Graphics::AddParticle(POSITION p)
{
	//This function adds ONE particle to the existing particle amount.


	// Original vertex amount
	unsigned int originalParticleCount = particlesystem->ParticleCount();
	unsigned int newParticleCount = -1;

	// Add one particle to the vector
	particlesystem->AddParticle(p);

	// Get the data pointer
	std::vector<POSITION> positions = particlesystem->ParticlePositionData(newParticleCount);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	// Discard the whole old system and set a new one
	context->Map(particleVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy(mappedResource.pData, positions.data(), sizeof(POSITION) * newParticleCount);
	context->Unmap(particleVertexBuffer, 0);
}

void Graphics::UploadParticleBuffer()
{
	unsigned int count = -1;

	// Fetch the data & count from the PS
	std::vector<POSITION> positions = particlesystem->ParticlePositionData(count);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));
	HRESULT hr = context->Map(particleVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy((POSITION*)mappedResource.pData, positions.data(), sizeof(POSITION) * count);
	context->Unmap(particleVertexBuffer, 0);
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






	particlesystem->Update(ms);
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


	// SETUP & DRAW GROUND PLANE
	stride = sizeof(VERTEX);
	offset = 0;
	shaders.SetObjectShader(context);
	context->IASetVertexBuffers(0, 1, &groundVertexBuffer, &stride, &offset);
	cBufferVertex.wvp = XMMatrixTranspose(WVP);
	context->UpdateSubresource(constantBufferVertex, 0, NULL, &cBufferVertex, 0, 0);
	context->VSSetConstantBuffers(0, 1, &constantBufferVertex);

	if (debug == false)
	{
		context->PSSetSamplers(0, 1, &textureSamplerState);
		context->PSSetShaderResources(0, 1, &textures[0]);
		context->Draw(groundVertexData.size(), 0);

	}
	else
	{
		RenderDebugObject(groundVertexData.size());
	}

	
	// SETUP & DRAW PARTICLES
	UploadParticleBuffer();

	stride = sizeof(POSITION);
	offset = 0;
	shaders.SetParticleShader(context);
	context->IASetVertexBuffers(0, 1, &particleVertexBuffer, &stride, &offset);
	cBufferParticle.wvp = XMMatrixTranspose(WVP);
	cBufferParticle.world = XMMatrixTranspose(World);
	cBufferParticle.campos = campos;
	cBufferParticle.camup = XMVectorSet(0, 1, 0, 1);
	cBufferParticle.size = XMFLOAT2(sizeX, sizeY);
	context->UpdateSubresource(constantBufferParticle, 0, NULL, &cBufferParticle, 0, 0);
	context->VSSetConstantBuffers(0, 1, &constantBufferParticle);
	context->GSSetConstantBuffers(0, 1, &constantBufferParticle);
	context->PSSetSamplers(0, 1, &textureSamplerState);

	if (debug == true)
	{
		// Debug texture
		context->PSSetShaderResources(0, 1, &textures[0]);
		RenderDebugObject(particlesystem->GetSize());
	}
	else
	{
		// Regular texture
		context->PSSetShaderResources(0, 1, &textures[1]);
		context->Draw(particlesystem->GetSize(), 0);

	}

	if (particleDebugID > -1)
	{
		context->IASetVertexBuffers(0, 1, &particleVertexBuffer, &stride, &offset);
		RenderDebugParticle(particleDebugID);
	}

	//if (debug == true) { RenderDebug(particleData.size()); }

	int vsync = 0;
#ifdef VSYNC_1
	vsync = 1;
#endif
	swapChain->Present(vsync, 0);
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
	debugParticle = particlesystem->GetPosition(particleID);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	context->Map(particleDebugVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy((POSITION*)mappedResource.pData, &debugParticle, sizeof(POSITION));
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
