#ifndef PIXEL_SHADER_H
#define PIXEL_SHADER_H
#include <core/Resource.h>
#include "graphics/BufferConstants.h"

namespace ice
{
	namespace graphics
	{
		class GraphicsDriver;

		class PixelShader
		{
		public:

			PixelShader(GraphicsDriver* driver)
				:m_driver(driver)
			{}

			virtual ~PixelShader(){}

			virtual void init(void* shaderByteCode, size_t shaderByteCodeSz) = 0;

		protected:

			GraphicsDriver* m_driver;
		};
	}
}

#endif