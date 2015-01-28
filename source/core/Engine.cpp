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
	registerSubSystem(&m_fileSystem);
}

void Engine::startGame()
{
	//Call start on all SubSystems
	std::unordered_map<EngineSystemType, IEngineSystem*>::iterator iter;
	for (iter = m_systemMap.begin(); iter != m_systemMap.end(); ++iter)
	{
		iter->second->start();
	}

	//Main game loop
	while (!glfwWindowShouldClose(m_window.getWindow()))
	{
		std::unordered_map<EngineSystemType, IEngineSystem*>::iterator iter;
		for (iter = m_systemMap.begin(); iter != m_systemMap.end(); ++iter)
		{
			iter->second->update();
		}
	}
	
	shutdown();
}

void Engine::registerSubSystem(IEngineSystem* system)
{
	#ifdef ICE_DEBUG
	std::unordered_map<EngineSystemType, IEngineSystem*>::iterator iter = m_systemMap.find(system->getType());
	assert(iter == m_systemMap.end());
	#endif

	m_systemMap[system->getType()] = system;
	system->onRegistered(this);
}

void Engine::shutdown()
{
	std::unordered_map<EngineSystemType, IEngineSystem*>::iterator iter;
	for (iter = m_systemMap.begin(); iter != m_systemMap.end(); ++iter)
	{
		iter->second->shutdown();
	}
}

IEngineSystem* Engine::getEngineSystem(EngineSystemType type)
{
	std::unordered_map<EngineSystemType, IEngineSystem*>::iterator iter = m_systemMap.find(type);
	if (iter != m_systemMap.end())
	{
		return iter->second;
	}

	return NULL;
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

