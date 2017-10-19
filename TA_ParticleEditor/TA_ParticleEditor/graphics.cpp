#include "graphics.h"

Graphics::Graphics(QWidget * parent)
{
	setParent(parent);
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);
	
	ps = new ParticleSystem();
	Initialize();
}

Graphics::~Graphics()
{
}

void Graphics::Initialize()
{
	HRESULT hr;
	
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

	desc.BufferCount = 1;
	desc.BufferDesc.Width = W;
	desc.BufferDesc.Height = H;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.SampleDesc.Count = 4;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = true;
	desc.OutputWindow = (HWND)winId();
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0,
										NULL, NULL, D3D11_SDK_VERSION,
										&desc, &swapChain, &device,
										NULL, &context);

	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
	hr = device->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
	backBuffer->Release();

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
	
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = W;
	viewport.Height = H;
	context->RSSetViewports(1, &viewport);

	// cBuffer
	D3D11_BUFFER_DESC cb_wvp_Desc;
	ZeroMemory(&cb_wvp_Desc, sizeof(D3D11_BUFFER_DESC));
	cb_wvp_Desc.Usage = D3D11_USAGE_DEFAULT;
	cb_wvp_Desc.ByteWidth = sizeof(cBuffer);
	cb_wvp_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb_wvp_Desc.CPUAccessFlags = 0;
	cb_wvp_Desc.MiscFlags = 0;
	cb_wvp_Desc.StructureByteStride = 0;
	hr = device->CreateBuffer(&cb_wvp_Desc, NULL, &constantBuffer);

	SetupCamera(XMVectorSet(0.0f, 1.0f, -10.0f, 0.0f), XMVectorSet(0.0f, 1.0f, -10.0f, 0.0f) + XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	LoadShaders();
	LoadQuad();
	LoadTextures();
}

void Graphics::SetupCamera(XMVECTOR pos, XMVECTOR dir, XMVECTOR up)
{
	//campos = XMVectorSet(0.0f, 1.0f, -10.0f, 0.0f);
	//camdir = campos + XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	//camup = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);


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
	hr = D3DX11CompileFromFileA(shaderpath.c_str(), 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, &blob, 0);
	if (hr != S_OK)
	{
		// Something went wrong with the shader
		std::string error = static_cast<char*>(blob->GetBufferPointer());
		MessageBoxA(NULL, error.c_str(), "PS Error", MB_OK);
	}

	device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
	device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

	context->VSSetShader(pVS, 0, 0);
	context->PSSetShader(pPS, 0, 0);

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = device->CreateInputLayout(ied, sizeof(ied) / sizeof(ied[0]), VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
	context->IASetInputLayout(pLayout);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Graphics::LoadQuad()
{
	HRESULT hr;

	vertices =
	{
		{ -5, -5, 0, 0, 1 },
		{ -5, 5, 0, 0, 0 },
		{ 5, 5, 0, 1, 0 },

		{ 5, 5, 0, 1, 0 },
		{ 5, -5, 0, 1, 1 },
		{ -5, -5, 0, 0, 1 }
	};

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(vertexDesc));

	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
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
}

void Graphics::Render()
{
	float color[4]  = { 0.2f, 0.2f, 0.2f, 1.0f };
	context->ClearRenderTargetView(renderTargetView, color);

	World = XMMatrixIdentity();
	View = XMMatrixLookAtLH(campos, camdir, camup);
	WVP = XMMatrixIdentity() * View * Projection;

	cBuffer.wvp = XMMatrixTranspose(WVP);
	cBuffer.world = XMMatrixTranspose(World);
	context->UpdateSubresource(constantBuffer, 0, NULL, &cBuffer, 0, 0);
	context->VSSetConstantBuffers(0, 1, &constantBuffer);
	context->PSSetSamplers(0, 1, &textureSamplerState);
	context->PSSetShaderResources(0, 1, &textures[0]);

	context->Draw(6, 0);


	swapChain->Present(0, 0);
}

void Graphics::paintEvent(QPaintEvent* evt)
{
	//qt paint
	Render();
}