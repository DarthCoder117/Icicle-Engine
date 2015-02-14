#include "graphics/Graphics.h"
#include <IcicleConfig.h>
#include <core/ResourceManager.h>
#include "graphics/Texture.h"

#ifdef ICE_WIN32
#include <Windows.h>
#else
#include <GLFW/glfw3.h>
#endif

#include <bgfx.h>
#include <bgfxplatform.h>
#include <bgfxdefines.h>

#include "core/Debug.h"

using namespace ice;
using namespace graphics;
using namespace core;
using namespace system;

using namespace bgfx;

using namespace std;

Graphics::Graphics(system::Window* window) 
	:m_window(window)
{
	m_windowSize = m_window->getWindowSize();
	m_window->registerWindowEventListener(this);
}

void Graphics::start()
{
	core::ResourceManager::instance()->registerFactory(new core::ResourceFactory<Texture>());

	#if defined(ICE_WINDOWS)
	bgfx::winSetHwnd(m_window->getSystemHandle());
	#elif defined(ICE_LINUX)
	bgfx::glfwSetWindow(m_window->getSystemHandle());
	#endif

	bgfx::init();
	
	Debug::info("Initilised bgfx");
	
	bgfx::reset(m_windowSize.x, m_windowSize.y, reset);
	Debug::info("Setting bgfx rendersize to ", m_windowSize.x, ":", m_windowSize.y);
	
	#ifdef ICE_DEBUG
	// Enable debug text.
	bgfx::setDebug(debug);
	#endif
	
	// Set view 0 clear state.
	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0xFFFFFFFF, 1.0f, 0);
}

void Graphics::shutdown()
{
	// Shutdown bgfx.
	bgfx::shutdown();
}


void Graphics::render() 
{
	// Set view 0 default viewport.
	bgfx::setViewRect(0, 0, 0, m_windowSize.x, m_windowSize.y);
	// This dummy draw call is here to make sure that view 0 is cleared
	// if no other draw calls are submitted to view 0.
	bgfx::submit(0);
	
	// Use debug font to print information about this example.
	
	bgfx::dbgTextClear();
	
	bgfx::dbgTextPrintf(0, 1, 0x4f, "Icicle Example");
	bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Initialization and debug text.");
	//bgfx::submit(0);
	
	// Advance to next frame. Rendering thread will be kicked to
	// process submitted rendering primitives.
		
	bgfx::frame();
}

void Graphics::onWindowEvent(const system::WindowEvent& evt)
{
	if (evt.type == WindowEvent::RESIZED) 
	{
		m_windowSize = evt.size;
		bgfx::reset(m_windowSize.x, m_windowSize.y, reset);
		
		Debug::info("Setting bgfx rendersize to ", m_windowSize.x, ":", m_windowSize.y);
	}
}