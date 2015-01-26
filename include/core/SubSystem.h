#ifndef SUB_SYSTEM_H
#define SUB_SYSTEM_H
#include "core/Uncopyable.h"
#include <typeinfo>

namespace ice
{
	namespace core
	{
		class Engine;

		typedef size_t SubSystemType;

		///@brief Interface for sub-systems within the engine.
		///It is recommended to inherit from SubSystem<T> instead of this interface.
		class ISubSystem
		{
		public:

			///@brief Called when the SubSystem is registered with the Engine.
			virtual void init(){}
			///@brief Called for each SubSystem before the Engine is shutdown.
			virtual void shutdown(){}

			Engine* getEngine(){ return m_engine; }

			virtual SubSystemType getType() = 0;

			void onInit(Engine* engine);

		protected:

			Engine* m_engine;
		};

		///@brief Base class for engine sub-systems. Provides automatic typing support.
		///Usage: class MySubSystem : public SubSystem<MySubSystem>
		template <typename T>
		class SubSystem : public ISubSystem
		{
		public:

			static SubSystemType getClassType(){ return typeid(T).hash_code(); }

			SubSystemType getType(){ return T::getClassType(); }
		};
	}
}

#endif