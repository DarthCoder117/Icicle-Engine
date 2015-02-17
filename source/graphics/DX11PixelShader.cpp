#include "graphics/DX11PixelShader.h"

#ifdef ICE_WINDOWS

using namespace ice;
using namespace graphics;

DX11PixelShader::~DX11PixelShader()
{
	if (m_PS)
	{
		m_PS->Release();
	}
}

void DX11PixelShader::init(void* shaderByteCode, size_t shaderByteCodeSz)
{
	HRESULT hr = m_device->CreatePixelShader(shaderByteCode, shaderByteCodeSz, NULL, &m_PS);
	if (FAILED(hr))
		return;
}

#endif