#include "system/Window.h"

#include <iostream>
#include "system/InputSystem.h"

using namespace ice;
using namespace core;
using namespace system;

Window::Window(const core::LaunchParameters& params)
{
	/* Initialize the library */
	if (!glfwInit()) {
		std::cout << "Failed to create glfw context\n";
	}
	
	/* Create a windowed mode window and its OpenGL context */
	m_window = glfwCreateWindow(params.m_windowSize.x, params.m_windowSize.y, params.m_windowName, NULL, NULL);
	
	if (!m_window) {
		glfwTerminate();
		std::cout << "Failed to create an window\n";
	}
	
	InputSystem::initialise(m_window);
}

void Window::start() {
	/* Make the window's context current */
	glfwMakeContextCurrent(m_window);
}

void Window::update()
{
	glfwPollEvents();
}

GLFWwindow* Window::getWindow() const
{
	return m_window;
}