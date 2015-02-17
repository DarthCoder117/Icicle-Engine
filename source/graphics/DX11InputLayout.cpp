#include "graphics/DX11InputLayout.h"
#include <D3Dcompiler.h>
#include <core/Debug.h>

using namespace ice;
using namespace graphics;

DX11InputLayout::~DX11InputLayout()
{
	m_layout->Release();
}

ID3DBlob* g_shaderSignature = NULL;

void DX11InputLayout::init(unsigned int vertexFormat)
{
	//Build list of D3D input elements
	Vector<D3D11_INPUT_ELEMENT_DESC> d3dElements;
	unsigned int idx = 0;

	addInputLayoutElement(VE_POSITION, vertexFormat, idx, d3dElements);

	addInputLayoutElement(VE_TEXCOORD0, vertexFormat, idx, d3dElements);
	addInputLayoutElement(VE_TEXCOORD1, vertexFormat, idx, d3dElements);
	addInputLayoutElement(VE_TEXCOORD2, vertexFormat, idx, d3dElements);
	addInputLayoutElement(VE_TEXCOORD3, vertexFormat, idx, d3dElements);
	addInputLayoutElement(VE_TEXCOORD4, vertexFormat, idx, d3dElements);
	addInputLayoutElement(VE_TEXCOORD5, vertexFormat, idx, d3dElements);
	addInputLayoutElement(VE_TEXCOORD6, vertexFormat, idx, d3dElements);
	addInputLayoutElement(VE_TEXCOORD7, vertexFormat, idx, d3dElements);

	addInputLayoutElement(VE_NORMAL, vertexFormat, idx, d3dElements);

	addInputLayoutElement(VE_DIFFUSE_COLOR, vertexFormat, idx, d3dElements);
	addInputLayoutElement(VE_SPECULAR_COLOR, vertexFormat, idx, d3dElements);

	//Get vertex shader signature.
	ID3DBlob* vsBlob = NULL;

	if (!g_shaderSignature)
	{
		generateShaderSignature(vertexFormat);
	}

	//Create input layout
	HRESULT hr = m_device->CreateInputLayout(&d3dElements[0], d3dElements.size(), g_shaderSignature->GetBufferPointer(), g_shaderSignature->GetBufferSize(), &m_layout);
	if (FAILED(hr))
	{
		return;
	}
	
	m_layout->AddRef();
}

void DX11InputLayout::generateShaderSignature(unsigned int vertexFormat)
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

void DX11InputLayout::addInputLayoutElement(VERTEX_ELEMENT element, unsigned int vertexFormat, unsigned int& idx, Vector<D3D11_INPUT_ELEMENT_DESC>& out)
{
	if (vertexFormat & element)
	{
		D3D11_INPUT_ELEMENT_DESC el;
		ZeroMemory(&el, sizeof(el));

		if (element == VE_POSITION)
		{
			el.SemanticName = "POSITION";
			el.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		else if (element == VE_TEXCOORD0)
		{
			el.SemanticName = "TEXCOORD";
			el.SemanticIndex = 0;
			el.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (element == VE_TEXCOORD1)
		{
			el.SemanticName = "TEXCOORD";
			el.SemanticIndex = 1;
			el.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (element == VE_TEXCOORD2)
		{
			el.SemanticName = "TEXCOORD";
			el.SemanticIndex = 2;
			el.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (element == VE_TEXCOORD3)
		{
			el.SemanticName = "TEXCOORD";
			el.SemanticIndex = 3;
			el.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (element == VE_TEXCOORD4)
		{
			el.SemanticName = "TEXCOORD";
			el.SemanticIndex = 4;
			el.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (element == VE_TEXCOORD5)
		{
			el.SemanticName = "TEXCOORD";
			el.SemanticIndex = 5;
			el.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (element == VE_TEXCOORD6)
		{
			el.SemanticName = "TEXCOORD";
			el.SemanticIndex = 6;
			el.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (element == VE_TEXCOORD7)
		{
			el.SemanticName = "TEXCOORD";
			el.SemanticIndex = 7;
			el.Format = DXGI_FORMAT_R32G32_FLOAT;
		}

		else if (element == VE_NORMAL)
		{
			el.SemanticName = "NORMAL";
			el.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		}

		else if (element == VE_DIFFUSE_COLOR)
		{
			el.SemanticName = "DIFFUSE_COLOR";
			el.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}
		else if (element == VE_SPECULAR_COLOR)
		{
			el.SemanticName = "SPECULAR_COLOR";
			el.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		el.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		el.AlignedByteOffset = 0;
		el.InputSlot = idx;

		out.push_back(el);

		idx++;
	}
}