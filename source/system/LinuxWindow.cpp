#include "system/LinuxWindow.h"
#include <iostream>

using namespace ice;
using namespace system;

#ifdef ICE_LINUX
LinuxWindow::LinuxWindow(const Vec2u& size, const String& windowTitle)
{
	/* Initialize the library */
	if (!glfwInit()) 
	{
		std::cout << "Failed to create glfw context\n";
	}

	/* Create a windowed mode window and its OpenGL context */
	m_window = glfwCreateWindow(size.x, size.y, windowTitle.c_str(), NULL, NULL);
	glfwSetWindowUserPointer(m_window, this);

	if (!m_window)
	{
		glfwTerminate();
		std::cout << "Failed to create an window\n";
	}

	//Window events
	glfwSetWindowCloseCallback(m_window, LinuxWindow::registerWindowCloseCallback);
	glfwSetWindowSizeCallback(m_window, LinuxWindow::registerWindowSizeCallback);
	glfwSetWindowPosCallback(m_window, LinuxWindow::registerWindowPositionCallback);
	glfwSetWindowIconifyCallback(m_window, LinuxWindow::registerWindowIconifiedCallback);
	glfwSetWindowFocusCallback(m_window, LinuxWindow::registerWindowFocusCallback);
	glfwSetWindowRefreshCallback(m_window, LinuxWindow::registerWindowRefreshCallback);

	InputSystem::initialise(m_window);
}

void LinuxWindow::start()
{
	/* Make the window's context current */
	glfwMakeContextCurrent(m_window);
}

bool LinuxWindow::run()
{
	glfwPollEvents();
	return !glfwWindowShouldClose(m_window);
}

void LinuxWindow::close()
{
	glfwSetWindowShouldClose(m_window, GL_TRUE);
}

void LinuxWindow::setWindowTitle(const String& title)
{
	glfwSetWindowTitle(m_window, title.c_str());
}

Vec2u LinuxWindow::getWindowSize()
{
	int renderWidth, renderHeight = 0;
	glfwGetWindowSize(m_window, &renderWidth, &renderHeight);
	return Vec2u(renderWidth, renderHeight);
}

WindowHandle LinuxWindow::getSystemHandle()
{
	return m_window;
}

void LinuxWindow::registerWindowFocusCallback(GLFWwindow* window, int focused)
{
	WindowEvent event;
	event.window = (Window*)glfwGetWindowUserPointer(window);
	
	if (focused) 
	{
		event.type = WindowEvent::GAINED_FOCUS;
	} 
	else 
	{
		event.type = WindowEvent::LOST_FOCUS;
	}

	((LinuxWindow*)glfwGetWindowUserPointer(window))->transmitWindowEvent(event);
}

void LinuxWindow::registerWindowIconifiedCallback(GLFWwindow* window, int iconified)
{
	WindowEvent event;
	event.window = (Window*)glfwGetWindowUserPointer(window);
	
	if (iconified) 
	{
		event.type = WindowEvent::MINIMIZED;
	}
	else 
	{
		event.type = WindowEvent::RESTORED;
	}

	((LinuxWindow*)glfwGetWindowUserPointer(window))->transmitWindowEvent(event);
}

void LinuxWindow::registerWindowPositionCallback(GLFWwindow* window, int xpos, int ypos)
{
	WindowEvent event;
	event.window = (Window*)glfwGetWindowUserPointer(window);
	event.type = WindowEvent::MOVED;

	event.position.x = xpos;
	event.position.y = ypos;

	((LinuxWindow*)glfwGetWindowUserPointer(window))->transmitWindowEvent(event);
}

void LinuxWindow::registerWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	WindowEvent event;
	event.window = (Window*)glfwGetWindowUserPointer(window);
	event.type = WindowEvent::RESIZED;

	event.size.x = width;
	event.size.y = height;

	((LinuxWindow*)glfwGetWindowUserPointer(window))->transmitWindowEvent(event);
}

void LinuxWindow::registerWindowCloseCallback(GLFWwindow* window)
{
	WindowEvent event;
	event.window = (Window*)glfwGetWindowUserPointer(window);
	event.type = WindowEvent::CLOSED;

	((LinuxWindow*)glfwGetWindowUserPointer(window))->transmitWindowEvent(event);
}

void LinuxWindow::registerWindowRefreshCallback(GLFWwindow* window)
{
	WindowEvent event;
	event.window = (Window*)glfwGetWindowUserPointer(window);
	event.type = WindowEvent::REFRESHED;

	((LinuxWindow*)glfwGetWindowUserPointer(window))->transmitWindowEvent(event);
}

#else
LinuxWindow::LinuxWindow(const Vec2u& size, const String& windowTitle)
{
	assert(0 && "Linux window is not supported on this platform.");
}

void LinuxWindow::start()
{
	
}

void LinuxWindow::close()
{

}

bool LinuxWindow::run()
{
	return false;
}

void LinuxWindow::setWindowTitle(const String& title)
{

}

Vec2u LinuxWindow::getWindowSize()
{
	return Vec2u(0, 0);
}

WindowHandle LinuxWindow::getSystemHandle()
{
	return NULL;
}
#endif