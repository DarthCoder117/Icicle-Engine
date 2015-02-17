#include "graphics/Texture2D.h"
#include <system/FileSystem.h>
#include "graphics/GraphicsDriver.h"

#define STB_IMAGE_IMPLEMENTATION
#include <../3rd-party/stb/stb_image.h>

using namespace ice;
using namespace graphics;

void Texture2D::load(const String& path)
{
	SharedPtr<core::DataStream> stream = system::FileSystem::instance()->openFile(path);
	if (stream && stream->isValid())
	{
		//Read in image data
		size_t bufferSz = stream->getSize();
		unsigned char* buffer = (unsigned char*)malloc(bufferSz);
		stream->read(buffer, bufferSz);
		stream->close();

		//Load pixel data from image
		int x = 0;
		int y = 0;
		int comp = 0;
		m_pixelData = stbi_load_from_memory(buffer, bufferSz, &x, &y, &comp, 4);

		if (m_pixelData)
		{
			//Store size
			m_size.x = x;
			m_size.y = y;

			//Determine texture format
			m_format = TF_RGBA8;

			//Just create the texture now if supported
			if (m_driver->getCaps().concurrentCreation)
			{
				init(m_size, m_pixelData, m_format);

				stbi_image_free(m_pixelData);
				m_pixelData = NULL;
			}
		}

		free(buffer);
	}
}

void Texture2D::onPostLoad()
{
	//If the image data hasn't been freed by now, then concurrent creation wasn't supported and it has to be created here.
	if (m_pixelData)
	{
		init(m_size, m_pixelData, m_format);

		stbi_image_free(m_pixelData);
		m_pixelData = NULL;
	}
}