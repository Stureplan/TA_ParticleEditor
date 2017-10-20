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
	Render();
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



	//D3D11_TEXTURE2D_DESC depthDesc;
	//ZeroMemory(&depthDesc, sizeof(depthDesc));

	
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = W;
	viewport.Height = H;
	context->RSSetViewports(1, &viewport);

	/*===================================================================================*/
	// CONSTANT BUFFER SETUP
	D3D11_BUFFER_DESC cb_wvp_Desc;
	ZeroMemory(&cb_wvp_Desc, sizeof(D3D11_BUFFER_DESC));
	cb_wvp_Desc.Usage = D3D11_USAGE_DEFAULT;
	cb_wvp_Desc.ByteWidth = sizeof(cBuffer);
	cb_wvp_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb_wvp_Desc.CPUAccessFlags = 0;
	cb_wvp_Desc.MiscFlags = 0;
	cb_wvp_Desc.StructureByteStride = 0;
	hr = device->CreateBuffer(&cb_wvp_Desc, NULL, &constantBuffer);
	/*===================================================================================*/


	SetupCamera(XMVectorSet(0.0f, 1.0f, -10.0f, 0.0f), XMVectorSet(0.0f, 1.0f, -10.0f, 0.0f) + XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	LoadShaders();
	LoadQuad();
	LoadTextures();
}

void Graphics::SetupCamera(XMVECTOR pos, XMVECTOR dir, XMVECTOR up)
{
	campos = pos;
	camdir = dir;
	camup = up;

	World = XMMatrixIdentity();
	View = XMMatrixLookAtLH(campos, camdir, camup);
	Projection = XMMatrixPerspectiveFovLH(0.4f * 3.14f, (float)W / (float)H, 1.0f, 1000.0f);
}

void Graphics::LoadShaders()
{
	std::string shaderpath = Utility::Path();

	// Insert shader path
	shaderpath.insert(shaderpath.size(), "Data\\shaders.shader");
	
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
		{ "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = device->CreateInputLayout(ied, sizeof(ied) / sizeof(ied[0]), VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
	context->IASetInputLayout(pLayout);
	//context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

}


void Graphics::LoadQuad()
{
	HRESULT hr;

	vertices =
	{
		/*{ -5, -5, 0, 0, 1 },
		{ -5, 5, 0, 0, 0 },
		{ 5, 5, 0, 1, 0 },

		{ 5, 5, 0, 1, 0 },
		{ 5, -5, 0, 1, 1 },
		{ -5, -5, 0, 0, 1 }*/
		{ 0, 0, 0, 0, 0 }

	};

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(vertexDesc));

	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	//vertexDesc.ByteWidth = sizeof(float) * 5 * vertices.size();
	vertexDesc.ByteWidth = sizeof(float) * 5 * vertices.size();
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.CPUAccessFlags = 0;
	vertexDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory(&vertexData, sizeof(vertexData));

	vertexData.pSysMem = vertices.data();
	hr = device->CreateBuffer(&vertexDesc, &vertexData, &vertexBuffer);

	UINT stride = sizeof(float) * 5;
	UINT offset = 0;

	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
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

void Graphics::Debug()
{
	debug = !debug;
}

void Graphics::Render()
{
	float color[4]  = { 0.2f, 0.2f, 0.2f, 1.0f };
	context->ClearRenderTargetView(renderTargetView, color);
	amt++;


	// Draw Particle 1
	ChangeRasterization(D3D11_FILL_SOLID);
	World = XMMatrixIdentity();
	//World = XMMatrixTranslation(-4, 4, -2);
	View = XMMatrixLookAtLH(campos, camdir, camup);
	WVP = World * View * Projection;

	cBuffer.wvp = XMMatrixTranspose(WVP);
	cBuffer.world = XMMatrixTranspose(World);
	cBuffer.campos = campos;
	cBuffer.camup = XMVectorSet(0, 1, 0, 1);
	context->UpdateSubresource(constantBuffer, 0, NULL, &cBuffer, 0, 0);
	context->VSSetConstantBuffers(0, 1, &constantBuffer);
	context->GSSetConstantBuffers(0, 1, &constantBuffer);
	context->PSSetSamplers(0, 1, &textureSamplerState);
	context->PSSetShaderResources(0, 1, &textures[0]);
	context->Draw(1, 0);

	if (debug == true)
	{
		ChangeRasterization(D3D11_FILL_WIREFRAME);
		context->PSSetSamplers(0, 1, &textureSamplerState);
		context->PSSetShaderResources(0, 1, &texture_debug);
		context->Draw(1, 0);
	}



	// Draw Particle 2
	/*World = XMMatrixTranslation(2, 2, 2);
	View = XMMatrixLookAtLH(campos, camdir, camup);
	WVP = World * View * Projection;

	cBuffer.wvp = XMMatrixTranspose(WVP);
	cBuffer.world = XMMatrixTranspose(World);
	context->UpdateSubresource(constantBuffer, 0, NULL, &cBuffer, 0, 0);
	context->VSSetConstantBuffers(0, 1, &constantBuffer);
	context->PSSetSamplers(0, 1, &textureSamplerState);
	context->PSSetShaderResources(0, 1, &textures[0]);
	context->Draw(1, 0);*/



	swapChain->Present(0, 0);
}

void Graphics::paintEvent(QPaintEvent* evt)
{
	//qt paint
	Render();
}
