#ifndef VERTEX_SHADER_H
#define VERTEX_SHADER_H
#include <core/Resource.h>
#include "graphics/BufferConstants.h"

namespace ice
{
	namespace graphics
	{
		class GraphicsDriver;

		class VertexShader
		{
		public:

			VertexShader(GraphicsDriver* driver)
				:m_driver(driver)
			{}

			virtual ~VertexShader(){}

			virtual void init(void* shaderByteCode, size_t shaderByteCodeSz) = 0;

		protected:

			GraphicsDriver* m_driver;
		};
	}
}

#endif