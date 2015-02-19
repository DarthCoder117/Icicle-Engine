#ifndef DX11_PIXEL_SHADER_H
#define DX11_PIXEL_SHADER_H
#include "graphics/PixelShader.h"
#ifdef ICE_WINDOWS
#include <d3d11.h>
#include "graphics/DX11GraphicsDriver.h"

namespace ice
{
	namespace graphics
	{
		class DX11PixelShader : public PixelShader
		{
		public:

			DX11PixelShader(GraphicsDriver* driver)
				:PixelShader(driver),
				m_device(((DX11GraphicsDriver*)driver)->getD3DDevice()),
				m_PS(NULL)
			{}

			~DX11PixelShader();

			void init(void* shaderByteCode, size_t shaderByteCodeSz);

			ID3D11PixelShader* getD3DShader(){ return m_PS; }

		private:

			ID3D11PixelShader* m_PS;
			ID3D11Device* m_device;
		};
	}
}

#endif

#endif