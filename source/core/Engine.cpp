#include "core/Engine.h"

#include <iostream>
#include <cassert>

#include <IcicleConfig.h>

using namespace ice;
using namespace core;
using namespace graphics;
using namespace system;

using namespace std;

Engine::Engine(const LaunchParameters& params, system::Window& window) :
	m_quit(false),
	m_launchParams(params),
	m_window(window),
	m_graphics(&m_window),
	m_fileSystem(params),
	m_threadPool(6)
{
	registerSubSystem(&m_window);
	m_window.registerWindowEventListener(this);

	registerSubSystem(&m_graphics);

	
	registerSubSystem(&m_fileSystem);
}

void Engine::init()
{
	//Call start on all SubSystems
	for (auto iter : m_engineSystems)
	{
		iter->start();
	}

	//This must be set before the game loop can start
	m_updateFinished.set();
}

void Engine::startGame()
{
	while (!m_quit)
	{
		update();
		render();
	}
	
	shutdown();
}

void Engine::updateTask()
{	
	for (auto iter : m_updateListeners)
	{
		iter->update();
	}

	//Notify threads that update is finished
	m_updateFinished.set();
}

void Engine::update()
{
	//Update the window
	m_quit = !m_window.run();

	//Start next game logic update after last one finishes
	m_updateFinished.wait();
	m_updateFinished.unset();
	m_threadPool.run(std::bind(&Engine::updateTask, this));

	//Create resources in main thread 
	m_resourceMgr.onPostLoad();
}

void Engine::render()
{
	//Render last simulated frame
	m_graphics.render();
}

void Engine::registerSubSystem(IEngineSystem* system)
{
	m_engineSystems.push_back(system);
	system->onRegistered(this);
}

void Engine::shutdown()
{
	for (auto iter : m_engineSystems)
	{
		iter->shutdown();
	}
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

