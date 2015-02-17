#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H
#include <core/Resource.h>
#include "graphics/BufferConstants.h"

namespace ice
{
	namespace graphics
	{
		class GraphicsDriver;

		class IndexBuffer
		{
		public:

			IndexBuffer(GraphicsDriver* driver)
				:m_driver(driver),
				m_numIndices(0),
				m_flags(0)
			{}

			virtual ~IndexBuffer(){}

			virtual bool init(unsigned int* indices, unsigned int numIndices, unsigned int flags) = 0 
			{ 
				m_numIndices = numIndices; 
				m_flags = flags; 

				return true;
			}

			unsigned int getNumIndices(){ return m_numIndices; }

			unsigned int getFlags(){ return m_flags; }

			///@brief Locks the vertex buffer to access the vertex data.
			///It is up to the implementation to duplicate vertex data in system RAM when needed.
			///System RAM copies are not stored by default.
			virtual unsigned int* lock(LOCK_MODE mode) = 0;

			///@brief Unlocks the vertex buffer after accessing vertex data.
			virtual void unlock() = 0;

		protected:

			GraphicsDriver* m_driver;

			unsigned int m_numIndices;
			unsigned int m_flags;
		};
	}
}

#endif