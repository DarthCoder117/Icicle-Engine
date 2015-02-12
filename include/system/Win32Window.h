#ifndef WIN32_WINDOW_H
#define WIN32_WINDOW_H
#include "system/Window.h"

namespace ice
{
	namespace system
	{
		class Win32Window : public Window
		{
		public:

			Win32Window(const Vec2u& size = Vec2u(1280, 720), const String& windowTitle = "Icicle Engine", HWND existingWindow = NULL);

			bool run();

			void close();

			void setWindowTitle(const String& title);

			Vec2u getWindowSize();

			WindowHandle getSystemHandle();

			#ifdef ICE_WINDOWS
			void windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		private:

			HWND m_window;
			#endif
		};
	}
}

#endif