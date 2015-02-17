#include "graphics/DX11ShaderCompiler.h"
#include <core/Debug.h>
#include <D3Dcompiler.h>

using namespace ice;
using namespace graphics;

SharedPtr<ShaderBlob> DX11ShaderCompiler::compileShader(const String& shaderSource, SHADER_TYPE shaderType)
{
	ID3DBlob* vsBlob;
	ID3DBlob* errorBlob;

	const char* entryPoint = "";
	const char* shaderModel = "";

	if (shaderType == ST_PIXEL)
	{
		entryPoint = "PS";
		shaderModel = "ps_5_0";
	}
	else if (shaderType == ST_VERTEX)
	{
		entryPoint = "VS";
		shaderModel = "vs_5_0";
	}
	else
	{
		core::Debug::log(core::LL_ERROR, "ShaderCompiler", "Unsupported shader type");
		return NULL;
	}

	HRESULT hr = D3DCompile(&shaderSource[0], shaderSource.size(), "shader", NULL, NULL, entryPoint, shaderModel, D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_DEBUG, NULL, &vsBlob, &errorBlob);
	if (FAILED(hr))
	{
		core::Debug::log(core::LL_ERROR, "vertex shader", (const char*)errorBlob->GetBufferPointer());

		errorBlob->Release();

		return NULL;
	}

	size_t bufferSz = vsBlob->GetBufferSize();
	void* buffer = malloc(bufferSz);
	memcpy(buffer, vsBlob->GetBufferPointer(), bufferSz);

	vsBlob->Release();

	return makeShared<ShaderBlob>(buffer, bufferSz);
}