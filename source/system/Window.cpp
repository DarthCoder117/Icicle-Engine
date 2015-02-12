#include "system/Window.h"

#include <iostream>
#include "system/InputSystem.h"

using namespace ice;
using namespace core;
using namespace system;

void Window::registerWindowEventListener(WindowEventListener* listener)
{
	m_windowEventListeners.push_back(listener);
}

void Window::unregisterWindowEventListener(WindowEventListener* listener)
{
	List<WindowEventListener*>::iterator iter;
	for (iter = m_windowEventListeners.begin(); iter != m_windowEventListeners.end(); ++iter)
	{
		if (*iter == listener)
		{
			m_windowEventListeners.erase(iter);
			return;
		}
	}
}

void Window::transmitWindowEvent(const WindowEvent& evt)
{
	for (auto listener : m_windowEventListeners)
	{
		listener->onWindowEvent(evt);
	}
}