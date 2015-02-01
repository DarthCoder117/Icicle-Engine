#ifndef GLOBAL_SYSTEM_H
#define GLOBAL_SYSTEM_H
#include "core/EngineSystem.h"
#include <cassert>

namespace ice
{
	namespace core
	{
		///@brief A global system can be accessed by the instance() method, similarly to a singleton.
		///Unlike a singleton however, GlobalSystem must be created manually before it can be used.
		///Manual creation fixes the problem that singletons have with multiple threads trying to access them.
		template <typename T>
		class GlobalSystem : public IEngineSystem
		{
		public:

			GlobalSystem()
			{
				if (!m_inst)
				{
					T::m_inst = (T*)this;
				}
				else
				{
					assert(0 && "Cannot initialize the same GlobalSystem more than once.");
				}
			}

			static T* instance()
			{
				static T* inst = 
				return m_inst;
			}
		};
	}
}

#endif