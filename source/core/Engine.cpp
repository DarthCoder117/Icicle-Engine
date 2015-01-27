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

Engine::Engine(const LaunchParameters& params)
	:m_launchParams(params),
	m_window(params),
	m_graphics(&m_window),
	m_fileSystem(params)
{
	m_window.registerWindowCallback(this);
	m_window.registerWindowCallback(&m_graphics);

	registerSubSystem(&m_window);
	registerSubSystem(&m_graphics);
	registerSubSystem(&m_fileSystem);

	
}

void Engine::startGame()
{
	//Call start on all SubSystems
	std::unordered_map<SubSystemType, ISubSystem*>::iterator iter;
	for (iter = m_systemMap.begin(); iter != m_systemMap.end(); ++iter)
	{
		iter->second->start();
	}

	//Main game loop
	while (m_window.isOpen())
	{
		std::unordered_map<SubSystemType, ISubSystem*>::iterator iter;
		for (iter = m_systemMap.begin(); iter != m_systemMap.end(); ++iter)
		{
			iter->second->update();
		}
	}
}

void Engine::registerSubSystem(ISubSystem* system)
{
	#ifdef ICE_DEBUG
	std::unordered_map<SubSystemType, ISubSystem*>::iterator iter = m_systemMap.find(system->getType());
	assert(iter == m_systemMap.end());
	#endif

	m_systemMap[system->getType()] = system;
	system->onRegistered(this);
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

void Engine::onWindowEvent(const sf::Event& evt) 
{
	if (evt.type == sf::Event::Closed)
	{
		m_window.close();
	}
}