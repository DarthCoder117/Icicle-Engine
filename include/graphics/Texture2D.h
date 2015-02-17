#ifndef TEXTURE_H
#define TEXTURE_H
#include <core/Resource.h>

namespace ice
{
	namespace graphics
	{
		enum TEXTURE_FORMAT
		{
			TF_RGBA8,
			TF_UNKNOWN
		};

		class GraphicsDriver;

		class Texture2D : public core::Resource<Texture2D>
		{
		public:

			Texture2D(GraphicsDriver* driver)
				:m_driver(driver),
				m_size(0, 0),
				m_pixelData(NULL),
				m_format(TF_UNKNOWN)
			{}

			virtual ~Texture2D(){}

			virtual void init(const Vec2u& size, unsigned char* pixelData, TEXTURE_FORMAT format) = 0;

			virtual void unload() = 0;

			void load(const String& path);

			void onPostLoad();

		protected:

			GraphicsDriver* m_driver;

			TEXTURE_FORMAT m_format;

			Vec2u m_size;

			unsigned char* m_pixelData;
		};
	}
}

#endif