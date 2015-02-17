#ifndef DX11_VERTEX_BUFFER_H
#define DX11_VERTEX_BUFFER_H
#include "graphics/VertexBuffer.h"
#ifdef ICE_WINDOWS
#include <d3d11.h>
#include "graphics/DX11GraphicsDriver.h"

namespace ice
{
	namespace graphics
	{
		class DX11VertexBuffer : public VertexBuffer
		{
		public:

			DX11VertexBuffer(GraphicsDriver* driver)
				:VertexBuffer(driver),
				m_device(((DX11GraphicsDriver*)driver)->getD3DDevice()),
				m_vertexData(NULL)
			{}

			~DX11VertexBuffer();

			bool init(void* vertices, unsigned int numVertices, unsigned int vertexSz, unsigned int flags, PRIMITIVE_TOPOLOGY primitiveTopology);

			void* lock(LOCK_MODE mode);

			void unlock();

			ID3D11Buffer* getD3DBuffer(){ return m_vertexBuffer; }

		private:

			void* m_vertexData;
			
			LOCK_MODE m_lockMode;

			ID3D11Device* m_device;
			ID3D11Buffer* m_vertexBuffer;
		};
	}
}

#endif

#endif