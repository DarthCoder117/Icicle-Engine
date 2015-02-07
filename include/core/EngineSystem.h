#ifndef SUB_SYSTEM_H
#define SUB_SYSTEM_H

#include "core/Uncopyable.h"
#include "core/LaunchParameters.h"

namespace ice
{
	namespace core
	{
		class Engine;

		///@brief Interface for sub-systems within the engine.
		class IEngineSystem : public Uncopyable
		{
		public:

			IEngineSystem(){}
			virtual ~IEngineSystem(){}

			///@brief Called before the game starts after all SubSystems have been registered.
			virtual void start(){}
			
			///@brief Pre-update step called before update.
			///All system's pre-update steps are performed asynchronously, but all of them must finish before the update steps will start.
			virtual void preUpdate(){}

			///@brief Called to update the SubSystem.
			///All system's update steps are performed asynchronously.
			virtual void update(){}

			///@brief Post update step called after update.
			///All system's post-update steps are performed asynchronously, but after all the update steps have finished.
			virtual void postUpdate(){}
			
			///@brief Called for each SubSystem before the Engine is shutdown.
			virtual void shutdown(){}

			///@return The Engine instance that this SubSystem is attached to.
			Engine* getEngine(){ return m_engine; }

			void onRegistered(Engine* engine);

		protected:
			Engine* m_engine;
		};
	}
}

#endif