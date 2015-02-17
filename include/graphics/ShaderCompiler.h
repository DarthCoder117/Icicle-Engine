#ifndef SHADER_COMPILER_H
#define SHADER_COMPILER_H
#include <IcicleCommon.h>
#include <core/Uncopyable.h>

namespace ice
{
	namespace graphics
	{
		enum SHADER_TYPE
		{
			ST_VERTEX,
			ST_PIXEL
		};

		class ShaderBlob
		{
		public:

			ShaderBlob(void* byteCode, size_t byteCodeSize)
				:m_byteCode(byteCode),
				m_byteCodeSize(byteCodeSize)
			{}

			~ShaderBlob()
			{
				if (m_byteCode)
				{
					free(m_byteCode);
				}
			}

			void* getByteCode(){ return m_byteCode; }

			size_t getByteCodeSize(){ return m_byteCodeSize; }

		private:

			void* m_byteCode;

			size_t m_byteCodeSize;
		};

		class ShaderCompiler : public core::Uncopyable
		{
		public:

			virtual SharedPtr<ShaderBlob> compileShader(const String& shaderSource, SHADER_TYPE shaderType) = 0;
		};
	}
}

#endif