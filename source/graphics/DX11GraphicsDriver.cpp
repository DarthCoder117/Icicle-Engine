#include "graphics/DX11GraphicsDriver.h"

#ifdef ICE_WINDOWS

#include "graphics/DX11Texture2D.h"
#include "graphics/DX11VertexBuffer.h"
#include "graphics/DX11IndexBuffer.h"
#include "graphics/DX11InputLayout.h"
#include "graphics/DX11VertexShader.h"
#include "graphics/DX11PixelShader.h"

using namespace ice;
using namespace graphics;

DX11GraphicsDriver::DX11GraphicsDriver(system::Window* window, u32 flags)
	:m_window(window),
	m_displayFlags(flags),
	m_currentIndexBuffer(NULL)
{
	//Create swap chain
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 2;                                    // double buffer
	scd.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;

	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	scd.BufferDesc.Width = window->getWindowSize().x;
	scd.BufferDesc.Height = window->getWindowSize().y;

	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	scd.OutputWindow = window->getSystemHandle();

	scd.SampleDesc.Count = 1;                               // how many multisamples
	//scd.SampleDesc.Quality = 16;

	if (flags & DF_FULLSCREEN)
	{
		scd.Windowed = false;
	}
	else
	{
		scd.Windowed = true;
	}

	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	UINT deviceFlags = 0;
	#ifdef ICE_DEBUG
	deviceFlags = D3D11_CREATE_DEVICE_DEBUG;
	#endif

	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		deviceFlags,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&m_swapChain,
		&m_device,
		NULL,
		&m_deviceContext);

	if (FAILED(hr))
	{
		printf("");
	}

	//Create shader compiler
	m_shaderCompiler.reset(new DX11ShaderCompiler(m_device));

	//Create render target
	ID3D11Texture2D *pBackBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	hr = m_device->CreateRenderTargetView(pBackBuffer, NULL, &m_backBuffer);
	pBackBuffer->Release();

	//Set initial render target
	m_deviceContext->OMSetRenderTargets(1, &m_backBuffer, NULL);

	//Set initial viewport
	setViewport(window->getWindowSize());

	//Init caps
	D3D11_FEATURE_DATA_THREADING featureData;
	m_device->CheckFeatureSupport(D3D11_FEATURE_THREADING, &featureData, sizeof(D3D11_FEATURE_DATA_THREADING));
	m_caps.concurrentCreation = (featureData.DriverConcurrentCreates == TRUE);

	unsetVertexBuffers();
}

DX11GraphicsDriver::~DX11GraphicsDriver()
{
	m_swapChain->SetFullscreenState(FALSE, NULL);

	m_swapChain->Release();
	m_backBuffer->Release();
	m_device->Release();
	m_deviceContext->Release();
}

void DX11GraphicsDriver::reset(const Vec2u& resolution)
{
	//TODO: Lock this reset method with a mutex

	//Resize buffers
	m_deviceContext->OMSetRenderTargets(0, 0, 0);

	m_backBuffer->Release();

	m_swapChain->ResizeBuffers(0, resolution.x, resolution.y, DXGI_FORMAT_UNKNOWN, 0);

	//Recreate render target view
	ID3D11Texture2D* pBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);
	
	m_device->CreateRenderTargetView(pBuffer, NULL, &m_backBuffer);

	pBuffer->Release();

	//Reset render target
	m_deviceContext->OMSetRenderTargets(1, &m_backBuffer, NULL);
}

void DX11GraphicsDriver::setViewport(const Vec2& vp)
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = vp.x;
	viewport.Height = vp.y;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	m_deviceContext->RSSetViewports(1, &viewport);
}

void DX11GraphicsDriver::clear(const Color3f& color, float depth, char stencil)
{
	float clearCol[4] = { color.r, color.g, color.b, 1.0f };

	m_deviceContext->ClearRenderTargetView(m_backBuffer, clearCol);
}

void DX11GraphicsDriver::present()
{
	m_swapChain->Present(0, 0);
}

const DriverCaps& DX11GraphicsDriver::getCaps()
{
	return m_caps;
}

ShaderCompiler* DX11GraphicsDriver::getShaderCompiler()
{
	return m_shaderCompiler.get();
}

void DX11GraphicsDriver::setVertexShader(VertexShader* vs)
{
	m_deviceContext->VSSetShader(((DX11VertexShader*)vs)->getD3DShader(), NULL, 0);
}

void DX11GraphicsDriver::setPixelShader(PixelShader* ps)
{
	m_deviceContext->PSSetShader(((DX11PixelShader*)ps)->getD3DShader(), NULL, 0);
}

void DX11GraphicsDriver::setInputLayout(InputLayout* layout)
{
	m_deviceContext->IASetInputLayout(((DX11InputLayout*)layout)->getD3DLayout());
}

void DX11GraphicsDriver::setVertexBuffer(VertexBuffer* vb, unsigned int slot)
{
	ID3D11Buffer* vertexBuffers[] = { ((DX11VertexBuffer*)vb)->getD3DBuffer() };
	UINT offsets[] = { 0 };
	UINT strides[] = { vb->getVertexSize() };

	m_deviceContext->IASetVertexBuffers(slot, 1, vertexBuffers, strides, offsets);
}

void DX11GraphicsDriver::unsetVertexBuffers()
{
	ID3D11Buffer* vertexBuffers[16];
	UINT offsets[16];
	UINT strides[16];
	ZeroMemory(vertexBuffers, 16);
	ZeroMemory(offsets, 16);
	ZeroMemory(strides, 16);

	m_deviceContext->IASetVertexBuffers(0, 16, vertexBuffers, strides, offsets);
}

void DX11GraphicsDriver::setIndexBuffer(IndexBuffer* buffer)
{
	if (buffer != m_currentIndexBuffer)
	{
		m_currentIndexBuffer = buffer;
		m_deviceContext->IASetIndexBuffer(((DX11IndexBuffer*)m_currentIndexBuffer)->getD3DBuffer(), DXGI_FORMAT_R32_UINT, 0);
	}
}

void DX11GraphicsDriver::setTexture(Texture2D* tex, unsigned int slot)
{
	ID3D11ShaderResourceView* resourceView = NULL;

	if (tex)
	{
		DX11Texture2D* d3dTex = (DX11Texture2D*)tex;
		resourceView = d3dTex->getShaderResourceView();
	}

	m_deviceContext->PSSetShaderResources(slot, 1, &resourceView);
}

void DX11GraphicsDriver::draw(unsigned int count, unsigned int offset)
{
	m_deviceContext->Draw(count, offset);
}

void DX11GraphicsDriver::drawIndexed(unsigned int offset)
{
	m_deviceContext->DrawIndexed(m_currentIndexBuffer->getNumIndices(), offset, 0);
}

Texture2D* DX11GraphicsDriver::createTexture()
{
	return new DX11Texture2D(this);
}

VertexBuffer* DX11GraphicsDriver::createVertexBuffer()
{
	return new DX11VertexBuffer(this);
}

IndexBuffer* DX11GraphicsDriver::createIndexBuffer()
{
	return new DX11IndexBuffer(this);
}

VertexShader* DX11GraphicsDriver::createVertexShader()
{
	return new DX11VertexShader(this);
}

PixelShader* DX11GraphicsDriver::createPixelShader()
{
	return new DX11PixelShader(this);
}

GRAPHICS_DRIVER_TYPE DX11GraphicsDriver::getDriverType()
{
	return GDT_DIRECT3D11;
}

#endif