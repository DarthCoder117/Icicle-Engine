#ifndef ENGINE_H
#define ENGINE_H
#include "core/Uncopyable.h"
#include <SFML/Window.hpp>
#include <vector>
#include <memory>

namespace ice
{
	namespace core
	{
		class WindowEventCallback
		{
		public:
		
			virtual ~WindowEventCallback(){}
			
			virtual void onWindowEvent(const sf::Event& evt){}
		};
	
		class Engine : public Uncopyable
		{
		public:
			
			Engine(sf::Window* window);
			
			void startGame();
			
			sf::Window* getWindow(){return m_window.get();}
			
		protected:
			
			std::unique_ptr<sf::Window> m_window;
			
			std::vector<WindowEventCallback*> m_windowCallbacks; 
		};
	}
}

#endif