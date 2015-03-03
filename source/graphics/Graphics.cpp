#include "graphics/Graphics.h"
#include <IcicleConfig.h>
#include <core/ResourceManager.h>
#include <core/Engine.h>
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

Graphics::Graphics(system::Window& window, GRAPHICS_DRIVER_TYPE driverType)
	:m_window(window)
{
	m_window.registerWindowEventListener(this);
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

void Graphics::init(core::Engine* engine)
{
	core::ResourceManager::instance()->registerFactory(new GraphicsResourceFactory(this));

	#if defined(ICE_WINDOWS)
	m_driver.reset(new DX11GraphicsDriver(&m_window));
	#elif defined(ICE_LINUX)

	#endif

	m_renderSystem2D.init(m_driver.get(), &engine->entities());
	registerRenderEventListener(&m_renderSystem2D);
}

void Graphics::registerRenderEventListener(RenderEventListener* listener)
{
	m_renderListeners.push_back(listener);
}

void Graphics::render() 
{
	glm::vec3 clearColor(0.6f, 0.6f, 0.6f);
	m_driver->clear(clearColor);

	//Iterate over all rendering listeners
	for (auto iter : m_renderListeners)
	{
		iter->render(RS_SHADOW_PASS);
	}

	for (auto iter : m_renderListeners)
	{
		iter->render(RS_OBJECT_RENDER);
	}

	for (auto iter : m_renderListeners)
	{
		iter->render(RS_POST_PROCESS);
	}

	for (auto iter : m_renderListeners)
	{
		iter->render(RS_OVERLAY);
	}

	m_driver->present();
}

void Graphics::onWindowEvent(const system::WindowEvent& evt)
{
	if (evt.type == system::WindowEvent::RESIZED) 
	{
		glm::uvec2 windowSz = evt.size;

		if (m_driver)
		{
			m_driver->reset(windowSz);
			m_driver->setViewport(windowSz);
		}
	}
}