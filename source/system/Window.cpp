#include "system/Window.h"

using namespace ice;
using namespace core;
using namespace system;

Window::Window(const core::LaunchParameters& params)
{
	m_window.create(params.m_windowSize, params.m_windowName);
}

void Window::setWindowTitle(const char* title)
{
	m_window.setTitle(title);
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