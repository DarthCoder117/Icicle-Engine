#ifndef WINDOW_H
#define WINDOW_H

#include "core/SubSystem.h"
#include <vector>
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

			Window(const sf::VideoMode& videoMode = sf::VideoMode(800, 600), const char* windowName = "Icicle Engine Window");

			void init();
			
			///@brief Called periodically to poll for window events and ensure that the window is running.
			void update();

			void shutdown();
			
			void registerWindowCallback(WindowEventCallback* callback);
			
			bool isOpen();
			void close();
			
			const sf::Vector2u getSize() const;
			
			sf::WindowHandle getSystemHandle() const;
		private:
			std::vector<WindowEventCallback*> m_windowCallbacks;
			
			sf::Window m_window;
		};
	}
}

#endif