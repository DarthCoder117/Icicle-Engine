#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "core/SubSystem.h"
#include "system/Window.h"
#include <bgfxdefines.h>
#include "system/InputSystem.h"


namespace ice
{
	namespace graphics
	{
		class Graphics : public core::SubSystem<Graphics>,  public system::WindowEventListener {
		public:
			Graphics(system::Window* window);
			
			void start();
			void update();
			void shutdown();
			
			void render();
			
			void onWindowEvent(system::WindowEvent event);
			
		private:
			static const uint32_t debug = BGFX_DEBUG_TEXT;
			static const uint32_t reset = BGFX_RESET_VSYNC;
			
			int32_t renderWidth;
			int32_t renderHeight;
			
			system::Window* m_window;
		};
	}
}

#endif //GRAPHICS_H