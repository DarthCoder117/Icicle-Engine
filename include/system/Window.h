#ifndef WINDOW_H
#define WINDOW_H

#include "core/SubSystem.h"
#include <list>
#include <SFML/Window.hpp>

namespace ice
{
	namespace system
	{
		class WindowEventCallback
		{
		public:

			virtual ~WindowEventCallback(){}

			virtual void onWindowEvent(const sf::Event& evt) = 0;
		};

		///@brief Manages the application window and sends window events to any subscribed callback listeners.
		class Window : public core::SubSystem<Window>
		{
		public:

			Window(const core::LaunchParameters& params);

			///@brief Called periodically to poll for window events and ensure that the window is running.
			void update();

			///@brief Changes the text displayed in the window title bar.
			void setWindowTitle(const char* title);

			///@brief Registers a callback to recieve window events.
			void registerWindowCallback(WindowEventCallback* callback);
			///@brief Unregisters a window event callback.
			void unregisterWindowCallback(WindowEventCallback* callback);
			
			///@return The size of the client area (excluding the title bar and borders)
			sf::Vector2u getWindowSize();
			///@return The OS window handle.
			sf::WindowHandle getSystemHandle() const;

			bool isOpen();
			void close();
			
			const sf::Vector2u getSize() const;
		private:	
			std::list<WindowEventCallback*> m_windowCallbacks;///< pointers will end up scattered around in memory anyways so list makes deletions more efficient.
			sf::Window m_window;
		};
	}
}

#endif