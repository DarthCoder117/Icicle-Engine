#ifndef DX11_VERTEX_SHADER_H
#define DX11_VERTEX_SHADER_H
#include "graphics/VertexShader.h"
#ifdef ICE_WINDOWS
#include <d3d11.h>
#include "graphics/DX11GraphicsDriver.h"

namespace ice
{
	namespace graphics
	{
		class DX11VertexShader : public VertexShader
		{
		public:

			DX11VertexShader(GraphicsDriver* driver)
				:VertexShader(driver),
				m_device(((DX11GraphicsDriver*)driver)->getD3DDevice()),
				m_VS(NULL)
			{}

			~DX11VertexShader();

			void init(void* shaderByteCode, size_t shaderByteCodeSz);

			ID3D11VertexShader* getD3DShadeR(){ return m_VS; }

		private:

			ID3D11VertexShader* m_VS;
			ID3D11Device* m_device;
		};
	}
}

#endif

#endif