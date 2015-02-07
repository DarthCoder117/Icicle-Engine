#include "core/Engine.h"

#include <iostream>
#include <cassert>

#include <IcicleConfig.h>

using namespace ice;
using namespace core;
using namespace graphics;
using namespace system;

using namespace std;

Engine::Engine(const LaunchParameters& params, system::Window& window)
	:m_launchParams(params),
	m_window(window),
	m_graphics(&m_window),
	m_fileSystem(params),
	m_threadPool(6),
	m_quit(false)
{
	registerSubSystem(&m_window);
	m_window.registerWindowEventListener(this);

	registerSubSystem(&m_graphics);
	//Gui must be registered after m_graphics
	#ifndef ICE_WINDOWS//Temporarily disabled on windows so other things can be tested before I build the CEGUI binaries...
	registerSubSystem(&m_gui);
	#endif
	registerSubSystem(&m_fileSystem);
}

void Engine::startGame()
{
	//Call start on all SubSystems
	for (auto iter : m_engineSystems)
	{
		iter->start();
	}

	m_updateFinished.set();

	//Run game loop
	while (!m_quit)
	{
		//Update the window
		m_quit = !m_window.run();

		//Start next game logic update after last one finishes
		m_updateFinished.wait();
		m_updateFinished.unset();
		m_threadPool.run(std::bind(&Engine::update, this));

		//Create resources in main thread 
		m_resourceMgr.onPostLoad();

		//Render last simulated frame
		render();
	}
	
	shutdown();
}

void Engine::update()
{	
	for (auto iter : m_updateListeners)
	{
		iter->update();
	}

	//Notify threads that update is finished
	m_updateFinished.set();
}

void Engine::render()
{
	//Begin rendering
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

