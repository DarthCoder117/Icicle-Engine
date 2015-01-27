#include "graphics/Graphics.h"

#include <bgfx.h>
#include <bgfxplatform.h>
#include <bgfxdefines.h>

#include <iostream>
using namespace ice;
using namespace graphics;
using namespace core;
using namespace system;

using namespace bgfx;

using namespace std;

#include <GL/gl.h>
#define ICE_DEBUG

Graphics::Graphics(system::Window* window) : m_window(window)
{
	renderWidth = m_window->getSize().x;
	renderHeight = m_window->getSize().y;
}

void Graphics::start()
{
	#ifdef __linux
		bgfx::x11SetDisplayWindow(XOpenDisplay(0), m_window->getSystemHandle());
	#else
		bgfx::winSetHwnd(m_window->getSystemHandle());
	#endif
		
	bgfx::init();
// 	bgfx::reset(renderWidth, renderHeight, reset);
	bgfx::reset(800,480,BGFX_RESET_VSYNC);
	
	#ifdef ICE_DEBUG
	// Enable debug text.
	bgfx::setDebug(debug);
	#endif
	
	// Set view 0 clear state.
	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,0x303030FF,1.0f,0);
}

void Graphics::update()
{
	// Set view 0 default viewport.
	bgfx::setViewRect(0, 0, 0, renderWidth, renderHeight);
	// This dummy draw call is here to make sure that view 0 is cleared
	// if no other draw calls are submitted to view 0.
	bgfx::submit(0);
	render();
}

void Graphics::shutdown()
{
	// Shutdown bgfx.
	bgfx::shutdown();
}


void Graphics::render() {
	// Use debug font to print information about this example.
	
	bgfx::dbgTextClear();
	
	bgfx::dbgTextPrintf(0, 1, 0x4f, "Icicle Example");
	bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Initialization and debug text.");
	//bgfx::submit(0);
	
	// Advance to next frame. Rendering thread will be kicked to
	// process submitted rendering primitives.
		
	bgfx::frame();
}

void Graphics::onWindowEvent(const sf::Event& evt) {
	if (evt.type == sf::Event::Resized)
	{
		renderWidth = evt.size.width;
		renderHeight = evt.size.height;
		
		#ifdef ICE_DEBUG
			std::cout << "Window resized to: " << evt.size.width << ":" << evt.size.height << std::endl;
		#endif
			
		shutdown();
		init();
	}
}
