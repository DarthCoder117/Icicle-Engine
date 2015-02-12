#ifndef WINDOW_H
#define WINDOW_H
#include <IcicleCommon.h>
#include "core/EngineSystem.h"

#ifdef ICE_WINDOWS
#include <Windows.h>
#else
#include <GLFW/glfw3.h>
#endif

namespace ice
{
	namespace system
	{
		#ifdef ICE_WINDOWS
		typedef HWND WindowHandle;
		#else
		typedef GLFWwindow* WindowHandle;
		#endif

		class Window;

		struct WindowEvent 
		{
			enum Type
			{
				GAINED_FOCUS,
				LOST_FOCUS,
				REFRESHED,
				MINIMIZED,
				RESTORED,
				MOVED,
				RESIZED,
				CLOSED
			};

			Window* window;
			Type type;
			
			Vec2u size;
			Vec2u position;
		};

		class WindowEventListener 
		{
		public:
			
			virtual void onWindowEvent(const WindowEvent& evt) = 0;
		};

		///@brief Manages the application window and sends window events to any subscribed callback listeners.
		class Window : public core::IEngineSystem
		{
		public:

			virtual ~Window(){}

			///@brief Called periodically to poll for window events and ensure that the window is running.
			virtual bool run() = 0;

			///@brief Closes the window.
			virtual void close() = 0;

			///@brief Changes the text displayed in the window's title bar.
			virtual void setWindowTitle(const String& title) = 0;

			///@return The size in pixels of the drawable client area of the window.
			virtual Vec2u getWindowSize() = 0;

			///@return The operating system's native handle to the window.
			virtual WindowHandle getSystemHandle() = 0;

			void registerWindowEventListener(WindowEventListener* listener);

			void unregisterWindowEventListener(WindowEventListener* listener);

		protected:

			///@brief Used by window implementations to send window events.
			void transmitWindowEvent(const WindowEvent& evt);

			List<WindowEventListener*> m_windowEventListeners;
		};
	}
}

#endif