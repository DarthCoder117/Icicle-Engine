#include "core/Engine.h"

#include <iostream>
#include <cassert>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <IcicleConfig.h>

using namespace ice;
using namespace core;
using namespace graphics;

using namespace std;

Engine::Engine()
{
	
}

void Engine::startGame()
{
	//m_graphics.render();

	while (m_window.run())
	{

	}

	//Shutdown all SubSystems
	std::unordered_map<SubSystemType, ISubSystem*>::iterator iter;
	for (iter = m_systemMap.begin(); iter != m_systemMap.end(); ++iter)
	{
		iter->second->shutdown();
	}
}

void Engine::registerSubSystem(ISubSystem* system)
{
	#ifdef ICE_DEBUG
	std::unordered_map<SubSystemType, ISubSystem*>::iterator iter = m_systemMap.find(system->getType());
	assert(iter != m_systemMap.end());
	#endif

	m_systemMap[system->getType()] = system;

	//Allow subsystem to initialize itself
	system->onInit(this);
}

ISubSystem* Engine::getSubSystem(SubSystemType type) 
{
	std::unordered_map<SubSystemType, ISubSystem*>::iterator iter = m_systemMap.find(type);
	if (iter != m_systemMap.end())
	{
		return iter->second;
	}

	return NULL;
}