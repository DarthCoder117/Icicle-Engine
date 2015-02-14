#ifndef TEXTURE_H
#define TEXTURE_H
#include <core/Resource.h>
#include <bgfx.h>

namespace ice
{
	namespace graphics
	{
		class Texture : public core::Resource<Texture>
		{
		public:

			Texture()
				:m_width(0),
				m_height(0)
			{}

			~Texture()
			{
				unload();
			}

			void load(const String& path);

			void onPostLoad();

			void unload();

		private:

			unsigned int m_width;
			unsigned int m_height;
			
			bgfx::Memory m_pixelData;

			bgfx::TextureHandle m_texture;
		};
	}
}

#endif