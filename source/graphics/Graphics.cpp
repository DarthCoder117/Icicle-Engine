#include "graphics/Graphics.h"
#include <IcicleConfig.h>
#include <core/ResourceManager.h>
#include "graphics/Texture2D.h"

#ifdef ICE_WINDOWS
#include <Windows.h>
#include "graphics/DX11GraphicsDriver.h"
#else
#include <GLFW/glfw3.h>
#endif

#include "core/Debug.h"

using namespace ice;
using namespace graphics;

Graphics::Graphics(system::Window* window, GRAPHICS_DRIVER_TYPE driverType)
	:m_window(window)
{
	m_windowSize = m_window->getWindowSize();
	m_window->registerWindowEventListener(this);
}

class GraphicsResourceFactory : public core::IResourceFactory
{
public:

	GraphicsResourceFactory(Graphics* graphics)
		:m_graphics(graphics)
	{}

	core::IResource* create(ResourceType type)
	{
		if (type == Texture2D::getClassType())
		{
			return m_graphics->getDriver()->createTexture();
		}

		return NULL;
	}

private:

	Graphics* m_graphics;
};

void Graphics::start()
{
	core::ResourceManager::instance()->registerFactory(new GraphicsResourceFactory(this));

	#if defined(ICE_WINDOWS)
	m_driver.reset(new DX11GraphicsDriver(m_window));
	#elif defined(ICE_LINUX)

	#endif
}

void Graphics::shutdown()
{
	
}

void Graphics::render() 
{
	Color3f clearColor(0.6f, 0.6f, 0.6f);
	m_driver->clear(clearColor);

	//Draw stuff...

	m_driver->present();
}

void Graphics::onWindowEvent(const system::WindowEvent& evt)
{
	if (evt.type == system::WindowEvent::RESIZED) 
	{
		m_windowSize = evt.size;

		if (m_driver)
		{
			m_driver->reset(m_windowSize);
			m_driver->setViewport(m_windowSize);
		}
	}
}