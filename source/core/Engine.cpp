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

Engine::Engine() : m_window()
{
	m_window.registerWindowCallback(this);
	registerSubSystem(&m_window);
}

void Engine::startGame(LaunchParameters& params)
{
	m_launchParams = params;//Store launch params before init so that subsystems can use them.

	init();

	//Main game loop
	while (m_window.isOpen())
	{
		std::unordered_map<SubSystemType, ISubSystem*>::iterator iter;
		for (iter = m_systemMap.begin(); iter != m_systemMap.end(); ++iter)
		{
			iter->second->update();
		}
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
	assert(iter == m_systemMap.end());
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

void Engine::onWindowEvent(const sf::Event& evt) {
	if (evt.type == sf::Event::Closed)
	{
		m_window.close();
	}
}

int ice::core::engineMain(Engine& engine, int argc, char *argv[])
{
	LaunchParameters params;
	params.argc = argc;
	params.argv = argv;

	engine.startGame(params);

	return 0;
}