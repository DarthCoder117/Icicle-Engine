#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "core/SubSystem.h"
#include "system/Window.h"
#include <bgfxdefines.h>

namespace ice
{
	namespace graphics
	{
		class Graphics : public core::SubSystem<Graphics>, public system::WindowEventCallback {
		public:
			Graphics(system::Window* window);
			
			void start();
			void update();
			void shutdown();
			
			void render();
		private:
			virtual void onWindowEvent(const sf::Event& evt);
			
		private:
			static const uint32_t debug = BGFX_DEBUG_TEXT;
			static const uint32_t reset = BGFX_RESET_VSYNC;
			
			uint32_t renderWidth;
			uint32_t renderHeight;
			
			system::Window* m_window;
		};
	}
}

#endif //GRAPHICS_H