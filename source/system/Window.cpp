#include "system/Window.h"

#include <iostream>

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
			std::list<WindowEventCallback*>::iterator iter;
			for (iter = m_windowCallbacks.begin(); iter != m_windowCallbacks.end(); ++iter)
			{
				(*iter)->onWindowEvent(evt);
			}
		}
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

const sf::Vector2u Window::getSize() const {
	return m_window.getSize();
}

void Window::registerWindowCallback(WindowEventCallback* callback)
{
	m_windowCallbacks.push_back(callback);
}

sf::WindowHandle Window::getSystemHandle() const {
	return m_window.getSystemHandle();
}

void Window::unregisterWindowCallback(WindowEventCallback* callback)
{
	std::list<WindowEventCallback*>::iterator iter;
	for (iter = m_windowCallbacks.begin(); iter != m_windowCallbacks.end(); ++iter)
	{
		if (*iter == callback)
		{
			m_windowCallbacks.erase(iter);
			return;
		}
	}
}

sf::Vector2u Window::getWindowSize()
{
	return m_window.getSize();
}