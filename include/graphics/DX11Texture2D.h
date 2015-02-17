#ifndef DX11_TEXTURE_H
#define DX11_TEXTURE_H
#include "graphics/Texture2D.h"
#ifdef ICE_WINDOWS
#include <d3d11.h>
#include "graphics/DX11GraphicsDriver.h"

namespace ice
{
	namespace graphics
	{
		class DX11Texture2D : public Texture2D
		{
		public:

			DX11Texture2D(GraphicsDriver* driver)
				:Texture2D(driver),
				m_device(((DX11GraphicsDriver*)driver)->getD3DDevice())
			{}

			~DX11Texture2D()
			{
				unload();
			}

			void init(const Vec2u& size, unsigned char* pixelData, TEXTURE_FORMAT format);

			void unload();

			ID3D11RenderTargetView* getRenderTargetView(){ return m_renderTargetView; }
			ID3D11ShaderResourceView* getShaderResourceView(){ return m_shaderResourceView; }

		private:

			ID3D11Device* m_device;

			ID3D11Texture2D* m_texture;
			ID3D11ShaderResourceView* m_shaderResourceView;

			ID3D11RenderTargetView* m_renderTargetView;
		};
	}
}

#endif

#endif