#ifndef ENGINE_H
#define ENGINE_H
#include <IcicleCommon.h>
#include "core/Uncopyable.h"
#include "core/EngineSystem.h"
#include "graphics/Graphics.h"
#include "system/Window.h"
#include "system/FileSystem.h"
#include "system/InputSystem.h"
#include "core/ResourceManager.h"
#include "system/ThreadPool.h"
#include "system/TaskGroup.h"
#include <gui/Gui.h>

namespace ice
{
	namespace core
	{
		///@brief Basic game logic update.
		///This is called synchronously from within the simulation thread immediately after the finalization step.
		class UpdateEventListener
		{
		public:

			virtual void update(){}
		};

		///@brief The Engine manages the game loop and SubSystems and serves as the base class for Icicle Engine applications.
		class Engine : public Uncopyable, public system::WindowEventListener, public system::KeyEventListener
		{
		public:

			Engine(const LaunchParameters& params, system::Window& window);

			///@brief Registers a SubSystem with the Engine.
			///Any registered SubSystem can be accessed by type later using getSubSystem().
			///The caller is responsible for managing the SubSystem's memory.
			void registerSubSystem(IEngineSystem* system);

			///@brief Initializes all registered subsystems. This must be called before startGame().
			void init();

			///@brief Updates the engine's game world simulation.
			void update();

			///@brief Render the last simulated frame.
			void render();

			///@brief Cleans up all registered systems after the game is finished.
			void shutdown();

			///@brief Starts a game loop with the engine.
			///If using a manually created window, then use update() and render() from within your own window loop.
			void startGame();

			///@return The parameters used when the engine starts up.
			LaunchParameters& getLaunchParameters(){ return m_launchParams; }

			system::Window& getWindow(){ return m_window; }

			graphics::Graphics& getGraphics() { return m_graphics; }

			system::FileSystem& getFileSystem(){ return m_fileSystem; }

			system::ThreadPool& getThreadPool(){ return m_threadPool; }

		private:

			bool m_quit;

			virtual void onWindowEvent(const system::WindowEvent& evt);
			virtual void onKeyEvent(system::KeyEvent event);
			
			LaunchParameters m_launchParams;

			system::Window& m_window;

			graphics::Graphics m_graphics;

			void updateTask();
			ThreadEvent m_updateFinished;
			
			system::FileSystem m_fileSystem;
			core::ResourceManager m_resourceMgr;
			
			Vector<IEngineSystem*> m_engineSystems;
			system::ThreadPool m_threadPool;
			TaskGroup m_simulationGroup;

			Vector<UpdateEventListener*> m_updateListeners;
		};
	}
}

#endif