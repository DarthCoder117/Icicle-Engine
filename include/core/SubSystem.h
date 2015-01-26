#ifndef SUB_SYSTEM_H
#define SUB_SYSTEM_H
#include "core/Uncopyable.h"
#include <typeinfo>

namespace ice
{
	namespace core
	{
		typedef size_t SubSystemType;

		class ISubSystem
		{
		public:

			virtual SubSystemType getType() = 0;
		};

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