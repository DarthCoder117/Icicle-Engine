#include "graphics/DX11IndexBuffer.h"

#ifdef ICE_WINDOWS

using namespace ice;
using namespace graphics;

DX11IndexBuffer::~DX11IndexBuffer()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
	}

	if (m_indexData)
	{
		free(m_indexData);
	}
}

bool DX11IndexBuffer::init(unsigned int* indices, unsigned int numIndices, unsigned int flags)
{
	IndexBuffer::init(indices, numIndices, flags);

	if (indices != NULL && numIndices >= 0)
	{
		//Set usage flags
		D3D11_USAGE usage = D3D11_USAGE_DEFAULT;
		if (flags & BF_DYNAMIC_USAGE)
		{
			usage = D3D11_USAGE_DYNAMIC;
		}
		else if (flags & BF_STATIC_USAGE)
		{
			usage = D3D11_USAGE_IMMUTABLE;
		}

		//Set CPU access flags
		UINT CPUAccessFlags = 0;
		if (flags & BF_CPU_ACCESS_READ)
		{
			m_indexData = (unsigned int*)malloc(numIndices*sizeof(unsigned int));
			memcpy(m_indexData, indices, numIndices*sizeof(unsigned int));
		}
		else if (flags & BF_CPU_ACCESS_WRITE)
		{
			if (flags & BF_DYNAMIC_USAGE)
			{
				CPUAccessFlags |= D3D11_CPU_ACCESS_WRITE;
			}
			else if (flags & BF_DEFAULT_USAGE)
			{
				m_indexData = (unsigned int*)malloc(numIndices*sizeof(unsigned int));
				memcpy(m_indexData, indices, numIndices*sizeof(unsigned int));
			}
		}

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = usage;
		bd.ByteWidth = sizeof(unsigned int)* numIndices;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = CPUAccessFlags;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = indices;

		// Create the buffer with the device.
		if (SUCCEEDED(m_device->CreateBuffer(&bd, &InitData, &m_indexBuffer)))
		{
			return true;
		}
	}

	return false;
}

unsigned int* DX11IndexBuffer::lock(LOCK_MODE mode)
{
	if (m_indexBuffer == NULL)
		return NULL;

	m_lockMode = mode;

	//Write mode is supported only for default and dynamic resources.
	if (mode == LM_WRITE)
	{
		//Dynamic usage simply maps the index buffer to allow writing
		if (m_flags & BF_DYNAMIC_USAGE)
		{
			ID3D11DeviceContext* context = NULL;
			m_device->GetImmediateContext(&context);

			D3D11_MAPPED_SUBRESOURCE mappedRes;
			context->Map(m_indexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedRes);

			return (unsigned int*)mappedRes.pData;
		}
		//For default usage, the system RAM index data is returned so that it can be updated with UpdateSubresource
		else if (m_flags & BF_DEFAULT_USAGE)
		{
			return m_indexData;
		}
	}
	//Read mode is supported for all resources, but only if a system RAM copy of the index data was created by specifying EBF_CPU_ACCESS_READ on buffer creation.
	else
	{
		if (m_flags & BF_CPU_ACCESS_READ)
		{
			return m_indexData;
		}
	}

	//Static buffers cannot be written to, and reads cannot be performed without the EBF_CPU_ACCESS_READ flag being specified on buffer creation.
	//If we get to this point, then both of those conditions were true and NULL is returned.
	return NULL;
}

void DX11IndexBuffer::unlock()
{
	if (m_indexBuffer == NULL)
		return;

	if (m_lockMode == LM_WRITE)
	{
		//Dynamic usage simply maps the index buffer to allow writing
		if (m_flags & BF_DYNAMIC_USAGE)
		{
			ID3D11DeviceContext* context = NULL;
			m_device->GetImmediateContext(&context);

			context->Unmap(m_indexBuffer, 0);
		}
		//For default usage, a temporary buffer is returned so that it can be updated with UpdateSubresource
		else if (m_flags & BF_DEFAULT_USAGE)
		{
			ID3D11DeviceContext* context = NULL;
			m_device->GetImmediateContext(&context);

			context->UpdateSubresource(m_indexBuffer, 0, NULL, m_indexData, 0, 0);
		}
	}

	//Read mode is implemented as a system RAM buffer, so no unlocking is required.
}

#endif