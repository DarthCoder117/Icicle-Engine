#include "graphics/DX11InputLayout.h"
#ifdef ICE_WINDOWS
#include <D3Dcompiler.h>
#include <core/Debug.h>

using namespace ice;
using namespace graphics;

DXGI_FORMAT icicleFormatToD3DFormat(INPUT_ELEMENT_FORMAT format)
{
	if (format == IEF_FLOAT4)
	{
		return DXGI_FORMAT_R32G32B32A32_FLOAT;
	}
	else if (format == IEF_FLOAT3)
	{
		return DXGI_FORMAT_R32G32B32_FLOAT;
	}
	else if (format == IEF_FLOAT2)
	{
		return DXGI_FORMAT_R32G32_FLOAT;
	}
	else if (format == IEF_FLOAT)
	{
		return DXGI_FORMAT_R32_FLOAT;
	}

	return DXGI_FORMAT_R32G32B32_FLOAT;
}

DX11InputLayout::~DX11InputLayout()
{
	m_layout->Release();
}

ID3DBlob* g_shaderSignature = NULL;

void DX11InputLayout::init(InputElementDesc elements[], unsigned int numElements)
{
	//Build list of D3D input elements
	Vector<D3D11_INPUT_ELEMENT_DESC> d3dElements;
	for (unsigned int i = 0; i < numElements; ++i)
	{
		D3D11_INPUT_ELEMENT_DESC el;
		ZeroMemory(&el, sizeof(el));

		el.SemanticName = elements[i].m_semanticName.c_str();
		el.SemanticIndex = elements[i].m_semanticIdx;
		el.Format = icicleFormatToD3DFormat(elements[i].m_format);
		el.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		el.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		el.InputSlot = elements[i].m_inputSlot;

		d3dElements.push_back(el);
	}

	//Get vertex shader signature.
	if (!g_shaderSignature)
	{
		generateShaderSignature();
	}

	//Create input layout
	HRESULT hr = m_device->CreateInputLayout(&d3dElements[0], d3dElements.size(), g_shaderSignature->GetBufferPointer(), g_shaderSignature->GetBufferSize(), &m_layout);
	if (FAILED(hr))
	{
		return;
	}
	
	m_layout->AddRef();
}

void DX11InputLayout::generateShaderSignature()
{
	ID3DBlob* vsBlob;
	ID3DBlob* errorBlob;

	String shaderSrc = "float4 empty_vs(uint i : SV_VertexID) : SV_POSITION{return 0;}";

	HRESULT hr = D3DCompile(&shaderSrc[0], shaderSrc.length(), "signature_verification_vertex_shader", NULL, NULL, "VS", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_DEBUG, NULL, &vsBlob, &errorBlob);
	if (FAILED(hr))
	{
		core::Debug::log(core::LL_ERROR, "vertex shader", (const char*)errorBlob->GetBufferPointer());

		errorBlob->Release();

		return;
	}

	g_shaderSignature = vsBlob;
}

#endif