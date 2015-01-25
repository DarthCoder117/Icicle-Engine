#ifndef SUB_SYSTEM_H
#define SUB_SYSTEM_H
#include "core/Uncopyable.h"

namespace ice
{
	namespace core
	{
		enum SubSystemType {
			GRAPHICS,
			WINDOW
		};

		class SubSystem
		{
		public:

			virtual SubSystemType getType() = 0;
		};
	}
}

#endif