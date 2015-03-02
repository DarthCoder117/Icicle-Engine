#include "graphics/DX11ConstantBuffer.h"

#ifdef ICE_WINDOWS

using namespace ice;
using namespace graphics;

DX11ConstantBuffer::DX11ConstantBuffer(GraphicsDriver* driver, void* data, size_t bufferSz)
	:m_device(((DX11GraphicsDriver*)driver)->getD3DDevice()),
	m_constBuffer(NULL),
	m_bufferSz(bufferSz)
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = m_bufferSz;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	HRESULT hr = m_device->CreateBuffer(&bd, NULL, &m_constBuffer);
	if (FAILED(hr))
	{
		return;
	}
}

DX11ConstantBuffer::~DX11ConstantBuffer()
{
	if (m_constBuffer)
	{
		m_constBuffer->Release();
	}
}

void DX11ConstantBuffer::updateBuffer(void* data)
{
	ID3D11DeviceContext* context;
	m_device->GetImmediateContext(&context);

	context->UpdateSubresource(m_constBuffer, 0, NULL, data, 0, 0);
}

size_t DX11ConstantBuffer::bufferSize()
{
	return m_bufferSz;
}

#endif