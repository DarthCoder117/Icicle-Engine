#ifndef ENGINE_H
#define ENGINE_H
#include "core/Uncopyable.h"
#include <SFML/Window.hpp>
#include <vector>

namespace ice
{
	namespace core
	{
		class WindowEventCallback
		{
		public:
		
			virtual ~WindowEventCallback(){}
			
			virtual void onWindowEvent(const sf::Event& evt) = 0;
		};
	
		class Engine : public Uncopyable
		{
		public:
		
			Engine(sf::Window& window);
			
			void startGame();
			
			sf::Window& getWindow(){return m_window;}
		protected:
			
			sf::Window &m_window;
			
			std::vector<WindowEventCallback*> m_windowCallbacks; 
		};
	}
}

#endif