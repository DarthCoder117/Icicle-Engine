#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "core/SubSystem.h"

namespace ice
{
	namespace graphics
	{
		class WindowEventCallback
		{
		public:
			
			virtual ~WindowEventCallback(){}
			
			virtual void onWindowEvent(const sf::Event& evt) = 0;
		};

		class Graphics : public core::SubSystem {
		public:
			Graphics();
			
			void render();
			
			sf::Window& getWindow(){return m_window;}
			
			virtual ice::core::SubSystemType getType();
		private:
			std::vector<WindowEventCallback*> m_windowCallbacks;
			sf::Window m_window;
		};
	}
}

#endif //GRAPHICS_H