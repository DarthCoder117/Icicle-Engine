#ifndef WINDOW_H
#define WINDOW_H
#include "core/SubSystem.h"
#include <vector>
#include <SFML/Window.hpp>

namespace ice
{
	namespace core
	{
		class WindowEventCallback
		{
		public:

			virtual ~WindowEventCallback(){}

			virtual void onWindowEvent(const sf::Event& evt) = 0;
		};

		class Window : public SubSystem
		{
		public:

			Window(const sf::VideoMode& videoMode = sf::VideoMode(800, 600), const char* windowName = "Icicle Engine Window");

			///@brief Called periodically to poll for window events and ensure that the window is running.
			bool run();

			void registerWindowCallback(WindowEventCallback* callback);

			SubSystemType getType()
			{
				return WINDOW;
			}

		private:

			std::vector<WindowEventCallback*> m_windowCallbacks;

			sf::Window m_window;
		};
	}
}

#endif