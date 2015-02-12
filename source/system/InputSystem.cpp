#include "system/InputSystem.h"

using namespace ice;
using namespace system;

std::vector<KeyEventListener*> InputSystem::m_keyListener;
std::vector<TextEventListener*> InputSystem::m_textListener;
std::vector<MouseEventListener*> InputSystem::m_mouseListener;


void InputSystem::initialise(GLFWwindow *window)
{
	glfwSetKeyCallback(window, InputSystem::registerKeyCallback);
	
	glfwSetCharCallback(window, InputSystem::registerTextCallback);
	
	glfwSetCursorPosCallback(window, InputSystem::registerMouseMoveCallback);
	glfwSetCursorEnterCallback(window, InputSystem::registerMouseEnterCallback);
	glfwSetMouseButtonCallback(window, InputSystem::registerMouseButtonCallback);
	glfwSetScrollCallback(window, InputSystem::registerMouseScrollCallback);
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


