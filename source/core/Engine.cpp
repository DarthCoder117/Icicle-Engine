#include "core/Engine.h"

#include <iostream>
#include <cassert>

#include <IcicleConfig.h>

using namespace ice;
using namespace core;
using namespace graphics;
using namespace system;

using namespace std;

Engine::Engine(system::Window& window, graphics::Graphics& graphics)
	:m_window(window),
	m_graphics(graphics),
	m_fileSystem(),
	m_threadPool(6)
{
	internalInit();
}

void Engine::internalInit()
{
	m_window.registerWindowEventListener(this);

	m_graphics.init(this);
	m_entityMgr.init(this);
}

void Engine::startGame()
{
	while (run())
	{
		update();
		render();
	}
}

bool Engine::run()
{
	return m_window.run();
}

void Engine::update()
{
	//Start game logic update.
	for (auto iter : m_updateListeners)
	{
		iter->update();
	}

	//Create resources in main thread if needed
	m_resourceMgr.onPostLoad();

	//Wait for game logic to finish updating.
	for (auto iter : m_updateListeners)
	{
		iter->finalize();
	}
}

void Engine::render()
{
	//Render frame
	m_graphics.render();
}

void Engine::registerUpdateListener(UpdateEventListener* listener)
{
	m_updateListeners.push_back(listener);
}

void Engine::onWindowEvent(const system::WindowEvent& evt)
{
	if (evt.type == WindowEvent::CLOSED)
	{
		evt.window->close();
	}
}

void Engine::onKeyEvent(KeyEvent event)
{
	if (event.key == GLFW_KEY_ESCAPE && event.action == GLFW_PRESS) 
	{
		m_window.close();
	}
}

