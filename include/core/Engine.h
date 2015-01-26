#ifndef ENGINE_H
#define ENGINE_H
#include "core/Uncopyable.h"
#include "core/SubSystem.h"
#include "graphics/Graphics.h"
#include "core/Window.h"
#include <SFML/Window.hpp>
#include <vector>
#include <unordered_map>

namespace ice
{
	namespace core
	{
		class Engine : public Uncopyable
		{
		public:
		
			Engine();

			void registerSubSystem(ISubSystem* system);
			ISubSystem* getSubSystem(SubSystemType type);
			template <typename T>
			T* getSubSystem(){ return (T*)getSubSystem(T::getClassType()); }
		
			graphics::Graphics* getGraphics(){ return &m_graphics; }
			Window* getWindow(){ return &m_window; }

			void startGame();

		private:
			
			graphics::Graphics m_graphics;
			Window m_window;

			std::unordered_map<SubSystemType, ISubSystem*> m_systemMap;
		};
	}
}

#endif