#ifndef SUB_SYSTEM_H
#define SUB_SYSTEM_H
#include "core/Uncopyable.h"

namespace ice
{
	namespace core
	{
		typedef unsigned int SubSystemType;

		///@brief ISubSystem interface for engine sub-system modules.
		///Inherit from the templated SubSystem class instead of this interface to take advantage of automatic typeing.
		class ISubSystem : public Uncopyable
		{
		public:

			virtual SubSystemType getType() = 0;

		protected:

			static SubSystemType getNextType();
			static SubSystemType m_nextType;
		};

		///@brief Base SubSystem class for creating new sub-system types.
		///Usage: class MyNewSubSystem : public SubSystem<MyNewSubSystem>
		template <typename S>
		class SubSystem : public ISubSystem
		{
		public:

			static SubSystemType getClassType()
			{
				static SubSystemType type = ISubSystem::getNextType();
				return type;
			}

			SubSystemType getType()
			{
				return S::getClassType();
			}
		};
	}
}

#endif