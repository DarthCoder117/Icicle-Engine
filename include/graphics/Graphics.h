#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <IcicleCommon.h>
#include "graphics/GraphicsDriver.h"
#include "graphics/RenderEventListener.h"
#include <system/Window.h>
#include <system/InputSystem.h>

#include "graphics/RenderSystem2D.h"

namespace ice
{
	namespace graphics
	{	
		///@brief Manages all graphics and rendering functionality.
		class Graphics : public system::WindowEventListener
		{
		public:

			///@param driverType The type of graphics driver to create. If left as GDT_UNKNOWN then it will be automatically selected. 
			Graphics(system::Window& window, GRAPHICS_DRIVER_TYPE driverType = GDT_UNKNOWN);
			
			void init(core::Engine* engine);

			///@brief Registers a rendering event listener.
			void registerRenderEventListener(RenderEventListener* listener);

			///@return A reference to the 2D rendering system.
			RenderSystem2D& get2DRenderingSystem(){ return m_renderSystem2D; }

			///@return The low level graphics driver.
			GraphicsDriver* getDriver(){ return m_driver.get(); }

			void render();
			
			void onWindowEvent(const system::WindowEvent& evt);
			
		private:
			
			RenderSystem2D m_renderSystem2D;

			system::Window& m_window;

			UniquePtr<GraphicsDriver> m_driver;

			List<RenderEventListener*> m_renderListeners;
		};
	}
}

#endif //GRAPHICS_H