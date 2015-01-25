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

SubSystem* Engine::getSubSystem(SubSystemType type) {
	switch (type) {
		case SubSystemType::GRAPHICS:
			return &m_graphics;
		case SubSystemType::WINDOW:
			return &m_window;
		default:
			return NULL;
	}
}