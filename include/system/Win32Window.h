#ifndef WIN32_WINDOW_H
#define WIN32_WINDOW_H
#include <IcicleCommon.h>

#ifdef ICE_WINDOWS

#include "system/Window.h"

namespace ice
{
	namespace system
	{
		class Win32Window : public Window
		{
		public:

			Win32Window(const glm::uvec2& size = glm::uvec2(1280, 720), const String& windowTitle = "Icicle Engine", HWND existingWindow = NULL);

			bool run();

			void close();

			void setWindowTitle(const String& title);

			glm::uvec2 getWindowSize();

			WindowHandle getSystemHandle();
			
			void windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		private:

			HWND m_window;
		};
	}
}

#endif
#endif