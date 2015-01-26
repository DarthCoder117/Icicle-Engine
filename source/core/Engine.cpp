#include "core/Engine.h"

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

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
}

void Engine::registerSubSystem(ISubSystem* system)
{
	std::unordered_map<SubSystemType, ISubSystem*>::iterator iter = m_systemMap.find(system->getType());
	if (iter != m_systemMap.end())
	{
		return;
	}

	m_systemMap[system->getType()] = system;
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