#ifndef DX11_SHADER_COMPILER_H
#define DX11_SHADER_COMPILER_H
#include "graphics/ShaderCompiler.h"
#ifdef ICE_WINDOWS
#include <d3d11.h>

namespace ice
{
	namespace graphics
	{
		class DX11ShaderCompiler : public ShaderCompiler
		{
		public:

			DX11ShaderCompiler(ID3D11Device* device)
				:m_device(device)
			{}

			SharedPtr<ShaderBlob> compileShader(const String& shaderSource, SHADER_TYPE shaderType);

		private:

			ID3D11Device* m_device;
		};
	}
}

#endif

#endif