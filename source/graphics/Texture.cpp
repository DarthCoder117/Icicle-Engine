#include "graphics/Texture.h"
#include <system/FileSystem.h>

#define STB_IMAGE_IMPLEMENTATION
#include <../3rd-party/stb/stb_image.h>

using namespace ice;
using namespace graphics;

void Texture::load(const String& path)
{
	/*SharedPtr<core::DataStream> stream = system::FileSystem::instance()->openFile(path);
	if (stream && stream->isValid())
	{
		size_t bufferSz = stream->getSize();
		m_pixelData.data = (unsigned char*)malloc(bufferSz + 1);
		stream->read(m_pixelData.data, bufferSz);
		m_pixelData.data[bufferSz - 1] = '\0';
		m_pixelData.size = bufferSz;
		stream->close();
	}*/
}

void Texture::onPostLoad()
{
	if (m_pixelData.data)
	{	
		//m_texture = bgfx::createTexture(&m_pixelData);
	}
}

void Texture::unload()
{
	if (m_pixelData.data)
	{
		//free(m_pixelData.data);
	}
}