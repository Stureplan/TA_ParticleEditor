#pragma once
#include <QWidget>

#include <dxgi.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <DirectXMath.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")


//#define W width()
//#define H height()
#define W 640
#define H 480


using namespace DirectX;

class Graphics : public QWidget 
{
	Q_OBJECT
	Q_DISABLE_COPY(Graphics)

public:
	Graphics(QWidget* parent = Q_NULLPTR);
	~Graphics();

	void Initialize();
	void Render();

	virtual QPaintEngine* paintEngine() const { return NULL; }

private:
	
protected:
	virtual void paintEvent(QPaintEvent* evt);


private:
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	IDXGISwapChain* swapChain;

	ID3D11RenderTargetView* renderTargetView;
	ID3D11Texture2D* backBuffer;

	D3D11_VIEWPORT viewport;
};
