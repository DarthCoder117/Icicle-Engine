#include "gui/Gui.h"

#include "core/Debug.h"

#include "GLFW/glfw3.h"

using namespace ice;
using namespace core;
using namespace gui;
using namespace CEGUI;

Gui::Gui() : m_lastMousePos(Vec2(0.0f,0.0f))
{
	m_clock.restart();
}

void Gui::start()
{
	Debug::info("Initilalising the Gui renderer");
	
	#ifdef ICE_LINUX
	m_renderer = &OpenGL3Renderer::create();
	#elif ICE_WINDOWS
	m_renderer = &DirectX9Renderer::create( myD3D9Device );
	#endif
	
	System::create(*m_renderer);
	
	m_context = &System::getSingleton().getDefaultGUIContext();
}

void Gui::update()
{
#ifdef ICE_LINUX
	// user function to draw 3D scene
	//draw3DScene();
	
	// draw GUI (should not be between glBegin/glEnd pair)
	// make sure that before calling renderGUI, that any bound textures and shaders 
	// used to render the scene above are disabled using glBindTexture(0) and glUseProgram(0) respectively
	// also set glActiveTexture(GL_TEXTURE_0) 
	System::getSingleton().renderAllGUIContexts();
#elif ICE_WINDOWS
	// Start the scene
	myD3DDevice->BeginScene();
	
	// clear display
	myD3DDevice->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	
	// user function to draw 3D scene
	draw3DScene();
	
	// draw GUI
	System::getSingleton().renderGUI();
	
	// end the scene
	myD3DDevice->EndScene();
	
	// finally present the frame.
	myD3DDevice->Present(0, 0, 0, 0);
#endif
	m_context->injectTimePulse( m_clock.getElapsedTime().asSeconds() );
	m_clock.restart();
}


void Gui::onKeyEvent(system::KeyEvent event)
{
// 	if (event.action == GLFW_PRESS) {
// 		m_context->injectKeyDown(event.scancode);
// 	} else if (event.action == GLFW_RELEASE) {
// 		m_contexti.njectKeyUp(event.scancode);
// 	}
	
}

void Gui::onMouseEvent(system::MouseEvent event)
{
	if (event.type == system::MouseEventType::MOUSEPOSITION) {
		m_context->injectMousePosition(event.data.position.x, event.data.position.y);
		
		m_context->injectMouseMove(m_lastMousePos.x - event.data.position.x, m_lastMousePos.y - event.data.position.y);
		
		m_lastMousePos = Vec2(event.data.position.x, event.data.position.y);
	} else if (event.type == system::MouseEventType::BUTTON) {
		if (event.data.buttonState.action == GLFW_PRESS) {
			switch (event.data.buttonState.button) {
				case GLFW_MOUSE_BUTTON_RIGHT:
					m_context->injectMouseButtonDown(MouseButton::RightButton);
					break;
				case GLFW_MOUSE_BUTTON_LEFT:
					m_context->injectMouseButtonDown(MouseButton::LeftButton);
					break;
				case GLFW_MOUSE_BUTTON_MIDDLE:
					m_context->injectMouseButtonDown(MouseButton::MiddleButton);
					break;
			}
		} else if (event.data.buttonState.action == GLFW_RELEASE) {
			switch (event.data.buttonState.button) {
				case GLFW_MOUSE_BUTTON_RIGHT:
					m_context->injectMouseButtonUp(MouseButton::RightButton);
					break;
				case GLFW_MOUSE_BUTTON_LEFT:
					m_context->injectMouseButtonUp(MouseButton::LeftButton);
					break;
				case GLFW_MOUSE_BUTTON_MIDDLE:
					m_context->injectMouseButtonUp(MouseButton::MiddleButton);
					break;
			}
		}
	} else if (event.type == system::MouseEventType::ENTERED && event.data.entered == 0) {
		m_context->injectMouseLeaves();
	} else if (event.type == system::MouseEventType::SCROLL) {
		m_context->injectMouseWheelChange( event.data.scrollState.xoffset );
	}
}

void Gui::onTextEvent(system::TextEvent event)
{
	m_context->injectChar(event.codepoint);
}

void Gui::onWindowEvent(system::WindowEvent event)
{

}

void Gui::shutdown()
{
	
}
