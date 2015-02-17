#ifndef LINUX_WINDOW_H
#define LINUX_WINDOW_H
#include "system/Window.h"

#include "system/InputSystem.h"

namespace ice
{
	namespace system
	{
		class LinuxWindow : public Window
		{
		public:

			LinuxWindow(const Vec2u& size = Vec2u(1280, 720), const String& windowTitle = "Icicle Engine");

			void start();

			bool run();

			void close();

			void setWindowTitle(const String& title);

			Vec2u getWindowSize();

			WindowHandle getSystemHandle();

			#ifdef ICE_LINUX
			static void registerWindowListener(WindowEventListener* listener);
			static void registerWindowFocusCallback(GLFWwindow* window, int focused);
			static void registerWindowIconifiedCallback(GLFWwindow* window, int iconified);
			static void registerWindowPositionCallback(GLFWwindow* window, int xpos, int ypos);
			static void registerWindowSizeCallback(GLFWwindow* window, int width, int height);
			static void registerWindowCloseCallback(GLFWwindow* window);
			static void registerWindowRefreshCallback(GLFWwindow* window);

		private:

			GLFWwindow* m_window;
			#endif
		};
	}
}

#endif