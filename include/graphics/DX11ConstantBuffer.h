#ifndef DX11_CONSTANT_BUFFER_H
#define DX11_CONSTANT_BUFFER_H
#include "graphics/ConstantBuffer.h"
#ifdef ICE_WINDOWS
#include <d3d11.h>
#include "graphics/DX11GraphicsDriver.h"

namespace ice
{
	namespace graphics
	{
		class DX11ConstantBuffer : public ConstantBuffer
		{
		public:

			DX11ConstantBuffer(GraphicsDriver* driver, void* data, size_t bufferSz);

			~DX11ConstantBuffer();

			void updateBuffer(void* data);

			size_t bufferSize();

			ID3D11Buffer* getD3DBuffer(){ return m_constBuffer; }

		private:

			ID3D11Device* m_device;
			ID3D11Buffer* m_constBuffer;

			size_t m_bufferSz;
		};
	}
}

#endif

#endif