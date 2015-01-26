#include "graphics/Graphics.h"

using namespace ice;
using namespace graphics;
using namespace core;

using namespace std;


Graphics::Graphics() {
	m_window.create(sf::VideoMode(800, 600), "Icicle test Window");
}

void Graphics::render() {
	while (m_window.isOpen())
	{
		//Handle window events
		sf::Event evt;
		while (m_window.pollEvent(evt))
		{
			//Send window event to all callbacks
			for (unsigned int i = 0; i < m_windowCallbacks.size(); ++i)
			{
				m_windowCallbacks[i]->onWindowEvent(evt);
			}
			
			if (evt.type == sf::Event::Closed)
			{
				m_window.close();
			}
		}
			
		m_window.display();
	}
	
}