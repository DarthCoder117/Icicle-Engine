#ifndef SUB_SYSTEM_H
#define SUB_SYSTEM_H
#include "core/Uncopyable.h"
#include "core/LaunchParameters.h"
#include "core/ThreadEvent.h"

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