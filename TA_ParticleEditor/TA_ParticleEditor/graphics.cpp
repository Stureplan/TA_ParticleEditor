#include "graphics.h"

Graphics::Graphics(QWidget * parent)
{
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);

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

	context->OMSetRenderTargets(1, &renderTargetView, NULL);

	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = W;
	viewport.Height = H;

}

void Graphics::Render()
{
	//dx11 render
	FLOAT color[4]  = { 1.0f, 0.0f, 1.0f, 1.0f };
	context->ClearRenderTargetView(renderTargetView, color);

	swapChain->Present(0, 0);
}

void Graphics::paintEvent(QPaintEvent* evt)
{
	//qt paint
	Render();
}