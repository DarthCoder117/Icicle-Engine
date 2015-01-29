#ifndef WINDOW_H
#define WINDOW_H

#include "core/EngineSystem.h"
#include <list>
#include <GLFW/glfw3.h>

namespace ice
{
	namespace system
	{
		///@brief Manages the application window and sends window events to any subscribed callback listeners.
		class Window : public core::IEngineSystem
		{
		public:

			Window(const core::LaunchParameters& params);

			void start();
			
			///@brief Called periodically to poll for window events and ensure that the window is running.
			void update();
			
			GLFWwindow* getWindow() const;
		private:	
			GLFWwindow* m_window;
		};
	}
}

#endif