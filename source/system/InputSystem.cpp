#include "system/InputSystem.h"

using namespace ice;
using namespace system;

std::vector<WindowEventListener*> InputSystem::m_windowListener;
std::vector<KeyEventListener*> InputSystem::m_keyListener;
std::vector<TextEventListener*> InputSystem::m_textListener;
std::vector<MouseEventListener*> InputSystem::m_mouseListener;


void InputSystem::initialise(GLFWwindow *window)
{
	glfwSetWindowCloseCallback(window, InputSystem::registerWindowCloseCallback);
	glfwSetWindowSizeCallback(window, InputSystem::registerWindowSizeCallback);
	glfwSetFramebufferSizeCallback(window, InputSystem::registerWindowFrameBufferSizeCallback);
	glfwSetWindowPosCallback(window, InputSystem::registerWindowPositionCallback);
	glfwSetWindowIconifyCallback(window, InputSystem::registerWindowIconifiedCallback);
	glfwSetWindowFocusCallback(window, InputSystem::registerWindowFocusCallback);
	glfwSetWindowRefreshCallback(window, InputSystem::registerWindowRefreshCallback);
	
	glfwSetKeyCallback(window, InputSystem::registerKeyCallback);
	
	glfwSetCharCallback(window, InputSystem::registerTextCallback);
	
	glfwSetCursorPosCallback(window, InputSystem::registerMouseMoveCallback);
	glfwSetCursorEnterCallback(window, InputSystem::registerMouseEnterCallback);
	glfwSetMouseButtonCallback(window, InputSystem::registerMouseButtonCallback);
	glfwSetScrollCallback(window, InputSystem::registerMouseScrollCallback);
}

void InputSystem::registerWindowListener(WindowEventListener* listener) 
{
	m_windowListener.push_back(listener);
}

void InputSystem::registerWindowFocusCallback(GLFWwindow* window, int focused) 
{
	WindowEvent event;
	event.window = window;
	event.type = WindowEventType::FOCUS;
	
	if (focused) {
		event.data.focused = true;
	} else {
		event.data.focused = false;
	}
	
	transmitWindowEvent(event);
}

void InputSystem::registerWindowIconifiedCallback(GLFWwindow* window, int iconified) 
{
	WindowEvent event;
	event.window = window;
	event.type = WindowEventType::ICONIFIED;
	
	if (iconified) {
		event.data.iconified = true;
	} else {
		event.data.iconified = false;
	}
	
	transmitWindowEvent(event);
}

void InputSystem::registerWindowPositionCallback(GLFWwindow* window, int xpos, int ypos) 
{
	WindowEvent event;
	event.window = window;
	event.type = WindowEventType::WINDOWPOSITION;
	
	event.data.position.x = xpos;
	event.data.position.y = ypos;
	
	transmitWindowEvent(event);
	
}

void InputSystem::registerWindowFrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	WindowEvent event;
	event.window = window;
	event.type = WindowEventType::FRAMBUFFERSIZE;
	
	event.data.size.width = width;
	event.data.size.height = height;
	
	transmitWindowEvent(event);
}
void InputSystem::registerWindowSizeCallback(GLFWwindow* window, int width, int height) 
{
	WindowEvent event;
	event.window = window;
	event.type = WindowEventType::WINDOWSIZE;
	
	event.data.size.width = width;
	event.data.size.height = height;
	
	transmitWindowEvent(event);
}
void InputSystem::registerWindowCloseCallback(GLFWwindow* window) 
{
	WindowEvent event;
	event.window = window;
	event.type = WindowEventType::CLOSE;

	transmitWindowEvent(event);
}

void InputSystem::registerWindowRefreshCallback(GLFWwindow* window) 
{
	WindowEvent event;
	event.window = window;
	event.type = WindowEventType::REFRESH;
	
	transmitWindowEvent(event);
}

void InputSystem::transmitWindowEvent(WindowEvent event)
{
	for (auto it : m_windowListener) {
		it->onWindowEvent(event);
	}
}



void InputSystem::registerKeyListener(KeyEventListener* listener) 
{
	m_keyListener.push_back(listener);
}

void InputSystem::registerKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	KeyEvent event;
	event.window = window;
	event.key = key;
	event.scancode = scancode;
	event.action = action;
	event.mods = mods;
	
	transmitKeyEvent(event);
}

void InputSystem::transmitKeyEvent(KeyEvent event) 
{
	for (auto it : m_keyListener) {
		it->onKeyEvent(event);
	}
}


void InputSystem::registerTextListener(TextEventListener* listener) {
	m_textListener.push_back(listener);
}

void InputSystem::registerTextCallback(GLFWwindow* window, unsigned int codepoint) {
	TextEvent event;
	event.window = window;
	event.codepoint = codepoint;
	
	transmitTextEvent(event);
}

void InputSystem::transmitTextEvent(TextEvent event)
{
	for (auto it : m_textListener) {
		it->onTextEvent(event);
	}
}

void InputSystem::registerMouseListener(MouseEventListener* listener)
{
	m_mouseListener.push_back(listener);
}

void InputSystem::registerMouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	MouseEvent event;
	
	event.window = window;
	event.type = MouseEventType::MOUSEPOSITION;
	event.data.position.x = xpos;
	event.data.position.y = ypos;
	
	transmitMouseEvent(event);
}

void InputSystem::registerMouseEnterCallback(GLFWwindow* window, int entered)
{
	MouseEvent event;
	
	event.window = window;
	event.type = MouseEventType::ENTERED;
	
	if (entered) {
		event.data.entered = true;
	} else {
		event.data.entered = false;
	}
	
	transmitMouseEvent(event);
}

void InputSystem::registerMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	MouseEvent event;
	
	event.window = window;
	event.type = MouseEventType::BUTTON;
	event.data.buttonState.action = action;
	event.data.buttonState.button = button;
	event.data.buttonState.mods = mods;
	
	transmitMouseEvent(event);
}

void InputSystem::registerMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	MouseEvent event;
	
	event.window = window;
	event.type = MouseEventType::SCROLL;
	event.data.scrollState.xoffset = xoffset;
	event.data.scrollState.yoffset = yoffset;
	
	transmitMouseEvent(event);
}


void InputSystem::transmitMouseEvent(MouseEvent event)
{
	for (auto it : m_mouseListener) {
		it->onMouseEvent(event);
	}
}


