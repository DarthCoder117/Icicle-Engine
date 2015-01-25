#include "core/Engine.h"

#include <iostream>

#include <SFML/Graphics.hpp>

using namespace ice;
using namespace core;

using namespace std;

Engine::Engine(sf::Window* window)
	:m_window(window)
{
	
}

void Engine::startGame()
{
	while (m_window->isOpen())
	{
		//Handle window events
		sf::Event evt;
		while (m_window->pollEvent(evt))
		{
			//Send window event to all callbacks
			for (unsigned int i = 0; i < m_windowCallbacks.size(); ++i)
			{
				m_windowCallbacks[i]->onWindowEvent(evt);
			}

			if (evt.type == sf::Event::Closed)
			{
				m_window->close();
			}
		}

	}
