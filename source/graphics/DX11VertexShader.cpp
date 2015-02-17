#include "graphics/DX11VertexShader.h"

using namespace ice;
using namespace graphics;

DX11VertexShader::~DX11VertexShader()
{
	if (m_VS)
	{
		m_VS->Release();
	}
}

void DX11VertexShader::init(void* shaderByteCode, size_t shaderByteCodeSz)
{
	HRESULT hr = m_device->CreateVertexShader(shaderByteCode, shaderByteCodeSz, NULL, &m_VS);
	if (FAILED(hr))
		return;
}