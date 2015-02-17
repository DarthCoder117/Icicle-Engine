#ifndef DX11_INDEX_BUFFER_H
#define DX11_INDEX_BUFFER_H
#include "graphics/IndexBuffer.h"
#ifdef ICE_WINDOWS
#include <d3d11.h>
#include "graphics/DX11GraphicsDriver.h"

namespace ice
{
	namespace graphics
	{
		class GraphicsDriver;

		class DX11IndexBuffer : public IndexBuffer
		{
		public:

			DX11IndexBuffer(GraphicsDriver* driver)
				:IndexBuffer(driver),
				m_device(((DX11GraphicsDriver*)driver)->getD3DDevice()),
				m_indexData(NULL)
			{}

			~DX11IndexBuffer();

			bool init(unsigned int* indices, unsigned int numIndices, unsigned int flags = BF_DEFAULT_USAGE);

			unsigned int* lock(LOCK_MODE mode);

			void unlock();

			ID3D11Buffer* getD3DBuffer(){ return m_indexBuffer; }

		protected:

			GraphicsDriver* m_driver;

			unsigned int* m_indexData;

			LOCK_MODE m_lockMode;

			ID3D11Device* m_device;
			ID3D11Buffer* m_indexBuffer;
		};
	}
}

#endif

#endif