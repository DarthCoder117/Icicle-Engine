#ifndef SUB_SYSTEM_H
#define SUB_SYSTEM_H

#include "core/Uncopyable.h"
#include "core/LaunchParameters.h"
#include <typeinfo>

#ifdef __linux
#include <stdlib.h>
#endif

namespace ice
{
	namespace core
	{
		class Engine;

		typedef size_t EngineSystemType;

		///@brief Interface for sub-systems within the engine.
		///It is recommended to inherit from SubSystem<T> instead of this interface.
		class IEngineSystem
		{
		public:

			IEngineSystem(){}
			virtual ~IEngineSystem(){}

			///@brief Called before the game starts after all SubSystems have been registered.
			virtual void start(){}
			
			///@brief Called to update the SubSystem
			virtual void update(){}
			
			///@brief Called for each SubSystem before the Engine is shutdown.
			virtual void shutdown(){}

			///@return The Engine instance that this SubSystem is attached to.
			Engine* getEngine(){ return m_engine; }

			virtual EngineSystemType getType() = 0;

			void onRegistered(Engine* engine);

		protected:

			Engine* m_engine;
		};

		///@brief Base class for engine sub-systems. Provides automatic typing support.
		///Usage: class MySubSystem : public SubSystem<MySubSystem>
		template <typename T>
		class EngineSystem : public IEngineSystem
		{
		public:
			static EngineSystemType getClassType(){ return typeid(T).hash_code(); }

			EngineSystemType getType(){ return T::getClassType(); }
		};
	}
}

#endif