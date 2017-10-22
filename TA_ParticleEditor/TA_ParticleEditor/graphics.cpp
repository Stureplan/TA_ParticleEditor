#include "graphics.h"

Graphics::Graphics(QWidget * parent)
{
	setParent(parent);
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);
	
	ps = new ParticleSystem();
	timer = new QTimer;
	timer->setInterval(16.666);
	connect(timer, SIGNAL(timeout()), this, SLOT(MyStart()));
	timer->start(0);

	Initialize();
}

void Graphics::MyStart()
{
	// Measurement for time spent rendering
	//QElapsedTimer t;
	//t.start();

	// DT is 16 ms (0.016 seconds per frame)
	MoveCamera(camvel * 0.016f * camspeed);
	Render();


	// Measure time spent rendering (does it even work?)
	//qDebug("%d", t.elapsed());
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
	//LoadShaders();
	
	LoadParticles();
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

void Graphics::LoadShaders()
{
	std::string shaderpath = Utility::Path();

	// Insert shader path
	shaderpath.insert(shaderpath.size(), "Data\\particle.hlsl");
	
	HRESULT hr;
	ID3D10Blob* blob;
	
	blob = NULL;
	hr = D3DX11CompileFromFileA(shaderpath.c_str(), 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, &blob, 0);
	if (hr != S_OK)
	{
		// Something went wrong with the shader
		std::string error = static_cast<char*>(blob->GetBufferPointer());
		MessageBoxA(NULL, error.c_str(), "VS Error", MB_OK);
	}

	blob = NULL;
	hr = D3DX11CompileFromFileA(shaderpath.c_str(), 0, 0, "GShader", "gs_4_0", 0, 0, 0, &GS, &blob, 0);
	if (hr != S_OK)
	{
		// Something went wrong with the shader
		std::string error = static_cast<char*>(blob->GetBufferPointer());
		MessageBoxA(NULL, error.c_str(), "PS Error", MB_OK);
	}

	blob = NULL;
	hr = D3DX11CompileFromFileA(shaderpath.c_str(), 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, &blob, 0);
	if (hr != S_OK)
	{
		// Something went wrong with the shader
		std::string error = static_cast<char*>(blob->GetBufferPointer());
		MessageBoxA(NULL, error.c_str(), "PS Error", MB_OK);
	}

	hr = device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
	hr = device->CreateGeometryShader(GS->GetBufferPointer(), GS->GetBufferSize(), NULL, &pGS);
	hr = device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

	context->VSSetShader(pVS, 0, 0);
	context->GSSetShader(pGS, 0, 0);
	context->PSSetShader(pPS, 0, 0);

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = device->CreateInputLayout(ied, sizeof(ied) / sizeof(ied[0]), VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
	context->IASetInputLayout(pLayout);
	//context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

}


void Graphics::LoadParticles()
{
	HRESULT hr;

	particleData =
	{
		/*{ -5, -5, 0, 0, 1 },
		{ -5, 5, 0, 0, 0 },
		{ 5, 5, 0, 1, 0 },

		{ 5, 5, 0, 1, 0 },
		{ 5, -5, 0, 1, 1 },
		{ -5, -5, 0, 0, 1 }*/
		{ -10, 10, 0 }
		//{-4,-7,0}

	};

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(vertexDesc));
	vertexDesc.ByteWidth = sizeof(PARTICLE) * particleData.size()*2;	//NOTE!!!!!! this is just simply reserved space for further vertices.
	vertexDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexDesc.MiscFlags = 0;
	vertexDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory(&vertexData, sizeof(vertexData));
	vertexData.pSysMem = particleData.data();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(&vertexDesc, &vertexData, &particleVertexBuffer);
}

void Graphics::LoadGroundPlane()
{
	HRESULT hr;
	groundData =
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
	vertexDesc.ByteWidth = sizeof(VERTEX) * groundData.size();
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.CPUAccessFlags = 0;
	vertexDesc.MiscFlags = 0;
	vertexDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory(&vertexData, sizeof(vertexData));
	vertexData.pSysMem = groundData.data();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(&vertexDesc, &vertexData, &groundVertexBuffer);
}

void Graphics::LoadTextures()
{
	HRESULT hr;
	ID3D11ShaderResourceView* tex;
	textures.push_back(tex);
	hr = D3DX11CreateShaderResourceViewFromFileA(device, std::string(Utility::Path()+"Data\\Textures\\debug.png").c_str(), NULL, NULL, &textures[0], NULL);
	hr = D3DX11CreateShaderResourceViewFromFileA(device, std::string(Utility::Path() + "Data\\Textures\\debug_wireframe.png").c_str(), NULL, NULL, &texture_debug, NULL);
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

void Graphics::TestIntersection(int x, int y)
{
	float nX = (2.0f * x / W - 1.0f);
	float nY = (-2.0f * y / H + 1.0f);

	//qDebug("Normalized X: %f", nX);
	//qDebug("Normalized Y: %f", nY);

	XMVECTOR origin = XMVectorSet(nX, nY, 0, 1);
	XMVECTOR destination = XMVectorSet(nX, nY, 1, 1);

	XMMATRIX inverse = XMMatrixInverse(NULL, View * Projection);


	origin = XMVector4Transform(origin, inverse);
	destination = XMVector4Transform(destination, inverse);

	XMFLOAT4 o;
	XMFLOAT4 d;

	XMStoreFloat4(&o, origin);
	XMStoreFloat4(&d, XMVector4Normalize(destination - origin));

	XMVECTOR vec0 = XMVectorSet(-5, 5, 0, 1);
	XMVECTOR vec1 = XMVectorSet(-5,-5, 0, 1);
	XMVECTOR vec2 = XMVectorSet(5, 5, 0, 1);
	XMVECTOR vec3 = XMVectorSet(5, -5, 0, 1);


	World = XMMatrixIdentity();
	XMVECTOR nVec0 = XMVector3Project(vec0, 0, 0, W, H, 0, 1, Projection, View, World);
	XMVECTOR nVec1 = XMVector3Project(vec1, 0, 0, W, H, 0, 1, Projection, View, World);
	XMVECTOR nVec2 = XMVector3Project(vec2, 0, 0, W, H, 0, 1, Projection, View, World);
	XMVECTOR nVec3 = XMVector3Project(vec3, 0, 0, W, H, 0, 1, Projection, View, World);


	XMFLOAT2 dest0;
	XMStoreFloat2(&dest0, nVec0);
	XMFLOAT2 dest1;
	XMStoreFloat2(&dest1, nVec1);
	XMFLOAT2 dest2;
	XMStoreFloat2(&dest2, nVec2);
	XMFLOAT2 dest3;
	XMStoreFloat2(&dest3, nVec3);


	//XMMATRIX mtx = Projection * View * World;
	//vec = XMVector4Transform(vec, mtx);
	//dest.x = dest.x / dest.w;
	//dest.y = dest.y / dest.w;
	//dest.z = dest.z / dest.w;
	//dest.w = 1;
	
	qDebug("X0: %f Y0: %f", dest0.x, dest0.y);
	qDebug("X1: %f Y1: %f", dest1.x, dest1.y);
	qDebug("X2: %f Y2: %f", dest2.x, dest2.y);
	qDebug("X3: %f Y3: %f", dest3.x, dest3.y);

	qDebug("Intersection Test 1: %d", PointInTriangle(x, y, dest0.x, dest0.y, dest1.x, dest1.y, dest2.x, dest2.y));
	qDebug("Intersection Test 2: %d", PointInTriangle(x, y, dest1.x, dest1.y, dest3.x, dest3.y, dest2.x, dest2.y));


	//qDebug("Intersection Test: %d", RaySphere(o, d, 0.1f));
	//qDebug("Intersection Test: %d", RaySphere(origin, destination, XMVectorSet(0,0,0,1), 1));





	//XMVECTOR v1 = XMVector3Unproject(XMVectorSet(x, y, 0, 1), 0.0f, 0.0f, W, H, 0.0f, 1.0f, Projection, View, World);
	//XMVECTOR v2 = XMVector3Unproject(XMVectorSet(x, y, 1, 1), 0.0f, 0.0f, W, H, 0.0f, 1.0f, Projection, View, World);
	//XMVECTOR vD = XMVector4Normalize(v2 - v1);
	//XMFLOAT4 dir; XMStoreFloat4(&dir, v1);
	AddParticle(PARTICLE(10, 10, 0));
	//vertices.push_back(VERTEX(-5, -5, 0));
	//vertices.push_back(VERTEX(5, 5, 0));
	//vertices.push_back(VERTEX(5, -5, 0));

}

bool Graphics::PointInTriangle(float x, float y, float x1, float y1, float x2, float y2, float x3, float y3)
{
	float l1 = (x - x1)*(y3 - y1) - (x3 - x1)*(y - y1);
	float l2 = (x - x2)*(y1 - y2) - (x1 - x2)*(y - y2);
	float l3 = (x - x3)*(y2 - y3) - (x2 - x3)*(y - y3);

	return (l1>0 && l2>0 && l3>0) || (l1<0 && l2<0 && l3<0);
}

bool Graphics::RaySphere(XMVECTOR origin, XMVECTOR direction, XMVECTOR position, float radius)
{
	XMVECTOR offset = origin - position;

	float radiusSquared = radius*radius;

	float p_d = Utility::Dot(offset, direction);

	if (p_d > 0 || Utility::Dot(offset, offset) < radiusSquared)
	{
		return false;
	}

	XMVECTOR approach = offset - p_d * direction;

	float approachSquared = Utility::Dot(approach, approach);

	if (approachSquared > radiusSquared)
	{
		return false;
	}

	return true;
}

bool Graphics::RaySphere(XMFLOAT4 origin, XMFLOAT4 direction, float radius)
{
	float a, b, c, discriminant;


	// Calculate the a, b, and c coefficients.
	a = (direction.x * direction.x) + (direction.y * direction.y) + (direction.z * direction.z);
	b = ((direction.x * origin.x) + (direction.y * origin.y) + (direction.z * origin.z)) * 2.0f;
	c = ((origin.x * origin.x) + (origin.y * origin.y) + (origin.z * origin.z)) - (radius * radius);

	// Find the discriminant.
	discriminant = (b * b) - (4 * a * c);

	// if discriminant is negative the picking ray missed the sphere, otherwise it intersected the sphere.
	if (discriminant < 0.0f)
	{
		return false;
	}

	return true;
}

void Graphics::AddParticle(PARTICLE v)
{
	// Original vertex amount
	unsigned int originalVerts = particleData.size();

	particleData.push_back(v);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	unsigned int newVerts = particleData.size();

	context->Map(particleVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy((PARTICLE*)mappedResource.pData, (void*)particleData.data(), sizeof(PARTICLE) * newVerts);
	context->Unmap(particleVertexBuffer, 0);

}


void Graphics::Debug()
{
	debug = !debug;
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
	context->PSSetSamplers(0, 1, &textureSamplerState);
	context->PSSetShaderResources(0, 1, &textures[0]);

	context->Draw(groundData.size(), 0);
	if (debug == true) { RenderDebug(groundData.size()); }

	
	// Draw Particles
	// do this before object too (IASetVertexBuffers)
	stride = sizeof(PARTICLE);
	offset = 0;
	shaders.SetParticleShader(context);
	context->IASetVertexBuffers(0, 1, &particleVertexBuffer, &stride, &offset);
	cBufferParticle.wvp = XMMatrixTranspose(WVP);
	cBufferParticle.world = XMMatrixTranspose(World);
	cBufferParticle.campos = campos;
	cBufferParticle.camup = XMVectorSet(0, 1, 0, 1);
	context->UpdateSubresource(constantBufferParticle, 0, NULL, &cBufferParticle, 0, 0);
	context->VSSetConstantBuffers(0, 1, &constantBufferParticle);
	context->GSSetConstantBuffers(0, 1, &constantBufferParticle);
	context->PSSetSamplers(0, 1, &textureSamplerState);
	context->PSSetShaderResources(0, 1, &textures[0]);

	context->Draw(particleData.size(), 0);
	if (debug == true) { RenderDebug(particleData.size()); }

	

	swapChain->Present(0, 0);
}

void Graphics::RenderDebug(unsigned int vtxcount)
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

void Graphics::paintEvent(QPaintEvent* evt)
{
	//qt paint
	Render();
}
