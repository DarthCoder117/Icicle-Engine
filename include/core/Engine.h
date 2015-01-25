#ifndef ENGINE_H
#define ENGINE_H
#include "core/Uncopyable.h"
#include "core/SubSystem.h"
#include "graphics/Graphics.h"
#include <SFML/Window.hpp>
#include <vector>

namespace ice
{
	namespace core
	{
		class Engine : public Uncopyable
		{
		public:
		
			Engine();
			
			void startGame();

			SubSystem* getSubSystem(SubSystemType type);
		private:
			graphics::Graphics m_graphics;
		};
	}
}

#endif