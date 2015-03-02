#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <IcicleCommon.h>
#include "graphics/GraphicsDriver.h"
#include <core/EngineSystem.h>
#include <system/Window.h>
#include <system/InputSystem.h>

namespace ice
{
	namespace graphics
	{
		class Graphics : public core::IEngineSystem, public system::WindowEventListener
		{
		public:

			///@param driverType The type of graphics driver to create. If left as GDT_UNKNOWN then it will be automatically selected. 
			Graphics(system::Window* window, GRAPHICS_DRIVER_TYPE driverType = GDT_UNKNOWN);
			
			GraphicsDriver* getDriver(){ return m_driver.get(); }

			void start();

			void shutdown();
			
			void render();
			
			void onWindowEvent(const system::WindowEvent& evt);
			
		private:
			
			glm::uvec2 m_windowSize;

			system::Window* m_window;

			UniquePtr<GraphicsDriver> m_driver;

			VertexShader* m_vs;
			PixelShader* m_ps;

			InputLayout* m_vertLayout;
			VertexBuffer* m_vertBuffer;
		};
	}
}

#endif //GRAPHICS_H