#include "core/Window.h"

using namespace ice;
using namespace core;

Window::Window(const sf::VideoMode& videoMode, const char* windowName)
{
	m_window.create(videoMode, windowName);
}

void Window::init()
{
}


void Window::update()
{
	if (m_window.isOpen())
	{
		//Handle window events
		sf::Event evt;
		while (m_window.pollEvent(evt))
		{
			//Send window event to all callbacks
			for (unsigned int i = 0; i < m_windowCallbacks.size(); ++i)
			{
				m_windowCallbacks[i]->onWindowEvent(evt);
			}
		}
		
		m_window.display();
	}
}

void Window::shutdown()
{
}


bool Window::isOpen()
{
	return m_window.isOpen();
}

void Window::close()
{
	m_window.close();
}

void Window::registerWindowCallback(WindowEventCallback* callback)
{
	m_windowCallbacks.push_back(callback);
}