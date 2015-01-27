#ifndef ENGINE_H
#define ENGINE_H
#include "core/Uncopyable.h"
#include "core/SubSystem.h"
#include "graphics/Graphics.h"
#include "system/Window.h"
#include "system/FileSystem.h"
#include "system/InputSystem.h"
#include <vector>
#include <memory>
#include <unordered_map>

namespace ice
{
	namespace core
	{
		///@brief The Engine manages the game loop and SubSystems and serves as the base class for Icicle Engine applications.
		class Engine : public Uncopyable, public system::WindowEventListener, public system::KeyEventListener
		{
		public:

			Engine(const LaunchParameters& params);
			
			///@brief Registers a SubSystem with the Engine.
			///Any registered SubSystem can be accessed by type later using getSubSystem().
			///The caller is responsible for managing the SubSystem's memory.
			void registerSubSystem(ISubSystem* system);

			///@return A pointer to the SubSystem of the specified type, or NULL if the SubSystem was never registered.
			ISubSystem* getSubSystem(SubSystemType type);
			template <typename T>
			T* getSubSystem(){ return (T*)getSubSystem( T::getClassType()); }

			///@brief Starts the game loop.
			void startGame();

			///@return The parameters used when the engine starts up.
			LaunchParameters& getLaunchParameters(){ return m_launchParams; }

			system::Window& getWindow(){ return m_window; }

			graphics::Graphics& getGraphics() { return m_graphics; }

			system::FileSystem& getFileSystem(){ return m_fileSystem; }
		private:
			virtual void onWindowEvent(system::WindowEvent event);
			virtual void onKeyEvent(system::KeyEvent event);
			
			LaunchParameters m_launchParams;

			system::Window m_window;

			graphics::Graphics m_graphics;

			system::FileSystem m_fileSystem;
			
			std::unordered_map<SubSystemType, ISubSystem*> m_systemMap;
		};
	}
}

#endif