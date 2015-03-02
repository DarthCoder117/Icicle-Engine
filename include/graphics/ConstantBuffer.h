#ifndef I_CONSTANT_BUFFER_H
#define I_CONSTANT_BUFFER_H
#include <IcicleCommon.h>

namespace ice
{
	namespace graphics
	{
		///@brief Stores shader parameters inside const buffers (or structs if const buffer type objects are not supported by the underlying API).
		///Parameter names are considered global and MUST be unique accross all parameter buffers.
		class ConstantBuffer
		{
		public:

			virtual ~ConstantBuffer(){}

			///@brief Updates the constant buffer's data.
			virtual void updateBuffer(void* data) = 0;

			///@return The size of the buffer in bytes
			virtual size_t bufferSize() = 0;
		};
	}
}

#endif