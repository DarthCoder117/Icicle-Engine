#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "IcicleCommon.h"
#include <bgfxdefines.h>

#include "core/EngineSystem.h"
#include "system/Window.h"
#include "system/InputSystem.h"


namespace ice
{
	namespace graphics
	{
		class Graphics : public core::IEngineSystem, public system::WindowEventListener
		{
		public:

			Graphics(system::Window* window);
			
			void start();

			void shutdown();
			
			void render();
			
			void onWindowEvent(const system::WindowEvent& evt);
			
		private:
			static const uint32_t debug = BGFX_DEBUG_TEXT;
			static const uint32_t reset = BGFX_RESET_VSYNC;
			
			Vec2u m_windowSize;

			system::Window* m_window;
		};
	}
}

#endif //GRAPHICS_H