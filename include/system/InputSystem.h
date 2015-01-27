#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <vector>
#include <GLFW/glfw3.h>
#include "core/SubSystem.h"

namespace ice
{
	namespace system
	{
		enum WindowEventType {
			FOCUS, REFRESH, ICONIFIED, WINDOWPOSITION, FRAMBUFFERSIZE, WINDOWSIZE, CLOSE
		};
		
		struct WindowEvent {
			GLFWwindow* window;
			WindowEventType type;
			union {
				struct{
					int width, height;
				} size;
				struct{
					int x, y;
				} position;
				bool iconified;
				bool focused;
			} data;
		};
		
		struct KeyEvent {
			GLFWwindow* window;
			int key;
			int scancode;
			int action;
			int mods;
		};
		
		struct TextEvent {
			GLFWwindow* window;
			unsigned int codepoint;
		};
		
		enum MouseEventType {
			MOUSEPOSITION, BUTTON, SCROLL, ENTERED
		};
		
		struct MouseEvent {
			GLFWwindow* window;
			MouseEventType type;
			
			union {
				struct {
					double x;
					double y;
				} position;
				bool entered;
				
				struct {
					int button;
					int action;
					int mods;	
				} buttonState;
				
				struct {
					double xoffset, yoffset;
				} scrollState;
			} data;
		};
		
		class WindowEventListener;
		class KeyEventListener;
		class TextEventListener;
		class MouseEventListener;
		
		class InputSystem
		{
		public:
			static void initialise(GLFWwindow* window);
			
			static void registerWindowListener(WindowEventListener* listener);
			static void registerWindowFocusCallback(GLFWwindow* window, int focused);
			static void registerWindowIconifiedCallback(GLFWwindow* window, int iconified);
			static void registerWindowPositionCallback(GLFWwindow* window, int xpos, int ypos);
			static void registerWindowFrameBufferSizeCallback(GLFWwindow* window, int width, int height);
			static void registerWindowSizeCallback(GLFWwindow* window, int width, int height);
			static void registerWindowCloseCallback(GLFWwindow* window);
			static void registerWindowRefreshCallback(GLFWwindow* window);
			
			static void registerKeyListener(KeyEventListener* listener);
			static void registerKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
			
			static void registerTextListener(TextEventListener* listener);
			static void registerTextCallback(GLFWwindow* window, unsigned int codepoint);
			
			static void registerMouseListener(MouseEventListener* listener);
			static void registerMouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
			static void registerMouseEnterCallback(GLFWwindow* window, int entered);
			static void registerMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
			static void registerMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
			
		private:
			static void transmitWindowEvent(WindowEvent event);
			static void transmitKeyEvent(KeyEvent event);
			static void transmitTextEvent(TextEvent event);
			static void transmitMouseEvent(MouseEvent event);
		private:
			static std::vector<WindowEventListener*> m_windowListener;
			static std::vector<KeyEventListener*> m_keyListener;
			static std::vector<TextEventListener*> m_textListener;
			static std::vector<MouseEventListener*> m_mouseListener;
		};
		
		class WindowEventListener {
		public :
			WindowEventListener() { InputSystem::registerWindowListener(this); }
			virtual void onWindowEvent(WindowEvent event) = 0;
		};
		
		class KeyEventListener {
		public :
			KeyEventListener() { InputSystem::registerKeyListener(this); };
			virtual void onKeyEvent(KeyEvent event) = 0;
		};
		
		class TextEventListener {
		public :
			TextEventListener() { InputSystem::registerTextListener(this); };
			virtual void onTextEvent(TextEvent event) = 0;
		};
		
		class MouseEventListener {
		public :
			MouseEventListener() { InputSystem::registerMouseListener(this); };
			virtual void onMouseEvent(MouseEvent event) = 0;
		};
		
	}
}

#endif //INPUTSYSTEM_H