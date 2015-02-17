#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H
#include "graphics/BufferConstants.h"

namespace ice
{
	namespace graphics
	{
		class GraphicsDriver;

		class VertexBuffer
		{
		public:

			VertexBuffer(GraphicsDriver* driver)
				:m_driver(driver),
				m_vertexSz(0),
				m_numVertices(0),
				m_flags(0),
				m_primitiveTopology(PT_TRIANGLELIST)
			{}

			virtual ~VertexBuffer(){}

			virtual bool init(void* vertices, unsigned int numVertices, unsigned int vertexSz, unsigned int flags = BF_DEFAULT_USAGE, PRIMITIVE_TOPOLOGY primitiveTopology = PT_TRIANGLELIST) = 0
			{
				m_numVertices = numVertices;
				m_vertexSz = vertexSz;
				m_flags = flags;
				m_primitiveTopology = primitiveTopology;

				return true;
			}

			unsigned int getVertexSize(){ return m_vertexSz; }

			unsigned int getNumVertices(){ return m_numVertices; }

			unsigned int getFlags(){ return m_flags; }

			PRIMITIVE_TOPOLOGY getPrimitiveTopology(){ return m_primitiveTopology; }

			///@brief Locks the vertex buffer to access the vertex data.
			///It is up to the implementation to duplicate vertex data in system RAM when needed.
			///System RAM copies are not stored by default.
			virtual void* lock(LOCK_MODE mode) = 0;

			///@brief Unlocks the vertex buffer after accessing vertex data.
			virtual void unlock() = 0;

		protected:

			GraphicsDriver* m_driver;

			unsigned int m_flags;

			PRIMITIVE_TOPOLOGY m_primitiveTopology;

			unsigned int m_numVertices;
			unsigned int m_vertexSz;
		};
	}
}

#endif