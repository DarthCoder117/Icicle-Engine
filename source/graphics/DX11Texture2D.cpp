#include "graphics/DX11Texture2D.h"
#include <core/Debug.h>

using namespace ice;
using namespace graphics;

DXGI_FORMAT convertColorFormat(TEXTURE_FORMAT format)
{
	if (format == TF_RGBA8)
	{
		return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	}

	return DXGI_FORMAT_UNKNOWN;
}

TEXTURE_FORMAT convertColorFormat(DXGI_FORMAT format)
{
	if (format == DXGI_FORMAT_R8G8B8A8_UNORM_SRGB)
	{
		return TF_RGBA8;
	}
	
	return TF_UNKNOWN;
}

size_t sizeOfDXGIFormat(DXGI_FORMAT format)
{
	switch (format)
	{
	case DXGI_FORMAT_R32G32B32A32_TYPELESS:
	case DXGI_FORMAT_R32G32B32A32_FLOAT:
	case DXGI_FORMAT_R32G32B32A32_UINT:
	case DXGI_FORMAT_R32G32B32A32_SINT:
		return 128;

	case DXGI_FORMAT_R32G32B32_TYPELESS:
	case DXGI_FORMAT_R32G32B32_FLOAT:
	case DXGI_FORMAT_R32G32B32_UINT:
	case DXGI_FORMAT_R32G32B32_SINT:
		return 96;

	case DXGI_FORMAT_R16G16B16A16_TYPELESS:
	case DXGI_FORMAT_R16G16B16A16_FLOAT:
	case DXGI_FORMAT_R16G16B16A16_UNORM:
	case DXGI_FORMAT_R16G16B16A16_UINT:
	case DXGI_FORMAT_R16G16B16A16_SNORM:
	case DXGI_FORMAT_R16G16B16A16_SINT:
	case DXGI_FORMAT_R32G32_TYPELESS:
	case DXGI_FORMAT_R32G32_FLOAT:
	case DXGI_FORMAT_R32G32_UINT:
	case DXGI_FORMAT_R32G32_SINT:
	case DXGI_FORMAT_R32G8X24_TYPELESS:
	case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
	case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
	case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
		return 64;

	case DXGI_FORMAT_R10G10B10A2_TYPELESS:
	case DXGI_FORMAT_R10G10B10A2_UNORM:
	case DXGI_FORMAT_R10G10B10A2_UINT:
	case DXGI_FORMAT_R11G11B10_FLOAT:
	case DXGI_FORMAT_R8G8B8A8_TYPELESS:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UINT:
	case DXGI_FORMAT_R8G8B8A8_SNORM:
	case DXGI_FORMAT_R8G8B8A8_SINT:
	case DXGI_FORMAT_R16G16_TYPELESS:
	case DXGI_FORMAT_R16G16_FLOAT:
	case DXGI_FORMAT_R16G16_UNORM:
	case DXGI_FORMAT_R16G16_UINT:
	case DXGI_FORMAT_R16G16_SNORM:
	case DXGI_FORMAT_R16G16_SINT:
	case DXGI_FORMAT_R32_TYPELESS:
	case DXGI_FORMAT_D32_FLOAT:
	case DXGI_FORMAT_R32_FLOAT:
	case DXGI_FORMAT_R32_UINT:
	case DXGI_FORMAT_R32_SINT:
	case DXGI_FORMAT_R24G8_TYPELESS:
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
	case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
	case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
	case DXGI_FORMAT_B8G8R8A8_UNORM:
	case DXGI_FORMAT_B8G8R8X8_UNORM:
		return 32;

	case DXGI_FORMAT_R8G8_TYPELESS:
	case DXGI_FORMAT_R8G8_UNORM:
	case DXGI_FORMAT_R8G8_UINT:
	case DXGI_FORMAT_R8G8_SNORM:
	case DXGI_FORMAT_R8G8_SINT:
	case DXGI_FORMAT_R16_TYPELESS:
	case DXGI_FORMAT_R16_FLOAT:
	case DXGI_FORMAT_D16_UNORM:
	case DXGI_FORMAT_R16_UNORM:
	case DXGI_FORMAT_R16_UINT:
	case DXGI_FORMAT_R16_SNORM:
	case DXGI_FORMAT_R16_SINT:
	case DXGI_FORMAT_B5G6R5_UNORM:
	case DXGI_FORMAT_B5G5R5A1_UNORM:
		return 16;

	case DXGI_FORMAT_R8_TYPELESS:
	case DXGI_FORMAT_R8_UNORM:
	case DXGI_FORMAT_R8_UINT:
	case DXGI_FORMAT_R8_SNORM:
	case DXGI_FORMAT_R8_SINT:
	case DXGI_FORMAT_A8_UNORM:
		return 8;

	case DXGI_FORMAT_BC2_TYPELESS:
	case DXGI_FORMAT_BC2_UNORM:
	case DXGI_FORMAT_BC2_UNORM_SRGB:
	case DXGI_FORMAT_BC3_TYPELESS:
	case DXGI_FORMAT_BC3_UNORM:
	case DXGI_FORMAT_BC3_UNORM_SRGB:
	case DXGI_FORMAT_BC5_TYPELESS:
	case DXGI_FORMAT_BC5_UNORM:
	case DXGI_FORMAT_BC5_SNORM:
		return 128;

	case DXGI_FORMAT_R1_UNORM:
	case DXGI_FORMAT_BC1_TYPELESS:
	case DXGI_FORMAT_BC1_UNORM:
	case DXGI_FORMAT_BC1_UNORM_SRGB:
	case DXGI_FORMAT_BC4_TYPELESS:
	case DXGI_FORMAT_BC4_UNORM:
	case DXGI_FORMAT_BC4_SNORM:
		return 64;

	case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
		return 32;

	case DXGI_FORMAT_R8G8_B8G8_UNORM:
	case DXGI_FORMAT_G8R8_G8B8_UNORM:
		return 32;

	case DXGI_FORMAT_UNKNOWN:
	default:
		return 0;
	}
}

void DX11Texture2D::init(const Vec2u& size, unsigned char* pixelData, TEXTURE_FORMAT format)
{
	//Init texture
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(td));

	td.Width = size.x;
	td.Height = size.y;
	td.MipLevels = 1;//TODO: Add support for mip maps
	td.ArraySize = 1;
	td.Format = convertColorFormat(format);
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;
	/*
	if (textureFlags & ETF_RENDER_TARGET)
	{
		td.MipLevels = 1;
		td.BindFlags |= D3D11_BIND_RENDER_TARGET;

		HRESULT hr = device->CreateTexture2D(&td, NULL, &m_texture);
		if (FAILED(hr))
			return;
	}
	else if (textureFlags & ETF_DEPTH_STENCIL_BUFFER)
	{
		td.MipLevels = 1;
		td.ArraySize = 1;
		td.SampleDesc.Count = 1;
		td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		td.CPUAccessFlags = 0;
		td.MiscFlags = 0;

		HRESULT hr = device->CreateTexture2D(&td, NULL, &m_texture);
		if (FAILED(hr))
		{
			core::Debug::log(core::ELL_ERROR, "Texture", "Failed to create 2D texture");
			return;
		}
	}*/
	//else
	{
		unsigned int elementSz = sizeOfDXGIFormat(convertColorFormat(format)) / 8;
		unsigned int pitch = size.x*elementSz;

		D3D11_SUBRESOURCE_DATA initData;
		ZeroMemory(&initData, sizeof(D3D11_SUBRESOURCE_DATA));
		initData.pSysMem = (void*)pixelData;
		initData.SysMemPitch = size.x*elementSz;
		initData.SysMemSlicePitch = size.x*size.y*elementSz;

		HRESULT hr = m_device->CreateTexture2D(&td, &initData, &m_texture);
		if (FAILED(hr))
		{
			core::Debug::log(core::LL_ERROR, "Texture", "Failed to create 2D texture");
			return;
		}
	}

	//Init shader resource view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&srvd, sizeof(srvd));
	srvd.Format = td.Format;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

	/*if (textureFlags & ETF_RENDER_TARGET)
	{
		srvd.Texture2D.MostDetailedMip = 0;
		srvd.Texture2D.MipLevels = 1;
	}
	else*/
	srvd.Texture2D.MostDetailedMip = 0;
	srvd.Texture2D.MipLevels = -1;

	HRESULT hr = m_device->CreateShaderResourceView(m_texture, &srvd, &m_shaderResourceView);
	if (FAILED(hr))
	{
		core::Debug::log(core::LL_ERROR, "Texture", "Failed to create shader resource view for texture");
		return;
	}
}

void DX11Texture2D::unload()
{
	if (m_renderTargetView)
	{
		m_renderTargetView->Release();
	}

	if (m_shaderResourceView)
	{
		m_shaderResourceView->Release();
	}

	if (m_texture)
	{
		m_texture->Release();
	}
}