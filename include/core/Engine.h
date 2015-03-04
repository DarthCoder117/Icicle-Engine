#ifndef ENGINE_H
#define ENGINE_H
#include <IcicleCommon.h>
#include "core/Uncopyable.h"
#include "core/World.h"
#include "graphics/Graphics.h"
#include "system/Window.h"
#include "system/FileSystem.h"
#include "system/InputSystem.h"
#include "core/ResourceManager.h"
#include "system/ThreadPool.h"
#include "system/TaskGroup.h"
#include "core/UpdateEventListener.h"
#include <gui/Gui.h>

namespace ice
{
	namespace core
	{
		///@brief The Engine manages the game loop and SubSystems and serves as the base class for Icicle Engine applications.
		class Engine : public Uncopyable, public system::WindowEventListener, public system::KeyEventListener
		{
		public:

			///@param window The render window. Cannot be NULL.
			///@param graphics The graphics module to use for rendering. Cannot be NULL.
			Engine(system::Window& window, graphics::Graphics& graphics);

			///@brief Registers an update event listener with the engine.
			void registerUpdateListener(UpdateEventListener* listener);

			///@brief Updates the window and returns whether or not the game should continue running.
			bool run();
			///@brief Updates the engine's game world simulation.
			void update();
			///@brief Render the last simulated frame.
			void render();

			///@brief Starts a game loop with the engine.
			///If using a manually created window, then use update() and render() from within your own window loop.
			void startGame();

			system::Window& window(){ return m_window; }
			graphics::Graphics& graphics() { return m_graphics; }

			World& world(){ return m_world; }

			system::FileSystem& getFileSystem(){ return m_fileSystem; }
			system::ThreadPool& getThreadPool(){ return m_threadPool; }
			core::ResourceManager& resourceManager(){ return m_resourceMgr; }

		private:

			void internalInit();

			virtual void onWindowEvent(const system::WindowEvent& evt);
			virtual void onKeyEvent(system::KeyEvent event);
			
			system::Window& m_window;
			graphics::Graphics& m_graphics;

			World m_world;
			
			core::ResourceManager m_resourceMgr;
			system::ThreadPool m_threadPool;
			system::FileSystem m_fileSystem;
			
			Vector<UpdateEventListener*> m_updateListeners;
		};
	}
}

#endif