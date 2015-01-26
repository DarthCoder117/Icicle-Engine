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
		struct LaunchParameters
		{
			int argc;
			char** argv;
		};

		///@brief The Engine manages the game loop and SubSystems and serves as the base class for Icicle Engine applications.
		class Engine : public Uncopyable, public system::WindowEventCallback
		{
		public:
			
			Engine();

			///@brief Called before the game loop to allow registering custom modules.
			virtual void init() = 0;

			///@brief Registers a SubSystem with the Engine.
			///Any registered SubSystem can be accessed by type later using getSubSystem().
			void registerSubSystem(ISubSystem* system);

			///@return A pointer to the SubSystem of the specified type, or NULL if the SubSystem was never registered.
			ISubSystem* getSubSystem(SubSystemType type);
			template <typename T>
			T* getSubSystem(){ return (T*)getSubSystem(T::getClassType()); }

			///@brief Starts the game loop and initializes all registered sub-systems.
			void startGame(LaunchParameters& params);

			///@return The parameters used when the engine starts up.
			const LaunchParameters& getLaunchParameters(){ return m_launchParams; }

			system::Window& getWindow(){ return m_window; }

		protected:

			virtual void onWindowEvent(const sf::Event& evt);
			
		protected:

			LaunchParameters m_launchParams;
			system::Window m_window;
			std::unordered_map<SubSystemType, ISubSystem*> m_systemMap;
		};

		extern int engineMain(Engine& engine, int argc, char *argv[]);

		#define START_ENGINE(EngineClass) int main(int argc, char *argv[])\
		{\
			EngineClass engine;\
			return engineMain(engine, argc, argv);\
		}
	}
}

#endif