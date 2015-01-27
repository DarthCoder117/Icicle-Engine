#include "system/Window.h"

#include <iostream>

using namespace ice;
using namespace core;
using namespace system;

Window::Window(const sf::VideoMode& videoMode, const char* windowName)
{
	m_window.create(videoMode, windowName, sf::Style::Default);
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