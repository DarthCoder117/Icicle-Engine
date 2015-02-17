#include "graphics/DX11VertexBuffer.h"

#ifdef ICE_WINDOWS

using namespace ice;
using namespace graphics;

bool DX11VertexBuffer::init(void* vertices, unsigned int numVertices, unsigned int vertexSz, unsigned int flags, PRIMITIVE_TOPOLOGY primitiveTopology)
{
	VertexBuffer::init(vertices, numVertices, vertexSz, flags, primitiveTopology);

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

	//Set CPU access flags if they are supported. Otherwise, emulate CPU access by duplicating vertex data in system RAM.
	UINT CPUAccessFlags = 0;
	if (flags & BF_CPU_ACCESS_READ)
	{
		m_vertexData = malloc(numVertices*vertexSz);
		memcpy(m_vertexData, vertices, numVertices*vertexSz);
	}
	if (flags & BF_CPU_ACCESS_WRITE)
	{
		if (flags & BF_DYNAMIC_USAGE)
		{
			CPUAccessFlags |= D3D11_CPU_ACCESS_WRITE;
		}
		else if (flags & BF_DEFAULT_USAGE)
		{
			m_vertexData = malloc(numVertices*vertexSz);
			memcpy(m_vertexData, vertices, numVertices*vertexSz);
		}
	}

	//Set bind flags
	UINT bindFlags = D3D11_BIND_VERTEX_BUFFER;
	if (flags & BF_WITH_STREAM_OUT)
	{
		bindFlags |= D3D11_BIND_STREAM_OUTPUT;
	}

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = vertexSz * numVertices;
	bd.CPUAccessFlags = CPUAccessFlags;
	bd.Usage = usage;
	bd.BindFlags = bindFlags;
	bd.MiscFlags = 0;

	//Create buffer with initial vertex data
	if (vertices != NULL && numVertices > 0)
	{
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = vertices;
		if (FAILED(m_device->CreateBuffer(&bd, &InitData, &m_vertexBuffer)))
			return false;
	}
	//Create buffer without initial vertex data
	else
	{
		if (FAILED(m_device->CreateBuffer(&bd, NULL, &m_vertexBuffer)))
			return false;
	}

	return true;
}

DX11VertexBuffer::~DX11VertexBuffer()
{
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
	}

	if (m_vertexData)
	{
		free(m_vertexData);
	}
}

void* DX11VertexBuffer::lock(LOCK_MODE mode)
{
	if (m_vertexBuffer == NULL)
		return NULL;

	m_lockMode = mode;

	//Write mode is supported only for default and dynamic resources.
	if (mode == LM_WRITE)
	{
		//Dynamic usage simply maps the vertex buffer to allow writing
		if (m_flags & BF_DYNAMIC_USAGE)
		{
			ID3D11DeviceContext* context = NULL;
			m_device->GetImmediateContext(&context);

			D3D11_MAPPED_SUBRESOURCE mappedRes;
			context->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedRes);

			return mappedRes.pData;
		}
		//For default usage, the system RAM vertex data is returned so that it can be updated with UpdateSubresource
		else if (m_flags & BF_DEFAULT_USAGE)
		{
			return m_vertexData;
		}
	}
	//Read mode is supported for all resources, but only if a system RAM copy of the vertex data was created by specifying EBF_CPU_ACCESS_READ on buffer creation.
	else
	{
		if (m_flags & BF_CPU_ACCESS_READ)
		{
			return m_vertexData;
		}
	}

	//Static buffers cannot be written to, and reads cannot be performed without the EBF_CPU_ACCESS_READ flag being specified on buffer creation.
	//If we get to this point, then both of those conditions were true and NULL is returned.
	return NULL;
}

void DX11VertexBuffer::unlock()
{
	if (m_vertexBuffer == NULL)
		return;

	if (m_lockMode == LM_WRITE)
	{
		//Dynamic usage simply maps the vertex buffer to allow writing
		if (m_flags & BF_DYNAMIC_USAGE)
		{
			ID3D11DeviceContext* context = NULL;
			m_device->GetImmediateContext(&context);

			context->Unmap(m_vertexBuffer, 0);
		}
		//For default usage, a temporary buffer is returned so that it can be updated with UpdateSubresource
		else if (m_flags & BF_DEFAULT_USAGE)
		{
			ID3D11DeviceContext* context = NULL;
			m_device->GetImmediateContext(&context);

			context->UpdateSubresource(m_vertexBuffer, 0, NULL, m_vertexData, 0, 0);
		}
	}

	//Read mode is implemented as a system RAM buffer, so no unlocking is required.
}

#endif