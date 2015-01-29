#include "core/Engine.h"

#include <iostream>
#include <cassert>

#include <IcicleConfig.h>

using namespace ice;
using namespace core;
using namespace graphics;
using namespace system;

using namespace std;

Engine::Engine(const LaunchParameters& params)
	:m_launchParams(params),
	m_window(params),
	m_graphics(&m_window),
	m_fileSystem(params)
{
	registerSubSystem(&m_window);
	registerSubSystem(&m_graphics);
	//Gui must be registered after m_graphics
	registerSubSystem(&m_gui);
	registerSubSystem(&m_fileSystem);
}

void Engine::startGame()
{
	//Call start on all SubSystems
	for (auto iter : m_engineSystems)
	{
		iter->start();
	}

	//Main game loop
	while (!glfwWindowShouldClose(m_window.getWindow()))
	{
		for (auto iter : m_engineSystems)
		{
			iter->update();
		}
	}
	
	shutdown();
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

void Engine::onWindowEvent(WindowEvent event)
{	
}

void Engine::onKeyEvent(KeyEvent event)
{
	if (event.key == GLFW_KEY_ESCAPE && event.action == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(event.window, GL_TRUE);
	}
}

