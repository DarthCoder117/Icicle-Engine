#include "graphics/Graphics.h"
#include <IcicleConfig.h>

#include <GLFW/glfw3.h>
#ifdef ICE_WIN32
#include <Windows.h>
#endif
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
#define ICE_DEBUG

Graphics::Graphics(system::Window* window) : m_window(window)
{
	glfwGetWindowSize(window->getWindow(), &renderWidth, &renderHeight);
}

void Graphics::start()
{
	bgfx::glfwSetWindow(m_window->getWindow());

	bgfx::init();
	
	bgfx::reset(renderWidth, renderHeight, reset);

	#ifdef ICE_DEBUG
	// Enable debug text.
	bgfx::setDebug(debug);
	#endif
	
	// Set view 0 clear state.
	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0xFFFFFFFF, 1.0f, 0);
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

void Graphics::onWindowEvent(WindowEvent event) {
	if (event.type == WindowEventType::WINDOWSIZE) {
		renderWidth = event.data.size.width;
		renderHeight = event.data.size.height;
		
		#ifdef ICE_DEBUG
		std::cout << "Window resized to: " << renderWidth << ":" << renderHeight << std::endl;
		#endif
	}
}