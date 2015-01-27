#ifndef ENGINE_H
#define ENGINE_H
#include "core/Uncopyable.h"
#include "core/SubSystem.h"
#include "graphics/Graphics.h"
#include "system/Window.h"
#include <SFML/Window.hpp>
#include <vector>
#include <unordered_map>

namespace ice
{
	namespace core
	{
		///@brief The Engine manages the game loop and SubSystems.
		class Engine : public Uncopyable, public system::WindowEventCallback
		{
		public:
		
			Engine();

			///@brief Registers a SubSystem with the Engine.
			///Any registered SubSystem can be accessed by type later using getSubSystem().
			void registerSubSystem(ISubSystem* system);

			///@return A pointer to the SubSystem of the specified type, or NULL if the SubSystem was never registered.
			ISubSystem* getSubSystem(SubSystemType type);
			template <typename T>
			T* getSubSystem(){ return (T*)getSubSystem(T::getClassType()); }

			///@brief Starts the game loop and initializes all registered sub-systems.
			void startGame();

			system::Window& getWindow(){ return m_window; }
			graphics::Graphics& getGraphics() { return m_graphics; }

		private:
			virtual void onWindowEvent(const sf::Event& evt);
			
		private:
			system::Window m_window;
			graphics::Graphics m_graphics;
			std::unordered_map<SubSystemType, ISubSystem*> m_systemMap;
		};
	}
}

#endif